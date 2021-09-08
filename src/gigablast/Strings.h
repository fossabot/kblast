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

// . a Strings class is a list of NULL-terminated strings all in one string

#ifndef _STRINGS_H_
#define _STRINGS_H_

#include "Mem.h"

class StringArray {
 public:
	Strings() { m_s = NULL; m_len = 0; };
	~Strings () { if (m_s) mfree(m_s,m_len,"Strings"); m_s = NULL; };
	void set ( char *s , long len ) { m_s=s; m_len=len; m_end=s+len; };
	char *getString ( long i ) ;
	// returns false and sets errno on error
	bool addString ( char *s ) {
		long len = gbstrlen(s);
		m_s = (long *) mrealloc (m_s, m_len, m_len+len+1, "Strings");
		if ( ! m_s ) return false;
		strcpy ( m_s + m_len , s );
		m_len += len + 1;
	};
	char *m_s;
	char *m_end;
	long  m_len;
};

class LongArray {
 public:
	LongArray() { m_x = NULL; m_n = 0; };
	~LongArray() { if (m_x) mfree(m_x,m_n*4,"LongArray"); m_x = NULL; };
	// returns false and sets errno on error
	bool addLong ( long x ) {
		m_x = (long *) mrealloc (m_x, m_n*4, m_n*4+4, "LongArray");
		if ( ! m_x ) return false;
		m_x [ m_n++ ] = x;
	};
	long getLong ( long i ) { return m_x[i]; };
	long *m_x;
	long  m_n;
};

class CharArray {
 public:
	CharArray() { m_x = NULL; m_n = 0; };
	~CharArray() { if (m_x) mfree(m_x,m_n,"CharArray"); m_x = NULL; };
	// returns false and sets errno on error
	bool addChar ( long x ) {
		m_x = (long *) mrealloc (m_x, m_n, m_n+1, "CharArray");
		if ( ! m_x ) return false;
		m_x [ m_n++ ] = x;
	};
	char getChar ( long i ) { return m_x[i]; };
	char *m_x;
	long  m_n;
};

#endif
