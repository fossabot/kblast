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

// . stores lists of common words for various languages
// . used to determine what language a word/page belongs to

#ifndef _LANGLIST_H_
#define _LANGLIST_H_

//#include "TermTable.h"
#include "Words.h"
#include "Lang.h"
#include "HashTableX.h"

class LangList {
public:
	LangList  ( );
	~LangList ( );

	void reset ( );
	// . returns false and sets errno on error
	// . loads language lists into memory
	// . looks under the langlist/ directory for langlist.# files
	//   each number corrisponds to a language
	bool loadLists ( );

	// . lookup word in language lists
	// . returns false if unknown true if found and lang set
	bool lookup ( long long      termId,
		      unsigned char *lang   );
	
	char* getCountryFromTld(char* tld, long tldLen);
	bool  isLangValidForTld(char* tld, long tldLen, unsigned char lang);
	bool  tldInit();

	inline uint8_t catIdToLang(uint32_t catid);
	inline uint32_t langToCatId(uint8_t lang);
	uint8_t isLangCat(int catid);


private:
	//TermTable langTable;
	//HashTableT<long, short> m_tldToCountry;
	HashTableX m_langTable;
	HashTableX m_tldToCountry;
};

extern class LangList g_langList;

#endif
