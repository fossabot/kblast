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

#ifndef _DOMAINS_H_
#define _DOMAINS_H_

// . get the domain name (name + tld) from a hostname
// . returns NULL if not in the accepted list
// . "host" must be NULL terminated and in LOWER CASE
// . returns ptr into host that marks the domain name
char *getDomain ( char *host , long hostLen , char *tld , long *dlen );

// when host is like 1.2.3.4 use this one
char *getDomainOfIp ( char *host , long hostLen , long *dlen );

// used by getDomain() above
char *getTLD ( char *host , long hostLen ) ;

// used by getTLD() above
bool isTLD ( char *tld , long tldLen ) ;

#endif
