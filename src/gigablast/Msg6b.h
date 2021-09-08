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

#ifndef _MSG6B_H_
#define _MSG6B_H_


#include "gb-include.h"
#include "Msg3a.h"
#include "Msg22.h"
#include "Query.h"

class Msg8a;
class Msg6b {
public:
	Msg6b();
	~Msg6b(); 
	void 	reset();


	bool getTitlerecSample(char* query,
			       char* coll,
			       long  collLen,
			       long  numSamples,
			       long  numToKeep,
			       void  *state,
			       bool  (*recordCallback) (void *state,
							TitleRec* tr,
							class TagRec *tagRec),
			       void  (*endCallback) (void *state),
			       bool  doSiteClustering,
			       bool  doIpClustering,
			       bool  getTagRecs,
			       long  niceness);
	bool gotDocIdList();
	bool callbackIfDone();
	bool getMsg22s(long sampleNum);
	bool gotMsg22s(long sampleNum);
	bool gotMsg8as(long sampleNum);



protected:
	Msg3a    m_msg3a;
	Msg22*   m_msg22s;
	Msg8a*    m_msg8as;
	//SiteRec* m_siteRecs;
	class TagRec   *m_tagRecs;

	long   m_numMsg22s;
	long   m_numGotten;
	long   m_numToGet;
	long   m_numToKeep;
	long   m_lastSlotUsed;

	long m_niceness;
	long m_numOutstanding;
	//bool m_getSiteRecs;
	bool m_getTagRecs;
	
	int64_t* m_docIdPtr;
	int64_t* m_lastDocIdPtr;

	Query  m_query;
	char   m_pwd [MAX_COLL_LEN];
	char   m_coll[MAX_COLL_LEN];
	long   m_collLen;

	bool  (*m_recordCallback) (void *state, 
				   TitleRec* tr,
				   class TagRec  *tagRec);
	void  (*m_endCallback)    (void *state);
	void  *m_callbackState;
};

#endif
