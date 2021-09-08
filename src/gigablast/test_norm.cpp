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

//#include <unicode/unorm.h>
#include "Unicode.h"


bool mainShutdown ( bool urgent ) ;
bool mainShutdown ( bool urgent ) {return true;}

// Test first 255 chars of unicode (iso-8859-1) for normalization
int main(int argc, char*argv){
	ucInit();
	long count = 0;
	for (UChar32 c = 0; c < 0x10000; c++){
		//UErrorCode err = U_ZERO_ERROR;
		//bool isNorm = unorm_isNormalized(&c, 
		//				 1, UNORM_NFKC,&err);
		//if (U_FAILURE(err)) printf("0x%02x: Error: %s\n", 
		//			   c, u_errorName(err));
		//else// if (!isNorm)
		//	printf("0x%02x(%c): %s %s\n", c,c,
		//	       isNorm?"Normal":"NOT Normal",
		//	       is_alnum((char)c)?"":"not alnum");
		if (ucIsWhiteSpace(c)){
			count++;
			printf("0x%02x (%c): whitespace\n", c, c);
		}
	}
	printf("Count: %d\n", count);
}
