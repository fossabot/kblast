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

/* When adding links/urls to spiderdb, Msg10.cpp, should lookup their IP
address if not already provided using a new Msg class. This is done by MsgC.
Msg class consults the local cache (g_dnsLocal) in Dns.cpp for the IP
address first, if not found it should then consult S_localDnsCache. If it 
is not found there, then send the dns lookup request to a host in
the cluster based on the hash of the hostname DIV'd with the number of hosts in
the cluster, g_hostdb.m_numHosts. The request should be looked up in 
g_dnsDistributed, not Dns.cpp's local cache, and delivered to
the responsible host. If not there, then the request should be sent to the
appropriate dns server. It is like an L1a/L1b/L2/L3 architecture, where L1 
is local, L2 is on a host in the network and L3 is on the dns server. The
returned result (the IP address) should be stored in all 4 caches.*/

#ifndef _MSGC_H_
#define _MSGC_H_

#include "UdpServer.h"
#include "Dns.h"
#include "Multicast.h"
#include "Rdb.h"
//#include "Spider.h"

class MsgC {

 public:

	MsgC();
	~MsgC();

	// Don't bother about dnsState, only Msg14 used to use it, and now 
	// since we are not using getIp in Msg16 anymore, it is useless.
	// returns false if blocked, true otherwise
	bool getIp(char  *hostname    , long   hostnameLen ,
		   long  *ip ,
		   void  *state ,
		   void (* callback) ( void *state , long ip ),
		   long  niceness = 2,
		   bool  forwardToProxy = false );
	// register our request handle with g_udp server
	bool registerHandler ( );

	long gotReply();

	void (*m_callback) (void *state ,long ip);

	// used by MsgE to store its data
	void *m_state2;
	void *m_state3;

	// private:
	Multicast m_mcast;
	Url   m_u;	
	char  m_request[MAX_URL_LEN];
	long *m_ipPtr;
	// for proxy forwarding:
	UdpSlot *m_slot;
	long     m_tmpIp;
	bool     m_forwardToProxy;
};

#endif
