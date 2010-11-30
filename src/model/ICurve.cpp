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

#include "ICurve.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{


//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& s, const ICurve::CurveData& val)
{
	for (ICurve::CurveData::const_iterator i = val.begin(); i != val.end(); i++)
		s	<< i->fPointA << i->fPointB << i->fPointC << i->fPointD; 
	return s;
}

const string ICurve::kCurveType("curve");
//--------------------------------------------------------------------------
ICurve::ICurve( const std::string& name, IObject* parent ) : IShapeMap(name, parent), fView(0)
{ 
	fTypeString = kCurveType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<CurveData>::create(getPoints());
}

//--------------------------------------------------------------------------
void ICurve::accept (Updater* u)
{
	u->updateTo (SICurve(this));
}

//--------------------------------------------------------------------------
void ICurve::print (ostream& out) const
{
	IShapeMap::print (out);
	unsigned int i, n = fPoints.size();
	std::string sep = "";
	for ( i = 0 ; i < n ; i++ ) {
		out << "Curve n°" << (i+1) << ": [ ("	<< fPoints[i].fPointA.first << "," << fPoints[i].fPointA.second << ");(" 
												<< fPoints[i].fPointB.first << "," << fPoints[i].fPointB.second << ");(" 
												<< fPoints[i].fPointC.first << "," << fPoints[i].fPointC.second << ");(" 
												<< fPoints[i].fPointD.first << "," << fPoints[i].fPointD.second << ")"
											<< "]" << sep;
		sep = " / ";
	}
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ICurve::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if ( (msg->params().size() > 1) && ( (msg->params().size() % 8)==1 ) ) {
		const float err = -55555;
		unsigned int i;
		//Build the vector of points reading the message.
		CurveData curveData;
		for ( i = 1 ; i < msg->params().size() ; i+=8 ) {
			BezierCurve bezierCurve;
			bezierCurve.fPointA.first = msg->params()[i]->value<float>(err);
			bezierCurve.fPointA.second = msg->params()[i+1]->value<float>(err);
			bezierCurve.fPointB.first = msg->params()[i+2]->value<float>(err);
			bezierCurve.fPointB.second = msg->params()[i+3]->value<float>(err);
			bezierCurve.fPointC.first = msg->params()[i+4]->value<float>(err);
			bezierCurve.fPointC.second = msg->params()[i+5]->value<float>(err);
			bezierCurve.fPointD.first = msg->params()[i+6]->value<float>(err);
			bezierCurve.fPointD.second = msg->params()[i+7]->value<float>(err);
			if (	(bezierCurve.fPointA.first==err) || (bezierCurve.fPointA.second==err)
				||	(bezierCurve.fPointB.first==err) || (bezierCurve.fPointB.second==err)
				||	(bezierCurve.fPointC.first==err) || (bezierCurve.fPointC.second==err)
				||	(bezierCurve.fPointD.first==err) || (bezierCurve.fPointD.second==err)
				)
				return MsgHandler::kBadParameters;
			curveData.push_back( bezierCurve );
		}
		
		//Compares the points vector with the current one.
		if ( curveData.size() != getPoints().size() ) {
			setPoints(curveData);
			newData(true);
			return MsgHandler::kProcessed;
		}
		for ( i = 0 ; i < curveData.size() ; i++ )
		{
			if (curveData[i] != getPoints()[i])
			{
				setPoints(curveData);
				newData(true);
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

}
