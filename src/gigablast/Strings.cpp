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

#include "Strings.h"

char *getString ( long i ) {

	static char *s_nextp = NULL;
	static char *s_nexti = -1;

	// boundary check
	if ( i < 0 ) return NULL;

	// was this call predicted?
	if ( i == s_nexti ) {
		// return NULL if none left
		if ( s_nextp >= m_end ) return NULL;
		// set next string ptr
		s_nextp = m_s + gbstrlen ( m_s ) + 1;
		s_nexti++;
		// return current
		return m_s;
	}

	// otherwise reset
	s_nextp = NULL;
	s_nexti = -1;

	// scan from beginning
	char *p     = m_s;
	long  count = 0;
	while ( p < m_end ) {
		// break on match
		if ( count == i ) break;
		// advance p
		p += gbstrlen ( p ) + 1;
		count++;
	}

	// return NULL if no match
	if ( p >= m_end ) return NULL;

	// set statics
	s_nextp = p + gbstrlen ( p ) + 1;
	s_nexti = count + 1;

	// return now
	return p;
}
