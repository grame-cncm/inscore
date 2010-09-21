/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __TTRect__
#define __TTRect__

#include <iostream>
#include <algorithm>
#include <vector>
#include "TSegment.h"

namespace interlude
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
				 TPoint(const TInterval<T>& p)		: fX(p.first()), fY(p.second()) {}
//	template <typename C> TPoint(const TPoint<C>& p) : fX(T(p.fX)), fY(T(p.fY)) {}
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
		
		void	  operator += ( const TPoint<T>& p)			{ (*this) = (*this) + p; }

 		/// check for 0,0 TPoint
		operator bool () const	{ return (fX != 0) || (fY != 0); }
};
typedef TPoint<long>	TLongPoint;
typedef TPoint<float>	TFloatPoint;

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
		TSize(const TInterval<T>& i): TPoint<T>(i.start(), i.end()) {}

		inline const T& x()			{ return TPoint<T>::fX; }
		inline const T& y()			{ return TPoint<T>::fY; }

		inline T width() const		{ return TPoint<T>::x(); }
		inline T height() const		{ return TPoint<T>::y(); }
		 
		void setWidth(const T& w)		{ this->fX = w; }
		void setHeight(const T& h)		{ this->fY = h; }
		 
		TSize<T> operator * ( T f )	{ return TSize<T>( width() * f , height() * f ); }
};

template <typename T> OSCStream& operator << (OSCStream& out, const TSize<T>& size)
										{ out << size.width() << size.height(); return out; }

typedef TSize<long>		TLongSize;
typedef TSize<float>	TFloatSize;

//--------------------------------------------------------------------------
/*!
	\brief a TRect implemented as a TSegment2D
*/
template<typename T> class TRect : public TSegment<T,2>
{
	typedef TSegment<T,2> S;
	public :
				 TRect() {}
				 TRect(const TPoint<T>& a)						: S(a.x(), a.y(), a.x(), a.y()) {}
				 TRect(const TPoint<T>& a, const TPoint<T>& b)	: S(a.x(), a.y(), b.x(), b.y()) {}
 				 TRect(const TSegment<T,2>& r)					: S( r.xinterval(), r.yinterval() ) {}
		virtual ~TRect() {}

		TPoint<T>	pos() const		{ return TPoint<T>(S::xinterval().first(), S::yinterval().first()); }
		TPoint<T>	brpos() const	{ return TPoint<T>(S::xinterval().second(), S::yinterval().second()); }
		TPoint<T>	blpos() const	{ return TPoint<T>(S::xinterval().first(), S::yinterval().second()); }
		TPoint<T>	trpos() const	{ return TPoint<T>(S::xinterval().second(), S::yinterval().first()); }
		
		inline T	width() const	{ return S::xinterval().size(); }
		inline T	height() const	{ return S::yinterval().size(); }
		TSize<T>	size() const	{ return TSize<T>(width(), height());}

		T			x()	const		{ return S::xinterval().first(); }
		T			y()	const		{ return S::yinterval().first(); }
		T			right() const	{ return S::xinterval().second(); }
		T			bottom() const	{ return S::yinterval().second(); }
		
		void setPos(const TPoint<T>& p)	{
			S::fXInterval = TInterval<T>(p.x(), p.x() + width());
			S::fYInterval = TInterval<T>(p.y(), p.y() + height());
		}

		void setWidth(T width)			{ S::fXInterval = TInterval<T> (x(), x() + width); }
		void setHeight(T height)		{ S::fYInterval = TInterval<T> (y(), y() + height); }
		void setSize(const TSize<T>& s)	{ setWidth(s.width()); setHeight(s.height()); }
		void setX(T x)					{ setPos( TPoint<T>( x , this->y() ) ); }
		void setY(T y)					{ setPos( TPoint<T>( this->x() , y ) ); }

		TPoint<T>	center()	const					{ return (pos() + brpos())/T(2); }

		void		moveBy( const TPoint<T>& delta )	{ setPos( pos() + delta ); }
};

typedef TRect<long>		TLongRect;
typedef TRect<float>	TFloatRect;
typedef std::vector<TLongRect >		TLongRectList;
typedef std::vector<TFloatRect >	TFloatRectList;

/*! @} */

} // end namespoace

#endif
