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

#include <stdio.h>
#include <stdlib.h>
#include "iconv.h"

#define BUFSIZE 1024*1024
int main(int argc, char **argv){
	char inbuf[BUFSIZE];

	iconv_t conv = iconv_open("UTF-8", "UTF-8");
	char *dummy = NULL;
	size_t dummy2 = 0;
	// reset convertor
	iconv(conv,NULL,NULL,&dummy,&dummy2);
	size_t inCursor = 0;

	while (!feof(stdin)){
		char outbuf[BUFSIZE];
		int count = fread(inbuf, 1, BUFSIZE, stdin);
		char *pin = inbuf;
		char *pout = outbuf;
		size_t incount = count;
		size_t outcount = BUFSIZE;
		
		int res = iconv(conv, &pin, &incount, &pout, &outcount);
		if (res < 0) {
			switch(errno) {
			case EILSEQ:
				printf("Illegal sequence: 0x%02x 0x%02x 0x%02x 0x%02x "
				       "at byte %d.\n", 
				       (unsigned char)*pin, 			
				       (unsigned char)*(pin+1),
 				       (unsigned char)*(pin+2), 
 				       (unsigned char)*(pin+3), 
				       pin-inbuf+inCursor);
				break;
			case EINVAL:
				printf("Invalid character: 0x%02x at byte %d.\n", 
				       (unsigned char)*pin, pin-inbuf+inCursor);
				break;
			}
		}
			
		
	}

}
