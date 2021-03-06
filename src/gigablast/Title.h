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

#ifndef _TITLE_H_
#define _TITLE_H_
#include "SafeBuf.h"
#include "Query.h"
//#include "CollectionRec.h"

#define TITLE_LOCAL_SIZE 2048

class LinkInfo;

class Title {

 public:

	Title();
	~Title();
	void reset();

	// . set m_title to the title of the document represented by "xd"
	// . if getHardTitle is true will always use the title in the <title>
	//   tag, but if that is not present, will try dmoz titles before
	//   resorting to trying to guess a title from the document content
	//   or incoming link text.
	// . uses the following:
	// .   title tag
	// .   dmoz title
	// .   meta title tag
	// .   incoming link text
	// .   <hX> tags at the top of the scored content
	// .   blurbs in bold at the top of the scored content
	// . removes starting/trailing punctuation when necessary
	// . does not consult words with scores of 0 (unless a meta tag)
	// . maxTitleChars is in chars (a utf16 char is 2 bytes or more)
	// . maxTitleChars of -1 means no max
	bool setTitle ( class XmlDoc   *xd            ,
			class Xml      *xml           ,
			class Words    *words         , 
			class Sections *sections      ,
			class Pos      *pos           ,
			long            maxTitleChars ,
			long            maxTitleWords ,
			SafeBuf *pbuf,
			Query          *q , // = NULL,
			CollectionRec  *cr , // = NULL ,
			long niceness );


	char *getTitle     ( ) { return m_title; };
	long  getTitleSize ( ) { return m_titleBytes; }; // does NOT include \0


	bool copyTitle ( class Words *words, class Pos *pos,
			 long  t0, long  t1 , class Sections *sections );

	//long getTitleScore( Words *w, long t0, long t1, long *numFoundQTerms,
	//		    long *alphaWordCount = NULL );
	
	float getSimilarity ( Words  *w1 , long i0 , long i1 ,
			      Words  *w2 , long t0 , long t1 );

	//static int cmpInLinkerScore(const void *A, const void *B);

	char *m_title;
	long  m_titleBytes; // in bytes. does NOT include \0
	long  m_titleAllocSize;
	char  m_localBuf [ TITLE_LOCAL_SIZE ];
	bool  m_htmlEncoded;
	char  m_niceness;

	// For weighting title scores with query terms
	Query *m_query;


	long  m_maxTitleChars;
	long  m_maxTitleWords;

	long m_titleTagStart ;
	long m_titleTagEnd   ;

 private:

	bool setTitle4 ( class XmlDoc   *xd            ,
			 class Xml      *xml           ,
			 class Words    *words         , 
			 class Sections *sections      , 
			 class Pos      *pos           ,
			 long            maxTitleChars ,
			 long            maxTitleWords ,
			 SafeBuf        *pbuf          ,
			 Query          *q             ,
			 CollectionRec  *cr            );

};

#endif
