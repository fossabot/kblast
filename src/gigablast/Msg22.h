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

// . get a TitleRec from url/coll or docId

#ifndef _MSG22_H_
#define _MSG22_H_

#include "Url.h"
#include "Multicast.h"

// m_url[0]!=0 if this is a url-based request and NOT docid-based
class Msg22Request {
public:
	long long m_docId;
	long      m_niceness;
	long      m_maxCacheAge;
	collnum_t m_collnum;
	char      m_justCheckTfndb  :1;
	char      m_getAvailDocIdOnly:1;
	char      m_doLoadBalancing :1;
	char      m_addToCache      :1;
	char      m_inUse           :1;
	char      m_url[MAX_URL_LEN+1];

	long getSize () {
		return (m_url - (char *)&m_docId) + 1+gbstrlen(m_url); };
	long getMinSize() {
		return (m_url - (char *)&m_docId) + 1; };

	Msg22Request() { m_inUse = 0; }
};

class Msg22 {

 public:
	Msg22();
	~Msg22();

	static bool registerHandler ( ) ;

	bool getAvailDocIdOnly ( class Msg22Request  *r              ,
				 long long preferredDocId ,
				 char *coll ,
				 void *state ,
				 void (* callback)(void *state) ,
				 long niceness ) ;

	// . make sure you keep url/coll on your stack cuz we just point to it
	// . see the other getTitleRec() description below for more details
	// . use a maxCacheAge of 0 to avoid the cache
	bool getTitleRec ( class Msg22Request *r ,
			   char      *url     ,
			   long long  docId   ,
			   char      *coll    ,
			   char     **titleRecPtrPtr  ,
			   long      *titleRecSizePtr ,
			   bool       justCheckTfndb ,
			   bool       getAvailDocIdOnly  ,
			   void      *state          , 
			   void     (* callback) (void *state ),
			   long       niceness       ,
			   bool       addToCache     ,
			   long       maxCacheAge    ,
			   long       timeout        ,
			   bool       doLoadBalancing = false );

	long long getAvailDocId ( ) { return m_availDocId; };

	// public so C wrappers can call
	void gotReply ( ) ;

	// this is a hack so Msg38 can store his this ptr here
	//void *m_parent; // used by Msg38
	//long  m_slot;   // for resending on same Msg22 slot in array
	//void *m_dataPtr;// for holding recepient record ptr of TopNode ptr

	char **m_titleRecPtrPtr;
	long  *m_titleRecSizePtr;

	void    (* m_callback ) (void *state);
	void     *m_state       ;
	//void     *m_state2      ;
	//void     *m_state3      ;

	bool      m_found;
	long long m_availDocId;
	// the error getting the title rec is stored here
	long      m_errno;

	bool m_outstanding ;

	// for sending the Msg22
	Multicast m_mcast;

	class Msg22Request *m_r;
};

#endif
