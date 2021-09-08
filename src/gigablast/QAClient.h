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

#ifndef QACLIENT_H___
#define QACLIENT_H___

//#include "HttpServer.h"
#include "Url.h"
#include "Titledb.h"

typedef void (*qatest_callback_t)(void *);
typedef void (*httpdoc_callback_t)(void *, class HttpDoc *);
#define MAX_QA_TESTS 2000

// keep track of everything involved with getting a doc by http
class HttpDoc {
public:
	HttpDoc();
	~HttpDoc();

	void reset();
	void            get(void *state, httpdoc_callback_t callback);
	Url 		m_url;
	bool 		m_done;
	long 		m_errno;
	long long 	m_startTime;
	long long 	m_elapsed;

	char           *m_buf;
	bool            m_ownBuf;
	long     	m_bufSize;

	char 	       *m_content;
	long     	m_contentLen;
	short           m_httpStatus;
	short           m_charset;
	void           *m_state;
	httpdoc_callback_t m_callback;
};

class QATest {
public:
	void reset();
	// Subclasses must define these funtions
	virtual ~QATest();
	virtual void startTest() = 0;
};

class QADiffTest: public QATest {
public:
	void reset() {
		m_state = NULL;
		m_callback = NULL;
		m_doc1.reset();
		m_doc2.reset();
		m_desc[0] = '\0';
	};
	bool set(char *desc,char *u1, char *u2, void*, qatest_callback_t);
	~QADiffTest(){reset();};
	void startTest();
	void processResults();

	HttpDoc m_doc1;
	HttpDoc m_doc2;

	// should these go in base class?
	void *m_state;
	qatest_callback_t m_callback;
	char m_desc[256];
private:
	// diff m_doc1 and m_doc2 using unix diff cmd
	void fileDiff();
	// diff m_doc1 and m_doc2 using xml tag diff
	void xmlDiff();
};

class QAClient {
	
public:
	QAClient();
	~QAClient();
	bool init(char *s1=NULL, char *s2=NULL, 
		  char *parserUrls=NULL, char *queryUrls=NULL);
	bool runTests();
	void runNextTest();
private:
	Url m_server1 ;
	Url m_server2 ;
	
	QATest *m_curTest;
	// for mnew/mdelete
	int m_curTestSize;

	char **m_parserUrls;
	long m_numParserUrls;

	char **m_queries;
	long m_numQueries;
	
	long m_numTests;
	long m_nextTest;

	char  *m_pbuf;
	long   m_pbufSize;
	char **m_pbufPtr;
	long   m_pbufPtrSize;
	char  *m_qbuf;
	long   m_qbufSize;
	char **m_qbufPtr;
	long   m_qbufPtrSize;
};

#endif 
