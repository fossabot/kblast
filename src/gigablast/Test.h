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

#ifndef _TEST_H_
#define _TEST_H_

#include "Msg4.h"
#include "Spider.h"
#include "HashTableX.h"

class Test {

 public:

	Test();

	char *getTestDir ( );

	//char *m_testDir;

	bool init ( ) ;
	void reset ( ) ;

	void removeFiles();
	void initTestRun();
	bool  injectLoop();

	void stopIt();

	// is test running now?
	bool m_isRunning;

	// how many urls we added to spiderdb via msg4
	long m_urlsAdded;

	long m_urlsIndexed;

	//bool m_spiderLinks;
	bool m_bypassMenuElimination;

	// are still in a loop adding urls to spiderdb via msg4?
	bool m_isAdding;

	long long m_testStartTime;
	
	// this is set to the errno if any error encounted during the test
	long m_errno ;

	// unique test id
	long m_runId ;

	char *m_coll ;

	SpiderRequest m_sreq;
	Msg4 m_msg4;

	// dedup table
	HashTableX m_dt;

	bool m_testSpiderEnabledSaved ;
	bool m_testParserEnabledSaved ;

	// file of urls in the test subdir is read into this buffer
	char *m_urlBuf ;
	char *m_urlEnd ;
	char *m_urlPtr ;
};

// the global class
extern Test g_test;

#endif
