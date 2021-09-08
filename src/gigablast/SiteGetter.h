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

#ifndef _SITEGETTER_H_
#define _SITEGETTER_H_

#include "gb-include.h"
#include "Msg0.h"
#include "Tagdb.h"

#define MAX_SITE_LEN 256

class SiteGetter {

public:

	SiteGetter();
	~SiteGetter();

	// . returns false if blocked, true otherwise
	// . sets g_errno on erorr
	bool getSite ( char         *url      ,
		       class TagRec *gr       ,
		       long          timestamp,
		       collnum_t collnum,
		       long          niceness ,
		       //bool          addTags  = false,
		       void         *state    = NULL ,
		       void (* callback)(void *state) = NULL ) ;


	bool setRecognizedSite ( );

	char *getSite    ( ) { return m_site   ; };
	long  getSiteLen ( ) { return m_siteLen; };

	//bool isIndependentSubsite() { return m_isIndependentSubsite; };

	bool getSiteList ( ) ;
	bool gotSiteList ( ) ;
	bool setSite ( ) ;

	class TagRec *m_gr;
	//class Url    *m_url;
	char         *m_url;
	collnum_t m_collnum;
	//bool          m_addTags;
	void         *m_state;
	void        (*m_callback) (void *state );
	RdbList       m_list;

	long          m_sitePathDepth;

	// use Msg0 for getting the no-split termlist that combines 
	// gbpathdepth: with the site hash in a single termid
	Msg0   m_msg0;
	//Msg9a  m_msg9a;
	long   m_pathDepth;
	long   m_maxPathDepth;
	long   m_niceness;
	long   m_oldSitePathDepth;
	char   m_allDone;
	long   m_timestamp;

	bool   m_hasSubdomain;

	// points into provided "u->m_url" buffer
	char   m_site[MAX_SITE_LEN+1];
	long   m_siteLen;

	//bool   m_isIndependentSubsite;

	bool   m_tryAgain;

	long   m_errno;

	// the tag rec we add
	TagRec m_addedTag;
};

#endif
