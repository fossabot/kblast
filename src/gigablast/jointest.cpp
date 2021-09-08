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

#include <pthread.h>

void *start ( void *args );

int main ( ) {
	pthread_t tid1,tid2,tid3;
 loop:
	pthread_create ( &tid1, NULL , start , NULL );
	pthread_create ( &tid2, NULL , start , NULL );
	pthread_create ( &tid3, NULL , start , NULL );
	pthread_join ( tid1 , NULL );
	pthread_join ( tid2 , NULL );
	pthread_join ( tid3 , NULL );
	goto loop;
}


void *start ( void *args ) {
	return NULL;
}
