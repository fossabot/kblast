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

#ifndef _ADULTBIT_H_
#define _ADULTBIT_H_

//#include "TermTable.h"
#include "Xml.h"

class AdultBit {

 public:

	bool isSet() { return m_isAdult; };
	bool isAdult() { return m_isAdult; };

	void set ( char *s , long niceness = 0) { m_isAdult = getBit ( s ); };
	void set ( bool flag ) { m_isAdult = flag; };

	void reset() { m_isAdult = false; };
	AdultBit() { reset(); };

 private:

	bool getBit    ( char *s , long niceness = 0);
	bool isDirty   ( char *s , long len ) ;
	bool isObscene ( char *s , long len ) ;

	bool m_isAdult;
};

#endif
