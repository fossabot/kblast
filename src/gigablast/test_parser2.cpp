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

#include "Unicode.h"

long elapsed_usec(const timeval* tv1, const timeval *tv2);
bool mainShutdown(bool urgent){return true;}
bool closeAll ( void *state , void (* callback)(void *state) ){return true;}
bool allExit ( ) {return true;}

int main(int argc, char **argv){
	if (argc < 2) {
		fprintf(stderr,"usage: %s filename [numTests]\n",argv[0]);
		exit(1);
	}
	if (!ucInit()){
		fprintf(stderr, "unable to initialize unicode tables\n");
		exit(1);
	}
	char * filename = argv[1];
	fprintf(stderr, "Reading \"%s\"\n", filename);
	FILE *fp = fopen(filename,"r");
	if (!fp){
		fprintf(stderr, "Error: could not open file \"%s\"\n", 
			filename);
		exit(1);
	}
	long numTests = 1000;
	if (argc == 3) {
		numTests = atol(argv[2]);
	}
	printf("Running %ld tests\n", numTests);

	// Get File size
	size_t file_size;
	fseek(fp, 0L, SEEK_END);
	file_size = (size_t)ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	char *file_buf = (char*)malloc(file_size+1);
	size_t nread = fread(file_buf, (size_t)1,file_size, fp);
	fclose(fp);
	
	if (nread != file_size){
		fprintf(stderr, "Warning: wanted %d chars, but read %d\n",
			file_size, nread);
	}
	file_buf[nread] = '\0';
	
	struct timeval tv1, tv2;
	struct timezone tz1, tz2;
	printf("\nParsing with char*\n");
	long totalCount = 0;
	long alnumCount;
	long punctCount;
	gettimeofday(&tv1, &tz1);
	for (long i=0; i<numTests;i++){
		
		char *p = file_buf;
		alnumCount = 0;
		punctCount = 0;
		while(*p){
			if (is_alnum(*p) && !(*p & 0x80))
				alnumCount++;
			else punctCount++;
			totalCount++;
			p++;
		}
	}
	gettimeofday(&tv2, &tz2);
	printf("Done\n");
        long elapsed = elapsed_usec(&tv1, &tv2);
	printf("%ld total chars, %ld usec, %ld char/usec "
	       "(%ld alnum, %ld punct)\n", 
	       totalCount, elapsed, totalCount/elapsed,alnumCount, punctCount);

	printf("\nParsing with utf8Decode\n");
	totalCount = 0;
	gettimeofday(&tv1, &tz1);
	for (long i=0; i<numTests;i++){
		
		char *p = file_buf;
		alnumCount = 0;
		punctCount = 0;
		while(*p){
			UChar32 c = utf8Decode(p, &p);
			//UChar32 c = *p;
			if (ucIsWordChar(c))
				alnumCount++;
			else punctCount++;
			totalCount++;
			//p++;
		}
	}
	gettimeofday(&tv2, &tz2);
	elapsed = elapsed_usec(&tv1, &tv2);
	printf("Done\n");
	printf("%ld total chars, %ld usec, %ld char/usec "
	       "(%ld alnum, %ld punct)\n", 
	       totalCount, elapsed, totalCount/elapsed,alnumCount, punctCount);
}
long elapsed_usec(const timeval* tv1, const timeval *tv2)
{
	long sec_elapsed = (tv2->tv_sec - tv1->tv_sec);
	long usec_elapsed = tv2->tv_usec - tv1->tv_usec;
	if (usec_elapsed<0){
		usec_elapsed += 1000000;
		sec_elapsed -=1;
	}
	usec_elapsed += sec_elapsed*1000000;
	return usec_elapsed;
}
