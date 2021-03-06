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

#ifndef _TIMER_H_
#define _TIMER_H_

class Timer { 
public:
        Timer () : m_start(0), m_end(0) {};
	Timer ( long long startTime ) : m_start(startTime), m_end(0) {};
	virtual ~Timer() {};

	virtual void start () { m_start = gettimeofdayInMillisecondsLocal(); };
	virtual void stop  () { m_end   = gettimeofdayInMillisecondsLocal(); };

	long long getSpan () { return m_end-m_start; };

	long long m_start;
	long long m_end;
};

class AutoTimer : public Timer {
public:
	AutoTimer  ( char *subtype, char *name, char *klass = NULL ) 
		: Timer(), m_subtype(subtype), m_name(name), m_class(klass) { 
		start(); };
	~AutoTimer () {
		stop();
		if ( m_class ) 
			log( LOG_TIMING, "%s: Took %lld ms for %s::%s", 
			     m_subtype, getSpan(), m_class, m_name );
		else
			log( LOG_TIMING, "%s: Took %lld ms for %s", 
			     m_subtype, getSpan(), m_name );
	};

	char *m_subtype;
	char *m_name;
	char *m_class;
};

class MicroTimer {
public:
	MicroTimer () : m_start(0), m_end(0) {};
	virtual ~MicroTimer () {};

	virtual void start () { m_start = gettimeofdayInMicroseconds(); };
	virtual void stop  () { m_end   = gettimeofdayInMicroseconds(); };

	uint64_t getSpan () { return m_end-m_start; };

	uint64_t m_start;
	uint64_t m_end;
};


class AutoMicroTimer : public MicroTimer {
public:
	AutoMicroTimer  ( char *subtype, char *name, char *klass = NULL ) 
		: MicroTimer(), m_subtype(subtype), m_name(name), m_class(klass) { 
		start(); };
	~AutoMicroTimer () {
		stop();
		if ( m_class ) 
			log( LOG_TIMING, "%s: Took %llu microseconds for %s::%s",
			     m_subtype, getSpan(), m_class, m_name );
		else
			log( LOG_TIMING, "%s: Took %llu microseconds for %s", 
			     m_subtype, getSpan(), m_name );
	};

	char *m_subtype;
	char *m_name;
	char *m_class;
};

#endif // _TIMER_H_
