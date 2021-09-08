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

// . Generic Container Interface

#ifndef _METACONTAINER_H_
#define _METACONTAINER_H_

#define MAX_URLLEN 128

#include "Xml.h"
#include "Log.h"
#include "Url.h"

class MetaContainer {
public:
	MetaContainer();
	virtual ~MetaContainer();

	// parse a page into this container
	virtual void parse     ( char *page, long pageLen );

	// build the meta html page from this container
	virtual long buildPage ( char *page );
	virtual void buildPage ( SafeBuf *sb );

	// url
	char m_url[MAX_URLLEN+1];
	long m_urlLen;

	// base container name
	char m_baseName[MAX_URLLEN+1];
	long m_baseNameLen;

	// ID
	long long m_id;
};

#endif
