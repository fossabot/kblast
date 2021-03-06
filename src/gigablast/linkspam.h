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

#ifndef _LINKSPAM_H_
#define _LINKSPAM_H_

#include "gb-include.h"
#include "ip.h"
//#include "TermTable.h"

bool setLinkSpam ( long             ip                 ,
                   long            *indCatIds          ,
                   long             numIndCatIds       ,
                   class Url       *linker             ,
                   long             siteNumInlinks     ,
		   class Xml       *xml                ,
		   class Links     *links              ,
		   bool             isContentTruncated ,
		   long             niceness           );

bool isLinkSpam  ( class Url       *linker         ,
		   long             ip             ,
		   long            *indCatIds      ,
		   long             numIndCatIds   ,
		   long             siteNumInlinks ,
		   class Xml       *xml            ,
		   class Links     *links          ,
		   long             maxDocLen      , 
		   char           **note           , 
		   Url             *linkee         ,
		   long             linkNode       , 
		   char            *coll           ,
		   long             niceness       );

char *getCommentSection ( char *haystack     ,
			  long  haystackSize ,
			  bool  isUnicode    ,
			  long  niceness     );
#endif
