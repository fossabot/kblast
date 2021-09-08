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

#ifndef JSON_H
#define JSON_H

#define JT_NULL 2
#define JT_NUMBER 3
#define JT_STRING 4
#define JT_ARRAY 5
#define JT_OBJECT 6
	
//#define JT_IsReference 256

#include "gb-include.h"
#include "Unicode.h"
#include "SafeBuf.h"

#define MAXJSONPARENTS 64

class JsonItem {

 public:
	// scan the linked list
	class JsonItem *m_next,*m_prev;
	class JsonItem *m_parent;//child;

	// the JT_* values above
	int m_type;

	// . the NAME of the item
	// . points into the ORIGINAL json string
	char *m_name;
	long m_nameLen;

	// for JT_NUMBER
	long m_valueLong;
	// for JT_NUMBER
	double m_valueDouble;

	// for JT_String
	long m_valueLen;

	// for JT_String
	long  getValueLen() { return m_valueLen; };

	// for arrays (JT_ARRAY), hack the char ptr into m_valueLong
	char *getArrayStart() { return (char *)m_valueLong; }
	long  getArrayLen  () { return m_valueLen; };

	// for JT_String
	char *getValue () { 
		// if value is another json object, then return NULL
		// must be string
		if ( m_type != JT_STRING ) return NULL;
		// otherwie return the string which is stored decoded
		// after this object in the same buffer
		return (char *)this + sizeof(JsonItem);
	};

	// convert nubers and bools to strings for this one
	char *getValueAsString ( long *valueLen ) ;

	// like acme.product.offerPrice if "acme:{product:{offerprice:1.23}}"
	bool getCompoundName ( SafeBuf &nameBuf ) ;

	bool isInArray ( );
};


class Json {
 public:

	void test();

	JsonItem *parseJsonStringIntoJsonItems ( char *json , long niceness );

	JsonItem *getFirstItem ( ) ;

	JsonItem *getItem ( char *name );

	JsonItem *addNewItem ();

	Json() { m_stackPtr = 0; m_prev = NULL; };
	
	SafeBuf m_sb;
	JsonItem *m_stack[MAXJSONPARENTS];
	long m_stackPtr;
	class JsonItem *m_prev;
};

#endif
