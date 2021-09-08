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

#include "Conf.h"
#include "Dns.h"
#include "HttpServer.h"
#include "HashTableT.h"
#include "Loop.h"
//#include "Links.h"
#include "iana_charset.h"
#include <sys/resource.h>  // setrlimit

struct StateBD {
	//Url m_u1,m_u2;
	//Url *m_u;
	char *m_u1,*m_u2;
	char *m_u;
	char *m_buf1;
	long m_buf1Len;
	long m_buf1MaxLen;
	long m_numUrlDocsSent;
	long m_numUrlDocsReceived;
	SafeBuf m_injectUrl;
};

struct StateBD2 {
	StateBD *m_st;
	long m_numRedirects;
	//Url m_url;
	char *m_url;
};

class Blaster {
 public:
	Blaster();
	~Blaster();
	
	void reset();

	bool init();

	void runBlaster(char *file1,char *file2,
			long maxNumThreads, long wait, 
			bool isLogFile,
			bool verbose,bool justDisplay,
			bool useProxy,
			bool injectUrlWithLinks = false ,
			bool injectUrl = false );

	void startBlastering();

	void freeStateBD(StateBD *st);

	void gotDoc1(void *state,TcpSocket *s);

	void gotDoc2(void *state,TcpSocket *s);

	void gotDoc3 ( void *state, TcpSocket *s);

	void gotDoc4 ( void *state, TcpSocket *s);

	void processLogFile(void *state);

	bool m_doInjection;
	bool m_doInjectionWithLinks;

 protected:
	long  m_maxNumThreads;
	long  m_launched;
	char *m_buf1;
	long  m_bufSize1;
	char *m_buf2;
	long m_bufSize2;
	char *m_p1;
	char *m_p1end;
	char *m_p2;
	char *m_p2end;
	long  m_totalUrls;
	long  m_totalDone;
	bool  m_portSwitch;
	long  m_wait;
	bool  m_justDisplay;
	bool  m_useProxy;
	bool  m_verbose;
	bool  m_isLogFile;
	long long m_startTime;
	long m_numUrls;
	char **m_lineStart;
	bool m_blasterDiff;
	bool m_print;
};

extern Blaster g_blaster;
