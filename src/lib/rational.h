/*
  Copyright (c) Grame 2009-2010

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

#ifndef __rational__
#define __rational__

#include <string>
#include <ostream>
#include <vector>
#include "export.h"

class OSCStream;
class IMessage;

namespace inscore
{

typedef long long rationalSize;

/*!
\brief	Rational number representation.
*/
class export rational 
{
   protected:
        rationalSize fNumerator;
        rationalSize fDenominator;        
      // Used by rationalise()
        rationalSize gcd ( rationalSize a, rationalSize b );
 
    public:	
  
        rational(int num);
        rational(int num, int denum);
        rational(long num, long denum);
        rational(long long num = 0, long long denom = 1);
        rational(const rational& d);
		rational(const rational& num, const rational& denom);
        rational(const std::string &str);
        rational(double f)							{ *this = f; }
        rational(double n, double d)				{ *this = n/d; }
    
        rationalSize getNumerator()	const			{ return fNumerator; }
        rationalSize getDenominator() const			{ return fDenominator; }
        void		setNumerator(long int d)		{ fNumerator = d; }
        void		setDenominator(long int d)		{ fDenominator = d; }
		void		set(long int n, long int d)		{ fNumerator = n; fDenominator = d; }
 
		rational& operator =(const rational& dur);
		rational& operator =(int dur)				{ fNumerator = dur; fDenominator = 1; return (*this); }
		rational& operator =(float f);
		rational& operator =(double f);
    
        rational operator +(const rational &dur) const;
        rational operator -(const rational &dur) const;
        rational operator *(const rational &dur) const; 
        rational operator /(const rational &dur) const;
        rational operator *(int num) const; 
        rational operator /(int num) const;
        rational operator *(long int num) const; 
        rational operator /(long int num) const;
        rational operator *(float num) const; 
        rational operator /(float num) const;
        rational operator *(double num) const; 
        rational operator /(double num) const;
  
        rational& operator +=(const rational &dur);
        rational& operator -=(const rational &dur);
        rational& operator *=(const rational &dur); 
        rational& operator /=(const rational &dur); 
        rational& operator *=(long int num);
        rational& operator /=(long int num);
 
        bool operator >(const rational &dur) const;
        bool operator >=(const rational &dur) const 	{ return !(*this < dur);}
        bool operator <(const rational &dur) const;
        bool operator <=(const rational &dur) const 	{ return !(*this > dur);}
        bool operator ==(const rational &dur) const;
        bool operator !=(const rational &dur) const		{ return !(*this == dur);}
      
        bool operator >	(double num) const;
        bool operator >=(double num) const;
        bool operator <	(double num) const;
        bool operator <=(double num) const;    
        bool operator ==(double) const;
       
        operator std::string () const;
		operator double () const;
		operator float () const;
		operator int () const; 
		operator long () const; 
		operator bool () const; 

        // Used to "rationalize" rational.
        void rationalize();

        // Used to "rationalize" rational.
        template <typename T> void print(T& out) const { out << getNumerator() << getDenominator(); }
};

#ifndef NO_OSCSTREAM
OSCStream&		operator << (OSCStream& out, const rational& r);
#endif
IMessage&		operator << (IMessage& out, const rational& r);
std::ostream&	operator << (std::ostream& out, const rational& r);

} // end namespace

#endif
