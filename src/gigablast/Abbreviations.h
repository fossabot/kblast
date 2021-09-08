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

// i guess _ABBREVIATIONS_H_ is reserved, so prepend _GB
#ifndef _GB_ABBREVIATIONS_H_
#define _GB_ABBREVIATIONS_H_

#include "Unicode.h"

// . is the word with this word id an abbreviation?
// . word id is just the hash64() of the word
bool isAbbr ( long long wid , bool *hasWordAfter = NULL ) ;

// to free the table's memory, Process::reset() will call this
void resetAbbrTable ( ) ;

#endif
