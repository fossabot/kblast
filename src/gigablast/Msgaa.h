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

#ifndef _MSGAA_H_
#define _MSGAA_H_

#include "gb-include.h"
#include "Url.h"
#include "SearchInput.h"

#define MAX_QBUF_SIZE (MAX_URL_LEN+200)

class Msgaa {

public:
	Msgaa();
	~Msgaa(); 

	bool addSitePathDepth ( class TagRec *gr  , 
				class Url    *url ,
				char *coll ,
				void *state ,
				void (* callback)(void *state) ) ;

	bool gotResults ( ) ;

	SearchInput m_si;
	class TagRec *m_gr;
	class Url    *m_url;
	char   *m_coll;
	void   *m_state;
	void  (*m_callback) (void *state );
	long    m_sitePathDepth;

	class Msg40 *m_msg40;
	long m_pathDepth;
	char m_qbuf[MAX_QBUF_SIZE];
	//long m_niceness;

	long m_oldSitePathDepth;
	long m_newSitePathDepth;

};

#endif
