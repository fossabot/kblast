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

#ifndef CRAWLBOT_H
#define CRAWLBOT_H

bool printCrawlDetailsInJson ( class SafeBuf *sb , class CollectionRec *cx ) ;

bool printCrawlDetailsInJson ( class SafeBuf *sb , class CollectionRec *cx, int version ) ;

// values for the diffbot dropdown
/*
#define DBA_NONE 0
#define DBA_ALL  1
#define DBA_ARTICLE_FORCE 2
#define DBA_ARTICLE_AUTO  3
#define DBA_PRODUCT_FORCE 4
#define DBA_PRODUCT_AUTO 5
#define DBA_IMAGE_FORCE 6
#define DBA_IMAGE_AUTO 7
#define DBA_FRONTPAGE_FORCE 8
#define DBA_FRONTPAGE_AUTO 9

// add new fields to END of list since i think we store the
// field we use as a number in the coll.conf, starting at 0
extern char *g_diffbotFields [];
*/

bool sendPageCrawlbot ( class TcpSocket *s , class HttpRequest *hr );

//bool handleDiffbotRequest ( TcpSocket *s , HttpRequest *hr ) ;
bool sendBackDump ( class TcpSocket *s, class HttpRequest *hr );

bool getSpiderRequestMetaList ( char *doc, 
				class SafeBuf *listBuf, 
				bool spiderLinks,
				class CollectionRec *cr);

#endif
