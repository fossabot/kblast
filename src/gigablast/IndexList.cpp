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

#include "IndexList.h"
#include <math.h>       // log() math functions
#include "Datedb.h"    // g_datedb

// . clear the low bits on the keys so terms are DELETED
// . used by Msg14 to delete a document completely from the index
void IndexList::clearDelBits ( ) {
	// get the list (may be the whole list, m_list)
	//key_t *keys = (key_t *) RdbList::getList();
	// . how many keys do we have?
	// . all keys should be 12 bytes since we don't repeat the termId
	//long   numKeys = RdbList::getListSize() / sizeof(key_t);
	// loop thru each key and clear it's del bit
	//for ( long i = 0 ; i < numKeys ; i++ ) 
	//	keys[i].n0 &= 0xfffffffffffffffeLL;
	char *p    = m_list;
	char *pend = m_list + m_listSize;
	long  step = m_ks;
	for ( ; p < pend ; p += step ) *p &= 0xfe;
}

void IndexList::print() { 
	if ( m_ks==16 ) logf(LOG_DEBUG,"db:      termId date    score docId");
	else            logf(LOG_DEBUG,"db:      termId score docId");
	long i = 0;
	for ( resetListPtr() ; ! isExhausted() ; skipCurrentRecord() ) {
		// print out date lists here
		if ( m_ks == 16 ) {
			logf(LOG_DEBUG,
			     "db: %04li) %020lli %10lu %03li %020lli",
			     i++ ,
			     getTermId16(m_listPtr),
			     getCurrentDate(),
			     (long)getCurrentScore(),
			     (long long)getCurrentDocId() );
			continue;
		}
		logf(LOG_DEBUG,"db: %04li) %020lli %03li %020lli" ,
		     i++ ,
		     (long long)getCurrentTermId12() ,
		     (long)getCurrentScore(),
		     (long long)getCurrentDocId() );
	}
}
