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

#ifndef GBINJECT_H
#define GBINJECT_H    

bool sendPageInject ( class TcpSocket *s, class HttpRequest *hr );

#include "XmlDoc.h"
#include "Users.h"
#include "Parms.h" // GigablastRequest

class Msg7 {

public:

	GigablastRequest m_gr;
	SafeBuf m_injectUrlBuf;
	bool m_firstTime;
	char *m_start;
	bool  m_fixMe;
	long  m_injectCount;

	bool       m_needsSet;
	XmlDoc     m_xd;
	TcpSocket *m_socket;
	SafeBuf    m_sb;
	char m_round;
	char m_useAhrefs;
	HashTableX m_linkDedupTable;

	void *m_state;
	void (* m_callback )(void *state);

	//long m_crawlbotAPI;

	Msg7 ();
	~Msg7 ();

	bool scrapeQuery ( );

	bool inject ( void *state ,
		      void (*callback)(void *state) );

};

extern bool g_inPageInject;

#endif
