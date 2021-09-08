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

// manages a link list of fixed-size links

class LinkedList {

 public:

	// . returns false and set g_errno on error
	// . comparison key is first 16 bytes of link data
	bool init ( long linkSize , long maxNumLinks );

	// . TRY to add a slot
	// . returns false if not added, true if added
	// . may kick out other links to make room
	bool addLink ( char *link );

	// get head link
	char *getHeadLink ( );

	// . get next link
	// . returns NULL if empty
	char *getNextLink ( char *link );

};
