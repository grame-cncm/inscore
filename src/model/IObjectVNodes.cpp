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

#include "IObjectVNodes.h"
#include "Updater.h"

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
// IObject implementation
//--------------------------------------------------------------------------
IObjectDebug::IObjectDebug(IObject * parent) : IVNode("debug", parent), fMap(false), fName(false)
{
	fMsgHandlerMap["map"]		= TSetMethodMsgHandler<IObjectDebug, bool>::create(this, &IObjectDebug::setMapDebug);
	fMsgHandlerMap["name"]		= TSetMethodMsgHandler<IObjectDebug, bool>::create(this, &IObjectDebug::setNameDebug);
	fMsgHandlerMap["signal"]	= TSetMethodMsgHandler<IObjectDebug, bool>::create(this, &IObjectDebug::setSignalDebug);
//	fMsgHandlerMap["map"]	= TSetMsgHandler<bool>::create(fMap);
//	fMsgHandlerMap["name"]	= TSetMsgHandler<bool>::create(fName);
//	fMsgHandlerMap["signal"]	= TSetMsgHandler<bool>::create(fSignal);
//	fMsgHandlerMap["feedbackClick"]	= TSetMsgHandler<bool>::create(fClick);
	
	fGetMsgHandlerMap["map"]	= TGetParamMsgHandler<bool>::create(fMap);
	fGetMsgHandlerMap["name"]	= TGetParamMsgHandler<bool>::create(fName);
	fGetMsgHandlerMap["signal"]	= TGetParamMsgHandler<bool>::create(fSignal);
	fGetMsgHandlerMap["feedbackClick"]	= TGetParamMsgHandler<bool>::create(fClick);
	
	fGetMsgHandlerMap["x"]		= 0;
	fGetMsgHandlerMap["y"]		= 0;
	fGetMsgHandlerMap["z"]		= 0;
	fGetMsgHandlerMap["angle"]	= 0;
	fGetMsgHandlerMap["scale"]	= 0;
	fGetMsgHandlerMap["show"]	= 0;
	fGetMsgHandlerMap["width"]	= 0;
	fGetMsgHandlerMap["height"] = 0;

	fGetMsgHandlerMap["date"]	= 0;
	fGetMsgHandlerMap["duration"]= 0;

	fGetMsgHandlerMap["color"]	= 0;
	fGetMsgHandlerMap["red"]	= 0;
	fGetMsgHandlerMap["green"]	= 0;
	fGetMsgHandlerMap["blue"]	= 0;
	fGetMsgHandlerMap["alpha"]	= 0;
	fGetMsgHandlerMap["hue"]	= 0;
	fGetMsgHandlerMap["saturation"] = 0;
	fGetMsgHandlerMap["brightness"]	= 0;
}

//--------------------------------------------------------------------------
int IObjectDebug::execute (const IMessage* msg)
{
	int status = IObject::execute(msg);
	if (status & MsgHandler::kProcessed)
		fParent->setState (kModified);
	return status;
}

//--------------------------------------------------------------------------
void IObjectDebug::accept (Updater* u)
{
	u->updateTo(this);
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
IMessageList IObjectDebug::get () const
{
	IMessageList outMsgs;
	IMessage * msg = new IMessage(getOSCAddress(), "map");
	*msg << getMapDebug();
	outMsgs += msg;
	msg = new IMessage(getOSCAddress(), "name");
	*msg << getNameDebug();
	outMsgs += msg;
	msg = new IMessage(getOSCAddress(), "signal");
	*msg << getSignalDebug();
	outMsgs += msg;
//	msg = new IMessage(getOSCAddress(), "click");
//	*msg << getClickDebug();
	outMsgs += msg;
	return outMsgs;
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IObjectDebug::print (ostream& out) const
{
	out << "  debug map: " << fMap << " name: " << fName << " signal: " << fSignal;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const SIObjectDebug& o)
{
	o->print(out);
	return out;
}

}
