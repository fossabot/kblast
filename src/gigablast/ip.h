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

#ifndef _IPROUTINES_H_
#define _IPROUTINES_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// what are my IPs?

// comcast home
//#define MATTIP1 "68.35.104.227"
//#define MATTIP1 "69.240.75.134"
//#define MATTIP1 "68.42.43.180"
#define MATTIP1 "68.35.74.178"

// local network
//#define MATTIP2 "192.168.1.2"
#define MATTIP2 "10.1.10.84"

// outbound from work network
//#define MATTIP3 "68.35.27.72"
#define MATTIP3 "64.139.94.202"

long  atoip ( char *s , long slen );
long  atoip ( char *s );//, long slen );
char *iptoa ( long ip );
// . get domain of ip address
// . first byte is the host (little endian)
long  ipdom ( long ip ) ;
// most significant 2 bytes of ip
long  iptop ( long ip ) ;
// . is least significant byte a zero?
// . if it is then this ip is probably representing a whole ip domain
bool  isIpDom ( long ip ) ;
// are last 2 bytes 0's?
long  isIpTop ( long ip ) ;

// returns number of top bytes in comon
long  ipCmp ( long ip1 , long ip2 ) ;


#endif

