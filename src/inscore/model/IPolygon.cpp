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
		s << i->first << i->second;
	return s;
}

const string IPolygon::kPolygonType("polygon");
//--------------------------------------------------------------------------
IPolygon::IPolygon( const std::string& name, IObject* parent ) : IShapeMap(name, parent)
{ 
	fTypeString = kPolygonType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<PolygonData>::create(getPoints());
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
		out << "(" << fPoints[i].first << ";" << fPoints[i].second << ")" << sep;
		sep = ",";
	}
	out << "]";

}

//--------------------------------------------------------------------------
void IPolygon::setPoints(const std::vector< std::pair<float,float> >& points)
{
	const float initmax = -1000000.f;
	const float initmin = -initmax;
	float xmin=initmin, xmax=initmax, ymin=initmin, ymax=initmax;
	for (unsigned int i = 0 ; i < points.size() ; i++ ) {
		if (points[i].first < xmin)		xmin = points[i].first;
		if (points[i].first > xmax)		xmax = points[i].first;
		if (points[i].second < ymin)	ymin = points[i].second;
		if (points[i].second > ymax)	ymax = points[i].second;
	}
	setWidth (xmax - xmin);
	setHeight(ymax - ymin);
	fXMin = -xmin;
	fYMin = -ymin;
	fPoints = points;
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IPolygon::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if ( (msg->size() > 1) && ( (msg->size() % 2)==1 ) ) {

		//Build the vector of points reading the message.
		std::vector< std::pair<float,float> > points;
		for (int i = 1 ; i < msg->size() ; i+=2 ) {
			std::pair<float,float> point;
			if (!msg->cast_param(i, point.first) || !msg->cast_param(i+1, point.second))
				return MsgHandler::kBadParameters;
			points.push_back( point );
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
