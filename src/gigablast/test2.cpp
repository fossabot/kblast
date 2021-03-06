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

// program to test Rdb

#include "gb-include.h"

long x,y,z;

#define x y

#undef x
#define y z
#define x y

int main ( int argc , char *argv[] ) {

	long m_bitScores[65536];
	long scores[16];
	long count = 65536;
	// . each set bit in singleMask and phraseMask have a term freq
	// . count can be 65536, so this can take a couple million cycles!!
	for ( unsigned long i = 0 ; i < count ; i++ ) {
		// loop through each on bit for "i"
		m_bitScores[i] = 0;
		if ( i & 0x0001 ) m_bitScores[i] += scores[0];
		if ( i & 0x0002 ) m_bitScores[i] += scores[1];
		if ( i & 0x0004 ) m_bitScores[i] += scores[2];
		if ( i & 0x0008 ) m_bitScores[i] += scores[3];
		if ( i & 0x0010 ) m_bitScores[i] += scores[4];
		if ( i & 0x0020 ) m_bitScores[i] += scores[5];
		if ( i & 0x0040 ) m_bitScores[i] += scores[6];
		if ( i & 0x0080 ) m_bitScores[i] += scores[7];
		if ( i & 0x0100 ) m_bitScores[i] += scores[8];
		if ( i & 0x0200 ) m_bitScores[i] += scores[9];
		if ( i & 0x0400 ) m_bitScores[i] += scores[10];
		if ( i & 0x0800 ) m_bitScores[i] += scores[11];
		if ( i & 0x1000 ) m_bitScores[i] += scores[12];
		if ( i & 0x2000 ) m_bitScores[i] += scores[13];
		if ( i & 0x4000 ) m_bitScores[i] += scores[14];
		if ( i & 0x8000 ) m_bitScores[i] += scores[15];
	}

}
