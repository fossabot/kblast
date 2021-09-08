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

#ifndef _DIR_H
#define _DIR_H

#include <sys/types.h>      // for opendir
#include <dirent.h>         // for opendir
#include "File.h" // for File::getFileSize()

class Dir {

 public:

	bool set      ( char *dirName );
	bool set      ( char *d1 , char *d2 );

	void reset    ( );

	bool open     ( );

	bool close    ( );

	void rewind   ( ); // rewind to get the first filename

	bool cleanOut ( ); // remove all files/dir in directory

	bool create   ( ); // create the directory

	char *getNextFilename ( char *pattern = NULL );

	// . calls getNextFilename and returns number of files matching the 
	//   pattern
	int getNumFiles             ( char *pattern = NULL );

	// . does not yet support recursion
	long long   getUsedSpace    ( );

	char *getNewFilename ( char *pattern  ) ;
	long long   getNewId       ( char *pattern  ) ;
	long long   getFileId      ( char *filename ) ;

	char *getDir     ( ) { return m_dirname; };
	char *getDirName ( ) { return m_dirname; };
	char *getDirname ( ) { return m_dirname; };
	char *getFullName ( char *filename ); // prepends path

	 Dir     ( );
	~Dir     ( );

 private:

	char          *m_dirname;
	DIR           *m_dir;
	bool m_needsClose;
};

#endif
