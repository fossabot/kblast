// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2000-2014 Matt Wells
// Copyright 2004-2013 Gigablast, Inc.
// Copyright 2013      Web Research Properties, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _MSG3A_H_
#define _MSG3A_H_

#include "Msg39.h"
#include "Stats.h"
//#include "Thesaurus.h"
#include "PostQueryRerank.h" // rscore_t
#include "Msg0.h"
#include "Msg1.h"

// 90MB for 32 nodes we got now with about 1.3B docs
#define DEFAULT_POSDB_READSIZE 90000000

void setTermFreqWeights ( collnum_t collnum, // char *coll,
			  class Query *q , 
			  long long *termFreqs, 
			  float *termFreqWeights ) ;

//#define MSG3A_TMP_BUFSIZE (MAX_RESULTS*18)

// ALWAYS get at least 20 docids so we can do better ranking
#define MIN_DOCS_TO_GET 20

#define RBUF_SIZE 2048

class Msg3a {
public:
	Msg3a();
	~Msg3a();
	void constructor();

	void reset ( );

	// . returns false if blocked, true otherwise
        // . sets errno on error
        // . "query/coll/docIds" should NOT be on the stack in case we block
	// . uses Query class to parse query
	// . uses Msg37 to retrieve term frequencies for each termId in query
	// . uses Indexdb class to intersect the lists to get results
	// . fills docIds buf with the resulting docIds
	// . sets *numDocIds to the # of resulting docIds
	// . if restrictindexdbForQuery is true we only read docIds from 
	//   indexdb root file
	// . this might ADJUST m_si->m_q.m_termFreqs[] to be more accurate
	// . NOTE: Msg39Request MUST NOT BE ON THE STACK! keep it persistent!
	bool getDocIds ( Msg39Request *r          ,
			 Query        *q          ,
			 void         *state      ,
			 void        (* callback) ( void *state ) ,
			 class Host *specialHost = NULL );


	bool gotTermFreqs();

	// Msg40 calls this to get Query m_q to pass to Summary class
	Query *getQuery ( ) { return m_q ; };

	// Msg40 calls these to get the data pointing into the reply
	long long *getDocIds        ( ) { return m_docIds;        };
	char      *getClusterLevels ( ) { return m_clusterLevels; };
	// we basically turn the scores we get from each msg39 split into
	// floats (rscore_t) and store them as floats so that PostQueryRerank
	// has an easier time
	double *getScores        ( ) { return m_scores;        };
	long   getNumDocIds     ( ) { return m_numDocIds; };

	long getSiteHash26 ( long i ) { 
		// if it was in the seoResults cache this will be non-NULL
		if ( m_siteHashes26 ) return m_siteHashes26[i];
		// otherwise, this is the standard method:
		return g_clusterdb.getSiteHash26((char *)&m_clusterRecs[i]); 
	};


	void printTerms ( ) ;

	// . estimates based on m_termFreqs, m_termSigns and m_numTerms
	// . received in reply
	long long  getNumTotalEstimatedHits ( ) { 
		return m_numTotalEstimatedHits; };

	// called when we got a reply of docIds
	bool gotAllShardReplies ( );

	bool gotCacheReply ( );

	bool mergeLists ( );

	bool gotReranked ( );

	bool gotClusterRecs ( bool calledFromMergeLists );

	bool gotClusterLevels ( );

	// . deserialize ourselves for the cache
	// . returns bytes written
	// . returns -1 and sets g_errno on error
	long getStoredSize ( );
	long serialize   ( char *buf , char *bufEnd );
	long deserialize ( char *buf , char *bufEnd );


	// incoming parameters passed to Msg39::getDocIds() function
	Query     *m_q;
	long       m_docsToGet;
	void      *m_state;
	void     (*m_callback ) ( void *state );

	// set by Msg3a initially
	//long       m_indexdbSplit;
	long m_numHosts;

	// used in XmlDoc.cpp for doing the seo keyword tool
	void      *m_hack;
	long       m_hackQNum;
	char      *m_hackQPtr;
	//void      *m_hackHost;
	//char       m_inUse;

	bool m_moreDocIdsAvail;
	long m_totalDocCount;

	// don't get more docIds than this from any one split
	long       m_maxDocIdsToCompute;
	// this is set if IndexTable::addLists() had an error
	long       m_errno;

	// this is now in here so Msg40 can send out one Msg3a per
	// collection if it wants to search an entire token
	Msg39Request m_rrr;

	// use msg37 to get TermFreqs
	//Msg37      m_msg37;
	long long  m_termFreqs      [MAX_QUERY_TERMS];
	float      m_termFreqWeights[MAX_QUERY_TERMS];

	// a multicast class to send the request, one for each split
	Multicast  m_mcast[MAX_SHARDS];

	// for timing how long things take
	long long  m_startTime;

	// this buffer should be big enough to hold all requests
	//char       m_request [MAX_MSG39_REQUEST_SIZE * MAX_SHARDS];
	long       m_numReplies;

	// . # estimated total hits
	long long  m_numTotalEstimatedHits;

	// we have one request that we send to each split
	class Msg39Request *m_r;
	char               *m_rbufPtr;
	long                m_rbufSize;
	char                m_rbuf [ RBUF_SIZE ];

	// now we send to the twin as well
	SafeBuf m_rbuf2;

	// each split gives us a reply
	class Msg39Reply   *m_reply       [MAX_SHARDS];
	long                m_replyMaxSize[MAX_SHARDS];

	char m_debug;

	// final merged lists go here
	long long      *m_docIds        ;
	double         *m_scores        ;
	class DocIdScore **m_scoreInfos ;
	//key_t          *m_recs          ; // clusterdb recs
	key_t          *m_clusterRecs   ;
	char           *m_clusterLevels ;
	// this is new
	collnum_t      *m_collnums;
	long            m_numDocIds     ;
	// the above ptrs point into this buffer
	char           *m_finalBuf;
	long            m_finalBufSize;

	// when merging this list of docids into a final list keep
	// track of the cursor into m_docIds[]
	long m_cursor;

	// what collection # are these docids from if m_collnums[] is NULL
	//collnum_t m_collnum;

	//
	// new things for seoresults cache
	//
	long           *m_siteHashes26;
	key_t           m_ckey; // cachedb key
	Msg0            m_msg0;
	Msg1            m_msg1;
	RdbList         m_seoCacheList;


	SectionStats    m_sectionStats;
};

#endif
