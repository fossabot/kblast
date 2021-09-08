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

#ifndef _REQUESTTABLE_H_
#define _REQUESTTABLE_H_

#include "gb-include.h"
#include "HashTableT.h"

class RequestTable {
 public:

	RequestTable ( ) ;
	~RequestTable ( ) ;
	void reset ( ) ;

	// returns number of requests in the table with this hash
	long addRequest ( long long  requestHash , void *state2 );

	void gotReply   ( long long  requestHash ,
			  char      *reply       ,
			  long       replySize   ,
			  void      *state1      ,
			  void     (*callback)(char *reply     ,
					       long  replySize ,
					       void *state1    ,
					       void *state2    ) );

	void cancelRequest ( long long requestHash , void *state2 );
	// . key of each slot is "requestHash"
	// . value of each slot is "state2" from call to addRequest above
	HashTableT <long long,long> m_htable;
	
	// . hash table buffer
	char m_buf[HT_BUF_SIZE];
	long m_bufSize;

	// what hash are we processing
	long long m_processHash;
};

#endif
