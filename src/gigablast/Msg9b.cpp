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

#include "gb-include.h"

#include "Msg9b.h"


// . returns false if blocked, true otherwise
// . sets g_errno on error
// . numCatids is an array of longs, each the number of catids for
//   the corrisponding url, length equal to number of urls
// . catids is an array of longs with the catids for the urls
bool Msg9b::addCatRecs ( char *urls        ,
			 char *coll        , 
			 long  collLen     ,
			 long  filenum     ,
			 void *state       ,
			 void (*callback)(void *state) ,
			 unsigned char *numCatids   ,
			 long *catids      ,
			 long niceness,
			 bool deleteRecs) {
	//long dbIndex = RDB_CATDB;
	// use default collection
	//coll    = g_conf.m_dirColl;
	//collLen = gbstrlen(coll);
	// catdb uses a dummy collection now, should not be looked at
	coll = "catdb";
	collLen = 5;
	
	// warning
	//if ( ! coll ) log(LOG_LOGIC,"net: NULL collection. msg9b.");
	// reset/free our list of siteRecs
	m_list.set ( NULL  , 
		     0     , 
		     NULL  ,
		     0     , 
		     -1    ,  // fixedDataSize
		     true  ,  // ownData?
		     false ); // use half keys?
	// ensure NULL terminated
	if ( coll[collLen] ) {
		log(LOG_LOGIC,"admin: Collection not NULL terminated.");
		char *xx = NULL; *xx = 0;
	}
	// . SiteRec bitmap is given in SiteRec.cpp
	// . key(12) + dataSize(4) + filenum(4) + url + ?NULL?
	// . assume about 15 bytes per url
	// . hopefully this will be big enough to prevent many reallocs
	long usize = gbstrlen(urls);
	long initSize = ((usize / 15)*(12+4+4+1) + usize);
	if ( ! m_list.growList ( initSize ) ) {
		g_errno = ENOMEM;
		log("admin: Failed to allocate %li bytes to hold "
		    "urls to add to tagdb.", initSize);
		return true;
	}
	// loop over all urls in "urls" buffer
	char *p = urls;
	// stop when we hit the NULL at the end of "urls"
	long k = 0;
	long c = 0;
	long lastk = 0;
	//long firstPosIds = -1;
	while ( *p ) {
		if (  *p != '\n' ||  lastk != k   ) {
			log (LOG_WARN, "Msg9b: FOUND BAD URL IN LIST AT %li, "
				       "EXITING", k );
			return true;
		}
		lastk++;
		// skip initial spaces
		char *lastp = p;
		while ( is_wspace_a (*p) ) p++;
		if (  p - lastp > 1 ) {
			log(LOG_WARN, "Msg9b: SKIPPED TWO SPACES IN A ROW AT "
				      " %li, EXITING", k );
			//return true;
		}
		// break if end
		if ( ! *p )
			break;
		// . if comment, skip until \n
		// . also, skip if its not alnum
		// . this is really assuming a format of one url per line,
		//   so a space separated list of urls may not work here
		if ( ! is_alnum_a (*p) ) { // *p == '#' ) { 
			while ( *p && *p != '\n' ) p++;
			// skip over the \n
			p++;
			// try the next line
			continue;
		}
		// find end of this string of non-spaces
		char *e = p; while ( *e && ! is_wspace_a (*e) ) e++;
		// . set the url
		// . but don't add the "www."
		// . watch out for
		//   http://twitter.com/#!/ronpaul to http://www.twitter.com/
		//   so do not strip # hashtags
		Url site;
		site.set ( p , e - p , false ); // addwww?
		// normalize the url
		g_catdb.normalizeUrl(&site, &site);

		// sanity
		if ( numCatids[k] > MAX_CATIDS ) { char *xx=NULL;*xx=0; }

		// make a siteRec from this url
		CatRec sr;
		// returns false and sets g_errno on error
		if ( ! sr.set ( &site, filenum, &catids[c], numCatids[k] ) )
			return true;
		// add url to our list
		// extract the record itself (SiteRec::m_rec/m_recSize)
		char *data     = sr.getData ();
		long  dataSize = sr.getDataSize ();
		key_t key;
		// sanity test
		CatRec cr2;
		if ( ! cr2.set ( NULL , sr.getData(), sr.getDataSize(),false)){
			char *xx=NULL;*xx=0; }
		// debug when generating catdb
		//char *x = p;
		//for ( ; x<e ; x++ ) {
		//	if ( x[0] == '#' )
		//		log("hey");
		//}
		if ( numCatids[k] == 0 )
			key = g_catdb.makeKey(&site, true);
		else
			key = g_catdb.makeKey(&site, false);

		// if it's an ip then ensure only last # can be 0
		//if ( site.isIp() &&  (site.getIp() & 0x00ff0000) == 0 )
		//	goto skip;
		// . add site rec to our list
		// . returns false and sets g_errno on error
		if ( numCatids[k] == 0 ) {
			if ( !m_list.addRecord(key, 0, NULL) )
				return true;
		}
		else if ( ! m_list.addRecord ( key, dataSize, data ) )
			return true;

		/*
		// debug point
		SafeBuf sb;
		//sb.safeMemcpy(p , e-p );
		sb.safeStrcpy(sr.m_url);
		sb.safePrintf(" ");
		for ( long i = 0 ; i < numCatids[k] ; i++ )
			sb.safePrintf ( "%li " , catids[c+i] );
		log("catdb: adding key=%s url=%s",
		    KEYSTR(&key,12),
		    sb.getBufStart());
		*/

		// debug
		//log("gencat: adding url=%s",sr.m_url);

		//skip:
		// now advance p to e
		p = e;
	
		c += numCatids[k];
		k++;
		
		QUICKPOLL((niceness));
	}
	log ( LOG_INFO, "Msg9b: %li sites and %li links added. "
	      "listSize=%li", k , c , m_list.m_listSize );
	// . now add the m_list to tagdb using msg1
	// . use high priority (niceness of 0)
	// . i raised niceness from 0 to 1 so multicast does not use the
	//   small UdpSlot::m_tmpBuf... might have a big file...
	return m_msg1.addList ( &m_list, RDB_CATDB, 
				(collnum_t)0 ,
				state , callback ,
				false , // force local?
				niceness     ); // niceness 
}
