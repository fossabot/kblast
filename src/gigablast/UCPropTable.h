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

#ifndef UCPROPTABLE_H___
#define UCPROPTABLE_H___

#include <sys/types.h>
#include <stdlib.h> //NULL

class UCPropTable {
public:
	UCPropTable(unsigned char valueSize = 1, 
		    unsigned char tableBits = 16) ;

	virtual ~UCPropTable() ;
	void reset();

	//void *getValue(unsigned long c);
	void *getValue(unsigned long c){
		unsigned long prefix = c >> m_tableBits;
		unsigned long key = c & m_tableMask;
		if (prefix >= m_numTables) return NULL;
		if (m_data[prefix] == NULL) return NULL;
		return (void*) (m_data[prefix] + key*m_valueSize);
	};

	bool setValue(unsigned long c, void *value);
	
	size_t getSize() {return getStoredSize() + m_numTables*sizeof(char*);};
	size_t getStoredSize() ;
	size_t serialize(char *buf, size_t bufSize);
	size_t deserialize(char *buf, size_t bufSize);

private:
	unsigned char **m_data;

	unsigned char m_valueSize;
	unsigned char m_tableBits;
	unsigned long m_tableSize;
	unsigned long m_tableMask;
	unsigned long m_numTables;
};
#endif
