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

// . used exculsively by RdbGet
// . used for scanning a key-range of records
// . does non-blocking disk reads
// . set loop to NULL to do blocking disk reads
// . we set m_errno to a positive value on error, so check it!
// . originally you could call getNextRecord() before the entire read
//   was complete. 

#ifndef _RDBSCAN_H_
#define _RDBSCAN_H_

#include "BigFile.h"
#include "Loop.h"
#include "RdbMap.h"
#include "RdbList.h"

class RdbScan {
	
 public:

	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . call this to start the read (sets up your key-range read too)
	// . endKey must be provided
	// . TODO: can we do multiple "simultaneous" non-blocking 
	//   reads on the same fd?
	// . we need array of files so BigFile::filecb() knows when file nuked
	bool setRead ( BigFile   *file          ,
		       long       fixedDataSize ,
		       long long  offset        ,
		       long       bytesToRead   ,
		       //key_t      startKey      , 
		       //key_t      endKey        , 
		       char      *startKey      , 
		       char      *endKey        , 
		       char       keySize       ,
		       RdbList   *list          , // we fill this up
		       void      *state         ,
		       void    (* callback ) ( void *state ) ,
		       bool       useHalfKeys   ,
		       char       rdbId,
		       long       niceness , // = MAX_NICENESS ,
		       bool       allowPageCache , // = true ,
		       bool       hitDisk        ); // = true );

	// RdbGet likes to get our list
	RdbList *getList ( ) { return m_list; };

	// was buffer shifted down 6 bytes to turn first key into a 12 byter?
	bool wasShifted () { return m_shifted; };


	void gotList ( );

	// we set this list with the read buffer on read completion
	RdbList  *m_list;

	// for doing non-blocking reads with BigFile::read()
	FileState m_fstate;

	// for dealing with half keys
	long m_off;

	// shifting it
	char m_shifted;

	char m_rdbId;

	// save for call to our gotListWrapper()
	//key_t  m_startKey;
	char m_startKey[MAX_KEY_BYTES];
	char m_endKey  [MAX_KEY_BYTES];
	long m_fixedDataSize;
	char m_useHalfKeys;
	long m_bytesToRead;
	void (* m_callback ) ( void *state ) ;
	void  *m_state;

	// for sanity checking
	BigFile   *m_file;
	long long  m_offset;
	char       m_ks;

	// for allowing page cache
	bool  m_allowPageCache;

	bool  m_hitDisk;
};

#endif
