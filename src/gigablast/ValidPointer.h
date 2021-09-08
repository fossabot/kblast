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

#ifndef _VALIDPOINTER_H_
#define _VALIDPOINTER_H_

#include "Mem.h"

enum {
	POINTER_INVALID = 0,
	POINTER_IN_DATA,
	POINTER_IN_HEAP,
	POINTER_IN_STACK
};

class ValidPointer {
	public:
		ValidPointer(void *firststackaddr);
		int isValidPointer(void *ptr);
	private:
		void *m_stackStart;
};

extern ValidPointer *g_validPointer;

extern "C" {
extern int isValidPointer(void *ptr);
} // extern "C"

#endif // _VALIDPOINTER_H_

