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

// ad fetcher and parser

#ifndef _ADS_H_
#define _ADS_H_

#include "Url.h"
#include "SafeBuf.h"
//#include "CollectionRec.h"

#define MAX_BLOB_SIZE 2048

#define MAX_ADS          20
#define MAX_FEEDS        4
#define MAX_AD_QUERY_LEN 1024

#define PI_PRIMARY      0
#define PI_BACKUP       1
#define SS_PRIMARY      2
#define SS_BACKUP       3


class Ads {
 public:

	 Ads();		// constructor
	~Ads();		// destructor

        bool getAds ( char           *q         , 
                      long            qlen      ,
                      long            pageNum   ,
                      long            queryIP   ,
                      char           *coll      ,
                      void           *state     ,
                      void          (*callback)(void *state) );
	// . returns false if blocks, true otherwise
	// . sets g_errno on error
	// . "q" is the NULL terminated query
	// . "ip" is the ip of the user performing the query
		
	long  getNumPaidInclusionAds ( ) { return m_numAds[m_indexPIAds]; };
	long  getNumSkyscraperAds    ( ) { return m_numAds[m_indexSSAds]; };
        bool  hasAds                 ( ) { 
                return (bool)(m_numAds[m_indexPIAds] || m_numAds[m_indexSSAds]);
        };
        bool  gotAllRequests         () {
                return (bool)(m_numGotAds >= MAX_FEEDS);
        };

        void  printPaidInclusionAds(SafeBuf *sb, long numCharPerLine );
        void  printSkyscraperAds   (SafeBuf *sb, long numCharPerLine );

	// need to keep public so wrapper can call
        void  gotDoc( class TcpSocket *ts, long index );
        void  selectDisplayAds( );
	void   *m_state;
	void  (*m_callback)(void *state);

        //static void initCollAvailAds(              );
        //static void setAvailableAds ( char *coll   );
        //static long getAdFeedIndex  ( collnum_t cn );

 private:
        bool getAd ( long            index     ,
                     char           *cgi       ,
                     long            numAds    );
        void printAd( SafeBuf *sb    , 
                      char *url      , long urlLen,
                      char *title    , long titleLen,
                      char *desc     , long descLen,
                      char *site     , long siteLen,
                      long  numCharPerLine );

        char *m_coll;
        long  m_queryIP;      
        long  m_pageAds;
        long  m_feedIndex;
        long  m_indexPIAds;
        long  m_indexSSAds;
        long  m_numGotAds;
        bool  m_adSSSameasPI;
        bool  m_adBSSSameasBPI;
        CollectionRec *m_cr;

        char  m_q        [ MAX_AD_QUERY_LEN ];
        long  m_qlen;
	char *m_titles   [MAX_FEEDS][ MAX_ADS ];
	long  m_titlesLen[MAX_FEEDS][ MAX_ADS ];
	char *m_desc     [MAX_FEEDS][ MAX_ADS ];
	long  m_descLen  [MAX_FEEDS][ MAX_ADS ];
	char *m_sites    [MAX_FEEDS][ MAX_ADS ];
	long  m_sitesLen [MAX_FEEDS][ MAX_ADS ];
	char *m_urls     [MAX_FEEDS][ MAX_ADS ];
	long  m_urlsLen  [MAX_FEEDS][ MAX_ADS ];
	long  m_numAds   [MAX_FEEDS];
	char *m_buf      [MAX_FEEDS];
	long  m_bufLen   [MAX_FEEDS];
	//Url m_url      [MAX_FEEDS];
	Xml   m_xml      [MAX_FEEDS];

        //static long s_availableAds[16][MAX_AD_FEEDS];
        //static long s_numAvailableAds[16];
};

struct AdFeed {
        Ads  *m_ads;
        long  m_index;
};

#endif
