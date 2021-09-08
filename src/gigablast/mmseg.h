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

#include <math.h>


void            open_lexicon(char *);
void            close_lexicon(void);
void            load_index(char *);
void            load_logcharfreq(char *);
int             search_head(int, char *);
int             search_body(int, long, int, char *);
void            segment(char *,char **, long **, bool **, bool **, long **);
void            mmsegment(char *, char **, long **, bool **, bool **, long **);

unsigned int    big5_character_test(unsigned char, unsigned char);
int             big5_charactertype_test(unsigned int);
//long  tokenizeChinese(char *, char *, long *, int *, int *, long);
long tokenizeChinese ( char *, char *, long *, bool *, bool *, long *);
