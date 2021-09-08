// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2000-2014 Matt Wells
// Copyright 2013      Web Research Properties, LLC
// Copyright 2004-2013 Gigablast, Inc.
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

// . highlights the terms in Query "q" in "xml" and puts results in m_buf

#include "Words.h"
#include "Query.h"
#include "Matches.h"
#include "Xml.h"
#include "Url.h"

#ifndef _HIGHLIGHT_H_
#define _HIGHLIGHT_H_

class Highlight {

 public:

	// . content is an html/xml doc
	// . we highlight Query "q" in "xml" as best as we can
	// . store highlighted text into "buf"
	// . return length stored into "buf"
	long set ( //char        *buf          ,
		   //long         bufLen       ,
		  SafeBuf *sb,
		   char        *content      ,
		   long         contentLen   , 
		   char         docLangId    ,
		   Query       *q            ,
		   bool         doStemming   ,
		   bool         useAnchors   , // = false ,
		   const char  *baseUrl      , // = NULL  ,
		   const char  *frontTag     , // = NULL  ,
		   const char  *backTag      , // = NULL  ,
		   long         fieldCode    , // = 0     ,
		   long         niceness    ) ;
	
	long set ( //char        *buf        ,
		  //long         bufLen     ,
		  SafeBuf *sb ,
		   Words       *words      ,
		   Matches     *matches    ,
		   bool         doStemming ,
		   bool         useAnchors = false ,
		   const char  *baseUrl    = NULL  ,
		   const char  *frontTag   = NULL  ,
		   const char  *backTag    = NULL  ,
		   long         fieldCode  = 0     ,
		   Query       *q	   = NULL  ) ;

	long getNumMatches() { return m_numMatches; }

 private:

	bool highlightWords ( Words *words , Matches *m , Query *q=NULL );

	// null terminate and store the highlighted content in m_buf
	//char    *m_buf ;
	//long     m_bufLen;
	//char    *m_bufPtr;
	//char    *m_bufEnd;
	class SafeBuf *m_sb;

	//Words    m_words;
	Matches  m_matches;
	//Xml     *m_xml;
	const char    *m_frontTag;
	const char    *m_backTag;
	long     m_frontTagLen;
	long     m_backTagLen;
	bool     m_doStemming;

	bool     m_useAnchors;  // click and scroll technology for cached pages
	long     m_anchorCounts [ MAX_QUERY_TERMS ];
	const char    *m_baseUrl;

	long m_numMatches;
	
	// so we don't repeat the same buf overflow error msg a gazillion times
	bool     m_didErrMsg;
	// . field code of the text excerpt to highlight
	// . only query terms with this fieldCode will be highlighted
	long     m_fieldCode;
};

#endif

