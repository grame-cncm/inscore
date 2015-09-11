/*
	INScore Project - libMapping
	Copyright (C) 2010-2012  Grame

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
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 */

#ifndef __lmtools__
#define __lmtools__

#include <math.h>
#include <iostream>
#include "rational.h"

#ifdef WIN32
#pragma warning (disable : 4094)

inline long lround(double x) { return long(floor(x + 0.5)); }
#endif

namespace libmapping 
{

/*!
\addtogroup MISC Misc.
@{
*/


/*!
\brief relaxed equality support for rational and float values
*/
class near {
	public:
		template <typename T> static bool check (T a, T b, T precision=0 )
					{ return ((a > b) ? (a - b) : (b - a)) <= precision; }
		static bool check (rational a, rational b, rational precision=rational(1,100000))
					{ return ((a > b) ? (a - b) : (b - a)) <= precision; }
		static bool check (float a, float b, float precision=0.000005 )
					{ return ((a > b) ? (a - b) : (b - a)) <= precision; }
};

/*!
\brief base class for automatic rounding operation.

_smartdouble is specialized to provide <i> smart cast </i> operations
i.e. rounding to the nearest value instead of standard cast
*/
class _smartdouble {
	protected:	double	fValue;
	public:		_smartdouble (double v) : fValue(v) {}
};

/// see _smartdouble
template <typename T> class smartdouble : public _smartdouble {
	public:
				 smartdouble (double v) : _smartdouble(v) {}
		inline operator T () const		{ return T(fValue); }
};

/// see _smartdouble
template <> class smartdouble<int>  : public _smartdouble {
	public:
				 smartdouble (double v) : _smartdouble(v) {}
		inline operator int () const		{ return lround(fValue); }
};

/// see _smartdouble
template <> class smartdouble<long> : public _smartdouble {
	public:
				 smartdouble (double v) : _smartdouble(v) {}
		inline operator long () const		{ return lround(fValue); }
};

/// see _smartdouble
template <> class smartdouble<rational> : public _smartdouble {
	public:
				 smartdouble (double v) : _smartdouble(v) {}
		inline operator rational () const		{ return rational(fValue); }
};

template <typename T> std::ostream& operator << (std::ostream& out, const smartdouble<T>& v)  { out << T(v); return out; } 

/*! @} */

}

#endif
