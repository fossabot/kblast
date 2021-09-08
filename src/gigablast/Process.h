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

#ifndef _PROCESS_H_
#define _PROCESS_H_

#define NO_MODE   0
#define EXIT_MODE 1
#define SAVE_MODE 2
#define LOCK_MODE 3


#include "HttpRequest.h"
//#include "Msg28.h"

class Process {

 public:

	bool getFilesToCopy ( char *srcDir , class SafeBuf *buf ) ;
	bool checkFiles ( char *dir );

	// . the big save command
	// . does not save everything, just the important stuff
	bool save ( );

	// . this will save everything and exit
	// . urgent is true if we cored
	bool shutdown ( bool   urgent,
			void  *state = NULL,
			void (*callback) (void *state ) = NULL);

	bool checkNTPD();

	Process                 ( ) ;
	bool init               ( ) ;
	bool isAnyTreeSaving    ( ) ;
	bool save2              ( ) ;
	bool shutdown2          ( ) ;
	void disableTreeWrites  ( ) ;
	void enableTreeWrites   ( ) ;
	bool isRdbDumping       ( ) ;
	bool isRdbMerging       ( ) ;
	bool saveRdbTrees       ( bool useThread ) ;
	bool saveRdbMaps        ( bool useThread ) ;
	bool saveRdbCaches      ( bool useThread ) ;
	bool saveBlockingFiles1 ( ) ;
	bool saveBlockingFiles2 ( ) ;
	void resetAll           ( ) ;
	void resetPageCaches    ( ) ;
	double getLoadAvg	( );
	void resetLoadAvg	( );

	long long getTotalDocsIndexed();
	long long m_totalDocsIndexed;

	class Rdb *m_rdbs[32];
	long       m_numRdbs;
	bool       m_urgent;
	char       m_mode;
	long long  m_lastSaveTime;
	long long  m_processStartTime;
	bool       m_sentShutdownNote;
	bool       m_blockersNeedSave;
	bool       m_repairNeedsSave;
	long       m_try;
	long long  m_firstShutdownTime;

	void        *m_callbackState;
	void       (*m_callback) (void *state);

	// a timestamp for the sig alarm handler in Loop.cpp
	long long m_lastHeartbeatApprox;

	void callHeartbeat ();

	bool m_threadOut;

	bool m_suspendAutoSave;

	bool gotPower ( TcpSocket *s );
	bool        m_powerReqOut;
	bool        m_powerIsOn;
	long long   m_powerOffTime;
	HttpRequest m_r;
	//Msg28       m_msg28;
	bool        m_exiting;
	bool        m_calledSave;

	bool gotFanReply ( TcpSocket *s );
	void checkFanSwitch ( ) ;
	bool m_fanReqOut;
	float m_dataCtrTemp;
	float m_roofTemp;
	long  m_currentFanState;
	long  m_desiredFanState;
	float m_diskUsage;
	long long m_diskAvail;
	char m_swapEnabled;
};

extern Process g_process;

extern char *g_files[];

#endif
