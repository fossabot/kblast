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

// . db of metalists used to delete a doc now

#ifndef _REVDB_H_
#define _REVDB_H_

#include "Rdb.h"
#include "Url.h"
#include "Conf.h"
#include "Xml.h"
#include "Titledb.h"

// new key format:
// . <docId>     - 38 bits
// . <delBit>    -  1 bit

// data format:
// . a metalist that is passed in to Msg4

class Revdb {

 public:

	// reset rdb
	void reset();

	bool verify ( char *coll );

	bool addColl ( char *coll, bool doVerify = true );

	// init m_rdb
	bool init ();

	// init secondary/rebuild revdb
	bool init2 ( long treeMem ) ;

	// like titledb basically
	key_t makeKey ( long long docId , bool del ) ;

	long long getDocId ( key_t *k );

	Rdb *getRdb() { return &m_rdb; };

	// holds binary format rev entries
	Rdb m_rdb;
};

extern class Revdb g_revdb;
extern class Revdb g_revdb2;

#endif
