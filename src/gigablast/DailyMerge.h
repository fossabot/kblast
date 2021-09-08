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
// Copyright Gigablast, Inc. Apr 2008

// tight merge indexdb and datedb at the given time every day

#ifndef _DAILYMERGE_H_
#define _DAILYMERGE_H_

#include "gb-include.h"
#include "Collectiondb.h"

class DailyMerge {
public:

	bool init();

	// is the scan active and adding recs to the secondary rdbs?
	bool isMergeActive() { return (m_mergeMode >= 1); };

	void dailyMergeLoop ( ) ;

	CollectionRec *m_cr;
	char           m_mergeMode;
	char           m_spideringEnabled;
	char           m_injectionEnabled;
	char           m_didDaily;
	time_t         m_savedStartTime;
};

// the global class
extern DailyMerge g_dailyMerge;

#endif
