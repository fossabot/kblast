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

// . This message class determines if the parms have changed
//   while a host is down, and resyncs them if they have


#ifndef _MSG3E_H_
#define _MSG3E_H_

#include "UdpServer.h" // for sending/handling requests
#include "Parms.h" 

class Msg3e {

 public:

	// register our 0x3f handler function
	bool registerHandler ( );

	// see if parms have changed
	void checkForNewParms ( );

	// send checksum to host
	void sendChecksum( Host *h );

	// send parms to host
	bool sendParms( Host *h );

	// public so C wrapper can call
	void gotReply ( ) ;

	// callback information
	void  *m_state  ;
	void (* m_callback)(void *state );

	// request buffer is just 4 bytes
	char m_request[ 4 ]; 
	char *m_reply; 
	long m_replySize;

	char m_goodReply;

	long m_errno;
};

#endif
