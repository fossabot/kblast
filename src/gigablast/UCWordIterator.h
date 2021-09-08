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

#ifndef UC_WORD_ITERATOR_H___
#define UC_WORD_ITERATOR_H___

#include "Unicode.h"
class UCWordIterator {
public:
	UCWordIterator();
	~UCWordIterator();
	bool setText(UChar* s, long slen, long version);
	UChar *getText();
	UChar32 currentCodePoint();

	// Set index to beginning of text
	long first();
	// find and return the index of the next word boundary
	long next();
	// end of text index
	long last();

	// current index
	long current();

	bool done() { return m_done; };
private:
	UChar *m_text;
	UChar *m_last;
	bool m_done;
	long m_textLen;
	UChar *m_current;
	UChar *m_next;

	UChar32 m_currentCP;
	UChar32 m_prevCP;
	UCScript m_currentScript;
	UCScript m_prevScript;

	UCProps m_currentProps;
	UCProps m_prevProps;
	
	long m_version; // titlerec version
};
#endif
