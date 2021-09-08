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

// . a network interface to Catdb.h
// . handles add/delete requests for catdb records
// . use the all powerful ../rdb/Msg1.h class to add lists or records to an rdb

#ifndef _MSG9B_H_
#define _MSG9B_H_

#include "Msg1.h"    // add an RdbList to an rdb
#include "RdbList.h"
#include "CatRec.h"
#include "Msg8b.h"

class Msg9b {

 public:
	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . "urls" is a NULL-terminated list of space-separated urls
	// . makes a siteRec for each url in "urls" and adds it to an RdbList
	// . then adds the records in the RdbList to their appropriate 
	//   host/tagdb using msg1
	bool addCatRecs  ( char *urls        ,
			   char *coll        , 
			   long  collLen     ,
			   long  filenum     ,
			   void *state       ,
			   void (*callback)(void *state) ,
			   unsigned char *numCatids ,
			   long *catids    ,
			   long niceness = MAX_NICENESS ,
			   bool deleteRecs = false );

	// use this to convey our data
	RdbList m_list;

	// used to add our assembled list
	Msg1 m_msg1;

	// used to keep track of calling class
	void *m_parent;

	//we use these to store the passed in values from update
	Url   m_url;
	char *m_coll;
	long  m_collLen;
	long  m_filenum;
	void *m_state;              
	void (*m_callback)(void *state);
	unsigned char *m_numCatids;
	long *m_catids;
	long m_niceness;
};


#endif
