/*

  INScore Project

  Copyright (C) 2016  Grame

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

#include "IArc.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string IArc::kArcType("arc");

//--------------------------------------------------------------------------
IArc::IArc( const std::string& name, IObject* parent ) : IRectShape(name, parent)
{
	fTypeString = kArcType;
	fStartAngle		= 0;
	fAngularRange	= 1;
	fArcLen			= 0;
	fCloseArc		= false;

	fMsgHandlerMap[kstart_GetSetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::setStartAngle);
	fMsgHandlerMap[krange_GetSetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::setAngularRange);
	fMsgHandlerMap[kdstart_SetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::dStartAngle);
	fMsgHandlerMap[kdrange_SetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::dRange);
	fMsgHandlerMap[kclose_GetSetMethod]		= TSetMethodMsgHandler<IArc, bool>::create(this, &IArc::setClosed);

	fGetMsgHandlerMap[kstart_GetSetMethod]		= TGetParamMsgHandler<float>::create(fStartAngle);
	fGetMsgHandlerMap[krange_GetSetMethod]		= TGetParamMsgHandler<float>::create(fAngularRange);
	fGetMsgHandlerMap[kclose_GetSetMethod]		= TGetParamMsgHandler<bool>::create(fCloseArc);

	setPenWidth (1.0);
	setBrushStyle ("none");
}

#define swap(a,b)	{ double tmp = a; a = b; b = tmp; }
//--------------------------------------------------------------------------
// computes an approximation of the arc length using segments measured
// every 0.2 degree
float IArc::arcLength () const
{
	double len = 0, step = 0.2 / 180.f * M_PI;
	double angle = (180 - getStartAngle ()) /180 * M_PI;
	double end	= angle + getAngularRange()   /180 * M_PI;
	
	if (angle > end) swap(angle, end)

	double r1 = getWidth() / 2;
	double r2 = getHeight() / 2;
	if (r1 > r2) swap(r1, r2)

	double x1 = r2*cos(-angle);
	double y1 = r1*sin(-angle);
	angle += step;
	while (angle <= end) {
		double x2 = r2*cos(-angle);
		double y2 = r1*sin(-angle);
		double x = x2 - x1;
		double y = y2 - y1;
		len += sqrt((x*x) + (y*y));
		x1 = x2; y1 = y2;
		angle += step;
	}
	return len;
}
//--------------------------------------------------------------------------
float IArc::getR (float ratio) const
{
	TFloatPoint p;
	arc2FramePoint (ratio, p);
	double r1 = getWidth() / 2;
	double r2 = getHeight() / 2;
	double dx = (p.fX * getWidth()) - r1;
	double dy = (p.fY * getHeight()) - r2;
	return sqrt((dx*dx) + (dy*dy));
	
//	double a = (180 - angle) /180 * M_PI;
//	double r1 = getWidth() / 2;
//	double r2 = getHeight() / 2;
//	if (r1 > r2) swap(r1, r2)
//	double x = r2*cos(-a);
//	double y = r1*sin(-a);
//	return sqrt((x*x) + (y*y));
}

//--------------------------------------------------------------------------
void IArc::accept (Updater* u)
{
	u->updateTo (SIArc(this));
}

//--------------------------------------------------------------------------
void IArc::print (ostream& out) const
{
	IShape::print (out);
	out << " arc" << endl;
}

//--------------------------------------------------------------------------
bool IArc::arc2FramePoint(float ratio, TFloatPoint& p) const
{
	float range	= getAngularRange()   /180 * M_PI;
	float start = (180 - getStartAngle ()) /180 * M_PI;

	double angle = 3 * M_PI + start - range + (ratio * range);
	double r1 = getWidth() / 2;
	double r2 = getHeight() / 2;
	if (r1 > r2) {
		p.fX = (r1*cos(angle) + r1) / (r1*2);
		p.fY = (r2*sin(angle) + r2) / (r2*2);
	}
	else {
		p.fX = (r2*cos(angle) + r2) / (r2*2);
		p.fY = (r1*sin(angle) + r1) / (r1*2);
	}
	return true;
}

//--------------------------------------------------------------------------
bool IArc::date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const
{
	const libmapping::rational dur = getDuration();
	if ((date < 0.) || (date > dur))	return false;

	float ratio = float(date) / float(dur);
	if (!closed()) return arc2FramePoint(ratio, p);

	float datelen	= (fArcLen + fR1 + fR2) * ratio;
	if (datelen <= fArcLen)
		return arc2FramePoint (datelen / fArcLen, p);
	
	datelen -= fArcLen;				// leaving the curve part
	if (datelen <= fR2) {			// browse the segment connected to the curve end
		TFloatPoint end;
		arc2FramePoint(1, end);		// retrieve the end point
		ratio = datelen / fR2;		// computes a ratio on segment length
		p.fX = end.fX + (0.5 - end.fX) * ratio;		// and computes the x and y corrdinates
		p.fY = end.fY + (0.5 - end.fY) * ratio;
//cout << "IArc::date2FramePoint on r2: " << fR2 << "  " << ratio << endl;
	}
	else {							// the first segment is done
		datelen -= fR2;				// adjust remaining length
		ratio = datelen / fR1;		// computes a ratio on last segment length
		TFloatPoint start;
		arc2FramePoint(0, start);	// retrieve the curve start point
		p.fX = 0.5 + (start.fX - 0.5) * ratio;	// and computes the x and y corrdinates
		p.fY = 0.5 + (start.fY - 0.5) * ratio;
//cout << "IArc::date2FramePoint on r1: " << fR1 << "  " << ratio << endl;;
	}
	return true;
}

//--------------------------------------------------------------------------
// the 'get' form without parameter
SIMessageList IArc::getSetMsg() const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kArcType <<  getWidth() << getHeight() << getStartAngle() << getAngularRange();
	outmsgs->list().push_back (msg);
	return outmsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IArc::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	if (msg->size() == 5) {
		float width, height, startangle, range;
		if (!msg->cast_param(1, width) || !msg->cast_param(2, height) || !msg->cast_param(3, startangle) || !msg->cast_param(4, range))
			return MsgHandler::kBadParameters;

		if ( ( width != getWidth() ) || ( height != getHeight() )
			|| ( startangle != getStartAngle() ) || ( range != getAngularRange() ) )
		{
			setWidth( width );
			setHeight( height );
			setStartAngle( startangle );
			setAngularRange( range );
			fArcLen = arcLength();
			fR1 = getR (0);
			fR2 = getR (1);
//cout << "IArc::set " << fArcLen << " " << fR1 << " " << fR2 << endl;
			newData(true);
			status = MsgHandler::kProcessed;
		}
		else status = MsgHandler::kProcessedNoChange;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}


}
