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

// Monitordb - a semi-permanent monitor for storing seo safebufs

// . Format of a 12-byte key in monitordb
// .
// . HHHHHHHH HHHHHHHH HHHHHHHH HHHHHHHH H = hash of the url
// . HHHHHHHH HHHHHHHH HHHHHHHH HHHHHHHH H = hash of the url
// . tttttttt 00000000 00000000 00000000 t = type of object

#ifndef _MONITORDB_H_
#define _MONITORDB_H_

// 12 byte key size
#define MONITORDBKS sizeof(key96_t)

#include "Rdb.h"
#include "DiskPageCache.h"

class Monitordb {
 public:
	void reset();

	bool init    ( );
	bool init2 ( long treeMem );
	bool verify  ( char *coll );
	bool addColl ( char *coll, bool doVerify = true );


	Rdb           *getRdb()           { return &m_rdb; };

	DiskPageCache *getDiskPageMonitor () { return &m_pc; };
	DiskPageCache m_pc;

 private:
	Rdb           m_rdb;

};

extern class Monitordb g_monitordb;

#endif
