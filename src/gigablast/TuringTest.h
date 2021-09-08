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

#ifndef _TURINGTEST_H_
#define _TURINGTEST_H_

#include "gb-include.h"
#include "TcpServer.h"
#include "HashTable.h"

class TuringTest {
 public:
	TuringTest();
	~TuringTest();
	static const long TMAX_HEIGHT = 19;
	static const long TMAX_WIDTH  = 15;
	static const long MASK  = 4095;
	// turing test routines

	//if they don't have permission, print the turing test
	//otherwise don't print anything.
	bool isHuman( HttpRequest *r);
	bool printTest ( SafeBuf* sb );

protected:
	HashTable m_answers;
	bool      m_tinit;
	long      m_nextQuestion;
	char      m_buf[26][TMAX_HEIGHT][TMAX_WIDTH];
};

extern TuringTest g_turingTest;
#endif
