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

	long count = 0;
	for ( long i = 0 ; i < 1000000 ; i+= 10000 ) 
		//printf("wget \"http://127.0.0.1:8000/search?q=%%22vital+records%%22&s=%li&n=10000&sc=0&dr=0&raw=8&rt=1&ff=0\" -O resultsvr.%li\n",i,count++);
		printf("wget \"http://127.0.0.1:8000/search?q=ext%%3Axml&s=%li&n=10000&sc=0&dr=0&raw=8&rt=1&ff=0\" -O results.%03li\n",i,count++ );
}
