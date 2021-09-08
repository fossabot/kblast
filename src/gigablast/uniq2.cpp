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
#include <errno.h>

int main ( int argc , char *argv[] ) {

	if ( argc != 2 ) {
		fprintf(stderr,"uniq2 <filename>\n");
		return -1;
	}

	char *fname = argv[1];

	FILE *fd = fopen ( fname , "r" );
	if ( ! fd ) {
		fprintf(stderr,"open %s : %s\n",
			fname,strerror(errno));
		return -1;
	}

	// one line at a time
	char s[1024];
	char last[1024];
	long count = 1;
	bool first = true;
	while ( fgets ( s , 1023 , fd ) ) {
		// remove \n
		s[gbstrlen(s)-1]='\0';
		// compare to last
		if ( first ) { strcpy ( last , s ); first = false; continue; }
		// same as last?
		if ( strcmp(s,last) == 0 ) { count++; continue; }
		// print out the old last
		fprintf(stdout,"%li %s\n",count,last);
		// otherwise, we become last
		strcpy ( last , s );
		// and count is reset
		count = 1;
	}
	return 0;
}
