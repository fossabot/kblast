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

// Message to generate the directory listing of a category.

#ifndef _MSG2B_H_
#define _MSG2B_H_

#include "Categories.h"

class Msg2b {
public:
	Msg2b();
	~Msg2b();

	// main call to generate directory
	bool generateDirectory ( long   dirId,
				 void  *state,
				 void (*callback)(void *state) );

	// serialize/deserialize
	long getStoredSize ( );
	long serialize     ( char *buf, long bufLen );
	long deserialize   ( char *buf, long bufLen );

	// callback
	void  *m_st;
	void (*m_callback)(void *state);

	// dir ID to get
	long m_dirId;

	// buffers for directory
	SubCategory *m_subCats;
	long         m_subCatsSize;
	long         m_numSubCats;
	char        *m_catBuffer;
	long         m_catBufferSize;
	long         m_catBufferLen;
};

#endif
