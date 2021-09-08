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

//Get stuff from remote hosts...
//


#ifndef _MSG1F_H_
#define _MSG1F_H_
#include "UdpSlot.h"
#include "UdpServer.h"
#include "TcpSocket.h"


class Msg1f {
 public:
        Msg1f();
        ~Msg1f();
	
	static bool init();

	static bool getLog(long hostId, 
			   long numBytes, 
			   void *state, 
			   void ( *callback) (void *state, UdpSlot* slot));

	
 private:
/* 	TcpSocket *m_socket; */
/* 	void *m_state; */
/* 	void ( *m_callback) (void *state)); */
};


#endif
