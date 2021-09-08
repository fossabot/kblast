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

// . A stripped down version of Msg36 that works on LINKDB instead of INDEXDB
// . Does not have cache, does not do exact count and does not do increment or
//   decrement count. 

#ifndef _MSG42_H_
#define _MSG42_H_

#include "UdpServer.h" // for sending/handling requests
#include "Multicast.h" // for sending requests
#include "Linkdb.h"
#include "Msg3.h"      // MAX_RDB_FILES definition
#include "RdbCache.h"

class Msg42 {

 public:

	// register our 0x42 handler function
	bool registerHandler ( );

	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . "termFreq" should NOT be on the stack in case we block
	// . sets *termFreq to UPPER BOUND on # of records with that "termId"
	bool getTermFreq ( char       *coll       ,
			   long        maxAge     ,
			   long long   termId     ,
			   void       *state      ,
			   void (* callback)(void *state ) ,
			   long        niceness = MAX_NICENESS );

	long long getTermFreq () { return m_termFreq; };

	// public so C wrapper can call
	void gotReply ( ) ;

	// we store the recvd termFreq in what this points to
	long long  m_termFreq ;

	// callback information
	void  *m_state  ;
	void (* m_callback)(void *state );

	// request buffer is just 8 bytes
	char m_request[8+MAX_COLL_LEN+1];

	// hold the reply now too
	char m_reply[8];

	// for sending the request
	Multicast m_mcast;
	long      m_errno;
};

#endif
