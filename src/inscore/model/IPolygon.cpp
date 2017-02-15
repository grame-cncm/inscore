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

#include "IPolygon.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{


//--------------------------------------------------------------------------
OSCStream& operator <<(OSCStream& s, const IPolygon::PolygonData& val)
{
	for (IPolygon::PolygonData::const_iterator i = val.begin(); i != val.end(); i++)
		s << i->fX << i->fY;
	return s;
}

const string IPolygon::kPolygonType("polygon");
//--------------------------------------------------------------------------
IPolygon::IPolygon( const std::string& name, IObject* parent ) : IShapeMap(name, parent)
{ 
	fTypeString = kPolygonType;
	fTotalLength = 0;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<PolygonData>::create(getPoints());
}

//--------------------------------------------------------------------------
float IPolygon::getLength(const TFloatPoint& p1, const TFloatPoint& p2) const
{
	double x = p2.fX - p1.fX;
	double y = p2.fY - p1.fY;
	return sqrt ((x*x) + (y*y));
}

//--------------------------------------------------------------------------
void IPolygon::getMetrics()
{
	fSegmentsLength.clear();
	fTotalLength = 0;
	size_t n = fPoints.size();
	if (n < 2) return;

	TFloatPoint p = fPoints[0];
	for ( size_t i = 1 ; i < n ; i++ ) {
		TFloatPoint pnext = fPoints[i];
		float len = p.distance (pnext);
		fTotalLength += len;
		fSegmentsLength.push_back(len);
		p = pnext;
	}
	float len = p.distance (fPoints[0]);
	fSegmentsLength.push_back(len);
	fTotalLength += len;
}

//--------------------------------------------------------------------------
bool IPolygon::date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const
{
	const libmapping::rational dur = getDuration();
	if ((date < 0.) || (date > dur))	return false;
	
	float datelen	= fTotalLength * float(date) / float(dur);  // convert the date into a length
	size_t n = fSegmentsLength.size();
	for (int i=0; i<n; i++) {			// look for the current segment
		float curlength = fSegmentsLength[i];
		if (datelen <= curlength) {				// here it is
			float ratio = datelen / curlength;	// this is the relative position on the current segment
			TFloatPoint current = fPoints[i];	// this is the current segment first point
			TFloatPoint next = (i+1) < n ? fPoints[i+1] : fPoints[0];	// this is the next point to join
			p.fX = (current.x() + fXMin + (next.x() - current.x()) * ratio) / getWidth();
			p.fY = (current.y() + fYMin + (next.y() - current.y()) * ratio) / getHeight();
			return true;
		}
		else datelen -= curlength;
	}
	return false;
}

//--------------------------------------------------------------------------
void IPolygon::accept (Updater* u)
{
	u->updateTo (SIPolygon(this));
}

//--------------------------------------------------------------------------
void IPolygon::print (ostream& out) const
{
	IShapeMap::print (out);
	size_t i, n = fPoints.size();
	std::string sep = "";
	for ( i = 0 ; i < n ; i++ ) {
		out << "(" << fPoints[i].fX << ";" << fPoints[i].fY << ")" << sep;
		sep = ",";
	}
	out << "]";

}

//--------------------------------------------------------------------------
void IPolygon::setPoints(const PolygonData& points)
{
	const float initmax = -1000000.f;
	const float initmin = -initmax;
	float xmin=initmin, xmax=initmax, ymin=initmin, ymax=initmax;
	for (unsigned int i = 0 ; i < points.size() ; i++ ) {
		if (points[i].fX < xmin)	xmin = points[i].fX;
		if (points[i].fX > xmax)	xmax = points[i].fX;
		if (points[i].fY < ymin)	ymin = points[i].fY;
		if (points[i].fY > ymax)	ymax = points[i].fY;
	}
	setWidth (xmax - xmin);
	setHeight(ymax - ymin);
	fXMin = -xmin;
	fYMin = -ymin;
	fPoints = points;
	getMetrics();
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IPolygon::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if ( (msg->size() > 1) && ( (msg->size() % 2)==1 ) ) {

		//Build the vector of points reading the message.
		PolygonData points;
		for (int i = 1 ; i < msg->size() ; i+=2 ) {
			float x, y;
			if (!msg->cast_param(i, x) || !msg->cast_param(i+1, y))
				return MsgHandler::kBadParameters;
			points.push_back( TFloatPoint(x, y) );
		}

		//Compares the points vector with the current one.
		bool set = points.size() != getPoints().size();
		for (unsigned int i = 0 ; !set && (i < points.size()) ; i++ )
			set = (points[i] != getPoints()[i]);
		if ( set ) {
			setPoints(points);
			newData(true);
			return MsgHandler::kProcessed;
		}
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

}
