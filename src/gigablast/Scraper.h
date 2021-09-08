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

#ifndef _SCRAPER_H_
#define _SCRAPER_H_

#include "Url.h"   // MAX_COLL_LEN
#include "XmlDoc.h"

#define MAX_SCRAPES_OUT 1

class Scraper {

 public:


	Scraper  ( );
	~Scraper ( );
 
	bool init ( );
	void wakeUp ( ) ;
	void gotPhrase ( ) ;
	//bool gotPages ( long i, TcpSocket *s ) ;
	//bool addedScrapedSites ( long i ) ;
	//bool gotUrlInfo ( long i ) ;
	//bool wrapItUp ( );
	bool indexedDoc ( );

	bool scrapeProCog();
	
	char m_coll[MAX_COLL_LEN];
	long m_numReceived;
	long m_numSent;

	long  m_qtype;
	//Url   m_urls[MAX_SCRAPES_OUT];
	//long  m_numUrls;

	//Msg9a m_msg9a[MAX_SCRAPES_OUT];

	//char  m_buf[50000];
	//char *m_bufPtr;
	//char *m_bufEnd;

	char  m_registered;

	XmlDoc m_xd;

	//long    m_numOutlinks;
	//Links   m_links;
	//MsgE    m_msge;
	//RdbList m_list;
	//Msg4    m_msg4;
};

extern class Scraper g_scraper;

#endif
