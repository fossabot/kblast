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

// . generic hash table class

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "Mem.h"     // for mcalloc and mmalloc

class HashTable {

 public:

	bool set ( long  initialNumSlots = 0    ,
		   char *buf             = NULL ,
		   long  bufSize         = 0    ,
		   char *label           = NULL );

	 HashTable       ( );
	~HashTable       ( );

	void setLabel ( char *label ) { m_label = label; };

	// . add key/value entry to hash table
	// . will grow hash table if it needs to
	bool addKey ( long key , long value , long *slot = NULL );

	// remove key/value entry to hash table
	bool removeKey  ( long key );

	// like removeKey
	void removeSlot ( long n );

	// . used by ../english/Bits.h to store stop words, abbr's, ...
	// . returns the score for this termId (0 means empty usually)
	long getValue ( long key );

	// value of 0 means empty
	bool isEmpty ( long key ) { return (getValue(key) == 0); };

	long getKey ( long n ) { return m_keys[n]; };

	long getSlot ( long key ) { return getOccupiedSlotNum ( key ); };

	void setValue ( long n , long val ) { m_vals[n] = val; };

	long getValueFromSlot ( long n ) { return m_vals[n]; };

	// frees the used memory, etc.
	void  reset  ( );

	// removes all key/value pairs from hash table, vacates all slots
	void  clear  ( );

	// how many are occupied?
	long getNumSlotsUsed ( ) { return m_numSlotsUsed; };

	// how many are there total? used and unused.
	long getNumSlots ( ) { return m_numSlots; };

	// both return false and set g_errno on error, true otherwise
	bool load ( char *dir , char *filename );
	bool save ( char *dir , char *filename );

 private:

	bool setTableSize ( long numSlots , char *buf , long bufSize );

	long getOccupiedSlotNum ( long key ) ;

	// . the array of buckets in which we store the terms
	// . scores are allowed to exceed 8 bits for weighting purposes
	long  *m_keys;
	long  *m_vals;

	long m_numSlots;
	long m_numSlotsUsed;
	unsigned long m_mask;

	char m_needsSave;
	char m_doFree;

	char *m_label;
};

#endif





