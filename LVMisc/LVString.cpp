/*
  WString.cpp - String library for Wiring & Arduino
  ...mostly rewritten by Paul Stoffregen...
  Copyright (c) 2009-10 Hernando Barragan.  All rights reserved.
  Copyright 2011, Paul Stoffregen, paul@pjrc.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "LVString.h"
#include "lv_misc/lv_mem.h"

#ifndef WIN32
static void itoa(unsigned int value,char *buf, unsigned char base)
{
    sprintf(buf,
            base==10?"%d":
            base==8?"%o":
            base==16?"%x":
            "%d",
            value);
}
#endif

static void utoa(unsigned int value,char *buf, unsigned char base)
{
    sprintf(buf,
            base==10?"%d":
            base==8?"%o":
            base==16?"%x":
            "%d",
            value);
}

static void ultoa(unsigned long value,char *buf, unsigned char base)
{
    sprintf(buf,
            base==10?"%ld":
            base==8?"%lo":
            base==16?"%lx":
            "%ld",
            value);
}

#ifndef WIN32
static void ltoa(unsigned long value,char *buf, unsigned char base)
{
    sprintf(buf,
            base==10?"%ld":
            base==8?"%lo":
            base==16?"%lx":
            "%ld",
            value);
}
#endif

static char* dtostrf(double _val,signed char _width,unsigned char _prec,char* _s)
{
    sprintf(_s,"%*.*f",_width,_prec,_val);
    return _s;
}

/*********************************************/
/*  Constructors                             */
/*********************************************/

LVString::LVString(const char *cstr)
{
	init();
	if (cstr) copy(cstr, strlen(cstr));
}

LVString::LVString(const LVString &value)
{
	init();
	*this = value;
}

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
LVString::LVString(LVString &&rval)
{
	init();
	move(rval);
}
LVString::LVString(LVStringSumHelper &&rval)
{
	init();
	move(rval);
}
#endif

LVString::LVString(char c)
{
	init();
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	*this = buf;
}

LVString::LVString(unsigned char value, unsigned char base)
{
	init();
	char buf[1 + 8 * sizeof(unsigned char)];
    utoa(value, buf, base);
	*this = buf;
}

LVString::LVString(int value, unsigned char base)
{
	init();
	char buf[2 + 8 * sizeof(int)];
	itoa(value, buf, base);
	*this = buf;
}

LVString::LVString(unsigned int value, unsigned char base)
{
	init();
	char buf[1 + 8 * sizeof(unsigned int)];
	utoa(value, buf, base);
	*this = buf;
}

LVString::LVString(long value, unsigned char base)
{
	init();
	char buf[2 + 8 * sizeof(long)];
	ltoa(value, buf, base);
	*this = buf;
}

LVString::LVString(unsigned long value, unsigned char base)
{
	init();
	char buf[1 + 8 * sizeof(unsigned long)];
	ultoa(value, buf, base);
	*this = buf;
}

LVString::LVString(float value, unsigned char decimalPlaces)
{
	init();
	char buf[33];
	*this = dtostrf(value, (decimalPlaces + 2), decimalPlaces, buf);
}

LVString::LVString(double value, unsigned char decimalPlaces)
{
	init();
	char buf[33];
	*this = dtostrf(value, (decimalPlaces + 2), decimalPlaces, buf);
}

LVString::~LVString()
{
    lv_mem_free(buffer);
}

/*********************************************/
/*  Memory Management                        */
/*********************************************/

inline void LVString::init(void)
{
	buffer = NULL;
	capacity = 0;
	len = 0;
}

void LVString::invalidate(void)
{
    if (buffer) lv_mem_free(buffer);
	buffer = NULL;
	capacity = len = 0;
}

unsigned char LVString::reserve(unsigned int size)
{
	if (buffer && capacity >= size) return 1;
	if (changeBuffer(size)) {
		if (len == 0) buffer[0] = 0;
		return 1;
	}
	return 0;
}

unsigned char LVString::changeBuffer(unsigned int maxStrLen)
{
    char *newbuffer = (char *) lv_mem_realloc(buffer, maxStrLen + 1);
	if (newbuffer) {
		buffer = newbuffer;
		capacity = maxStrLen;
		return 1;
	}
	return 0;
}

/*********************************************/
/*  Copy and Move                            */
/*********************************************/

LVString & LVString::copy(const char *cstr, unsigned int length)
{
	if (!reserve(length)) {
		invalidate();
		return *this;
	}
	len = length;
	strcpy(buffer, cstr);
	return *this;
}

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
void LVString::move(LVString &rhs)
{
	if (buffer) {
        if (rhs.buffer && capacity >= rhs.len) {
			strcpy(buffer, rhs.buffer);
			len = rhs.len;
			rhs.len = 0;
			return;
		} else {
			free(buffer);
		}
	}
	buffer = rhs.buffer;
	capacity = rhs.capacity;
	len = rhs.len;
	rhs.buffer = NULL;
	rhs.capacity = 0;
	rhs.len = 0;
}
#endif

LVString & LVString::operator = (const LVString &rhs)
{
	if (this == &rhs) return *this;
	
	if (rhs.buffer) copy(rhs.buffer, rhs.len);
	else invalidate();
	
	return *this;
}

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
LVString & LVString::operator = (LVString &&rval)
{
	if (this != &rval) move(rval);
	return *this;
}

LVString & LVString::operator = (LVStringSumHelper &&rval)
{
	if (this != &rval) move(rval);
	return *this;
}
#endif

LVString & LVString::operator = (const char *cstr)
{
	if (cstr) copy(cstr, strlen(cstr));
	else invalidate();
	
	return *this;
}

/*********************************************/
/*  concat                                   */
/*********************************************/

unsigned char LVString::concat(const LVString &s)
{
	return concat(s.buffer, s.len);
}

unsigned char LVString::concat(const char *cstr, unsigned int length)
{
	unsigned int newlen = len + length;
	if (!cstr) return 0;
	if (length == 0) return 1;
	if (!reserve(newlen)) return 0;
	strcpy(buffer + len, cstr);
	len = newlen;
	return 1;
}

unsigned char LVString::concat(const char *cstr)
{
	if (!cstr) return 0;
	return concat(cstr, strlen(cstr));
}

unsigned char LVString::concat(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	return concat(buf, 1);
}

unsigned char LVString::concat(unsigned char num)
{
	char buf[1 + 3 * sizeof(unsigned char)];
	itoa(num, buf, 10);
	return concat(buf, strlen(buf));
}

unsigned char LVString::concat(int num)
{
	char buf[2 + 3 * sizeof(int)];
	itoa(num, buf, 10);
	return concat(buf, strlen(buf));
}

unsigned char LVString::concat(unsigned int num)
{
	char buf[1 + 3 * sizeof(unsigned int)];
	utoa(num, buf, 10);
	return concat(buf, strlen(buf));
}

unsigned char LVString::concat(long num)
{
	char buf[2 + 3 * sizeof(long)];
	ltoa(num, buf, 10);
	return concat(buf, strlen(buf));
}

unsigned char LVString::concat(unsigned long num)
{
	char buf[1 + 3 * sizeof(unsigned long)];
    ultoa(num, buf, (unsigned char)10);
	return concat(buf, strlen(buf));
}

unsigned char LVString::concat(float num)
{
	char buf[20];
	char* string = dtostrf(num, 4, 2, buf);
	return concat(string, strlen(string));
}

unsigned char LVString::concat(double num)
{
	char buf[20];
	char* string = dtostrf(num, 4, 2, buf);
	return concat(string, strlen(string));
}

/*********************************************/
/*  Concatenate                              */
/*********************************************/

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, const LVString &rhs)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(rhs.buffer, rhs.len)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, const char *cstr)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!cstr || !a.concat(cstr, strlen(cstr))) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, char c)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(c)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, unsigned char num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, int num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, unsigned int num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, long num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, unsigned long num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, float num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

LVStringSumHelper & operator + (const LVStringSumHelper &lhs, double num)
{
    LVStringSumHelper &a = const_cast<LVStringSumHelper&>(lhs);
	if (!a.concat(num)) a.invalidate();
	return a;
}

/*********************************************/
/*  Comparison                               */
/*********************************************/

int LVString::compareTo(const LVString &s) const
{
	if (!buffer || !s.buffer) {
		if (s.buffer && s.len > 0) return 0 - *(unsigned char *)s.buffer;
		if (buffer && len > 0) return *(unsigned char *)buffer;
		return 0;
	}
	return strcmp(buffer, s.buffer);
}

unsigned char LVString::equals(const LVString &s2) const
{
	return (len == s2.len && compareTo(s2) == 0);
}

unsigned char LVString::equals(const char *cstr) const
{
	if (len == 0) return (cstr == NULL || *cstr == 0);
	if (cstr == NULL) return buffer[0] == 0;
	return strcmp(buffer, cstr) == 0;
}

unsigned char LVString::operator<(const LVString &rhs) const
{
	return compareTo(rhs) < 0;
}

unsigned char LVString::operator>(const LVString &rhs) const
{
	return compareTo(rhs) > 0;
}

unsigned char LVString::operator<=(const LVString &rhs) const
{
	return compareTo(rhs) <= 0;
}

unsigned char LVString::operator>=(const LVString &rhs) const
{
	return compareTo(rhs) >= 0;
}

unsigned char LVString::equalsIgnoreCase( const LVString &s2 ) const
{
	if (this == &s2) return 1;
	if (len != s2.len) return 0;
	if (len == 0) return 1;
	const char *p1 = buffer;
	const char *p2 = s2.buffer;
	while (*p1) {
		if (tolower(*p1++) != tolower(*p2++)) return 0;
	} 
	return 1;
}

unsigned char LVString::startsWith( const LVString &s2 ) const
{
	if (len < s2.len) return 0;
	return startsWith(s2, 0);
}

unsigned char LVString::startsWith( const LVString &s2, unsigned int offset ) const
{
	if (offset > len - s2.len || !buffer || !s2.buffer) return 0;
	return strncmp( &buffer[offset], s2.buffer, s2.len ) == 0;
}

unsigned char LVString::endsWith( const LVString &s2 ) const
{
	if ( len < s2.len || !buffer || !s2.buffer) return 0;
	return strcmp(&buffer[len - s2.len], s2.buffer) == 0;
}

/*********************************************/
/*  Character Access                         */
/*********************************************/

char LVString::charAt(unsigned int loc) const
{
	return operator[](loc);
}

void LVString::setCharAt(unsigned int loc, char c)
{
	if (loc < len) buffer[loc] = c;
}

char & LVString::operator[](unsigned int index)
{
	static char dummy_writable_char;
	if (index >= len || !buffer) {
		dummy_writable_char = 0;
		return dummy_writable_char;
	}
	return buffer[index];
}

char LVString::operator[]( unsigned int index ) const
{
	if (index >= len || !buffer) return 0;
	return buffer[index];
}

void LVString::getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index) const
{
	if (!bufsize || !buf) return;
	if (index >= len) {
		buf[0] = 0;
		return;
	}
	unsigned int n = bufsize - 1;
	if (n > len - index) n = len - index;
	strncpy((char *)buf, buffer + index, n);
	buf[n] = 0;
}

/*********************************************/
/*  Search                                   */
/*********************************************/

int LVString::indexOf(char c) const
{
	return indexOf(c, 0);
}

int LVString::indexOf( char ch, unsigned int fromIndex ) const
{
	if (fromIndex >= len) return -1;
	const char* temp = strchr(buffer + fromIndex, ch);
	if (temp == NULL) return -1;
	return temp - buffer;
}

int LVString::indexOf(const LVString &s2) const
{
	return indexOf(s2, 0);
}

int LVString::indexOf(const LVString &s2, unsigned int fromIndex) const
{
	if (fromIndex >= len) return -1;
	const char *found = strstr(buffer + fromIndex, s2.buffer);
	if (found == NULL) return -1;
	return found - buffer;
}

int LVString::lastIndexOf( char theChar ) const
{
	return lastIndexOf(theChar, len - 1);
}

int LVString::lastIndexOf(char ch, unsigned int fromIndex) const
{
	if (fromIndex >= len) return -1;
	char tempchar = buffer[fromIndex + 1];
	buffer[fromIndex + 1] = '\0';
	char* temp = strrchr( buffer, ch );
	buffer[fromIndex + 1] = tempchar;
	if (temp == NULL) return -1;
	return temp - buffer;
}

int LVString::lastIndexOf(const LVString &s2) const
{
	return lastIndexOf(s2, len - s2.len);
}

int LVString::lastIndexOf(const LVString &s2, unsigned int fromIndex) const
{
  	if (s2.len == 0 || len == 0 || s2.len > len) return -1;
	if (fromIndex >= len) fromIndex = len - 1;
	int found = -1;
	for (char *p = buffer; p <= buffer + fromIndex; p++) {
		p = strstr(p, s2.buffer);
		if (!p) break;
		if ((unsigned int)(p - buffer) <= fromIndex) found = p - buffer;
	}
	return found;
}

LVString LVString::substring(unsigned int left, unsigned int right) const
{
	if (left > right) {
		unsigned int temp = right;
		right = left;
		left = temp;
	}
    LVString out;
	if (left >= len) return out;
	if (right > len) right = len;
	char temp = buffer[right];  // save the replaced character
	buffer[right] = '\0';	
	out = buffer + left;  // pointer arithmetic
	buffer[right] = temp;  //restore character
	return out;
}

/*********************************************/
/*  Modification                             */
/*********************************************/

void LVString::replace(char find, char replace)
{
	if (!buffer) return;
	for (char *p = buffer; *p; p++) {
		if (*p == find) *p = replace;
	}
}

void LVString::replace(const LVString& find, const LVString& replace)
{
	if (len == 0 || find.len == 0) return;
	int diff = replace.len - find.len;
	char *readFrom = buffer;
	char *foundAt;
	if (diff == 0) {
		while ((foundAt = strstr(readFrom, find.buffer)) != NULL) {
			memcpy(foundAt, replace.buffer, replace.len);
			readFrom = foundAt + replace.len;
		}
	} else if (diff < 0) {
		char *writeTo = buffer;
		while ((foundAt = strstr(readFrom, find.buffer)) != NULL) {
			unsigned int n = foundAt - readFrom;
			memcpy(writeTo, readFrom, n);
			writeTo += n;
			memcpy(writeTo, replace.buffer, replace.len);
			writeTo += replace.len;
			readFrom = foundAt + find.len;
			len += diff;
		}
		strcpy(writeTo, readFrom);
	} else {
		unsigned int size = len; // compute size needed for result
		while ((foundAt = strstr(readFrom, find.buffer)) != NULL) {
			readFrom = foundAt + find.len;
			size += diff;
		}
		if (size == len) return;
		if (size > capacity && !changeBuffer(size)) return; // XXX: tell user!
		int index = len - 1;
		while (index >= 0 && (index = lastIndexOf(find, index)) >= 0) {
			readFrom = buffer + index + find.len;
			memmove(readFrom + diff, readFrom, len - (readFrom - buffer));
			len += diff;
			buffer[len] = 0;
			memcpy(buffer + index, replace.buffer, replace.len);
			index--;
		}
	}
}

void LVString::remove(unsigned int index){
	// Pass the biggest integer as the count. The remove method
	// below will take care of truncating it at the end of the
	// string.
	remove(index, (unsigned int)-1);
}

void LVString::remove(unsigned int index, unsigned int count){
	if (index >= len) { return; }
	if (count <= 0) { return; }
	if (count > len - index) { count = len - index; }
	char *writeTo = buffer + index;
	len = len - count;
	strncpy(writeTo, buffer + index + count,len - index);
	buffer[len] = 0;
}

void LVString::toLowerCase(void)
{
	if (!buffer) return;
	for (char *p = buffer; *p; p++) {
		*p = tolower(*p);
	}
}

void LVString::toUpperCase(void)
{
	if (!buffer) return;
	for (char *p = buffer; *p; p++) {
		*p = toupper(*p);
	}
}

void LVString::trim(void)
{
	if (!buffer || len == 0) return;
	char *begin = buffer;
	while (isspace(*begin)) begin++;
	char *end = buffer + len - 1;
	while (isspace(*end) && end >= begin) end--;
	len = end + 1 - begin;
	if (begin > buffer) memcpy(buffer, begin, len);
	buffer[len] = 0;
}

/*********************************************/
/*  Parsing / Conversion                     */
/*********************************************/

long LVString::toInt(void) const
{
	if (buffer) return atol(buffer);
	return 0;
}

float LVString::toFloat(void) const
{
	return float(toDouble());
}

double LVString::toDouble(void) const
{
	if (buffer) return atof(buffer);
	return 0;
}
