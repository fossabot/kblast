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

// . get the number of records (termId/docId/score tuple) in an IndexList(s)
//   for a given termId(s)
// . if it's truncated then interpolate based on score
// . TODO: use g_conf.m_truncationLimit
// . used for query routing
// . used for query term weighting (IDF)
// . used to set m_termFreq for each termId in query in the Query class

#ifndef _MSG36_H_
#define _MSG36_H_

#include "UdpServer.h" // for sending/handling requests
#include "Multicast.h" // for sending requests
#include "Indexdb.h"
#include "Msg3.h"      // MAX_RDB_FILES definition
#include "RdbCache.h"

class Msg36 {

 public:

	// register our 0x36 handler function
	bool registerHandler ( );

	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . "termFreq" should NOT be on the stack in case we block
	// . sets *termFreq to UPPER BOUND on # of records with that "termId"
	bool getTermFreq ( collnum_t collnum,//char       *coll       ,
			   long        maxAge     ,
			   long long   termId     ,
			   void       *state      ,
			   void (* callback)(void *state ) ,
			   long        niceness = MAX_NICENESS ,
			   bool        exactCount  = false     ,
			   bool        incCount    = false     ,
			   bool        decCount    = false     ,
			   bool        isSplit     = true);

	long long getTermFreq () { return m_termFreq; };

	// public so C wrapper can call
	void gotReply ( ) ;

	// we store the recvd termFreq in what this points to
	long long  m_termFreq ;

	// info stored in us by Msg37.cpp
	void *m_this;
	long  m_i;
	long  m_j;

	// callback information
	void  *m_state  ;
	void (* m_callback)(void *state );

	// request buffer is just 8 bytes
	char m_request[1+8+MAX_COLL_LEN+1];

	// hold the reply now too
//#ifdef SPLIT_INDEXDB
//	char m_reply[8*INDEXDB_SPLIT];
//#else
//	char m_reply[8];
//#endif
	char m_reply[8*MAX_SHARDS];

	// for sending the request
//#ifdef SPLIT_INDEXDB
	//Multicast m_mcast[INDEXDB_SPLIT];
	Multicast m_mcast[1];//MAX_SHARDS];
	long      m_numRequests;
	long      m_numReplies;
	long      m_errno;
	bool      m_isSplit;
//#else
//	Multicast m_mcast;
//#endif

	long      m_niceness;
};

//extern class RdbCache g_qtable;

#endif
