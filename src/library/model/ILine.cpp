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

#include <math.h>

#include "ILine.h"
#include "ITLError.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string ILine::kLineType("line");

// Initialize map to convert enum array head to string
std::map<enum ILine::ArrowHeadType, std::string> ILine::arrowMap = ILine::createArrowMap();

//--------------------------------------------------------------------------
ILine::ILine( const std::string& name, IObject* parent ) : IShapeMap(name, parent), fWAMode(false),
	fArrowLeft(NONE), fArrowRight(NONE), fArrowSizeLeft(1.0), fArrowSizeRight(1.0)
{ 
	fTypeString = kLineType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler< TFloatPoint >::create( getPoint() );

	// Arrow specific method
	fGetMsgHandlerMap[karrows_GetSetMethod]	= TGetParamMethodHandler<ILine, string (ILine::*)() const>::create(this, &ILine::getArrows);
	fMsgHandlerMap[karrows_GetSetMethod]	= TMethodMsgHandler<ILine>::create(this, &ILine::setArrowsMsg);

	fPenWidth = 1.0f;
}

//--------------------------------------------------------------------------
void ILine::accept (Updater* u)
{
	u->updateTo (SILine(this));
}

//--------------------------------------------------------------------------
void ILine::print (ostream& out) const
{
	IShapeMap::print (out);
	out << fPoint << endl;
}


//--------------------------------------------------------------------------
// the 'get' form without parameter
SIMessageList ILine::getSetMsg() const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kLineType << "xy" << fPoint;
	outmsgs->list().push_back (msg);
	return outmsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ILine::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;
	if (msg->size() == 3) {
		float x, y;
		if ((!msg->param(1, x)) || (!msg->param(2, y)))
			return MsgHandler::kBadParameters;
		setPoint( TFloatPoint(x,y) );
		status = MsgHandler::kProcessed;
		newData(true);
		ITLErr << "set line without mode is deprecated" << ITLEndl;
	}
	else if (msg->size() == 4) {
		string mode; float a, b; int ai, bi;
		if (!msg->param(1, mode))
			return MsgHandler::kBadParameters;
		if (!msg->param(2, a)) {
			if (msg->param(2, ai)) a = float(ai);
			else return MsgHandler::kBadParameters;
		}
		if (!msg->param(3, b)) {
			if (msg->param(3, bi)) b = float(bi);
			else return MsgHandler::kBadParameters;
		}
		if (mode == "xy") {
			setPoint( TFloatPoint(a, b) );
		}
		else if (mode == "wa") {
			fWAMode = true;
			double x = a * cos(M_PI * b / 180);
			double y = a * sin(M_PI * b / 180);
			setPoint( TFloatPoint(x, y) );
		}
		else return MsgHandler::kBadParameters;
		newData(true);
		status = MsgHandler::kProcessed;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

//--------------------------------------------------------------------------
bool ILine::getArrowType(string typeString, enum ArrowHeadType & type)
{
	if(typeString == "none") {
		type = NONE;
		return true;
	}
	if(typeString == "triangle") {
		type = TRIANGLE;
		return true;
	}
	if(typeString == "diamond") {
		type = DIAMOND;
		return true;
	}
	if(typeString == "disk") {
		type = DISK;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
map<enum ILine::ArrowHeadType, string> ILine::createArrowMap()
{
	map<enum ArrowHeadType, string> myMap;
	myMap[NONE] = "none";
	myMap[TRIANGLE] = "triangle";
	myMap[DIAMOND] = "diamond";
	myMap[DISK] = "disk";
	return myMap;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ILine::setArrowsMsg(const IMessage* msg)
{
	if(msg->size() != 2)
		return MsgHandler::kBadParameters;
	string type;
	enum ArrowHeadType left, right;
	if (msg->param(0, type)) {
		if(!getArrowType(type, left))
			return MsgHandler::kBadParameters;
	}
	if (msg->param(1, type)) {
		if(!getArrowType(type, right))
			return MsgHandler::kBadParameters;
	}
	fArrowLeft = left;
	fArrowRight = right;
	newData(true);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
string ILine::getArrows() const
{
	return arrowMap[fArrowLeft] + " " + arrowMap[fArrowRight];
}

}
