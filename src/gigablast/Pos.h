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

#ifndef _POS_H_
#define _POS_H_

#include "Words.h"

// this class is used to measure the number of characters between two "words"
// (as defined in the Words.cpp class) in units of "characters". A utf8
// character can be 1, 2, 3 or 4 bytes, so be careful.

#define POS_LOCALBUFSIZE 20

class Pos {

 public:

	Pos();
	~Pos();
	void reset();

	bool set    ( class Words  *words   ,
		      class Sections *sections ,
		      char         *f      = NULL ,
		      char         *fend   = NULL ,
		      long         *flen   = NULL ,
		      long          a      =  0   ,
		      long          b      = -1   ,
		      // you can provide it with a buffer to prevent a malloc
		      char         *buf    = NULL ,
		      long          bufSize= 0    );

	// . filter out xml words [a,b] into plain text, stores into "p"
	// . will not exceed "pend"
	// . returns number of BYTES stored into "p"
	long filter ( char         *p     ,
		      char         *pend  ,
		      class Words  *words ,
		      long          a     =  0 ,
		      long          b     = -1 ,
		      class Sections *sections = NULL );

	long getMemUsed () { return m_bufSize; };

	// . the position in CHARACTERS of word i is given by m_pos[i]
	// . this is NOT the byte position. you can have 2, 3 or even 4
	//   byte characters in utf8. the purpose here is for counting 
	//   "letters" or "characters" for formatting purposes.
	long *m_pos;
	long  m_numWords;

	char  m_localBuf [ POS_LOCALBUFSIZE ];
	char *m_buf;
	long  m_bufSize;

	bool  m_needsFree;
};

#endif
