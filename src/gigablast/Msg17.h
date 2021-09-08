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

// . a distributed cache (borg) for caching search results (Msg40s)
// . each cache entry is essentially a serialized Msg40 class 
// . the Msg40 class contains a Msg39 class and a bunch of Msg20 classes
// . the Msg39 class holds the docIds, a Msg20 class holds a title/summary/...
// . the compressed Msg40 class should fit into MSG17_BUF_SIZE bytes of buffer
// . g_conf.m_pageCacheEnabled will turn on/off this cache

#ifndef _MSG17_H_
#define _MSG17_H_

// no use to make this bigger than UdpSlot's TMPBUFSIZE because
// these are based on real-time signals we can't alloc in a async signal
// handler so we have to rely on UdpSlot::m_tmpBuf to hold the compressed Msg40
#include "UdpSlot.h"
// there is no need to send the store request to the async server
//#define MSG17_BUF_SIZE (TMPBUFSIZE)
#define MSG17_BUF_SIZE (50*1024)

// . the cache the holds our compressed Msg40s
// . it is global so PageStats.cpp can display its stats
#define SEARCHRESULTS_CACHEID 0
// . this cache holds data generated by site link info
//#define SITELINKINFO_CACHEID  1
// . this cache holds site qualities
//#define SITEQUALITY_CACHEID  2
//#define ROOTVOTES_CACHEID 1
//#define SEORESULTS_CACHEID 1

// . should be the total number of caches listed above
//#define MAX_GENERIC_CACHES    3
#define MAX_GENERIC_CACHES    1

class Msg17 {

 public:

	Msg17();
	~Msg17();
	void reset();

	// register our request handle with g_udp server
	bool registerHandler ( );

	// . get this Msg40 from the distributed cache
	// . key is formed from Query's termIds, sc, dr,  and other things
	// . returns false if blocked, true otherwise
	// . sets errno on error
	// . call Msg17::wasFound() to see if your Msg40 was found
	//bool getFromCache ( class Msg40 *msg40 ,
	bool getFromCache ( char   cacheId ,
			    key_t  key ,
			    char **recPtr ,
			    long  *recSize ,
			    collnum_t collnum,
			    void  *state ,
			    void (* callback) (void *state) ,
			    long   niceness,
			    long   timeout );

	// make the key for retrieving or storing the serialized Msg40
	key_t makeKey ( class Msg40 *msg40 ) ;

	// call this after getFromCache() is done to see if it set your Msg40
	bool wasFound ( ) { return m_found; };

	// at what time was this entry cached?
	time_t getCachedTime      ( ) { return getTime() - m_cachedTimeDelta ;};
	time_t getCachedTimeDelta ( ) { return m_cachedTimeDelta ; };

	// . get the host responsible for caching the record with key "k"
	// . skips over dead hosts uniformly
	// . returns NULL if all hosts are dead! how can that happen?
	Host *getResponsibleHost ( key_t k , Hostdb *hostdb ) ;

	// . if you had to make your own Msg40 class because it wasn't cached
	//   then you should store it in the cache here
	// . returns false if blocked, true otherwise
	// . MAY set g_errno on error
	//bool storeInCache ( class Msg40 *msg40 );
	bool storeInCache ( char  cacheId ,
			    key_t key ,
			    char *recPtr ,
			    long  recSize ,
			    collnum_t collnum,
			    long  niceness ,
			    long  timeout );

	// keep public so wrappers can access
	bool gotReply ( class UdpSlot *slot , char *cbuf , long cbufSize ,
			bool includesCachedTime ) ;

	void *m_state;
	void  (* m_callback) (void *state );
	
	// request is just a key
	key_t   m_key ;
	char  **m_recPtr;
	long   *m_recSize;
	long    m_tmpRecSize;
	char    m_cacheId;

	// store compressed replies in here to avoid additional calls to malloc
	//char m_buf [ MSG17_BUF_SIZE ];
	char *m_cbuf;
	long  m_cbufSize;

	// did we find it in the cache
	bool m_found;

	time_t m_cachedTimeDelta;

	long m_niceness;

	// ptr to "it"
	class Msg40 *m_msg40;

	char m_request [ 12 + 1 + 8 ]; // key + flag + collnum_t
};

// allow our cache to be used by PageStats.cpp to display its stats
extern class RdbCache g_genericCache[MAX_GENERIC_CACHES];

extern long *g_genericCacheMaxAge[MAX_GENERIC_CACHES] ;

// smaller than the above cache, 10% of it. used for saving network
//extern class RdbCache g_genericCacheSmallLocal[MAX_GENERIC_CACHES];

// . compress option array, compressed implies allocated uncompressed buffer
//   which the caller is responsible for.  Uncompressed data will be stored in
//   the m_buf.
extern char g_genericCacheCompress[MAX_GENERIC_CACHES];

#endif