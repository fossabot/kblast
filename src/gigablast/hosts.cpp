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

int main ( int argc , char *argv[] ) {

	//for ( long i = 0 ; i < 137 ; i++ ) 
	//	printf("66.154.103.%li gk%li\n",i+36,136+i);

	printf ("# the new hosts.conf format:\n"
"\n"
"# <hostId> <hostname> [portoffset] [# <comment>]\n"
"# spare    <hostname> [portoffset] [# <comment>]\n"
"# proxy    <hostname> [portoffset] [# <comment>]\n"
"\n"
"# we use /etc/hosts to get the ip of eth0\n"
"# we insert an 'i' into hostname to get ip of eth1\n"
"\n"
"working-dir: /w/\n"
"port-offset: 2\n"
"index-splits: 64\n"
"\n"
		);

	long gk = 0;
	for ( long i = 0 ; i < 256 ; i++ ) {
		if ( i && (i%16==0) ) gk += 16;
		// wrap to lower rack half at 128
		if ( i == 128 ) gk = 16;
		printf("%03li\tgk%li\n",i,gk);
		gk++;
	}


	for ( long i = 256 ; i < 271 ; i++ )
		printf ("spare\tgk%li\n",i);

	printf ("#proxy\tproxy0\n");
	printf ("#proxy\tproxy1\n");

	return 0;
}
