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

// . gets an RdbList from disk
// . reads from N specified files and stores results in N RdbLists

#ifndef _MSG3_H_
#define _MSG3_H_

// . max # of rdb files an rdb can have w/o merging
// . merge your files to keep the number of them low to cut down # of seeks
// . we try to keep it down to only 1 file through merging
// . now that we embed a title file num in tfndb for each docid, titledb
//   only needs to be merged to collide positive/negative recs to save disk
//   space, so we do not want to be limited by number of files for titledb
// . we bumped this up to 512 to help get more sites out of site search
//#define MAX_RDB_FILES 512
// allow us to spider for a while without having to merge
//#define MAX_RDB_FILES 2048
// make Msg5 footprint smaller
//#define MAX_RDB_FILES 512
// make Msg5 footprint smaller since we have "whitelist" in msg2.cpp
// we need to run one msg5 per whitelisted site then and we can have up to
// 500 sites in the whitelist.
#define MAX_RDB_FILES 1024

//#define MSG3_BUF_SIZE ((sizeof(RdbScan)+sizeof(key_t)+sizeof(RdbList)+20)*6)
//#define MSG3_BUF_SIZE ((sizeof(RdbScan)+MAX_KEY_BYTES+sizeof(RdbList)+20)*6)
#define MSG3_BUF_SIZE 64

#include "RdbList.h"
#include "RdbScan.h"

class Msg3 {

 public:

	Msg3();
	~Msg3();

	// just sets # of read lists (m_numScansCompleted) to 0
	void reset();

	// . try to get at least minRecSizes worth of records
	// . endKey of "list" may be less than "endKey" provided
	// . sometimes there is a disk read error (due to merge deleting files)
	//   and retryNum/maxRetries help define the retries
	// . if "numFiles" is -1, it means read ALL files available
	// . if "justGetEndKey" is true, then the call just sets
	//   m_msg3.m_endKey and m_msg3.m_constrainKey. This is just used
	//   by Msg5.cpp to constrain the endKey so it can read the recs
	//   from the tree using that endKey, and not waste time.
	bool readList  ( char           rdbId         ,
			 //char          *coll          ,
			 collnum_t collnum ,
			 //key_t          startKey      , 
			 //key_t          endKey        , 
			 char          *startKey      , 
			 char          *endKey        , 
			 long           minRecSizes   , // scan size(-1 all)
			 long           startFileNum  , // first file to scan
			 long           numFiles      , // rel.2 startFileNum
			 void          *state         , // for callback
			 void         (* callback ) ( void *state ) ,
			 long           niceness      , // = MAX_NICENESS ,
			 long           retryNum      , // = 0             ,
			 long           maxRetries    , // = -1
			 bool           compensateForMerge ,
			 long long      syncPoint     , // = -1 (none)
			 bool           justGetEndKey = false ,
			 bool           allowPageCache = true ,
			 bool           hitDisk        = true );

	// for retrieving unmerged lists
	RdbList *getList       ( long i ) {return &m_lists[i];};
	long     getTfn        ( long i ) {return  m_tfns[i];};
	long     getNumLists   (        ) {return m_numScansCompleted; };

	// keep public for doneScanningWrapper to use
	bool      doneScanning    ( );

	// on read/write error we sleep and retry
	bool doneSleeping ();

	long      m_numScansStarted;
	long      m_numScansCompleted;
	void     *m_state       ;
	void    (* m_callback )( void *state );

	//private:

	// this might increase m_minRecSizes
	void compensateForNegativeRecs ( class RdbBase *base ) ;

	// . sets page ranges for RdbScan (m_startpg[i], m_endpg[i])
	// . returns the endKey for all RdbScans
	//key_t setPageRanges ( class RdbBase *base     ,
	void  setPageRanges ( class RdbBase *base     ,
			      long      *fileNums     ,
			      long       numFileNums  ,
			      //key_t      startKey     , 
			      //key_t      endKey       ,
			      char      *startKey     , 
			      char      *endKey       ,
			      //long       minRecSizes  );
			      long       minRecSizes  );

	// . buries bad pages from the m_lists we read from disk
	// . usually modifies m_badStartKey, m_badEndKey
	// . "n" is the bad list index into m_lists[]
	void extractBadness ( long n );

	// the rdb we're scanning for
	char  m_rdbId;
	//char *m_coll;
	collnum_t m_collnum;

	// the scan classes, 1 per file, used to read from that file
	RdbScan *m_scans ; // [ MAX_RDB_FILES ];

	// page ranges for each scan computed in setPageRanges()
	long    *m_startpg ; //    [ MAX_RDB_FILES ];
	long    *m_endpg   ; //    [ MAX_RDB_FILES ];

	//key_t   *m_hintKeys    ; // [ MAX_RDB_FILES ];
	char    *m_hintKeys    ; // [ MAX_RDB_FILES ];
	long    *m_hintOffsets ; // [ MAX_RDB_FILES ];

	long     m_startFileNum;
	long     m_numFiles    ;

	long    *m_fileNums    ; // [ MAX_RDB_FILES ];
	long     m_numFileNums;

	// hold the lists we read from disk here
	RdbList  *m_lists ; // [ MAX_RDB_FILES ];
	long     *m_tfns  ; // [ MAX_RDB_FILES ];

	// key range to read
	//key_t     m_fileStartKey;
	//key_t     m_startKey;
	//key_t     m_endKey;
	char     *m_fileStartKey;
	char      m_startKey[MAX_KEY_BYTES];
	char      m_endKey[MAX_KEY_BYTES];

	// end key to use when calling constrain_r()
	//key_t     m_constrainKey;
	char      m_constrainKey[MAX_KEY_BYTES];

	// min bytes to read
	long      m_minRecSizes;

	// keep some original copies incase errno == ETRYAGAIN
	//key_t     m_endKeyOrig;
	char      m_endKeyOrig[MAX_KEY_BYTES];
	long      m_minRecSizesOrig;

	long      m_niceness;

	// last error received from doing all reads
	int       m_errno;

	// only retry up to m_maxRetries times in case it was a fluke
	long        m_retryNum;
	long        m_maxRetries;

	// for debugging
	long long   m_startTime;

	// . these hints make a call to constrain() fast
	// . used to quickly contrain the tail of a 1-list read
	long        m_hintOffset;
	//key_t       m_hintKey;
	char        m_hintKey[MAX_KEY_BYTES];

	bool        m_compensateForMerge;

	//long long   m_syncPoint;

	char  m_buf[MSG3_BUF_SIZE];
	char *m_alloc;
	long  m_allocSize;
	long  m_numChunks;
	char  m_ks;

	// for allowing the page cache
	bool  m_allowPageCache;

	bool  m_listsChecked;

	bool  m_hadCorruption;

	bool  m_hitDisk;
};

extern long g_numIOErrors;

#endif
