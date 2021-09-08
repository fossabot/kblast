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

#include "SearchInput.h"
#include "Parms.h"         // g_parms
//#include "CollectionRec.h" // cr
#include "Pages.h"         // g_msg
#include "LanguageIdentifier.h"
#include "CountryCode.h"
#include "geo_ip_table.h"
#include "Users.h"
#include "Address.h" // getLatLonFromUserInput
#include "Timedb.h"
#include "PageResults.h"

char getFormatFromRequest ( class HttpRequest *hr ) ;

SearchInput::SearchInput() {
	reset();
}
SearchInput::~SearchInput() {
	reset();
}
void SearchInput::reset ( ) {
}

//void SearchInput::setToDefaults ( CollectionRec *cr , long niceness ) {
void SearchInput::clear ( long niceness ) {
	// reset it first
	reset();
	// set all to 0 just to avoid any inconsistencies
	long size = (char *)&m_END_TEST - (char *)&m_START;
	memset ( this , 0x00 , size );
	m_sbuf1.reset();
	m_sbuf2.reset();
	m_sbuf3.reset();

	// set these
	m_numLinesInSummary  = 2;
	m_docsWanted         = 10;
	m_boolFlag           = 2;
	m_maxQueryTerms      = 1000;
	m_niceness           = niceness;

	//m_defaultSortLanguageLen = 0;
}


// . make a key for caching the search results page based on this input
// . do not use all vars, like the m_*ToDisplay should not be included
key_t SearchInput::makeKey ( ) {
	// hash the query
	long       n       = m_q.getNumTerms  ();
	long long *termIds = m_q.getTermIds   ();
	char      *signs   = m_q.getTermSigns ();
	key_t k;
	k.n1 = 0;
	k.n0 = hash64 ( (char *)termIds , n * sizeof(long long) );
	k.n0 = hash64 ( (char *)signs   , n , k.n0 );
	// user defined weights, for weighting each query term separately
	for ( long i = 0 ; i < n ; i++ ) {
		k.n0 = hash64 ((char *)&m_q.m_qterms[i].m_userWeight,4, k.n0);
		k.n0 = hash64 ((char *)&m_q.m_qterms[i].m_userType  ,1, k.n0);
	}
	// space separated, NULL terminated, list of meta tag names to display
	if ( m_displayMetas          ) 
		k.n0 = hash64b ( m_displayMetas          , k.n0 );
	// name of collection in external cluster to get titleRecs for 
	// related pages from
	//if ( m_rp_getExternalPages && m_rp_externalColl )
	//	k.n0 = hash64b ( m_rp_externalColl , k.n0 );
	// collection e import from
	//if ( m_importColl )
	//	k.n0 = hash64b ( m_importColl , k.n0 );
	// the special query parm
	//if ( m_sq && m_sqLen > 0 )
	//	k.n0 = hash64 ( m_sq , m_sqLen , k.n0 );
	//if ( m_noDocIds && m_noDocIdsLen )
	//	k.n0 = hash64 ( m_noDocIds , m_noDocIdsLen , k.n0 );
	//if ( m_noSiteIds && m_noSiteIdsLen )
	//	k.n0 = hash64 ( m_noSiteIds , m_noSiteIdsLen , k.n0 );

	// no need to hash these again separately, they are in between 
	// m_START and m_END_HASH
	// language
	//if ( m_language )
	//	k.n0 = hash64 ( m_language , k.n0 );
	//if ( m_gblang )
	//	k.n0 = hash64 ( m_gblang , k.n0 );
	// . now include the hash of the search parameters
	// . nnot incuding m_docsToScanForTopics since since we got TopicGroups
	char *a = ((char *)&m_START) + 4 ; // msg40->m_dpf;
	char *b =  (char *)&m_END_HASH   ; // msg40->m_topicGroups;
	long size = b - a; 
	// push and flush some parms that should not contribute
	//long save1 = m_refs_numToDisplay;
	//long save2 = m_rp_numToDisplay;
	//long save3 = m_numTopicsToDisplay;
	//m_refs_numToDisplay  = 0;
	//m_rp_numToDisplay    = 0;
	//m_numTopicsToDisplay = 0;
	// and hash it all up
	k.n0 = hash64 ( a , size , k.n0 );
	// and pop out the parms that did not contribute
	//m_refs_numToDisplay  = save1;
	//m_rp_numToDisplay    = save2;
	//m_numTopicsToDisplay = save3;
	// hash each topic group
	for ( long i = 0 ; i < m_numTopicGroups ; i++ ) {
		TopicGroup *t = &m_topicGroups[i];
		//k.n0 = hash64 ( t->m_numTopics           , k.n0 );
		k.n0 = hash64 ( t->m_maxTopics           , k.n0 );
		k.n0 = hash64 ( t->m_docsToScanForTopics , k.n0 );
		k.n0 = hash64 ( t->m_minTopicScore       , k.n0 );
		k.n0 = hash64 ( t->m_maxWordsPerTopic    , k.n0 );
		k.n0 = hash64b( t->m_meta                , k.n0 );
		k.n0 = hash64 ( t->m_delimeter           , k.n0 );
		k.n0 = hash64 ( t->m_useIdfForTopics     , k.n0 );
		k.n0 = hash64 ( t->m_dedup               , k.n0 );
	}
	// . boolean queries have operators (AND OR NOT ( ) ) that we need
	//   to consider in this hash as well. so
	// . so just hash the whole damn query
	if ( m_q.m_isBoolean ) {
		char *q    = m_q.getQuery();
		long  qlen = m_q.getQueryLen();
		k.n0 = hash64 ( q , qlen , k.n0 );
	}

	// Language stuff
	//k.n0 = hash64(m_defaultSortLanguage, m_defaultSortLanguageLen, k.n0);
	//k.n0 = hash64(m_defaultSortCountry , m_defaultSortCountryLen , k.n0);

	// debug
	//logf(LOG_DEBUG,"query: q=%s k.n0=%llu",m_q.getQuery(),k.n0);

	//Msg1aParms* m1p = msg40->getReferenceParms();
	//if( m1p ) {
	//	k.n0=hash64(((char*)m1p)+sizeof(long), 
	//		    sizeof(Msg1aParms)-8,k.n0);
	//}
	return k;
}

void SearchInput::test ( ) {
	// set all to 0 just to avoid any inconsistencies
	char *a = ((char *)&m_START) + 4 ; // msg40->m_dpf;
	char *b =  (char *)&m_END_TEST;
	long size = b - a;
	memset ( a , 0x00 , size );
	// loop through all possible cgi parms to set SearchInput
	for ( long i = 0 ; i < g_parms.m_numSearchParms ; i++ ) {
		Parm *m = g_parms.m_searchParms[i];
		char *x = (char *)this + m->m_off;
		if ( m->m_type != TYPE_BOOL ) *(long *)x = 0xffffffff;
		else                          *(char *)x = 0xff;
	}
	// ensure we're all zeros now!
	long fix = a - (char *)this;
	unsigned char *p = (unsigned char *)a;
	for ( long i = 0 ; i < size ; i++ ) {
		if ( p[i] == 0xff ) continue;
		// find it
		long off = i + fix;
		char *name = NULL; // "unknown";
		for ( long k = 0 ; k < g_parms.m_numSearchParms ; k++ ) {
			Parm *m = g_parms.m_searchParms[k];
			if ( m->m_off != off ) continue;
			name = m->m_title;
			break;
		}
		if ( ! name ) continue;
		log("query: Got uncovered SearchInput parm at offset "
		    "%li in SearchInput. name=%s.",off,name);
	}
}

void SearchInput::copy ( class SearchInput *si ) {
	memcpy ( (char *)this , (char *)si , sizeof(SearchInput) );
}

class SearchInput *g_si = NULL;

bool SearchInput::set ( TcpSocket *sock , HttpRequest *r ) { //, Query *q ) {

	// store list of collection #'s to search here. usually just one.
	m_collnumBuf.reset();

	// zero out everything, set niceness to 0
	clear ( 0 ) ;

	// save it now
	m_sock = sock;

	// still his buffer. m_hr will free the stuff, but "r" can
	// still access it for the time being, and not free it
	m_hr.stealBuf ( r );

	char *coll = g_collectiondb.getDefaultColl ( r );

	//////
	//
	// build "m_collnumBuf" to consist of all the collnums we should
	// be searching.
	//
	///////

	m_firstCollnum = -1;
	// set this to the collrec of the first valid collnum we encounter
	CollectionRec *cr = NULL;
	// now convert list of space-separated coll names into list of collnums
	char *p = coll;
	// if no collection list was specified look for "token=" and
	// use those to make collections. hack for diffbot.
	char *token = r->getString("token",NULL);
	// find all collections under this token
	for ( long i = 0 ; i < g_collectiondb.m_numRecs ; i++ ) {
		// must not have a "&c="
		if ( p ) break;
		// must have a "&token="
		if ( ! token ) break;
		// skip if empty
		CollectionRec *tmpcr = g_collectiondb.m_recs[i];
		if ( ! tmpcr ) continue;
		// skip if does not match token
		if ( strcmp(token,tmpcr->m_diffbotToken.getBufStart()) ) 
			continue;
		// . we got a match
		// . set initial junk
		if ( ! cr ) {
			cr = tmpcr;
			m_firstCollnum = tmpcr->m_collnum;
		}
		// save the collection #
		if ( ! m_collnumBuf.safeMemcpy ( &tmpcr->m_collnum, 
						 sizeof(collnum_t) ) )
			return false;
	}

	// if we had a "&c=..." in the GET request process that
	if ( p ) {
	loop:
		char *end = p;
		for ( ; *end && ! is_wspace_a(*end) ; end++ );
		// temp null
		char c = *end;
		*end = '\0';
		CollectionRec *tmpcr = g_collectiondb.getRec ( p );
		// set defaults from the FIRST one
		if ( tmpcr && ! cr ) {
			cr = tmpcr;
			m_firstCollnum = tmpcr->m_collnum;
		}
		if ( ! tmpcr ) { 
			g_errno = ENOCOLLREC;
			log("query: missing collection %s",p);
			g_msg = " (error: no such collection)";		
			return false;
		}
		// add to our list
		if (!m_collnumBuf.safeMemcpy(&cr->m_collnum,sizeof(collnum_t)))
			return false;
		// restore the \0 character we wrote in there
		*end = c;
		// advance
		p = end;
		// skip to next collection name if there is one
		while ( *p && is_wspace_a(*p) ) p++; 
		// now add it's collection # to m_collnumBuf if there
		if ( *p ) goto loop;
	}

	/////
	//
	// END BUILDING m_collnumBuf
	//
	/////


	// save the collrec
	m_cr = cr;

	// must have had one
	if ( ! cr ) {
		log("si: collection does not exist");
		g_errno = ENOCOLLREC;
		return false;
	}

	// and set from the http request. will set m_coll, etc.
	g_parms.setToDefault ( (char *)this , OBJ_SI );


	///////
	//
	// set defaults of some things based on format language
	//
	//////

	// get the format. "xml" "html" "json" --> FORMAT_HTML, FORMAT_CSV ...
	char tmpFormat = getFormatFromRequest ( &m_hr );
	// now override automatic defaults for special cases
	if ( tmpFormat != FORMAT_HTML ) {
		m_familyFilter            = 0;
		m_numTopicsToDisplay      = 0;
		m_doQueryHighlighting     = 0;
		m_spellCheck              = 0;
		m_getDocIdScoringInfo = false;
	}
	// if they have a list of sites...
	else if ( m_sites && m_sites[0] ) {
		m_doSiteClustering        = false;
		m_ipRestrictForTopics     = false;
	}




	// and set from the http request. will set m_coll, etc.
	g_parms.setFromRequest ( &m_hr , sock , cr , (char *)this , OBJ_SI );


	m_coll = coll;

	// it sets m_formatStr above, but we gotta set this...
	m_format = tmpFormat;


	//////
	//
	// fix some parms
	//
	//////

	// set m_isAdmin to zero if no correct ip or password
	if ( ! g_conf.isRootAdmin ( sock , &m_hr ) ) m_isAdmin = 0;


	//
	// TODO: use Parms.cpp defaults
	//
	TopicGroup *tg = &m_topicGroups[0];

	//
	//
	// gigabits
	//
	//
	tg->m_numTopics = 50;
	tg->m_maxTopics = 50;
	tg->m_docsToScanForTopics = m_docsToScanForTopics;
	tg->m_minTopicScore = 0;
	tg->m_maxWordsPerTopic = 6;
	tg->m_meta[0] = '\0';
	tg->m_delimeter = '\0';
	tg->m_useIdfForTopics = false;
	tg->m_dedup = true;
	// need to be on at least 2 pages!
	tg->m_minDocCount = 2;
	tg->m_ipRestrict = true;
	tg->m_dedupSamplePercent = 80;
	tg->m_topicRemoveOverlaps = true;
	tg->m_topicSampleSize = 4096;
	// max sequential punct chars allowedin a topic
	tg->m_topicMaxPunctLen = 1;
	m_numTopicGroups = 1;

	//////////////////////////////////////
	//
	// transform input into classes
	//
	//////////////////////////////////////

	// allow for "qlang" if still don't have it
	//long gglen2;
	//char *gg2 = r->getString ( "qlang" , &gglen2 , NULL );
	//if ( m_gblang == 0 && gg2 && gglen2 > 1 )
	//	m_gblang = getLanguageFromAbbr(gg2);
	
	// fix query by removing lang:xx from ask.com queries
	//char *end = m_query + m_queryLen -8;
	//if ( m_queryLen > 8 && m_query && end > m_query && 
	//     strncmp(end," lang:",6)==0 ) {
	//	char *asklang = m_query+m_queryLen - 2;
	//	m_gblang = getLanguageFromAbbr(asklang);
	//	m_queryLen -= 8;
	//	m_query[m_queryLen] = 0;
	//	
	//}

	// . returns false and sets g_errno on error
	// . sets m_qbuf1 and m_qbuf2
	// . sets:
	//   m_sbuf1
	//   m_sbuf2
	//   m_sbuf3
	//   m_displayQuery
	//   m_qe (encoded query)
	//   m_rtl (right to left like hebrew)
	//   m_highlightQuery
	if ( ! setQueryBuffers (r) )
		return log("query: setQueryBuffers: %s",mstrerror(g_errno));

	/* --- Virtual host language detection --- */
	/*
	if(r->getHost()) {
		bool langset = getLanguageFromAbbr(m_defaultSortLanguage);
		char *cp;
		if(!langset && (cp = strrchr(r->getHost(), '.'))) {
			uint8_t lang = getLanguageFromUserAgent(++cp);
			if(lang) {
				// char langbuf[128];
		// sprintf(langbuf, "qlang=%s\0", getLanguageAbbr(lang));
			//m_defaultSortLanguage = getLanguageAbbr(lang);
                                char *tmp = getLanguageAbbr(lang);
                                strncpy(m_defaultSortLanguage, tmp, 6);
				// log(LOG_INFO,
			//	getLanguageString(lang), r->getHost(), this);
			}
		}
	}
	*/
	/* --- End Virtual host language detection --- */


	//char *qs1 = m_defaultSortLanguage;

	// this overrides though
	//long qlen2;
	//char *qs2 = r->getString ("qlang",&qlen2,NULL);
	//if ( qs2 ) qs1 = qs2;
	
	//m_queryLang = getLanguageFromAbbr ( qs1 );

	//m_queryLang = detectQueryLanguage();

	//char *qs1 = getLangAbbr(m_queryLang);

	log("query: using default lang of %s",m_defaultSortLang);

	// get code
	m_queryLangId = getLangIdFromAbbr ( m_defaultSortLang );

	// allow for 'xx', which means langUnknown
	if ( m_defaultSortLang && 
	     m_defaultSortLang[0] && 
	     m_defaultSortLang[0]!='x' && 
	     m_queryLangId == langUnknown )
		log("query: qlang of \"%s\" is NOT SUPPORTED",
		    m_defaultSortLang);

	// . the query to use for highlighting... can be overriden with "hq"
	// . we need the language id for doing synonyms
	if ( m_prepend && m_prepend[0] )
		m_hqq.set2 ( m_prepend , m_queryLangId , true );
	else if ( m_highlightQuery && m_highlightQuery[0] )
		m_hqq.set2 ( m_highlightQuery , m_queryLangId , true );
	else if ( m_query && m_query[0] )
		m_hqq.set2 ( m_query , m_queryLangId , true );

	// log it here
	log("query: got query %s",m_sbuf1.getBufStart());

	// . now set from m_qbuf1, the advanced/composite query buffer
	// . returns false and sets g_errno on error (ETOOMANYOPERANDS)
	if ( ! m_q.set2 ( m_sbuf1.getBufStart(), 
			  m_queryLangId , 
			  m_queryExpansion ) ) {
		g_msg = " (error: query has too many operands)";
		return false;
	}

	if ( m_q.m_truncated && m_q.m_isBoolean ) {
		g_errno = ETOOMANYOPERANDS;
		g_msg = " (error: query has too many operands)";
		return false;
	}

	// turn off some parms
	if ( m_q.m_hasUrlField  ) 
		m_ipRestrictForTopics = false;
	if ( m_q.m_hasIpField   )
		m_ipRestrictForTopics = false;
	if ( m_q.m_hasPositiveSiteField ) {
		m_ipRestrictForTopics = false;
		m_doSiteClustering    = false;
	}
	if ( m_q.m_hasQuotaField ) {
		m_doSiteClustering    = false;
		m_doDupContentRemoval = false;
	}


	// sanity check
	if(m_firstResultNum < 0) m_firstResultNum = 0;

	// DEBUG: temp hack
	// static bool first = true;
	//  if ( first ) { 
	//  	first = false;
	//  	m_firstResultNum = 10;
	//  }


	// . if query has url: or site: term do NOT use cache by def.
	// . however, if spider is off then use the cache by default
	if ( m_useCache == -1 && g_conf.m_spideringEnabled ) {
		if      ( m_q.m_hasPositiveSiteField ) m_useCache = 0;
		else if ( m_q.m_hasIpField   ) m_useCache = 0;
		else if ( m_q.m_hasUrlField  ) m_useCache = 0;
		else if ( m_sites && m_sites[0] ) m_useCache = 0;
		//else if ( m_whiteListBuf.length() ) m_useCache = 0;
		else if ( m_url && m_url[0]   ) m_useCache = 0;
	}

	// if useCache is still -1 then turn it on
	if ( m_useCache == -1 ) m_useCache = 1;

	// never use cache if doing a rerank (msg3b)
	//if ( m_rerankRuleset >= 0 ) m_useCache = 0;
	bool readFromCache = false;
	if ( m_useCache ==  1  ) readFromCache = true;
	if ( m_rcache   ==  0  ) readFromCache = false;
	if ( m_useCache ==  0  ) readFromCache = false;
	// if useCache is false, don't write to cache if it was not specified
	if ( m_wcache == -1 ) {
		if ( m_useCache ==  0 ) m_wcache = 0;
		else                    m_wcache = 1;
	}
	// save it
	m_rcache = readFromCache;

	return true;
}

// . sets m_qbuf1[] and m_qbuf2[]
// . m_qbuf1[] is the advanced query
// . m_qbuf2[] is the query to be used for spell checking
// . returns false and set g_errno on error
bool SearchInput::setQueryBuffers ( HttpRequest *hr ) {

	m_sbuf1.reset();
	m_sbuf2.reset();
	m_sbuf3.reset();

	short qcs = csUTF8;
	if (m_queryCharset && m_queryCharset[0]){
		// we need to convert the query string to utf-8
		long qclen = gbstrlen(m_queryCharset);
		qcs = get_iana_charset(m_queryCharset, qclen );
		if (qcs == csUnknown) {
			//g_errno = EBADCHARSET;
			//g_msg = "(error: unknown query charset)";
			//return false;
			qcs = csUTF8;
		}
	}
	// prepend sites terms
	long numSites = 0;
	char *csStr = NULL;
	numSites = 0;
	csStr = get_charset_str(qcs);

	/*
	if ( m_sites && m_sites[0] ) {
		char *s = m_sites;
		char *t;
		long  len;
		m_sbuf1.pushChar('(');// *p++ = '(';
	loop:
		// skip white space
		while ( *s && ! is_alnum_a(*s) ) s++;
		// bail if done
		if ( ! *s ) goto done;
		// get length of it
		t = s;
		while ( *t && ! is_wspace_a(*t) ) t++;
		len = t - s;
		// add site: term
		//if ( p + 12 + len >= pend ) goto toobig;
		if ( numSites > 0 ) m_sbuf1.safeStrcpy ( " UOR " );
		m_sbuf1.safeStrcpy ( "site:" );
		//p += ucToUtf8(p, pend-p,s, len, csStr, 0,0);
		m_sbuf1.safeMemcpy ( s , len );
		//memcpy ( p , s , len     ); p += len;
		// *p++ = ' ';
		m_sbuf1.pushChar(' ');
		s = t;
		numSites++;
		goto loop;
	done:
		m_sbuf1.safePrintf(") | ");
		// inc totalLen
		m_sitesQueryLen = m_sitesLen + (numSites * 10);
	}
	*/

	// prepend
	char *qp = hr->getString("prepend",NULL,NULL);
	if( qp && qp[0] ) {
		//if( p > pstart ) *p++ =  ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//p += sprintf( p, "+gblang:%li |", m_gblang );
		m_sbuf1.safePrintf( "%s", qp );
	}

	// append site: term
	// if ( m_sites && m_sites[0] ) {
	// 	if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
	// 	m_sbuf1.safePrintf("+site:");
	// 	m_sbuf1.safeStrcpy(m_sites);
	// }

	if ( m_familyFilter ) {
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		m_sbuf1.safePrintf("gbisadult:0 | ");
	}

	// append gblang: term
	// if( m_gblang > 0 ) {
	// 	//if( p > pstart ) *p++ =  ' ';
	// 	if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
	// 	//p += sprintf( p, "+gblang:%li |", m_gblang );
	// 	m_sbuf1.safePrintf( "+gblang:%li |", m_gblang );
	// }
	// bookmark here so we can copy into st->m_displayQuery below
	//long displayQueryOffset = m_sbuf1.length();
	// append url: term
	if ( m_url && m_url[0] ) {
		//if ( p > pstart ) *p++ = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//memcpy ( p , "+url:" , 5 ); p += 5;
		m_sbuf1.safeStrcpy ( "+url:");
		//memcpy ( p , m_url , m_urlLen ); p += m_urlLen;
		m_sbuf1.safeStrcpy ( m_url );
	}
	// append url: term
	if ( m_link && m_link[0] ) {
		//if ( p > pstart ) *p++ = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//memcpy ( p , "+link:" , 6 ); p += 6;
		m_sbuf1.safeStrcpy ( "+link:");
		//memcpy ( p , m_link , m_linkLen ); p += m_linkLen;
		m_sbuf1.safeStrcpy ( m_link );
	}
	// append the natural query
	if ( m_query && m_query[0] ) {
		//if ( p  > pstart  ) *p++  = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//p += ucToUtf8(p, pend-p, m_query, m_queryLen, csStr, 0,0);
		m_sbuf1.safeStrcpy ( m_query );
		//memcpy ( p  , m_query , m_queryLen ); p  += m_queryLen;
		// add to spell checked buf, too		
		//if ( p2 > pstart2 ) *p2++ = ' ';
		if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
		//p2 +=ucToUtf8(p2, pend2-p2, m_query, m_queryLen, csStr, 0,0);
		m_sbuf2.safeStrcpy ( m_query );
		//memcpy ( p2 , m_query , m_queryLen ); p2 += m_queryLen;
	}
	// if ( m_query2 && m_query2[0] ) {
	// 	//if ( p3 > pstart3 ) *p3++ = ' ';
	// 	if ( m_sbuf3.length() ) m_sbuf3.pushChar(' ');
	// 	//p3+=ucToUtf8(p3, pend3-p3, m_query2, m_query2Len, csStr,0,0);
	// 	m_sbuf3.safeStrcpy ( m_query2 );
	// }
	//if (g_errno == EILSEQ){ // illegal character seq
	//	log("query: bad char set");
	//	g_errno = 0;
	//	if (qcs == csUTF8) {qcs = csISOLatin1;goto doOver;}
	//	if (qcs != csISOLatin1) {qcs = csUTF8;goto doOver;}
	//}
	// append quoted phrases to query
	if ( m_quote1 && m_quote1[0] ) {
		//if ( p  > pstart  ) *p++  = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//*p++ = '+';
		//*p++ = '\"';
		m_sbuf1.safeStrcpy("+\"");
		//p += ucToUtf8(p, pend-p, m_quote1, m_quoteLen1, csStr, 0,0);
		m_sbuf1.safeStrcpy ( m_quote1 );
		//memcpy ( p , m_quote1 , m_quoteLen1 ); p += m_quoteLen1 ;
		//*p++ = '\"';
		m_sbuf1.safeStrcpy("\"");
		// add to spell checked buf, too
		//if ( p2 > pstart2 ) *p2++ = ' ';
		if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
		//*p2++ = '+';
		//*p2++ = '\"';
		m_sbuf2.safeStrcpy("+\"");
		//p2+=ucToUtf8(p2, pend2-p2, m_quote1, m_quoteLen1, csStr,0,0);
		m_sbuf2.safeStrcpy ( m_quote1 );
		//memcpy ( p2 , m_quote1 , m_quoteLen1 ); p2 += m_quoteLen1 ;
		//*p2++ = '\"';
		m_sbuf2.safeStrcpy("\"");
	}
	//if (g_errno == EILSEQ){ // illegal character seq
	//	g_errno = 0;
	//	if (qcs == csUTF8) {qcs = csISOLatin1;goto doOver;}
	//	if (qcs != csISOLatin1) {qcs = csUTF8;goto doOver;}
	//}
	if ( m_quote2 && m_quote2[0] ) {
		//if ( p  > pstart  ) *p++  = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//*p++ = '+';
		//*p++ = '\"';
		m_sbuf1.safeStrcpy("+\"");
		//p += ucToUtf8(p, pend-p, m_quote2, m_quoteLen2, csStr, 0,0);
		m_sbuf1.safeStrcpy ( m_quote2 );
		//memcpy ( p , m_quote2 , m_quoteLen2 ); p += m_quoteLen2 ;
		//*p++ = '\"';
		m_sbuf1.safeStrcpy("\"");
		// add to spell checked buf, too
		//if ( p2 > pstart2 ) *p2++ = ' ';
		if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
		//*p2++ = '+';
		//*p2++ = '\"';
		m_sbuf2.safeStrcpy("+\"");
		//p2+=ucToUtf8(p2, pend2-p2, m_quote2, m_quoteLen2, csStr,0,0);
		m_sbuf2.safeStrcpy ( m_quote2 );
		//memcpy ( p2 , m_quote2 , m_quoteLen2 ); p2 += m_quoteLen2 ;
		//*p2++ = '\"';
		m_sbuf2.safeStrcpy("\"");
	}
	//if (g_errno == EILSEQ){ // illegal character seq
	//	g_errno = 0;
	//	if (qcs == csUTF8) {qcs = csISOLatin1;goto doOver;}
	//	if (qcs != csISOLatin1) {qcs = csUTF8;goto doOver;}
	//}

	// append plus terms
	if ( m_plus && m_plus[0] ) {
		char *s = m_plus;
		char *send = m_plus + gbstrlen(m_plus);
		//if ( p > pstart && p < pend ) *p++  = ' ';
		//if ( p2 > pstart2 && p2 < pend2) *p2++ = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
		while (s < send) {
			while (isspace(*s) && s < send) s++;
			char *s2 = s+1;
			if (*s == '\"') {
				// if there's no closing quote just treat
				// the end of the line as such
				while (*s2 != '\"' && s2 < send) s2++;
				if (s2 < send) s2++;
			} else {
				while (!isspace(*s2) && s2 < send) s2++;
			}
			if (s2 < send) break;
			//if (p < pend) *p++ = '+';
			//if (p2 < pend2) *p2++ = '+';
			m_sbuf1.pushChar('+');
			m_sbuf2.pushChar('+');
			//p += ucToUtf8(p, pend-p, s, s2-s, csStr, 0,0);
			//p2 += ucToUtf8(p2, pend2-p2, s, s2-s, csStr, 0,0);
			m_sbuf1.safeMemcpy ( s , s2 - s );
			m_sbuf2.safeMemcpy ( s , s2 - s );
			/*
			if (g_errno == EILSEQ) { // illegal character seq
				g_errno = 0;
				if (qcs == csUTF8) {
					qcs = csISOLatin1;
					goto doOver;
				}
				if (qcs != csISOLatin1) {
					qcs = csUTF8;
					goto doOver;
				}
			}
			*/
			s = s2 + 1;
			if (s < send) {
				//if (p < pend) *p++ = ' ';
				//if (p2 < pend2) *p2++ = ' ';
				if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
				if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
			}
		}

	}  
	// append minus terms
	if ( m_minus && m_minus[0] ) {
		char *s = m_minus;
		char *send = m_minus + gbstrlen(m_minus);
		//if ( p > pstart && p < pend ) *p++  = ' ';
		//if ( p2 > pstart2 && p2 < pend2) *p2++ = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
		while (s < send) {
			while (isspace(*s) && s < send) s++;
			char *s2 = s+1;
			if (*s == '\"') {
				// if there's no closing quote just treat
				// the end of the line as such
				while (*s2 != '\"' && s2 < send) s2++;
				if (s2 < send) s2++;
			} else {
				while (!isspace(*s2) && s2 < send) s2++;
			}
			if (s2 < send) break;
			//if (p < pend) *p++ = '-';
			//if (p2 < pend2) *p2++ = '-';
			m_sbuf1.pushChar('-');
			m_sbuf2.pushChar('-');
			//p += ucToUtf8(p, pend-p, s, s2-s, csStr, 0,0);
			//p2 += ucToUtf8(p2, pend2-p2, s, s2-s, csStr, 0,0);
			m_sbuf1.safeMemcpy ( s , s2 - s );
			m_sbuf2.safeMemcpy ( s , s2 - s );
			/*
			if (g_errno == EILSEQ) { // illegal character seq
				g_errno = 0;
				if (qcs == csUTF8) {
					qcs = csISOLatin1;
					goto doOver;
				}
				if (qcs != csISOLatin1) {
					qcs = csUTF8;
					goto doOver;
				}
			}
			*/
			s = s2 + 1;
			if (s < send) {
				//if (p < pend) *p++ = ' ';
				//if (p2 < pend2) *p2++ = ' ';
				if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
				if ( m_sbuf2.length() ) m_sbuf2.pushChar(' ');
			}
		}
	}
	// append gbkeyword:numinlinks if they have &mininlinks=X, X>0
	long minInlinks = m_hr.getLong("mininlinks",0);
	if ( minInlinks > 0 ) {
		//if ( p > pstart ) *p++ = ' ';
		if ( m_sbuf1.length() ) m_sbuf1.pushChar(' ');
		//char *str = "gbkeyword:numinlinks";
		//long  len = gbstrlen(str);
		//memcpy ( p , str , len );
		//p += len;
		m_sbuf1.safePrintf ( "gbkeyword:numinlinks");
	}

	// null terms
	if ( ! m_sbuf1.pushChar('\0') ) return false;
	if ( ! m_sbuf2.pushChar('\0') ) return false;
	if ( ! m_sbuf3.pushChar('\0') ) return false;

	// the natural query
	m_displayQuery = m_sbuf2.getBufStart();// + displayQueryOffset;

	if ( ! m_displayQuery ) m_displayQuery = "";

	while ( *m_displayQuery == ' ' ) m_displayQuery++;

	//m_displayQueryLen = gbstrlen(m_displayQuery);//p-m_displayQuery


	//log("query: got query %s",m_sbuf1.getBufStart());
	//log("query: got display query %s",m_displayQuery);

	// urlencoded display query
	m_qe.urlEncode ( m_displayQuery );

	// urlEncode(m_qe,
	// 	  MAX_QUERY_LEN*2,
	// 	  m_displayQuery,
	// 	  gbstrlen(m_displayQuery));
	



	//////////
	//
	// show DMOZ BREADCRUMB if doing a 
	// "gbpcatid:<catid> |" (Search restricted to category)
	// "gbcatid:<catid>"    (DMOZ urls in that topic, c=dmoz3)
	//
	//////////
	long pcatId = -1;
	long dcatId  = -1;
	// get the final query
	char *q =m_sbuf1.getBufStart();

	if ( q ) sscanf(q,"gbpcatid:%li",&pcatId);
	if ( q ) sscanf(q,"gbcatid:%li",&dcatId);
	// pick the one that is valid
	long catId = -1;
	if ( pcatId >= 0 ) catId = pcatId;
	if ( dcatId >= 0 ) catId = dcatId;
	
	//////
	//
	// save catid into the state
	m_catId = catId;
	//
	///////

	// are we a right to left language like hebrew?
	if ( catId > 0 && g_categories->isIdRTL(catId) )
		m_isRTL = true;
	else
		m_isRTL = false;

	return true;
}

/*
uint8_t SearchInput::detectQueryLanguage(void) {
	uint8_t lang = 0;
	// Check to see if default language is set.
	// This should override everything else.
	//if(m_defaultSortLanguage)
	//		lang = getLanguageFromAbbr(m_defaultSortLanguage);

	// Set query language from User Agent string, if possible
	if(!lang && m_hr.getUserAgent())
		lang= g_langId.guessLanguageFromUserAgent(m_hr.getUserAgent());

	// guess from query terms
	if(!lang && m_q)
		lang = g_langId.guessLanguageFromQuery(m_q);

	// guess from IP addr of the requester
	if(!lang && m_queryIP)
		lang = g_langId.guessLanguageFromIP(m_queryIP);

	// Save for later
	m_langHint = lang;

	if(m_gbcountry && m_gbcountryLen > 0)
		m_country = g_countryCode.getIndexOfAbbr(m_gbcountry);

	if(!m_country) {
		// Now guess country of the query.
		char *codep = g_langId.findGeoIP(m_queryIP, geoIPNumRows - 1, 0);
		if(codep) m_country = g_countryCode.getIndexOfAbbr(codep);

		// Many doofuses just download firefox and don't set it
		// up properly, so this takes second place to the IP search.
		if(!m_country)
			m_country = g_langId.guessCountryFromUserAgent(m_hr.getUserAgent());

	}

	return(lang);
}
*/

char getFormatFromRequest ( HttpRequest *r ) {

	char *formatStr = r->getString("format");

	if ( ! formatStr ) return FORMAT_HTML;

	char format = FORMAT_HTML;

	// what format should search results be in? default is html
	if ( formatStr && strcmp(formatStr,"html") == 0 ) format = FORMAT_HTML;
	if ( formatStr && strcmp(formatStr,"json") == 0 ) format = FORMAT_JSON;
	if ( formatStr && strcmp(formatStr,"xml") == 0 ) format = FORMAT_XML;
	if ( formatStr && strcmp(formatStr,"csv") == 0 ) format = FORMAT_CSV;
	if ( formatStr && strcmp(formatStr,"iframe")==0)
		format=FORMAT_WIDGET_IFRAME;
	if ( formatStr && strcmp(formatStr,"ajax")==0)
		format=FORMAT_WIDGET_AJAX;
	if ( formatStr && strcmp(formatStr,"append")==0)
		format=FORMAT_WIDGET_APPEND;

	// support old api &xml=1 to mean &format=1
	if ( r->getLong("xml",0) ) {
		format = FORMAT_XML;
	}

	// also support &json=1
	if ( r->getLong("json",0) ) {
		format = FORMAT_JSON;
	}

	if ( r->getLong("csv",0) ) {
		format = FORMAT_CSV;
	}

	if ( r->getLong("iframe",0) ) {
		format = FORMAT_WIDGET_IFRAME;
	}

	if ( r->getLong("ajax",0) ) {
		format = FORMAT_WIDGET_AJAX;
	}

	if ( r->getLong("append",0) ) {
		format = FORMAT_WIDGET_APPEND;
	}

	return format;
}
