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

// . get many RdbLists at once
// . used by ../indexdb/Msg39.cpp to get many IndexLists (RdbLists)

#ifndef _MSG2_H_
#define _MSG2_H_

#include "Query.h"  // MAX_QUERY_TERMS
#include "Msg0.h"

// define the max # of lists you can get as the max # of query terms for now
#define MAX_NUM_LISTS MAX_QUERY_TERMS

// launch up to 25 msg0 requests at a time
//#define MSG2_MAX_REQUESTS 25

// how many outstanding msg5 requests at one time?
#define MSG2_MAX_REQUESTS MAX_QUERY_TERMS

// support the &sites=xyz.com+abc.com+... to restrict search results to
// provided sites.
#define MAX_WHITELISTS 500

class Msg2 {

 public:

	Msg2();
	void reset();

	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . "termIds/termFreqs" should NOT be on the stack in case we block
	bool getLists ( long     rdbId       ,
			collnum_t collnum ,//char    *coll        ,
			long     maxAge      ,
			bool     addToCache  ,
			//key_t   *startKeys   ,
			//key_t   *endKeys     ,
			//char    *startKeys   ,
			//char    *endKeys     ,
			//class QueryTerm *qterms ,
			class Query *query ,
			// restrict search results to this list of sites,
			// i.e. "abc.com+xyz.com+..." (Custom Search)
			char *whiteList,
			// for intersecting ranges of docids separately
			// to prevent OOM errors
			long long docIdStart,
			long long docIdEnd,
			// isSplit[i] is true if list #i is split.
			// i.e. gbdom:xyz.com, etc.
			//char    *isSplit , 
			long    *minRecSizes ,
			//long     numLists    ,
			RdbList *lists       ,
			void    *state       ,
			void (* callback)(void *state )  ,
			class Msg39Request *request ,
			long     niceness = MAX_NICENESS ,
			bool     doMerge  = true         ,
			bool     isDebug  = false        ,
			long    *bestSenderHostIds = NULL    ,
			bool     restrictPosdb   = false   ,
			char     forceParitySplit     = -1   ,
			bool     checkCache           = false);
	bool getLists();

	long  m_i;

	// list of sites to restrict search results to. space separated
	char *m_whiteList;
	long long m_docIdStart;
	long long m_docIdEnd;
	char *m_p;
	long  m_w;
	RdbList m_whiteLists [ MAX_WHITELISTS ];

	// for posdbtable to get lists
	//long getNumListGroups ( ) { return m_query->m_numTerms; }

	// . get each list group
	// . lists are from oldest to newest
	//RdbList **getListGroup       ( long i ){return m_msg5[i].m_listPtrs;}
	//long   getNumListsInGroup ( long i ){return m_msg5[i].m_numListPtrs;}


	RdbList *getList ( long i ) { return &m_lists[i]; }
	long getNumLists ( ) { return m_query->m_numTerms; }

	// get how many bytes we read
	//long getTotalRead() { return m_totalRead; };

	class Msg5 *getAvailMsg5();
	void returnMsg5 ( class Msg5 *msg5 ) ;

	// leave public so C wrapper can call
	bool gotList ( RdbList *list );

	// we can get up to MAX_QUERY_TERMS term frequencies at the same time
	Msg5 m_msg5  [ MSG2_MAX_REQUESTS ];
	//Msg0 m_msg0  [ MSG2_MAX_REQUESTS ];
	bool m_avail [ MSG2_MAX_REQUESTS ]; // which msg0s are available?

	long m_errno;

	RdbList *m_lists;

	//char      m_inProgress [ MAX_NUM_LISTS ];
	//char      m_slotNum    [ MAX_NUM_LISTS ];

	// used for getting component lists if compound list is empty
	void     mergeLists_r       ( ) ;
	long    *m_componentCodes;
	char    *m_ignore;
	class Query *m_query;
	class QueryTerm *m_qterms;
	//char     m_cacheKeys[MAX_NUM_LISTS * MAX_KEY_BYTES];
	long    *m_minRecSizes;
	long     m_maxAge;
	long     m_numLists;
	bool     m_getComponents;
	char     m_rdbId;
	bool     m_addToCache;
	//char    *m_coll;
	collnum_t m_collnum;
	bool     m_restrictPosdb;
	long     m_compoundListMaxSize;
	char     m_forceParitySplit;
	bool     m_checkCache;
	long     m_k;
	long     m_n;
	//RdbList *m_listPtrs [ MAX_NUM_LISTS ];

	class Msg39Request *m_req;
	
	// true if its a compound list that needs to be inserted into the cache
	//char m_needsCaching [ MAX_NUM_LISTS ];

	long m_numReplies  ;
	long m_numRequests ;

	void *m_state ;
	void ( * m_callback ) ( void *state );
	long  m_niceness;

	// . should lists from cache, tree and disk files be merged into one?
	// . or appended out of order? 
	// . avoiding merge saves query engine valuable time
	bool m_doMerge;

	// if this is true we log more output
	bool m_isDebug;

	// keep a count of bytes read from all lists (local or remote)
	//long m_totalRead;

	// start time
	long long m_startTime;
};

#endif
