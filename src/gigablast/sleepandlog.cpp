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

#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

static long long gettimeofdayInMilliseconds() ;

long long gettimeofdayInMilliseconds() {
	struct timeval tv;
	gettimeofday ( &tv , NULL );
	return(long long)(tv.tv_usec/1000)+((long long)tv.tv_sec)*1000;
}

int main ( int argc , char *argv[] ) {
	long long last = -1LL;
 loop:
	long long now = gettimeofdayInMilliseconds();
	char *msg;
	long long diff = now - last;
	if ( last != -1LL && diff >= 2000 ) 
		fprintf (stderr,"last=%lli now=%lli diff=%lli\n", 
			 last,now,diff);
	last = now;
	sleep(1);
	goto loop;
}
