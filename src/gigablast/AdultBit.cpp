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

#include "gb-include.h"

#include "AdultBit.h"
#include "HashTableX.h"

// . returns true if document is adult, false otherwise
bool AdultBit::getBit ( char *s , long niceness) {

	// rudimentary adult detection algorithm
	long  i   = 0;
	long  dirties = 0;
	long  j;
	long  slen;
 loop:

	// skip until we hit an alpha
	while ( s[i] && ! is_alpha_a(s[i]) ) i++;
	// return if done
	if ( ! s[i] ) return false;
	// . point to char after this alpha
	// . return if none
	j = i + 1;
	// find end of the alpha char sequence
	while ( s[j] && is_alpha_a(s[j]) ) j++;
	// skip over 1 or 2 letter words
	slen = j - i; 
	if ( slen <= 2 ) { i = j; goto loop; }
	// it's adult content if it has just 1 obscene word
	if ( isObscene ( (char *) s+i , slen ) ) return true;

	// W = non-dirty word
	// D = dirty word
	// . = sequence of punctuation/num and/or 1 to 2 letter words
	// dirty sequences: 
	// . D . D . D .     (dirties=6)
	// . D . W . D . D . (dirties=5)
	// . basically, if 3 out of 4 words in a subsequence are
	//   "dirty" then the whole document is "adult" content
	if ( isDirty ( (char *) s+i , slen ) ) {
		dirties += 2;
		if ( dirties >= 5 ) return true;
		i = j;
		goto loop;
	}

	dirties--;
	if ( dirties < 0 ) dirties = 0;

	QUICKPOLL((niceness));
	i = j;
	goto loop;
}

static HashTableX  s_dtable;
bool AdultBit::isDirty ( char *s , long len ) {

	static bool       s_isInitialized = false;
	static char      *s_dirty[] = {
		"anal",
		"analsex",
		"blowjob",
		"blowjobs",
		"boob",
		"boobs",
		"clitoris",
		"cock",
		"cocks",
		"cum",
		"dick",
		"dicks",
		"gangbang",
		"gangbangs",
		"gangbanging",
		"movie",
		"movies",
		"oral",
		"oralsex",
		"porn",
		"porno",
		"pussy",
		"pussies",
		"sex",
		"sexy",
		"tit",
		"tits",
		"video",
		"videos",
		"xxx",
		"xxxx",
		"xxxx"
	};

	if ( ! s_isInitialized ) {
		// set up the hash table
		if ( ! s_dtable.set ( 8,4,sizeof(s_dirty  )*2,NULL,0,false,0,
				      "adulttab")) 
			return log("build: Error initializing "
				    "dirty word hash table." );
		// now add in all the dirty words
		long n = (long)sizeof(s_dirty)/ sizeof(char *); 
		for ( long i = 0 ; i < n ; i++ ) {
			long long h = hash64b ( s_dirty  [i] );
			if ( ! s_dtable.addTerm (&h, i+1) ) return false;
		}
		s_isInitialized = true;
	} 

	// compute the hash of the word "s"
	long long h = hash64Lower_a ( s , len );

	// get from table
	return s_dtable.getScore ( &h );
}		


static HashTableX  s_otable;
bool AdultBit::isObscene ( char *s , long len ) {

	static bool       s_isInitialized = false;
	static char      *s_obscene[] = {
		"clit",
		"clits",
//		"cum",    magna cum laude
		"cums",
		"cumshot",
		"cunt",
		"cunts",
		"milf",
		"rimjob",
		"felch",
		"fuck",
		"fucked",
		"fucker",
		"fucking",
		"fucks",
		"whore",
		"whores"
	};

	if ( ! s_isInitialized ) {
		// set up the hash table
		if ( ! s_otable.set ( 8,4,sizeof(s_obscene)*2,NULL,0,false,0,
				      "obscenetab") ) 
			return log("build: Error initializing "
				    "obscene word hash table." );
		// now add in all the stop words
		long n = sizeof(s_obscene) / sizeof(char *);
		for ( long i = 0 ; i < n ; i++ ) {
			long long h = hash64b ( s_obscene[i] );
			if ( ! s_otable.addTerm ( &h, i+1 ) ) return false;
		}
		s_isInitialized = true;
	} 

	// compute the hash of the word "s"
	long long h = hash64Lower_a ( s , len );

	// get from table
	return s_otable.getScore ( &h );
}		

void resetAdultBit ( ) {
	s_dtable.reset();
	s_otable.reset();
}
