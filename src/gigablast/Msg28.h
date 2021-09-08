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

// . propagate config changes to all hosts via an http request
// . uses udp server
// . keeps sending forever to dead hosts


#ifndef _MSG28_H_
#define _MSG28_H_

#include "TcpSocket.h"
#include "HttpRequest.h"

class Msg28 {

 public:

	Msg28();
	~Msg28();

	bool massConfig ( char  *requestBuf              ,
			  void  *state                   ,
			  void (* callback) (void *state ) ) ;

	// . returns false if blocked, true otherwise
	// . sets g_errno on error
	// . sendToProxy only used to stop the proxy
	bool massConfig ( class TcpSocket *s, class HttpRequest *r , 
			  long hostId , 
			  void *state , void (* callback) (void *state) ,
			  bool ourselvesLast = true ,
			  bool sendToProxy = false ,
			  // this not -1 if specifying a range of docids
			  // in the closed interval, [hostId,hostId2]
			  long hostId2 = -1 );

	bool registerHandler ( ) ;

	bool doSendLoop ( );

	bool         m_ourselvesLast;
	void        *m_state;
	void      (* m_callback ) ( void *state );

	long  m_i;

	char *m_buf;
	long  m_bufSize;
	long  m_bufLen;

	long  m_numRequests;
	long  m_numReplies;
	long  m_numHosts;

	long  m_hostId;
	long  m_hostId2;

	bool  m_sendToProxy;
	long  m_sendTotal;

	bool  m_freeBuf;
};

#endif
