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

#include "IRect.h"
#include "IMessage.h"
#include "Methods.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string IRect::kRectType("rect");

//--------------------------------------------------------------------------
IRect::IRect( const std::string& name, IObject* parent ) : IRectShape(name, parent), fRadius(0.f,0.f)
{ 
	fTypeString = kRectType;
	fMsgHandlerMap[kradius_GetSetMethod]		= TSetMethodMsgHandler<IRect, TFloatSize>::create(this, &IRect::setRadius);
	fGetMsgHandlerMap[kradius_GetSetMethod]		= TGetParamMsgHandler<TFloatSize>::create(fRadius);
}



//--------------------------------------------------------------------------
TFloatPoint IRect::radius2FramePoint(float angle, float w, float h) const
{
	angle = angle / 180 * M_PI;
	return TFloatPoint ( w * (cos(angle) + 1) / getWidth(), h * (sin(angle) + 1) / getHeight());
}


//--------------------------------------------------------------------------
// check if datelen is inside a corner
// arguments are the following
// - date		: the date to be converted into a point
// - datelen	: the date converted into a length, is between 0 and the total object length
// - startangle	: the corner start angle
//				  actually the detection works by half corner since the rect segments are browsed in clockwise order
//				  thus each corner start angle is a multiple of 45 (in degrees)
// - dist		: the distance covered by the current corner
// - w			: the distance covered by a corner on the x axis
// - h			: the distance covered by a corner on the y axis
// - offset		: an offset to add to the computed point (if any)
//				  this offset moves the point to the effective corner
// - p			: on output, the computed point
bool IRect::checkCorner(const libmapping::rational& date, float datelen, float startangle, float dist, float w, float h, const TFloatPoint& offset, TFloatPoint& p) const
{
	// when the date becomes negative, it means that the point is not on a corner
	if (datelen < 0) return IObject::date2FramePoint(date, p);
	// when the date is less than the distance of the current corner
	if (datelen < dist) {									// then the point is on a corner
		float angle = startangle + (datelen / dist) * 45;	// computes an angle as a ratio over the current distance
		p = radius2FramePoint(angle, w, h);					// computes the point as an ellipse point
		p += offset;										// and move the point to the corresponding corner
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IRect::date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const
{
	if ((fRadius.height()<=0) || (fRadius.width()<=0)) return IObject::date2FramePoint(date, p);

	const libmapping::rational dur = getDuration();
	if ((date < 0.) || (date > dur))	return false;

	float w	= getWidth();
	float h = getHeight();
	float objlen	= (w + h) * 2;
	float datelen	= objlen * float(date) / float(dur);

	float topr  = w * 0.5 * (fRadius.width() / 100);
	float leftr = h * 0.5 * (fRadius.height() / 100);
	float wr	= w - topr;
	float hr	= h - leftr;
	TFloatPoint offset(0,0);

								// top left corner second part
	if (checkCorner (date, datelen, 225, topr, topr, leftr, offset, p))		return true;

	datelen -= wr;				// remove the middle segment length
	offset.fX = (wr-topr)/w;	// top right corner first part
	if (checkCorner (date, datelen, 270, topr, topr, leftr, offset, p))		return true;

	datelen -= topr;			// top right corner second part
	if (checkCorner (date, datelen, 315, leftr, topr, leftr, offset, p))	return true;

	datelen -= hr;				// remove the middle segment length
	offset.fY = (hr-leftr)/h;	// bottom right corner first part
	if (checkCorner (date, datelen, 0, leftr, topr, leftr, offset, p))		return true;

	datelen -= leftr;			// bottom right corner second part
	if (checkCorner (date, datelen, 45, topr, topr, leftr, offset, p))		return true;

	datelen -= wr;
	offset.fX = 0;				// bottom left corner first part
	if (checkCorner (date, datelen, 90, topr, topr, leftr, offset, p))		return true;

	datelen -= topr;			// bottom left corner second part
	if (checkCorner (date, datelen, 135, leftr, topr, leftr, offset, p))	return true;

	datelen -= hr;
	offset.fY = 0;				// top left corner first part
	if (checkCorner (date, datelen, 180, leftr, topr, leftr, offset, p))	return true;

	return IObject::date2FramePoint(date, p);
}


//--------------------------------------------------------------------------
void IRect::accept (Updater* u)
{
	u->updateTo (SIRect(this));
}


}
