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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main ( int argc , char *argv[] ) {
	if ( argc !=2 ) {
		fprintf(stderr,"need filename parm\n"); return -1; }
	char *filename = argv[1];
	// now make a new socket descriptor
	int sd = socket ( AF_INET , SOCK_STREAM , 0 ) ;
	if ( sd < 0 ) { fprintf(stderr,"no socket\n"); return -1; }
	// now we have a connect just starting or already in progress
	struct sockaddr_in to;
	to.sin_family = AF_INET;
	// our ip's are always in network order, but ports are in host order
	// convert to int
	struct in_addr in;
	in.s_addr = 0;
	//inet_aton ( "207.114.174.29" , &in );
	inet_aton ( "192.168.1.10" , &in );

	to.sin_addr.s_addr =  in.s_addr;
	to.sin_port        = htons ((unsigned short)( 8000));
	bzero ( &(to.sin_zero) , 8 ); // TODO: bzero too slow?
	if ( connect ( sd, (sockaddr *)&to, sizeof(to) ) != 0 ) {
		fprintf(stderr,"connect failed\n"); 
		return -1;
	}
	char buf [ 1024*1024*4 ];
	char *p = buf;

	char *mime = 
		"POST /inject HTTP/1.0\r\n"
		"Content-Length: 0000000\r\n"
		"Content-Type: text/html\r\n"
		"Connection: Close\r\n\r\n";

	char *ctype = "text/html";
	
	if ( strstr ( filename , ".doc" ) ) ctype = "application/msword";
	if ( strstr ( filename , ".pdf" ) ) ctype = "application/pdf";

	sprintf ( p , 

		  "%s"
		  "u=myurl&c=&delete=0&ip=4.5.6.7&iplookups=0&dedup=1&"
		  "rs=7&quick=1&hasmime=1&"
		  "ucontent=HTTP 200\r\n"
		  "Last-Modified: Sun, 06 Nov 1994 08:49:37 GMT\r\n"
		  "Connection: Close\r\n"
		  "Content-Type: %s\r\n"
		  "\r\n" ,
		  mime ,ctype );
	p += gbstrlen ( p );

	// put pdf here
	int fd;
	fd = open ( filename , O_RDONLY );
	if ( fd < 0 ) {
		fprintf(stderr,"open %s failed\n", filename); 
		return -1;
	}
	int n = read ( fd , p , 3*1024*1024 );
	if ( n <= 0 ) {
		fprintf(stderr,"read 0 bytes of %s\n",filename); 
		return -1;
	}
	fprintf(stderr,"read %i bytes of %s\n",n,filename); 
	p += n;
	long size = p - buf;
	// set content length
	long clen = size - gbstrlen(mime);
	char ttt[16];
	sprintf ( ttt , "%07li", clen );
	fprintf(stderr,"clen=%li\n",clen);
	fprintf(stderr,"lastchar=%li\n",(long)buf[size-1]);
	fprintf(stderr,"lastchar-1=%li\n",(long)buf[size-2]);
	char *cptr = strstr ( buf , "Content-Length: ");
	if ( ! cptr ) { fprintf(stderr,"cptr NULL\n"); return -1; }
	cptr += 16; // point to it
	memcpy ( cptr , ttt , 7 );
	// print the mime
	char *xx = buf + gbstrlen(mime) ; // + 200
	char c = *xx;
	*xx = '\0';
	fprintf(stderr,"mime=%s",buf);
	*xx = c;
	fprintf(stderr,"\nsending %li bytes\n",size);
	// now inject it
	long sent = 0;
 loop:
	n = send ( sd , buf + sent , size - sent , 0 );
	fprintf(stderr,"n=%i\n",n);
	if ( n == 0 && sent != size ) goto loop;
	if ( n > 0 ) { 
		fprintf(stderr,"did %li\n",n);
		sent += n; 
		goto loop; 
	}
	//if ( n == -1 && errno == EAGAIN ) goto loop;
	if ( sent != size ) {
		fprintf(stderr,"only sent %i bytes of %li\n",sent,size);
		fprintf(stderr,"err=%s\n",strerror(errno));
		return -1;
	}
	// no need to wait for reply
	char reply[1024];
	n = read ( sd , buf , 1000 );
	fprintf ( stderr, "read %i bytes\n",n);
	close (sd );
	return 0;
}
