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


#ifndef __IRect__
#define __IRect__

#include "IRectShape.h"
#include "TRect.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IRect;
typedef class libmapping::SMARTP<IRect>	SIRect;
//--------------------------------------------------------------------------
/*!
	\brief a rectangle shape.
*/
class IRect : public IRectShape
{
	TFloatPoint radius2FramePoint(float angle, float w, float h) const;
	bool		checkCorner(const libmapping::rational& date, float datelen, float angle, float dist, float w, float h, const TFloatPoint& offset, TFloatPoint& p) const;

	public:
		static const std::string kRectType;
		static SIRect create(const std::string& name, IObject* parent)	{ return new IRect(name, parent); }

		virtual void	accept (Updater*);
		virtual void		setRadius (const TFloatSize& r)	{ fRadius = r; }
		virtual TFloatSize	getRadius () const				{ return fRadius; }
        virtual bool date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const;

	protected:
				 IRect( const std::string& name, IObject* parent );
		virtual ~IRect() {}
	
		TFloatSize	fRadius;
};

/*! @} */

} // end namespoace

#endif
