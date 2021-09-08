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

#ifndef _STOPWORDS_H_
#define _STOPWORDS_H_

#include "Unicode.h"

// . this returns true if h is the hash of an ENGLISH stop word
// . list taken from www.superjournal.ac.uk/sj/application/demo/stopword.htm 
// . stop words with "mdw" next to them are ones I added
bool isStopWord ( char *s , long len , long long h ) ;

// used by Synonyms.cpp
bool isStopWord2 ( long long *h ) ;

bool isStopWord32 ( long h ) ;

//just a stub for now
//bool isStopWord ( UChar *s , long len , long long h );


// . damn i forgot to include these above
// . i need these so m_bitScores in IndexTable.cpp doesn't have to require
//   them! Otherwise, it's like all queries have quotes around them again...
bool isQueryStopWord ( char *s , long len , long long h ) ;
//bool isQueryStopWord ( UChar *s , long len , long long h ) ;

// is it a COMMON word?
long isCommonWord ( long long h ) ;

long isCommonQueryWordInEnglish ( long long h ) ;

bool initWordTable(class HashTableX *table, char* words[], long size ,
		   char *label);

bool isVerb ( long long *hp ) ;

// for Process.cpp::resetAll() to call when exiting to free all mem
void resetStopWordTables();

extern HashTableX s_table32;

#endif
