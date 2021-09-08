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

#ifndef REBALANCE_H
#define REBALANCE_H

#include "gb-include.h"
#include "types.h"
#include "RdbList.h"
#include "Msg4.h"
#include "Msg5.h"
#include "SafeBuf.h"

class Rebalance {

 public:

	Rebalance();

	char *getNeedsRebalance ( ) ;
	void rebalanceLoop ( ) ;
	void scanLoop ( ) ;
	bool scanRdb ( ) ;
	bool gotList ( ) ;
	bool saveRebalanceFile ( ) ;

	//bool m_inRebalanceLoop;
	long m_numForeignRecs;
	long long m_rebalanceCount;
	long long m_scannedCount;

	long m_rdbNum;
	collnum_t m_collnum;
	collnum_t m_lastCollnum;
	class Rdb *m_lastRdb;
	long m_lastPercent;
	char m_nextKey[MAX_KEY_BYTES];
	char m_endKey[MAX_KEY_BYTES];
	bool m_needsRebalanceValid;
	char m_needsRebalance;
	bool m_warnedUser;
	bool m_userApproved;
	bool m_isScanning;
	long m_blocked;
	bool m_allowSave;

	bool m_registered;
	RdbList m_list;
	SafeBuf m_posMetaList;
	SafeBuf m_negMetaList;
	Msg4 m_msg4a;
	Msg4 m_msg4b;
	Msg5 m_msg5;
};

extern Rebalance g_rebalance;

#endif
