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

#include "ip.h"

long atoip ( char *s , long slen ) {
	// point to it
	char *p = s;
	if ( s[slen] ) {
		// copy into buffer and NULL terminate
		char buf[1024];
		if ( slen >= 1024 ) slen = 1023;
		memcpy ( buf , s , slen );
		buf [ slen ] = '\0';
		// point to that
		p = buf;
	}
	// convert to int
	struct in_addr in;
	in.s_addr = 0;
	inet_aton ( p , &in );
	// ensure this really is a long before returning ip
	if ( sizeof(in_addr) == 4 ) return in.s_addr;
	// otherwise bitch and return 0
	log("ip:bad inet_aton"); 
	return 0; 
}

long atoip ( char *s ) {
	// convert to int
	struct in_addr in;
	in.s_addr = 0;
	inet_aton ( s , &in );
	// ensure this really is a long before returning ip
	if ( sizeof(in_addr) == 4 ) return in.s_addr;
	// otherwise bitch and return 0
	log("ip:bad inet_aton"); 
	return 0; 
}

char *iptoa ( long ip ) {
	static char s_buf [ 32 ];
	sprintf ( s_buf , "%hhu.%hhu.%hhu.%hhu",
		  (unsigned char)(ip >>  0)&0xff,
		  (unsigned char)(ip >>  8)&0xff,
		  (unsigned char)(ip >> 16)&0xff,
		  (unsigned char)(ip >> 24)&0xff);
	return s_buf;
	//struct in_addr in;
	//in.s_addr = ip;
	//return inet_ntoa ( in );
}

// . get domain of ip address
// . first byte is the host (little endian)
long  ipdom ( long ip ) { return ip & 0x00ffffff; };

// most significant 2 bytes of ip
long  iptop ( long ip ) { return ip & 0x0000ffff; };

// . is least significant byte a zero?
// . if it is then this ip is probably representing a whole ip domain
bool  isIpDom ( long ip ) { return ( (ip & 0xff000000) == 0 ); };

// are last 2 bytes 0's?
long  isIpTop ( long ip ) { return ( (ip & 0xffff0000) == 0 ); };

// returns number of top bytes in comon
long  ipCmp ( long ip1 , long ip2 ) {
	char *a = (char *)&ip1;
	char *b = (char *)&ip2;
	// little endian compare
	if ( a[3] != b[3] ) return 0;
	if ( a[2] != b[2] ) return 1;
	if ( a[1] != b[1] ) return 2;
	if ( a[0] != b[0] ) return 3;
	return 4; // exact match
}

