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

#include "ValidPointer.h"

ValidPointer *g_validPointer = NULL;

ValidPointer::ValidPointer(void *firststackaddr) {
	m_stackStart = firststackaddr;
	if(g_validPointer) {
		log(LOG_LOGIC, "init: Second instantiation of ValidPointer, this is a bug\n");
		char *xx = NULL; *xx = 0;
	}
	g_validPointer = this;
}

// Wonky pointer tricks, read the ELF spec before you
// monkey with this.
int ValidPointer::isValidPointer(void *ptr) {
			uint32_t stackvar = 0;
			extern void *__FRAME_BEGIN__;
			extern void *_end;
			if(ptr < __FRAME_BEGIN__) return(POINTER_INVALID);
			if(ptr < _end) return(POINTER_IN_DATA);
			// Sadly, this isn't definitive, but it's a good guess
			if((uint32_t)ptr < ((uint32_t)&_end + g_mem.getMaxMem()))
				return(POINTER_IN_HEAP);
			if(ptr < m_stackStart && ptr > &stackvar) return(POINTER_IN_STACK);
			return(POINTER_INVALID);
		}

extern "C" {
int isValidPointer(void *ptr) {
#if 0
	// Disabled, it returns invalid on some valid pointers.
	if(!g_validPointer) {
		log(LOG_WARN,
		    "init: Pointer Validation not set up yet, this is a bug.\n");
		return(POINTER_INVALID);
	}
	return(g_validPointer->isValidPointer(ptr));
#else // 0
	return(true);
#endif // 0
}
} // extern "C"
