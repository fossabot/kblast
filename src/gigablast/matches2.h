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

#ifndef _MATCHES_FUNC_H_
#define _MATCHES_FUNC_H_

// use these routines for matching any of a list of substrings in the haystack.
// the Matches array is the list of substrings to match in the "haystack". this
// should be *very* fast.
class Needle {
public:
	char *m_string;
	char  m_stringSize;
	char  m_id;
	// if m_isSection is true, getMatch() only matches if haystack 
	// ptr is < linkPos
	char  m_isSection; 
	long  m_count;
	char *m_stringSave;
	char  m_stringSizeSave;
	char *m_firstMatch;
	// used by XmlDoc::getEventSummary()
	float m_score;
	// used by XmlDoc::getEventSummary() to point to query word #
	long  m_qwn;
};


char *getMatches2 ( Needle *needles          , 
		    long    numNeedles       ,
		    char   *haystack         , 
		    long    haystackSize     ,
		    char   *linkPos          ,
		    long   *n                ,
		    bool    stopAtFirstMatch ,
		    bool   *hadPreMatch      ,
		    bool    saveQuickTables  ,
		    long    niceness         );



#endif 
