/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __TTRect__
#define __TTRect__

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "TSegment.h"

namespace inscore
{

//--------------------------------------------------------------------------
/*!
	\brief a two dimensions location
*/
template<typename T> class TPoint
{
	public :
		T fX;
		T fY;

				 TPoint()							: fX(0), fY(0) {}
				 TPoint(T x)						: fX(x), fY(x) {}
				 TPoint(T x, T y)					: fX(x), fY(y) {}
				 TPoint(const TPoint& p)			: fX(p.fX), fY(p.fY) {}
		virtual ~TPoint() {}

		/// TPoint conversion to string
		operator std::string () const {
			std::ostringstream res;
			res << "[" << fX << "," << fY << "]";
			return res.str();
		}
		
		inline T x() const		{ return fX; }
		inline T y() const		{ return fY; }
		
		TPoint<T> operator * ( const T& f ) const	{ return TPoint<T>( fX * f , fY * f ); }
		TPoint<T> operator / ( const T& f ) const	{ return TPoint<T>( fX / f , fY / f ); }
		TPoint<T> operator + ( const TPoint<T>& p ) const { return TPoint<T>( fX + p.fX , fY + p.fY ); }
		TPoint<T> operator - ( const TPoint<T>& p ) const { return TPoint<T>( fX - p.fX , fY - p.fY ); }
		TPoint<T> operator * ( const TPoint<T>& p ) const { return TPoint<T>( fX * p.fX , fY * p.fY ); }
		TPoint<T> operator / ( const TPoint<T>& p ) const { return TPoint<T>( fX / p.fX , fY / p.fY ); }

		TPoint<T> operator == ( const TPoint<T>& p ) const	{ return ( (fX == p.fX ) && ( fY == p.fY )); }
		TPoint<T> operator != ( const TPoint<T>& p ) const	{ return ( (fX != p.fX ) || ( fY != p.fY )); }
	
		void	  operator += ( const TPoint<T>& p)			{ (*this) = (*this) + p; }
		void	  operator -= ( const TPoint<T>& p)			{ (*this) = (*this) - p; }

		T		distance( const TPoint<T>& p)	{	T x = fX - p.x(); T y = fY - p.y();
													return T(sqrt((x*x) + (y*y))); }

 		/// check for 0,0 TPoint
		operator bool () const	{ return (fX != 0) || (fY != 0); }
};
typedef TPoint<long>	TLongPoint;
typedef TPoint<double>	TFloatPoint;

template<typename T>
std::ostream& operator << (std::ostream& out, const TPoint<T>& p) { out << std::string(p); return out; }


//--------------------------------------------------------------------------
template<typename T>
class TSize : public TPoint<T>
{
	public :
		TSize() {}
		TSize(T width, T height)	: TPoint<T>(width, height) {}
		TSize(const TPoint<T>& p)	: TPoint<T>(p) {}

		inline const T& x()			{ return TPoint<T>::fX; }
		inline const T& y()			{ return TPoint<T>::fY; }

		inline T width() const		{ return TPoint<T>::x(); }
		inline T height() const		{ return TPoint<T>::y(); }
		 
		void setWidth(const T& w)		{ this->fX = w; }
		void setHeight(const T& h)		{ this->fY = h; }
		 
		TSize<T> operator * ( T f )	{ return TSize<T>( width() * f , height() * f ); }
};


typedef TSize<int>		TIntSize;
typedef TSize<long>		TLongSize;
typedef TSize<double>	TFloatSize;

//--------------------------------------------------------------------------
/*!
	\brief a TRect implemented as a TSegment2D
*/
template<typename T> class TRect
{
	TPoint<T>	fTopLeft;
	TPoint<T>	fBottomRight;

	public :
				 TRect() {}
				 TRect(const TPoint<T>& a)						: fTopLeft(a), fBottomRight(a) {}
				 TRect(const TPoint<T>& a, const TPoint<T>& b)	: fTopLeft(a), fBottomRight(b) {}
		virtual ~TRect() {}

		TPoint<T>	pos() const		{ return fTopLeft; }
		TPoint<T>	brpos() const	{ return fBottomRight; }
		TPoint<T>	blpos() const	{ return TPoint<T>(fTopLeft.x(), fBottomRight.y()); }
		TPoint<T>	trpos() const	{ return TPoint<T>(fBottomRight.x(), fTopLeft.y()); }
		
		inline T	width() const	{ return fBottomRight.x() - fTopLeft.x() ; }
		inline T	height() const	{ return fBottomRight.y() - fTopLeft.y() ; }
		TSize<T>	size() const	{ return TSize<T>(width(), height());}

		T			x()	const		{ return fTopLeft.x(); }
		T			y()	const		{ return fTopLeft.y(); }
		T			right() const	{ return fBottomRight.x(); }
		T			bottom() const	{ return fBottomRight.y(); }
		
		void setPos(const TPoint<T>& p)	{
			TPoint<T> shift = fTopLeft - p;
			fTopLeft = p;
			fBottomRight -= shift;
		}

		void setWidth(T width)			{ fBottomRight = TPoint<T>(fTopLeft.x() + width, fBottomRight.y()); }
		void setHeight(T height)		{fBottomRight = TPoint<T>(fBottomRight.x(), fTopLeft.y() + height); }
		void setSize(const TSize<T>& s)	{ setWidth(s.width()); setHeight(s.height()); }
		void setX(T x)					{ setPos( TPoint<T>( x , this->y() ) ); }
		void setY(T y)					{ setPos( TPoint<T>( this->x() , y ) ); }

		/// inclusion of a location
		bool include(const TPoint<T>& location) const	{ return (location.x() >= fTopLeft.x()) && (location.x() <= fBottomRight.x()) 
															&& (location.y() >= fTopLeft.y()) && (location.y() <= fBottomRight.y()); }
		/// inclusion of a rect
		bool include(const TRect<T>& r) const			{ return include(r.pos()) && include(r.brpos()); }
		/// intersection with a rect
		bool intersect(const TRect<T>& r) const			{ return include(r.pos()) || include(r.brpos()) || include(r.blpos()) || include(r.trpos()); }

		TPoint<T>	center()	const					{ return (pos() + brpos())/T(2); }
		void		moveBy( const TPoint<T>& delta )	{ setPos( pos() + delta ); }

        operator std::string () const					{
			std::ostringstream res;
			res << fTopLeft << "," << fBottomRight;
			return res.str();
		}
};

template<typename T>
std::ostream& operator << (std::ostream& out, const TRect<T>& r) { out << std::string(r); return out; }

typedef TRect<long>		TLongRect;
typedef TRect<double>	TFloatRect;
typedef std::vector<TLongRect >		TLongRectList;
typedef std::vector<TFloatRect >	TFloatRectList;

/*! @} */

} // end namespoace

#endif
