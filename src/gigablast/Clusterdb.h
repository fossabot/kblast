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

// . a clusterRec now no longer exists, per se
// . it is the same thing as the key of the titleRec in titledb
// . titleRecs now contain the site and content hashes in the low bits
//   of their key. 
// . this allows us to store much cluster info in Titledb's RdbMap
// . so to get cluster info, just read in the titleRec, you do not even
//   need to uncompress it, just get the info from its key
// . we still use the cache here, however, to cache the keys (clusterRecs)
// . later, i may have to do some fancy footwork if we want to store all
//   clusterRecs (titleKeys) in memory.
// . TODO: what if stored file offsets in tfndb, too, then titledb RdbMap
//   would not be necessary?
//
// . clusterdb will now serve to help do fast site clustering by retaining
//   docids and site hashes in memory
//
//   00000000 00000000 0000000d dddddddd  d = docid
//   dddddddd dddddddd dddddddd dddddfll  f = family filter bit
//   llllssss ssssssss ssssssss sssssshz  q = year quarter bits
//                                        l = language bits
//   					  s = site hash
//   					  h = half bit
//   					  z = del bit

#ifndef _CLUSTERDB_H_
#define _CLUSTERDB_H_

//#include "TitleRec.h"  // SAMPLE_VECTOR_SIZE
#include "Rdb.h"
#include "Url.h"
#include "Conf.h"
#include "Titledb.h"
#include "DiskPageCache.h"

// these are now just TitleRec keys
#define CLUSTER_REC_SIZE (sizeof(key_t))
// this now includes the gigabit vector
#define VECTOR_REC_SIZE (sizeof(key_t)+SAMPLE_VECTOR_SIZE+GIGABIT_VECTOR_SIZE)

class Clusterdb {

  public:

	// reset rdb
	void reset();
	
	// set up our private rdb
	bool init ( );

	// init the rebuild/secondary rdb, used by PageRepair.cpp
	bool init2 ( long treeMem );

	bool verify ( char *coll );

	bool addColl ( char *coll, bool doVerify = true );

	Rdb *getRdb  ( ) { return &m_rdb; };

	// make the cluster rec
	void makeRecFromTitleRec ( char     *rec,
				   class TitleRec *titleRec,
				   bool      isDelKey );

	// make the cluster rec
	void makeRecFromTitleRecKey ( char *rec,
				      char *key,
				      bool  isDelKey );

	// make the cluster rec key
	key_t makeClusterRecKey ( long long     docId,
				  bool          familyFilter,
				  uint8_t       languageBits,
				  long          siteHash,
				  bool          isDelKey,
				  bool          isHalfKey = false );

	key_t makeFirstClusterRecKey ( long long docId ) {
		return makeClusterRecKey ( docId, false, 0, 0, true ); };
	key_t makeLastClusterRecKey  ( long long docId ) {
		return makeClusterRecKey ( docId, true, 0xff, 0xffffffff,
					   false, true ); };

	// convert a titlerec key into a clusterec key
	key_t convertTitleRecKey ( key_t titleKey );

	/*
	unsigned long getGroupId ( long long docId ) {
		return g_titledb.getGroupId ( docId ); };
		
	// cluster rec should be stored on same host as titleRec with the
	// same docId that this key contains
	unsigned long getGroupIdFromKey ( key_t *key ) {
		return g_titledb.getGroupId ( getDocId ( *key ) ); };
	*/

	// NOTE: THESE NOW USE THE REAL CLUSTERDB REC
	// // docId occupies the most significant bytes of the key
	// now docId occupies the bits after the first 23
	long long getDocId ( void *k ) {
		//long long docId = (k.n0) >> (32+24);
		//docId |= ( ((unsigned long long)(k.n1)) << 8 );
		long long docId = (((key_t *)k)->n0) >> 35;
		docId |= ( ((unsigned long long)(((key_t *)k)->n1)) << 29 );
		return docId;
	};

	//long long getDocId ( char *r ) {
	//	return getDocId(*(key_t*)r);
	//}

	unsigned long getSiteHash26 ( char *r ) {
		//return g_titledb.getSiteHash ( (key_t *)r ); };
		return ((unsigned long)(((key_t*)r)->n0 >> 2) & 0x03FFFFFF);
	};

	unsigned long hasAdultContent ( char *r ) {
		//return g_titledb.hasAdultContent ( *(key_t *)r ); };
		return ((unsigned long)(((key_t*)r)->n0 >> 34) & 0x00000001);
	};

	unsigned char getLanguage ( char *r ) {
		return ((unsigned char)(((key_t*)r)->n0 >> 28) & 0x0000003F);
	}

	// NOTE: THESE USE THE OLD "CLUSTERDB" REC GENERATED BY MSG22 (VECTOR)
	//unsigned long getContentHash ( char *r ) {
	//	return g_titledb.getContentHash ( *(key_t *)r ); };

	char getFamilyFilter ( char *r ) {
		if ( (*(long long *)r) & 0x0000000400000000LL ) return 1;
		return 0;
	};


	//unsigned long hasAdultWords   ( char *r ) {
	//	return g_titledb.hasAdultWords ( *(key_t *)r ); };

	//unsigned long hasAdultCategory ( char *r ) {
	//	return g_titledb.hasAdultCategory ( *(key_t *)r ); };

	//unsigned char getLanguageFromVector ( char *r ) {
	//	return 0;
	//}

	// the random sample vector
	/*
	void getSampleVector     ( char *vec  , 
				   class Doc *doc, 
				   char *coll ,
				   long  collLen ,
				   long niceness = 0 );
	*/
	//void getSampleVector     ( char *vec  , class TermTable *table );
	char getSampleSimilarity ( char *vec0 , char *vec1 , long size );
	// get the content vector from a cluster rec (used by Msg38.cpp)
	//char *getSampleVector  ( char *rec ) { return rec + sizeof(key_t); };

	//char *getGigabitVector    ( char *rec ) { 
	//	return rec + sizeof(key_t) + SAMPLE_VECTOR_SIZE ; };
	//char getGigabitSimilarity ( char *vec0 , char *vec1 ,
	//			    long *qtable , long numSlots ) ;

	DiskPageCache *getDiskPageCache() { return &m_pc; };

  private:

	// this rdb holds urls waiting to be spidered or being spidered
	Rdb m_rdb;

	DiskPageCache m_pc;
};

extern class Clusterdb g_clusterdb;
extern class Clusterdb g_clusterdb2;

#endif
