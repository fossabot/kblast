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

// . a cache to store Msg40's (docIds/summaries)

#ifndef _MSG40CACHE_
#define _MSG40CACHE_

class Msg40Cache {

 public:

	// returns true if we found in cache and set "msg40", false otherwise
	bool setFromCache (Msg40 *msg40 );

};

extern class Msg40Cache g_msg40Cache;

#endif
