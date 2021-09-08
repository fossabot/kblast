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

#ifndef _SANITY_H_
#define _SANITY_H_

#define SANITYCHECK(c)            (gb_sanityCheck((c),__FILE__,__FUNCTION__,__LINE__))
#define SANITYCHECKMSG(c, msg)    (gb_sanityCheckMsg((c),(msg),__FILE__,__FUNCTION__,__LINE__))

inline void gb_sanityCheck ( bool cond, 
			     const char *file, const char *func, const int line ) {
	if ( ! cond ) {
		log( LOG_LOGIC, "SANITY CHECK FAILED /%s:%s:%d/", 
		     file, func, line );
		char *xx = NULL; *xx = 0;
	}
}

inline void gb_sanityCheckMsg ( bool cond, char *msg, 
				const char *file, const char *func, const int line ) {
	if ( ! cond ) {
		log( LOG_LOGIC, "SANITY CHECK FAILED: %s /%s:%s:%d/", 
		     msg, 
		     file, func, line );
		char *xx = NULL; *xx = 0;
	}
}


#endif // _SANITY_H_

