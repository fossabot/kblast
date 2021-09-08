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

#ifndef _TFNDB_H_
#define _TFNDB_H_

#include "Rdb.h"
#include "Url.h"
#include "Conf.h"
#include "Titledb.h"
#include "DiskPageCache.h"

// . we now use "tfndb" *only* to map docids to a title file #

// . a key in tfndb is 96 bits (compressed) and has this format:
// . <docId>       38 bits
// . <urlHash48>   48 bits
// . <tfn>          8 bits
// . <halfbit>      1 bit
// . <delbit>       1 bit

class Tfndb {

  public:

	// reset rdb
	void reset();

	bool verify ( char *coll );

	//bool addColl ( char *coll, bool doVerify = true );
	
	// set up our private rdb
	bool init ( );

	// init the rebuild/secondary rdb, used by PageRepair.cpp
	bool init2 ( long treeMem );

	Rdb *getRdb  ( ) { return &m_rdb; };

	key_t makeKey (long long docId, long long uh48,long tfn,bool isDelete);

	key_t makeMinKey ( long long docId ) {
		return makeKey ( docId ,0, 0 , true ); };

	key_t makeMaxKey ( long long docId ) {
		return makeKey ( docId , 0x0000ffffffffffffLL,0xff, false ); };

	long long getDocId ( key_t *k ) { 
		long long d = k->n1;
		d <<= 6;
		d |= k->n0>>58;
		return d;
	};

	long getTfn ( key_t *k ) { return ((k->n0) >>2) & 0xff; };

	long long getUrlHash48 ( key_t *k ) {
		return ((k->n0>>10) & 0x0000ffffffffffffLL); };

	DiskPageCache *getDiskPageCache() { return &m_pc; };

  private:

	// this rdb holds urls waiting to be spidered or being spidered
	Rdb m_rdb;

	DiskPageCache m_pc;

};

extern class Tfndb g_tfndb;
extern class Tfndb g_tfndb2;

#endif
