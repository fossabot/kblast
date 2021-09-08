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

#include "hash.h"

int main(int argc, char **argv) {
	
	char *str1 = "Apple";
	char *str2 = "Candy";
	char *str3 = "AppleCandy";

	long long h1, h2, h3,h4;
	hashinit();
	h1 = hash64Lower(str1, gbstrlen(str1));
	h2 = hash64Lower(str2, gbstrlen(str2));
	printf("h1: %lld, h2: %lld\n", h1, h2);

	h3 = hash64Lower(str3, gbstrlen(str3));
	h4 = hash64Lower(str2, gbstrlen(str2),h1);
	printf("h3: %lld, h4: %lld\n", h3,h4);
	
	long long h5;
	h5 = h1^h2;
	printf("h5: %lld\n", h5);

	long long h6;
	h6 = hash64(h1,h2);
	printf("h6: %lld\n", h6);
}
