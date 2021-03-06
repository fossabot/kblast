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

#ifndef UCNORMALIZER_H___
#define UCNORMALIZER_H___

#define UC_KOMPAT_MASK 1
#define UC_COMPOSE_MASK 2

enum UCNormForm {
	ucNFD  = 0,
	ucNFC  = UC_COMPOSE_MASK,
	ucNFKD = UC_KOMPAT_MASK,
	ucNFKC = (UC_KOMPAT_MASK|UC_COMPOSE_MASK)
};


// Combined Kompatibility Form
long ucNormalizeNFKC(UChar *outBuf, long outBufSize,
		     UChar *inBuf, long inBufSize, bool strip = false);

// Decomposed Kompatibility Form
long ucNormalizeNFKD(UChar *outBuf, long outBufSize,
		 UChar *inBuf, long inBufSize);

bool initCompositionTable();
void resetCompositionTable() ;

#endif
