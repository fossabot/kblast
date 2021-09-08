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

#ifndef _SYNONYMS_H_
#define _SYNONYMS_H_

#include "Xml.h"
#include "SafeBuf.h"
#include "StopWords.h"
#include "fctypes.h"

#define SOURCE_NONE       0
#define SOURCE_PRESET     1
#define SOURCE_WIKTIONARY 2
#define SOURCE_WIKTIONARY_EN 3
#define SOURCE_GENERATED  4
#define SOURCE_BIGRAM     5
#define SOURCE_TRIGRAM    6
#define SOURCE_NUMBER     7

// per word!
#define MAX_SYNS 64

#define TMPSYNBUFSIZE (MAX_SYNS*(8+8+8+1+4+4+4+4+4))

long long getSynBaseHash64 ( char *qstr , uint8_t langId ) ;

char *getSourceString ( char source );

class Synonyms {

 public:

	Synonyms();
	~Synonyms();

	void reset();

	long getSynonyms ( class Words *words , 
			   long wordNum , 
			   uint8_t langId ,
			   char *tmpBuf ,
			   long niceness ) ;

	
	bool addWithoutApostrophe ( long wordNum , class HashTableX *dt ) ;
	bool addAmpPhrase ( long wordNum , class HashTableX *dt ) ;
	bool addStripped ( char *w,long wlen, class HashTableX *dt ) ;

	long m_niceness;
	long m_version; // titlerec version

	//char    *m_langVec;
	char     m_docLangId;
	class Words *m_words;

	// temporarily store all synonyms here of the word for synonyms
	// like the accent-stripped version of the word. otherwise we
	// can just point to the wiktionary-buf.txt representation in memory.
	SafeBuf m_synWordBuf;

	// for each synonym of this word we fill out these:
	long long  *m_aids;
	long long  *m_wids0;
	long long  *m_wids1;
	char      **m_termPtrs;
	long       *m_termOffs;
	long       *m_termLens;
	long       *m_numAlnumWords;
	long       *m_numAlnumWordsInBase;
	char       *m_src;

	long long *m_aidsPtr;
	long long *m_wids0Ptr;
	long long *m_wids1Ptr;
	char     **m_termPtrsPtr;
	long      *m_termOffsPtr;
	long      *m_termLensPtr;
	long      *m_numAlnumWordsPtr;
	long      *m_numAlnumWordsInBasePtr;
	char      *m_srcPtr;

};

#endif
