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

#ifndef _COUNTRYCODE_H
#define _COUNTRYCODE_H

#include "HashTableT.h"
#include "types.h"

// . used by Events.cpp to keep things small
// . get a single byte country id from a 2 character country code
uint8_t getCountryId ( char *cc ) ;

// map a country id to the two letter country abbr
char *getCountryCode ( uint8_t crid );

class CountryCode {
	public:
		CountryCode();
		~CountryCode();
		void init(void);
		int getNumCodes(void);
		const char *getAbbr(int index);
		const char *getName(int index);
		int getIndexOfAbbr(const char *abbr);
		unsigned short getCountryFromDMOZ(long catid);
		uint8_t getLanguageFromDMOZ(long catid);
		int createHashTable(void);
		bool loadHashTable(void);
		void reset();
		long getNumEntries(void);
		void debugDumpNumbers(void);
         	uint64_t getLanguagesWritten(int index);
	private:
		int fillRegexTable(void);
		void freeRegexTable(void);
		int lookupCountryFromDMOZTopic(const char *catname, int len);
		bool m_init;
		HashTableT<unsigned short, int>m_abbrToIndex;
		HashTableT<unsigned short, const char *>m_abbrToName;
};

extern CountryCode g_countryCode;

// We're currently at 24x or so...
#define MAX_COUNTRIES (255)

#endif // _COUNTRYCODE_H

