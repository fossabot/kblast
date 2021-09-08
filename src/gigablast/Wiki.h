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

#ifndef _WIKI_H_
#define _WIKI_H_

#include "BigFile.h"
#include "HashTableX.h"

class Wiki {

 public:

	Wiki();
	~Wiki();
	void reset();


	long getNumWordsInWikiPhrase ( long i , class Words *words );

	// if a phrase in a query is in a wikipedia title, then increase
	// its affWeights beyond the normal 1.0
	bool setPhraseAffinityWeights ( class Query *q , float *affWeights ,
					bool *oneTitle = NULL );
	
	// . we hit google with random queries to see what blog sites and
	//   news sites they have
	// . stores phrase in m_randPhrase
	// . returns false if blocks, true otherwise
	// . sets g_errno on error and returns true
	// . callback will be called with g_errno set on error as well
	bool getRandomPhrase ( void *state , void (* callback)(void *state) );

	bool isInWiki ( uint32_t h ) { return ( m_ht.getSlot ( &h ) >= 0 ); };
	
	void doneReadingWiki ( ) ;

	// . load from disk
	// . wikititles.txt (loads wikititles.dat if and date is newer)
	bool load();
	
	bool loadText ( long size ) ;

	// . save the binary hash table to disk to make loading faster
	// . wikititles.dat
	bool saveBinary();
	
	HashTableX m_ht;
	
	char m_buf[5000];

	char m_randPhrase[512];

	BigFile m_f;

	void *m_state;
	void (* m_callback)(void *);

	long m_txtSize;

	long m_errno;

	char m_opened;
	FileState m_fs;
};

extern class Wiki g_wiki;

#endif
