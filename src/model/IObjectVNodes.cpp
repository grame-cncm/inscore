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

namespace inscore
{

//--------------------------------------------------------------------------
// IObject implementation
//--------------------------------------------------------------------------
IObjectDebug::IObjectDebug(IObject * parent) : IVNode("debug", parent), fMap(false), fName(false)
{
	fMsgHandlerMap[kmap_GetSetMethod]		= TSetMethodMsgHandler<IObjectDebug, bool>::create(this, &IObjectDebug::setMapDebug);
	fMsgHandlerMap[kname_GetSetMethod]		= TSetMethodMsgHandler<IObjectDebug, bool>::create(this, &IObjectDebug::setNameDebug);
	fMsgHandlerMap[kwatch_GetSetMethod]		= SMsgHandler(0);
	fMsgHandlerMap[kwatchplus_SetMethod]	= SMsgHandler(0);
	
	fGetMsgHandlerMap[kmap_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fMap);
	fGetMsgHandlerMap[kname_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fName);
	fGetMultiMsgHandlerMap[kwatch_GetSetMethod]	= SGetParamMultiMsgHandler(0);
	fGetMultiMsgHandlerMap[kalias_GetSetMethod]	= SGetParamMultiMsgHandler(0);
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
SIMessageList IObjectDebug::getSetMsg () const
{
	SIMessageList outMsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kmap_GetSetMethod);
	*msg << getMapDebug();
	outMsgs->list().push_back (msg);
	msg = IMessage::create(getOSCAddress(), kname_GetSetMethod);
	*msg << getNameDebug();
	outMsgs->list().push_back (msg);
	return outMsgs;
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IObjectDebug::print (ostream& out) const
{
	out << "  debug map: " << fMap << " name: " << fName ; //<< " signal: " << fSignal;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const SIObjectDebug& o)
{
	o->print(out);
	return out;
}

}
