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

#include "gb-include.h"

#include "Lang.h"

void languageToString ( unsigned char langId , char *buf ) {
	char *p = getLanguageString ( langId );
	if ( ! p ) p = "ERROR";
	strcpy(buf,p);
}

static char *s_nativeLangStrings[] = {
	"unknown",
	"english",
	"français",
	"español",
	"русcкий",
	"t?rk?e", // not sure...
	"japanese", // don't know yet
	"chinese traditional", // don't know yet
	"chinese simplified", // don't know yet
	"korean", // don't know yet
	"deutsch",
	"nederlands",
	"italiano",
	"suomi",
	"svenska",
	"norsk",
	"português",
	"vietnamese", // don't know yet
	"arabic", // don't know yet
	"hebrew", // don't know yet
	"indonesian", // don't know yet
	"greek", // don't know yet
	"thai", // don't know yet
	"hindi", // don't know yet
	"bengala", // don't know yet
	"polski",
	"tagalog", // don't know yet

	"latin",
	"esperanto",
	"catalan",
	"bulgarian",
	"translingual",
	"serbo-croatin",
	"hungarian",
	"danish",
	"lithuanian",
	"czech",
	"galician",
	"georgian",
	"scottish gaelic",
	"gothic",
	"romanian",
	"irish",
	"latvian",
	"armenian",
	"icelandic",
	"ancient greek",
	"manx",
	"ido",
	"persian",
	"telugu",
	"venetian",
	"malagasy",
	"kurdish",
	"luxembourgish",
	"estonian",

	NULL
};
static char *s_lowerLangStrings[] = {
	"unknown","english","french","spanish","russian","turkish","japanese",
	"chinese traditional","chinese simplified","korean","german","dutch",
	"italian","finnish","swedish","norwegian","portuguese","vietnamese",
	"arabic","hebrew","indonesian","greek","thai","hindi","bengala",
	"polish","tagalog",

	"latin",
	"esperanto",
	"catalan",
	"bulgarian",
	"translingual",
	"serbo-croatian",
	"hungarian",
	"danish",
	"lithuanian",
	"czech",
	"galician",
	"georgian",
	"scottish gaelic",
	"gothic",
	"romanian",
	"irish",
	"latvian",
	"armenian",
	"icelandic",
	"ancient greek",
	"manx",
	"ido",
	"persian",
	"telugu",
	"venetian",
	"malagasy",
	"kurdish",
	"luxembourgish",
	"estonian",

	NULL
};

static char *s_langStrings[] = {
	"Unknown","English","French","Spanish","Russian","Turkish","Japanese",
	"Chinese Traditional","Chinese Simplified","Korean","German","Dutch",
	"Italian","Finnish","Swedish","Norwegian","Portuguese","Vietnamese",
	"Arabic","Hebrew","Indonesian","Greek","Thai","Hindi","Bengala",
	"Polish","Tagalog",

	"Latin",
	"Esperanto",
	"Catalan",
	"Bulgarian",
	"Translingual",
	"Serbo-Croatian",
	"Hungarian",
	"Danish",
	"Lithuanian",
	"Czech",
	"Galician",
	"Georgian",
	"Scottish Gaelic",
	"Gothic",
	"Romanian",
	"Irish",
	"Latvian",
	"Armenian",
	"Icelandic",
	"Ancient Greek",
	"Manx",
	"Ido",
	"Persian",
	"Telugu",
	"Venetian",
	"Malagasy",
	"Kurdish",
	"Luxembourgish",
	"Estonian",
	NULL
};

char* getLanguageString ( unsigned char langId ) {
	if ( langId >= sizeof(s_langStrings)/sizeof(char *) ) return NULL;
	return s_langStrings[langId];
};

char* getNativeLanguageString ( unsigned char langId ) {
	if ( langId >= sizeof(s_nativeLangStrings)/sizeof(char *) ) return NULL;
	return s_nativeLangStrings[langId];
};

static char *s_langAbbr[] = {
	"xx","en","fr","es","ru","tr","ja","zh_tw","zh_cn","ko","de","nl",
	"it","fi","sv","no","pt","vi","ar","he","id","el","th","hi",
	"bn","pl","tl",

	"la", // latin
	"eo", // esperanto
	"ca", // catalan
	"bg", // bulgarian
	"tx", // translingual
	"sr", // serbo-crotian
	"hu", // hungarian
	"da", // danish
	"lt", // lithuanian
	"cs", // czech
	"gl", // galician
	"ka", // georgian
	"gd", // scottish gaelic
	"go", // gothic, MADE UP!
	"ro", // romanian
	"ga", // irish
	"lv", // latvian
	"hy", // armenian
	"is", // icelandic
	"ag", // ancient gree, MADE UP!
	"gv", // manx
	"io", // ido
	"fa", // persian
	"te", // telugu
	"vv", // venetian MADE UP!
	"mg", // malagasy
	"ku", // kurdish
	"lb", // luxembourgish
	"et", // estonian
	NULL
};

// fix bug:
//#ifndef PRIVATESTUFF
#define csISOLatin6 cslatin6
//#endif

static unsigned char s_langCharset[] = {
	csUnknown,csISOLatin1,csISOLatin1,csISOLatin1,//"xx","en","fr","es",
	csUnknown,csUnknown,csUnknown,csUnknown,//"ru","zz","ja","zh_tw",
	csUnknown,csUnknown,csISOLatin1,csISOLatin1,//"zh_cn","ko","de","nl",
	csISOLatin1,csISOLatin6,csISOLatin6,csISOLatin6,//"it","fi","sv","no",
	csISOLatin1,csUnknown,csUnknown,csUnknown,//"pt","vi","ar","he",
	csUnknown,csUnknown,csUnknown,csUnknown,//"id","el","th","hi",
	csUnknown,csUnknown,csUnknown,//"bn","pl","tl","en_uk",
	csUnknown//"en_au"
};

uint8_t getLanguageFromName(uint8_t *name) {
	int x;
	for(x = 0; x < MAX_LANGUAGES && s_lowerLangStrings[x]; x++)
		if(!strcasecmp((char*)name, s_lowerLangStrings[x])) return(x);
	for(x = 0; x < MAX_LANGUAGES && s_nativeLangStrings[x]; x++)
		if(!strcasecmp((char*)name, s_nativeLangStrings[x])) return(x);
	return(0);
}

uint8_t getLangIdFromAbbr ( char *abbr ) {
	int x;
	for(x = 0; x < MAX_LANGUAGES && s_langAbbr[x]; x++)
		if(!strcasecmp((char*)abbr, s_langAbbr[x])) return x;
	// english?
	if ( ! strcasecmp((char *)abbr,"en_uk")) return langEnglish;
	if ( ! strcasecmp((char *)abbr,"en_us")) return langEnglish;
	//char *xx=NULL;*xx=0;
	return langUnknown;//0;
}

char *getLangAbbr ( uint8_t langId ) {
	return s_langAbbr[langId]; 
}

char* getLanguageAbbr ( unsigned char langId ) {
	if ( langId >= sizeof(s_langAbbr)/sizeof(char *) ) return NULL;
	return s_langAbbr[langId];
};

unsigned char  getLanguageCharset ( unsigned char langId ){
	if ( langId >= sizeof(s_langAbbr)/sizeof(char *) ) return csUnknown;
	return s_langCharset[langId];
}

/*
unsigned char getLanguageFromScript(UChar32 c) {
	switch(ucGetScript(c)) {
	case ucScriptArabic:
		return langArabic;
		break;
	case ucScriptGreek:
		return langGreek;
		break;
	case ucScriptHangul:
	case ucScriptHanunoo:
		return langKorean;
		break;
		//case ucScriptHan:
		//return langChineseTrad;

	case	ucScriptHiragana:
	case	ucScriptKannada:
	case	ucScriptKatakana:
	case	ucScriptKatakana_Or_Hiragana:
		return langJapanese;
		break;
	case ucScriptHebrew:
		return langHebrew;
		break;
	case ucScriptThai:
		return langThai;
		break;
	case ucScriptBengali:
		return langBengala;
		break;
	case ucScriptDevanagari:
		return langHindi;
		break;

	default:
		return langUnknown;
		break;
	}
};
*/

unsigned char getLanguageFromAbbr(char *abbr) {
	// if(!strcmp(abbr, "en-GB")) return langBritish;
	// if(!strcmp(abbr, "en_AU")) return langAustralia;
	// if(!strcmp(abbr, "en-AU")) return langAustralia;
	if(!strcmp(abbr, "en_US")) return langEnglish;
	if(!strcmp(abbr, "en-US")) return langEnglish;
	if(!strcmp(abbr, "en")) return langEnglish;
	if(!strcmp(abbr, "fr")) return langFrench;
	if(!strcmp(abbr, "es_MX")) return langSpanish;
	if(!strcmp(abbr, "es-MX")) return langSpanish;
	if(!strcmp(abbr, "es")) return langSpanish;
	if(!strcmp(abbr, "ru")) return langRussian;
	if(!strcmp(abbr, "ua")) return langRussian; // ukrainian?
	if(!strcmp(abbr, "ja")) return langJapanese;
	if(!strcmp(abbr, "zh_tw")) return langChineseTrad;
	if(!strcmp(abbr, "zh_cn")) return langChineseSimp;
	if(!strcmp(abbr, "ko")) return langKorean;
	if(!strcmp(abbr, "de")) return langGerman;
	if(!strcmp(abbr, "nl")) return langDutch;
	if(!strcmp(abbr, "it")) return langItalian;
	if(!strcmp(abbr, "fi")) return langFinnish;
	if(!strcmp(abbr, "sv")) return langSwedish;
	if(!strcmp(abbr, "no")) return langNorwegian;
	if(!strcmp(abbr, "pt")) return langPortuguese;
	if(!strcmp(abbr, "vi")) return langVietnamese;
	if(!strcmp(abbr, "ar")) return langArabic;
	if(!strcmp(abbr, "he")) return langHebrew;
	if(!strcmp(abbr, "id")) return langIndonesian;
	if(!strcmp(abbr, "el")) return langGreek;
	if(!strcmp(abbr, "th")) return langThai;
	if(!strcmp(abbr, "hi")) return langHindi;
	if(!strcmp(abbr, "bn")) return langBengala;
	if(!strcmp(abbr, "pl")) return langPolish;
	if(!strcmp(abbr, "tl")) return langTagalog;
	if(!strcmp(abbr, "tr")) return langTurkish;
	return langUnknown;
}

unsigned char getLanguageFromAbbrN(char *abbr) {
	// if(!strcmp(abbr, "en-GB")) return langBritish;
	// if(!strcmp(abbr, "en_AU")) return langAustralia;
	// if(!strcmp(abbr, "en-AU")) return langAustralia;
	if(!strncasecmp(abbr, "en_US", 5)) return langEnglish;
	if(!strncasecmp(abbr, "en-US", 5)) return langEnglish;
	if(!strncasecmp(abbr, "en", 2)) return langEnglish;
	if(!strncasecmp(abbr, "fr", 2)) return langFrench;
	if(!strncasecmp(abbr, "es_MX", 5)) return langSpanish;
	if(!strncasecmp(abbr, "es-MX", 5)) return langSpanish;
	if(!strncasecmp(abbr, "es", 2)) return langSpanish;
	if(!strncasecmp(abbr, "ru", 2)) return langRussian;
	if(!strncasecmp(abbr, "ua", 2)) return langRussian; // ukrainian?
	if(!strncasecmp(abbr, "ja", 2)) return langJapanese;
	if(!strncasecmp(abbr, "zh_tw", 5)) return langChineseTrad;
	if(!strncasecmp(abbr, "zh_cn", 5)) return langChineseSimp;
	if(!strncasecmp(abbr, "ko", 2)) return langKorean;
	if(!strncasecmp(abbr, "de", 2)) return langGerman;
	if(!strncasecmp(abbr, "nl", 2)) return langDutch;
	if(!strncasecmp(abbr, "it", 2)) return langItalian;
	if(!strncasecmp(abbr, "fi", 2)) return langFinnish;
	if(!strncasecmp(abbr, "sv", 2)) return langSwedish;
	if(!strncasecmp(abbr, "no", 2)) return langNorwegian;
	if(!strncasecmp(abbr, "pt", 2)) return langPortuguese;
	if(!strncasecmp(abbr, "vi", 2)) return langVietnamese;
	if(!strncasecmp(abbr, "ar", 2)) return langArabic;
	if(!strncasecmp(abbr, "he", 2)) return langHebrew;
	if(!strncasecmp(abbr, "id", 2)) return langIndonesian;
	if(!strncasecmp(abbr, "el", 2)) return langGreek;
	if(!strncasecmp(abbr, "th", 2)) return langThai;
	if(!strncasecmp(abbr, "hi", 2)) return langHindi;
	if(!strncasecmp(abbr, "bn", 2)) return langBengala;
	if(!strncasecmp(abbr, "pl", 2)) return langPolish;
	if(!strncasecmp(abbr, "tl", 2)) return langTagalog;
	if(!strncasecmp(abbr, "tr", 2)) return langTurkish;
	return langUnknown;
}

unsigned char getLanguageFromUnicodeAbbr(char *abbr) {
	// if     (!memcmp(abbr, "e\0n\0_\0g\0b\0",10)) return langBritish;
	// else if(!memcmp(abbr, "e\0n\0-\0g\0b\0",10)) return langBritish;
	// else if(!memcmp(abbr, "e\0n\0_\0a\0u\0",10)) return langAustralia;
	// else if(!memcmp(abbr, "e\0n\0-\0a\0u\0",10)) return langAustralia;
	if(!memcmp(abbr, "en_us",5)) return langEnglish;
	if(!memcmp(abbr, "en-us",5)) return langEnglish;
	if(!memcmp(abbr, "es_mx",5)) return langSpanish;
	if(!memcmp(abbr, "es-mx",5)) return langSpanish;
	if(!memcmp(abbr, "zh_tw",5)) return langChineseTrad;
	if(!memcmp(abbr, "zh_cn",5)) return langChineseSimp;
	if(!memcmp(abbr, "en",2)) return langEnglish;
	if(!memcmp(abbr, "fr",2)) return langFrench;
	if(!memcmp(abbr, "es",2)) return langSpanish;
	if(!memcmp(abbr, "ru",2)) return langRussian;
	if(!memcmp(abbr, "ja",2)) return langJapanese;
	if(!memcmp(abbr, "ko",2)) return langKorean;
	if(!memcmp(abbr, "de",2)) return langGerman;
	if(!memcmp(abbr, "nl",2)) return langDutch;
	if(!memcmp(abbr, "it",2)) return langItalian;
	if(!memcmp(abbr, "fi",2)) return langFinnish;
	if(!memcmp(abbr, "sv",2)) return langSwedish;
	if(!memcmp(abbr, "no",2)) return langNorwegian;
	if(!memcmp(abbr, "pt",2)) return langPortuguese;
	if(!memcmp(abbr, "vi",2)) return langVietnamese;
	if(!memcmp(abbr, "ar",2)) return langArabic;
	if(!memcmp(abbr, "he",2)) return langHebrew;
	if(!memcmp(abbr, "id",2)) return langIndonesian;
	if(!memcmp(abbr, "el",2)) return langGreek;
	if(!memcmp(abbr, "th",2)) return langThai;
	if(!memcmp(abbr, "hi",2)) return langHindi;
	if(!memcmp(abbr, "bn",2)) return langBengala;
	if(!memcmp(abbr, "pl",2)) return langPolish;
	if(!memcmp(abbr, "tl",2)) return langTagalog;
	if(!memcmp(abbr, "tr",2)) return langTurkish;
	return langUnknown;
}


unsigned char getLanguageFromCountryCode(char *code) {
	// Check the ones we know are different first,
	// then revert to abbr
	if(!strcmp(code, "us")) return(langEnglish);
	if(!strcmp(code, "uk")) return(langEnglish);
	// if(!strcmp(code, "gb")) return(langBritish);
	// if(!strcmp(code, "vg")) return(langBritish);
	if(!strcmp(code, "vi")) return(langEnglish);
	// if(!strcmp(code, "au")) return(langAustralia);
	if(!strcmp(code, "ae")) return(langArabic);
	if(!strcmp(code, "cn")) return(langChineseSimp);
	if(!strcmp(code, "tw")) return(langChineseTrad);
	if(!strcmp(code, "vn")) return(langVietnamese);
	return(getLanguageFromAbbr(code));
}

// This is only here to avoid mangling the string
// as we look for tags, if at all possible use the
// getLanguageFromAbbr instead.
unsigned char getLanguageFromUserAgent(char *abbr) {
	// if(!strncmp(abbr, "en_GB", 5)) return langBritish;
	// if(!strncmp(abbr, "en-GB", 5)) return langBritish;
	// if(!strncmp(abbr, "en_AU", 5)) return langAustralia;
	// if(!strncmp(abbr, "en-AU", 5)) return langAustralia;
	if(!strncmp(abbr, "en_US", 5)) return langEnglish;
	if(!strncmp(abbr, "en-US", 5)) return langEnglish;
	if(!strncmp(abbr, "en", 2)) return langEnglish;
	if(!strncmp(abbr, "fr", 2)) return langFrench;
	if(!strncmp(abbr, "es_MX", 5)) return langSpanish;
	if(!strncmp(abbr, "es-MX", 5)) return langSpanish;
	if(!strncmp(abbr, "es", 2)) return langSpanish;
	if(!strncmp(abbr, "ru", 2)) return langRussian;
	if(!strncmp(abbr, "ja", 2)) return langJapanese;
	if(!strncmp(abbr, "zh_tw", 5)) return langChineseTrad;
	if(!strncmp(abbr, "zh_cn", 5)) return langChineseSimp;
	if(!strncmp(abbr, "ko", 2)) return langKorean;
	if(!strncmp(abbr, "de", 2)) return langGerman;
	if(!strncmp(abbr, "nl", 2)) return langDutch;
	if(!strncmp(abbr, "it", 2)) return langItalian;
	if(!strncmp(abbr, "fi", 2)) return langFinnish;
	if(!strncmp(abbr, "sv", 2)) return langSwedish;
	if(!strncmp(abbr, "no", 2)) return langNorwegian;
	if(!strncmp(abbr, "pt", 2)) return langPortuguese;
	if(!strncmp(abbr, "vi", 2)) return langVietnamese;
	if(!strncmp(abbr, "ar", 2)) return langArabic;
	if(!strncmp(abbr, "he", 2)) return langHebrew;
	if(!strncmp(abbr, "id", 2)) return langIndonesian;
	if(!strncmp(abbr, "el", 2)) return langGreek;
	if(!strncmp(abbr, "th", 2)) return langThai;
	if(!strncmp(abbr, "hi", 2)) return langHindi;
	if(!strncmp(abbr, "bn", 2)) return langBengala;
	if(!strncmp(abbr, "pl", 2)) return langPolish;
	if(!strncmp(abbr, "tl", 2)) return langTagalog;
	if(!strncmp(abbr, "tr", 2)) return langTurkish;
	return langUnknown;
}

// . these are going to be adult, in any language
// . this seems only to be used by Speller.cpp when splitting up words
//   in the url domain. 
// . s/slen is a full word that is found in our "dictionary" so using
//   phrases like biglittlestuff probably should not go here.
bool isAdult( char *s, long slen, char **loc ) {
	char **p = NULL;
	char *a = NULL;
	p = &a;
	if ( loc ) 
		p = loc;
	// check for naughty words
	if ( ( *p = strnstr ( s , slen , "upskirt"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "downblouse" ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "adult"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "shemale"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "spank"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "dildo"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "shaved"     ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "bdsm"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "voyeur"     ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "shemale"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "fisting"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "escorts"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "vibrator"   ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "rgasm"      ) ) ) return true; // 0rgasm
	if ( ( *p = strnstr ( s , slen , "orgy"       ) ) ) return true; 
	if ( ( *p = strnstr ( s , slen , "orgies"     ) ) ) return true; 
	if ( ( *p = strnstr ( s , slen , "orgasm"     ) ) ) return true; 
	if ( ( *p = strnstr ( s , slen , "masturbat"  ) ) ) return true; 
	if ( ( *p = strnstr ( s , slen , "stripper"   ) ) ) return true; 
	if ( ( *p = strnstr ( s , slen , "lolita"     ) ) ) return true; 
	//if ( ( *p = strnstr ( s , slen , "hardcore"   ) ) ) return true; ps2hardcore.co.uk
	if ( ( *p = strnstr ( s , slen , "softcore"   ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "whore"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "slut"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "smut"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "tits"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "lesbian"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "swinger"    ) ) ) return true;
	// fetish is not necessarily a porn word, like native americans
	// make "fetishes" and it was catching cakefetish.com, a food site
	//if ( ( *p = strnstr ( s , slen , "fetish"   ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "housewife"  ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "housewive"  ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "nude"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "bondage"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "centerfold" ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "incest"     ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "pedophil"   ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "pedofil"    ) ) ) return true;
	// hornyear.com
	if ( ( *p = strnstr ( s , slen , "horny"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "pussy"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "pussies"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "penis"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "vagina"     ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "phuck"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "blowjob"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "gangbang"   ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "xxx"        ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "porn"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "felch"      ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "cunt"       ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "bestial"    ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "tranny"     ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "beastial"   ) ) ) return true;
	if ( ( *p = strnstr ( s , slen , "crotch"     ) ) ) return true;
	//if ( ( *p = strnstr ( s , slen , "oral"     ) ) ) return true; // moral, doctorial, ..
	// these below may have legit meanings
	if ( ( *p = strnstr ( s , slen , "kink"       ) ) ) {
		if ( strnstr ( s , slen , "kinko" ) ) return false;// the store
		return true;
	}
	if ( ( *p = strnstr ( s , slen , "sex"      ) ) ) {
		// sexton, sextant, sextuplet, sextet
		if ( strnstr ( s , slen , "sext"       ) ) return false; 
		if ( strnstr ( s , slen , "middlesex"  ) ) return false;
		if ( strnstr ( s , slen , "sussex"     ) ) return false;
		if ( strnstr ( s , slen , "essex"      ) ) return false;
		if ( strnstr ( s , slen , "deusex"     ) ) 
			return false; // video game
		if ( strnstr ( s , slen , "sexchange"  ) ) 
			return false; // businessexh
		if ( strnstr ( s , slen , "sexpress"   ) ) 
			return false; // *express
		if ( strnstr ( s , slen , "sexpert"    ) ) 
			return false; // *expert
		if ( strnstr ( s , slen , "sexcel"     ) ) 
			return false; // *excellence
		if ( strnstr ( s , slen , "sexist"     ) ) 
			return false; // existence
		if ( strnstr ( s , slen , "sexile"     ) ) 
			return false; // existence
		if ( strnstr ( s , slen , "harassm"    ) ) 
			return false; // harassment
		if ( strnstr ( s , slen , "sexperi"    ) ) 
			return false; // experience
		if ( strnstr ( s , slen , "transex"    ) ) 
			return false; // transexual
		if ( strnstr ( s , slen , "sexual"     ) ) 
			return false; // abuse,health
		if ( strnstr ( s , slen , "sexpo"      ) ) 
			return false; // expo,expose
		if ( strnstr ( s , slen , "exoti"      ) ) 
			return false; // exotic(que)
		if ( strnstr ( s , slen , "sexclu"     ) ) 
			return false; // exclusive/de
		return true;
	}
	// www.losAnaLos.de
	// sanalcafe.net
	if ( ( *p = strnstr ( s , slen , "anal" ) ) ) {
		if ( strnstr ( s , slen , "analog"     ) ) 
			return false; // analogy
		if ( strnstr ( s , slen , "analy"      ) ) 
			return false; // analysis
		if ( strnstr ( s , slen , "canal"      ) ) 
			return false;
		if ( strnstr ( s , slen , "kanal"      ) ) 
			return false; // german
		if ( strnstr ( s , slen , "banal"      ) ) 
			return false;
		return true;
	}
	if ( ( *p = strnstr ( s , slen , "cum" ) ) ) {
		if ( strnstr ( s , slen , "circum"     ) ) 
			return false; // circumvent
		if ( strnstr ( s , slen , "magn"       ) ) 
			return false; // magna cum
		if ( strnstr ( s , slen , "succu"      ) ) 
			return false; // succumb
		if ( strnstr ( s , slen , "cumber"     ) ) 
			return false; // encumber
		if ( strnstr ( s , slen , "docum"      ) ) 
			return false; // document
		if ( strnstr ( s , slen , "cumul"      ) ) 
			return false; // accumulate
		if ( strnstr ( s , slen , "acumen"     ) ) 
			return false; // acumen
		if ( strnstr ( s , slen , "cucum"      ) ) 
			return false; // cucumber
		if ( strnstr ( s , slen , "incum"      ) ) 
			return false; // incumbent
		if ( strnstr ( s , slen , "capsicum"   ) ) return false; 
		if ( strnstr ( s , slen , "modicum"    ) ) return false; 
		if ( strnstr ( s , slen , "locum"      ) ) 
			return false; // slocum
		if ( strnstr ( s , slen , "scum"       ) ) return false; 
		if ( strnstr ( s , slen , "accu"       ) ) 
			return false; // compounds!
		// arcum.de
		// cummingscove.com
		// cumchristo.org
		return true;
	}
	//if ( ( *p = strnstr ( s , slen , "lust"        ) ) ) {
	//	if ( strnstr ( s , slen , "illust"   ) ) return false; // illustrated
	//	if ( strnstr ( s , slen , "clust"    ) ) return false; // cluster
	//	if ( strnstr ( s , slen , "blust"    ) ) return false; // bluster
	//	if ( strnstr ( s , slen , "lustrad"  ) ) return false; // balustrade
	//	// TODO: plusthemes.com wanderlust
	//	return true;
	//}
	// brettwatt.com
	//if ( ( *p = strnstr ( s , slen , "twat"       ) ) ) {
	//	if ( strnstr ( s , slen , "watch"    ) ) return false; // wristwatch
	//	if ( strnstr ( s , slen , "atwater"  ) ) return false;
	//	if ( strnstr ( s , slen , "water"    ) ) return false; // sweetwater
	//	return true;
	//}
	if ( ( *p = strnstr ( s , slen , "clit" ) ) && 
	       ! strnstr ( s , slen , "heraclitus" ) )
		return true;
	// fuckedcompany.com is ok
	if ( ( *p = strnstr ( s , slen , "fuck" ) ) && 
	       ! strnstr ( s , slen , "fuckedcomp" ) )
		return true;
	if ( ( *p = strnstr ( s , slen , "boob" ) ) && 
	       ! strnstr ( s , slen , "booboo"     ) )
		return true;
	if ( ( *p = strnstr ( s , slen , "wank" ) )&& 
	       ! strnstr ( s , slen , "swank"      ) )
		return true;
	// fick is german for fuck (fornication under consent of the king)
	if ( ( *p = strnstr ( s , slen , "fick" ) )&& 
	       ! strnstr ( s , slen , "fickle" ) &&
	       ! strnstr ( s , slen , "traffick"   ) )return true;
	// sclerotic
	// buerotipp.de
	if ( ( *p = strnstr ( s , slen , "eroti") ) && 
	       ! strnstr ( s , slen , "sclero"     ) )
		return true;
	// albaberlin.com
	// babelfish.altavista.com
	if ( ( *p = strnstr ( s , slen , "babe" ) ) && 
	       ! strnstr ( s , slen , "toyland"   ) &&
	       ! strnstr ( s , slen , "babel"      ) )
		return true;
	// what is gaya.dk?
	if ( ( *p = strnstr ( s , slen , "gay" ) ) && 
	       ! strnstr ( s , slen , "gaylord"    ) )
		return true;
	// url appears to be ok
	return false;
}
