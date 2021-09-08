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

#include "Msg40Cache.h"

// the global cache
Msg40Cache g_msg40Cache;

// returns true if we found in cache and set "msg40", false otherwise
bool Msg40Cache::setFromCache ( Msg40 *msg40 ) {

	// make the key based on the input parms like # of docs wanted,
	// start doc #, site clustering on, ...
	key_t k = msg40->makeKey ( );

	// look in cache, return false if not in there
	if ( ! m_cache.getList ( k , k   , 
				 &list   , 
				 false   ,  // do copy?
				 60*60*2 ,  // 2 hours max age
				 true    )) // keep stats
		return false;

	// set the msg40 from the list's data buf
	char *data     = list.getList();
	long  dataSize = list.getListSize();

	setMsg40FromData ( msg40 , data , dataSize );

	return true;
}

