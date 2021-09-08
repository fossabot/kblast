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

#ifndef ENTITIES_H__
#define ENTITIES_H__

// . i only support characters from 0-255
// . i do not plan on having unicode support, but may think about it later
// . Partap seems like a chump...I'll probably make him do it

//#include "TermTable.h"  // for hashing entity encodings
#include "Unicode.h"

// call these two
// JAB: const-ness for the optimizer
long getEntity_a          ( char *s , long maxLen , uint32_t *c );

//long getEntity_utf8 (char *s , long maxLen , long *d , long *ds ) ;

#endif
