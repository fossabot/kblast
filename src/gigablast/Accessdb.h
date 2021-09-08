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

#ifndef _ACCESSDB_H_
#define _ACCESSDB_H_

bool sendPageAccount ( class TcpSocket *s , class HttpRequest *r ) ;

#include "Rdb.h"
#include "Msg4.h"

class AccessRec {
 public:
	key128_t  m_key128;
	long      m_ip;
	long long m_fbId; // facebook id, 0 if none
};

class Accessdb {

 public:
	// reset m_rdb
	void reset() { m_rdb.reset(); };

	// initialize m_rdb
	bool init( );

	bool addColl ( char *coll, bool doVerify = false );

	Rdb *getRdb() { return &m_rdb; }

	key128_t makeKey1 ( long long now, long long widgetId64 ) ;
	key128_t makeKey2 ( long long now, long long widgetId64 ) ;

	bool addAccess ( class HttpRequest *r , long ip );

	bool registerHandler ( ) ;

	Rdb 	  m_rdb;
	
	long m_niceness;
	
	AccessRec m_arec[2];

	Msg4 m_msg4;
	bool m_msg4InUse;
};

extern class Accessdb g_accessdb;

#endif
