/*
  Copyright (c) Grame 2003

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#include <iostream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <string.h>

#include "rational.h"

using namespace std;

namespace libmapping
{

// ------------------------------------------------------------------------------
// constructors
// ------------------------------------------------------------------------------
rational::rational(const string &str) : fNumerator(0), fDenominator(1)
{
	istringstream buffer(str);
	buffer >> fNumerator;
	if (!buffer.fail()) {
		char slash;
		buffer >> slash;
		buffer >> fDenominator;
	}
	if (buffer.fail()) {
		fNumerator  = 0;
		fDenominator = 0;
	}
}

rational::rational(int num) : fNumerator(num), fDenominator(1)	{}
rational::rational(int num, int denum) : fNumerator(num), fDenominator(denum)	{}
rational::rational(long num, long denum) : fNumerator(num), fDenominator(denum)	{}
rational::rational(long long num, long long denom) : fNumerator(num), fDenominator(denom)	{}
rational::rational(const rational& d) : fNumerator(d.fNumerator), fDenominator(d.fDenominator) {}
rational::rational(const rational& num, const rational& denom) 
	: fNumerator(num.fNumerator * denom.fDenominator), fDenominator(denom.fNumerator * num.fDenominator) { rationalize(); }

// ------------------------------------------------------------------------------
// assignment
// ------------------------------------------------------------------------------
rational& rational::operator =(const rational& dur) {
    fNumerator   = dur.fNumerator;
    fDenominator = dur.fDenominator;
	return *this; 
}

//#define MAXCONV (111546435 << 1)		// actually 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23
#define MAXCONV (5105100)				// actually 2 * 3 * 5 * 7 * 11 * 13 * 17 * 10
rational& rational::operator =(double f) {
	long lf = long(f > 0 ? f : -f);
	long mult = MAXCONV / (lf ? lf : 1);
    fNumerator   = rationalSize(f * mult);
    fDenominator = mult;
	rationalize();
	return *this; 
}

// ------------------------------------------------------------------------------
// operations
// ------------------------------------------------------------------------------
rational rational::operator +(const rational &dur) const {
    rational r(rationalSize((fNumerator * dur.fDenominator) + (dur.fNumerator * fDenominator)), fDenominator * dur.fDenominator);
	r. rationalize();
	return r;
}

rational rational::operator -(const rational &dur) const {
	rational r(fNumerator * dur.fDenominator - dur.fNumerator * fDenominator, fDenominator * dur.fDenominator);
	r. rationalize();
	return r;
}

rational rational::operator *(const rational &dur) const {
	rational r(fNumerator * dur.fNumerator, fDenominator * dur.fDenominator);
	r. rationalize();
	return r;
}

rational rational::operator /(const rational &dur) const {
	rational r(fNumerator * dur.fDenominator, fDenominator * dur.fNumerator);
	r. rationalize();
	return r;
}

rational rational::operator *(int num) const { 
	rational r(fNumerator * num, fDenominator);
	r. rationalize();
	return r;
}

rational rational::operator /(int num) const { 
	rational r(fNumerator, fDenominator * num); 
	r. rationalize();
	return r;
}

rational rational::operator *(long int num) const { 
	rational r(fNumerator * num, fDenominator);
	r. rationalize();
	return r;
}

rational rational::operator /(long int num) const { 
	rational r(fNumerator, fDenominator * num); 
	r. rationalize();
	return r;
}

rational rational::operator *(float num) const { 
	rational r(num);
	return this->operator *(r);
}

rational rational::operator /(float num) const { 
	rational r(num);
	return this->operator /(r);
}

rational rational::operator *(double num) const { 
	rational r(num);
	return this->operator *(r);
}

rational rational::operator /(double num) const { 
	rational r(num);
	return this->operator /(r);
}

rational& rational::operator +=(const rational &dur)
{
    if(fDenominator == dur.fDenominator) {
		fNumerator += dur.fNumerator;
	} else {
		fNumerator = fNumerator * dur.fDenominator + dur.fNumerator * fDenominator;
		fDenominator *= dur.fDenominator;
		rationalize();
	}
	return *this; 
}

rational& rational::operator -=(const rational &dur)
{
	if(fDenominator == dur.fDenominator) {
		fNumerator -= dur.fNumerator;
	} else {
		fNumerator = fNumerator * dur.fDenominator - dur.fNumerator * fDenominator;
		fDenominator *= dur.fDenominator;
		rationalize();
    }	
	return (*this);
}

rational& rational::operator *=(const rational &dur)
{
    fNumerator   *= dur.fNumerator;
    fDenominator *= dur.fDenominator;
	rationalize();
	return *this; 
}

rational& rational::operator /=(const rational &dur)
{
    fNumerator   *= dur.fDenominator;
    fDenominator *= dur.fNumerator;
	rationalize();
	return *this; 
}

rational& rational::operator *=(long int num) { 
	fNumerator *= num;
	rationalize();
	return *this; 
}

rational& rational::operator /=(long int num) { 
	fDenominator *= num; 
	rationalize();
	return *this; 
}


// ------------------------------------------------------------------------------
// operators
// ------------------------------------------------------------------------------
bool rational::operator >(const rational &dur) const
{
	// a/b > c/d if and only if a * d > b * c.
	return ((fNumerator * dur.fDenominator) > (fDenominator * dur.fNumerator));
}

bool rational::operator <(const rational &dur) const
{
    // a/b < c/d if and only if a * d < b * c.
    return ((fNumerator * dur.fDenominator) < (fDenominator * dur.fNumerator));
}

bool rational::operator ==(const rational &dur) const
{
    // a/b == c/d if a * d == b * c.
	// doesn't work when one of the rational is 0/0
	return ((fNumerator * dur.fDenominator) == (fDenominator * dur.fNumerator));
}

bool rational::operator >(double num) const		{ return (double(*this) > num); }
bool rational::operator >= (double num) const	{ return (double(*this) >= num); }
bool rational::operator <(double num) const		{ return (double(*this) < num); }
bool rational::operator <=(double num) const	{ return (double(*this) <= num); }
bool rational::operator ==(double num) const	{ return (double(*this) == num); }


rational::operator string() const
{
    ostringstream res;
    res << fNumerator << "/" << fDenominator;
    return res.str();
}

rational::operator double() const	{ return (fDenominator != 0) ? ((double)fNumerator/(double)fDenominator) : 0; }
rational::operator float() const	{ return (fDenominator != 0) ? ((float)fNumerator/(float)fDenominator) : 0; }
rational::operator int() const		{ return int(floor(double(*this) + 0.5f)); }
rational::operator long() const		{ return long(floor(double(*this) + 0.5f)); }
rational::operator bool() const		{ return (fNumerator != 0) && (fDenominator != 0); }


// ------------------------------------------------------------------------------
// gcd(a, b) calculates the gcd of a and b using Euclid's algorithm.
rationalSize rational::gcd(rationalSize a1, rationalSize b1)
{
    rationalSize r;
	rationalSize a = (a1 < 0) ? -a1 : a1;
	rationalSize b = (b1 < 0) ? -b1 : b1;

    if (a && b) {
        while (b > 0){
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
    return 1;
}

void rational::rationalize()
{
    rationalSize g = gcd(fNumerator, fDenominator);
	fNumerator /= g;
    fDenominator /= g;
    if (fNumerator == 0) fDenominator = 1;
}

// ------------------------------------------------------------------------------
std::ostream&	operator << (std::ostream& out, const rational& r)	{ out << string(r); return out; }

} // end namespace
