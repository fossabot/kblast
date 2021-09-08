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

// . get the number of records (termId/docId/score tuple) in an IndexList(s)
//   for a given termId(s)
// . if it's truncated then interpolate based on score
// . used for query routing
// . used for query term weighting (IDF)
// . used to set m_termFreq for each termId in query in the Query class

#ifndef _MSG37_H_
#define _MSG37_H_

#include "Msg36.h"
#include "Query.h"  // MAX_QUERY_TERMS

#define MAX_MSG36_OUT 20

class Msg37 {

 public:

	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . "termIds/termFreqs" should NOT be on the stack in case we block
	bool getTermFreqs ( collnum_t collnum ,
			    long        maxAge     ,
			    long long  *termIds    ,
			    long        numTermIds ,
			    long long  *termFreqs  ,
			    void       *state      ,
			    void (* callback)(void *state ) ,
			    long        niceness   , // = MAX_NICENESS
			    bool        exactCount );

	bool launchRequests ( ) ;

	// leave public so C wrapper can call
	bool gotTermFreq ( Msg36 *msg36 ) ;

	// we can get up to MAX_QUERY_TERMS term frequencies at the same time
	Msg36 m_msg36 [ MAX_MSG36_OUT ]; // [ MAX_QUERY_TERMS ];
	char  m_inUse [ MAX_MSG36_OUT ];
	long  m_i;

	// . ptr to "termFreqs" passed in by getTermFreqs[]
	// . we remember it so we can set them
	long long *m_termFreqs;
	long       m_numTerms;

	long m_numReplies  ;
	long m_numRequests ;
	long m_errno;

	void *m_state ;
	void ( * m_callback ) ( void *state );

	long  m_niceness;

	bool  m_exactCount;

	collnum_t m_collnum;

	long        m_maxAge;
	long long  *m_termIds ;
};

#endif
