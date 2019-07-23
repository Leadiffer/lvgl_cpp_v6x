/*
  WString.h - String library for Wiring & Arduino
  ...mostly rewritten by Paul Stoffregen...
  Copyright (c) 2009-10 Hernando Barragan.  All right reserved.
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

#ifndef LVSTRING_H
#define LVSTRING_H
#ifdef __cplusplus


//#ifdef ARDUINO

//#include <Arduino.h>
//using LVString = String;
//using LVStringSumHelper = StringSumHelper;

//#else

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LVMemory.h"

// When compiling programs with this class, the following gcc parameters
// dramatically increase performance and memory (RAM) efficiency, typically
// with little or no increase in code size.
//     -felide-constructors
//     -std=c++0x



// An inherited class for holding the result of a concatenation.  These
// result objects are assumed to be writable by subsequent concatenations.
class LVStringSumHelper;

// The string class

/**
 * @brief LVString
 * 实现是源自于Arduino中的WString的String类
 * 这里将原本的free realloc函数替换成lvgl的接口
 * lv_mem_free , lv_mem_realloc,便于内存管理
 */
class LVString
{
    LV_MEMORY
	// use a function pointer to allow for "if (s)" without the
	// complications of an operator bool(). for more information, see:
	// http://www.artima.com/cppsource/safebool.html
    typedef void (LVString::*StringIfHelperType)() const;
	void StringIfHelper() const {}

public:
	// constructors
	// creates a copy of the initial value.
	// if the initial value is null or invalid, or if memory allocation
	// fails, the string will be marked as invalid (i.e. "if (s)" will
	// be false).
    LVString(const char *cstr = "");
    LVString(const LVString &str);
       #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
    LVString(LVString &&rval);
    LVString(LVStringSumHelper &&rval);
	#endif
    explicit LVString(char c);
    explicit LVString(unsigned char, unsigned char base=10);
    explicit LVString(int, unsigned char base=10);
    explicit LVString(unsigned int, unsigned char base=10);
    explicit LVString(long, unsigned char base=10);
    explicit LVString(unsigned long, unsigned char base=10);
    explicit LVString(float, unsigned char decimalPlaces=2);
    explicit LVString(double, unsigned char decimalPlaces=2);
    ~LVString(void);

	// memory management
	// return true on success, false on failure (in which case, the string
	// is left unchanged).  reserve(0), if successful, will validate an
	// invalid string (i.e., "if (s)" will be true afterwards)
	unsigned char reserve(unsigned int size);
	inline unsigned int length(void) const {return len;}

	// creates a copy of the assigned value.  if the value is null or
	// invalid, or if the memory allocation fails, the string will be
	// marked as invalid ("if (s)" will be false).
    LVString & operator = (const LVString &rhs);
    LVString & operator = (const char *cstr);
       #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
    LVString & operator = (LVString &&rval);
    LVString & operator = (LVStringSumHelper &&rval);
	#endif

	// concatenate (works w/ built-in types)

	// returns true on success, false on failure (in which case, the string
	// is left unchanged).  if the argument is null or invalid, the
	// concatenation is considered unsucessful.
    unsigned char concat(const LVString &str);
	unsigned char concat(const char *cstr);
	unsigned char concat(char c);
	unsigned char concat(unsigned char c);
	unsigned char concat(int num);
	unsigned char concat(unsigned int num);
	unsigned char concat(long num);
	unsigned char concat(unsigned long num);
	unsigned char concat(float num);
	unsigned char concat(double num);

	// if there's not enough memory for the concatenated value, the string
	// will be left unchanged (but this isn't signalled in any way)
    LVString & operator += (const LVString &rhs)	{concat(rhs); return (*this);}
    LVString & operator += (const char *cstr)		{concat(cstr); return (*this);}
    LVString & operator += (char c)			{concat(c); return (*this);}
    LVString & operator += (unsigned char num)		{concat(num); return (*this);}
    LVString & operator += (int num)			{concat(num); return (*this);}
    LVString & operator += (unsigned int num)		{concat(num); return (*this);}
    LVString & operator += (long num)			{concat(num); return (*this);}
    LVString & operator += (unsigned long num)	{concat(num); return (*this);}
    LVString & operator += (float num)		{concat(num); return (*this);}
    LVString & operator += (double num)		{concat(num); return (*this);}

    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, const LVString &rhs);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, const char *cstr);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, char c);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, unsigned char num);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, int num);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, unsigned int num);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, long num);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, unsigned long num);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, float num);
    friend LVStringSumHelper & operator + (const LVStringSumHelper &lhs, double num);

	// comparison (only works w/ Strings and "strings")
    operator StringIfHelperType() const { return buffer ? &LVString::StringIfHelper : 0; }
    int compareTo(const LVString &s) const;
    unsigned char equals(const LVString &s) const;
	unsigned char equals(const char *cstr) const;
    unsigned char operator == (const LVString &rhs) const {return equals(rhs);}
	unsigned char operator == (const char *cstr) const {return equals(cstr);}
    unsigned char operator != (const LVString &rhs) const {return !equals(rhs);}
	unsigned char operator != (const char *cstr) const {return !equals(cstr);}
    unsigned char operator <  (const LVString &rhs) const;
    unsigned char operator >  (const LVString &rhs) const;
    unsigned char operator <= (const LVString &rhs) const;
    unsigned char operator >= (const LVString &rhs) const;
    unsigned char equalsIgnoreCase(const LVString &s) const;
    unsigned char startsWith( const LVString &prefix) const;
    unsigned char startsWith(const LVString &prefix, unsigned int offset) const;
    unsigned char endsWith(const LVString &suffix) const;

	// character acccess
	char charAt(unsigned int index) const;
	void setCharAt(unsigned int index, char c);
	char operator [] (unsigned int index) const;
	char& operator [] (unsigned int index);
	void getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index=0) const;
	void toCharArray(char *buf, unsigned int bufsize, unsigned int index=0) const
		{ getBytes((unsigned char *)buf, bufsize, index); }
    const char* c_str() const { return buffer; }
    operator const char* () const { return buffer; }
	char* begin() { return buffer; }
	char* end() { return buffer + length(); }
	const char* begin() const { return c_str(); }
	const char* end() const { return c_str() + length(); }

	// search
	int indexOf( char ch ) const;
	int indexOf( char ch, unsigned int fromIndex ) const;
    int indexOf( const LVString &str ) const;
    int indexOf( const LVString &str, unsigned int fromIndex ) const;
	int lastIndexOf( char ch ) const;
	int lastIndexOf( char ch, unsigned int fromIndex ) const;
    int lastIndexOf( const LVString &str ) const;
    int lastIndexOf( const LVString &str, unsigned int fromIndex ) const;
    LVString substring( unsigned int beginIndex ) const { return substring(beginIndex, len); };
    LVString substring( unsigned int beginIndex, unsigned int endIndex ) const;

	// modification
	void replace(char find, char replace);
    void replace(const LVString& find, const LVString& replace);
	void remove(unsigned int index);
	void remove(unsigned int index, unsigned int count);
	void toLowerCase(void);
	void toUpperCase(void);
	void trim(void);

	// parsing/conversion
	long toInt(void) const;
	float toFloat(void) const;
	double toDouble(void) const;

protected:
	char *buffer;	        // the actual char array
	unsigned int capacity;  // the array length minus one (for the '\0')
	unsigned int len;       // the String length (not counting the '\0')
protected:
	void init(void);
	void invalidate(void);
	unsigned char changeBuffer(unsigned int maxStrLen);
	unsigned char concat(const char *cstr, unsigned int length);

	// copy and move
    LVString & copy(const char *cstr, unsigned int length);
       #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
    void move(LVString &rhs);
	#endif
};

class LVStringSumHelper : public LVString
{
public:
    LVStringSumHelper(const LVString &s) : LVString(s) {}
    LVStringSumHelper(const char *p) : LVString(p) {}
    LVStringSumHelper(char c) : LVString(c) {}
    LVStringSumHelper(unsigned char num) : LVString(num) {}
    LVStringSumHelper(int num) : LVString(num) {}
    LVStringSumHelper(unsigned int num) : LVString(num) {}
    LVStringSumHelper(long num) : LVString(num) {}
    LVStringSumHelper(unsigned long num) : LVString(num) {}
    LVStringSumHelper(float num) : LVString(num) {}
    LVStringSumHelper(double num) : LVString(num) {}
};
//#endif  // ARDUINO
#endif  // __cplusplus
#endif  // LVSTRING_H
