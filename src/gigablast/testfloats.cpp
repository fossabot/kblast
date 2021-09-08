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

//#include "gb-include.h"
#include <sys/time.h>  // gettimeofday() 
#include <stdio.h>

long long gettod ( ) {
	struct timeval tv;
	gettimeofday ( &tv , 0 );
	long long now=(long long)(tv.tv_usec/1000)+((long long)tv.tv_sec)*1000;
	return now;
}

int main ( int argc , char *argv[] ) {

	float x=  0.4598;
	float y = 13.4567;

	printf("start float loop\n");
	float z;
	long long start = gettod();
	for ( long i = 0 ; i < 10000000 ; i++ ) 
		z = x * y;
	long long end = gettod();
	printf("float muls took %llims\n",end-start);

	long xi = 14598;
	long yi = 134567;
	long zi;
	start = gettod();
	for ( long i = 0 ; i < 10000000 ; i++ ) 
		zi = xi * yi;
	end = gettod();
	printf("int muls took %llims\n",end-start);




	start = gettod();
	for ( long i = 0 ; i < 10000000 ; i++ ) 
		z = x + y;
	end = gettod();
	printf("float adds took %llims\n",end-start);


	start = gettod();
	for ( long i = 0 ; i < 10000000 ; i++ ) 
		zi = xi + yi;
	end = gettod();
	printf("int adds took %llims\n",end-start);


	start = gettod();
	for ( long i = 0 ; i < 10000000 ; i++ ) 
		z = x / y;
	end = gettod();
	printf("float divs took %llims\n",end-start);


	start = gettod();
	for ( long i = 0 ; i < 10000000 ; i++ ) 
		zi = xi / yi;
	end = gettod();
	printf("int divs took %llims\n",end-start);



	return 0;
}
