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

#ifndef __FLAGS_H_
#define __FLAGS_H_

class Flags {
public:
	static const long NoMin;
	static const long NoMax;

	Flags();
	~Flags();
	
	void reset  ();
	bool resize ( long size );
	
	char getFlag ( long n           ) { return m_flags[n]; };
	void setFlag ( long n, char set );

	long getNumFlags () { return m_numFlags; };
	long getNumSet   () { return m_numSet; };
	long getHighestSet () { return m_highestSet; };
	long getLowestSet  () { return m_lowestSet; };
	

	void dumpFlags();

private:
	long  m_numFlags;   
	long  m_numSet;     
	long  m_highestSet; 
	long  m_lowestSet;  

	char *m_flags;
};

void testFlags();

#endif // __FLAGS_H_
