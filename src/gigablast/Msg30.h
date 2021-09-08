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

// . call g_collectiondb.reloadList(), resets m_lastTimes in spiderLoop to 0's
// . this will cause it to reset m_startKeys to 0

#ifndef _MSG30_H_
#define _MSG30_H_

//#include "CollectionRec.h"

class Msg30 {

 public:

	bool registerHandler();

	// . send an updated collection rec to ALL hosts
	// . returns false if blocked, true otherwise
	// . sets errno on error
	bool update ( CollectionRec *rec      ,
		      bool           deleteIt ,
		      void          *state    , 
		      void         (* callback)(void *state ) );

	// leave public for wrappers to call
	void    *m_state ;
	void   (* m_callback)(void *state ) ;

	long    m_requests;
	long    m_replies;

	char    m_sendBuf [ sizeof(CollectionRec) ];
	long    m_sendBufSize;
};

#endif
