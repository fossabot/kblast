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

#include "Pages.h"
#include "Parms.h"

#include "Collectiondb.h"


#define BABY_BLUE  "e0e0d0"
#define LIGHT_BLUE "d0d0e0"
#define DARK_BLUE  "c0c0f0"
#define GREEN      "00ff00"
#define RED        "ff0000"
#define YELLOW     "ffff00"


bool sendPageSpam ( TcpSocket *s , HttpRequest *r ) {
	long  collLen = 0;
	char *coll  = r->getString ( "c" , &collLen  , NULL /*default*/);

	// get collection rec
	CollectionRec *cr = g_collectiondb.getRec ( coll );
	// bitch if no collection rec found
	if ( ! cr ) {
		g_errno = ENOCOLLREC;
		log("build: Spam Controls Failed. "
		    "Collection \"%s\" does not exist."
		    ,coll);
		return g_httpServer.sendErrorReply(s,500,
						   "collection does not exist");
	}


// 	long  user   = g_pages.getUserType ( s , r );
// 	long  pwdLen = 0;
// 	char *pwd   = r->getString ( "pwd" , &pwdLen, "");

	SafeBuf sb;
	sb.reserve(32768);

	// 	char *ss = sb.getBuf();
	// 	char *ssend = sb.getBufEnd();
// 	g_pages.printAdminTop ( &sb , PAGE_SPAM, user ,
// 				coll , pwd , s->m_ip );
	//      sb.incrementLength(sss - ss);



	sb.safePrintf("\n<table width=100%% bgcolor=#%s "
		      "cellpadding=4 border=1>\n", 
		      BABY_BLUE);
	sb.safePrintf("<tr><td colspan=2 bgcolor=#%s>"
		      "<center><b>Spam Controls</b></center></td></tr>", 
		      DARK_BLUE);

	// 	ss = sb.getBuf();
	// 	ssend = sb.getBufEnd();
	g_parms.printParms (&sb, s, r);
	//	sb.incrementLength(sss - ss);



	sb.safePrintf ("<tr><td colspan=\"2\"><center>"
		       "<input type=submit value=\"Update\" border=0>"
		       "</center></td></tr>");

	sb.safePrintf ("</table><br><br>\n" );

	return g_httpServer.sendDynamicPage ( s , (char*) sb.getBufStart(), 
					      sb.length() , -1 , false);
}
