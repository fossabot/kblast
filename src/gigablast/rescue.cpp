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

// program to rescue data from a core and save it as coreSeg.offset.size

#include "gb-include.h"

#include "File.h"

int main ( int argc , char *argv[] ) {
	// must have big filename
	if ( argc != 4 ) {
		fprintf(stderr,"rescure [corefile] [offset] [size]\n");
		exit(-1);
	}
	long coreOffset = atol(argv[2]);
	long coreSize   = atol(argv[3]);
	File f;
	f.set ( argv[1] );
	if ( ! f.open ( O_RDONLY ) ) {
		fprintf(stderr,"could not open core file %s", argv[1] );
		exit(-1);
	}
	// read whole file into memory
	char *buf = (char *) malloc ( coreSize );
	if ( ! buf ) {
		fprintf(stderr,"could not alloc %li bytes", coreSize );
		exit(-1);
	}
	if ( f.read ( buf , coreSize , coreOffset ) < 0 ) {
		fprintf(stderr,"could not read %li bytes", coreSize );
		exit(-1);
	}
	// now dump to separate file
	f.close();
	char name[64];
	sprintf(name,"coreSeg.%li.%li", coreOffset, coreSize );
	f.set ( name );
	f.open ( O_RDWR );
	f.write ( buf , coreSize );
	f.flush();
}

