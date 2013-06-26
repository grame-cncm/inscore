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

#include <sstream>

#include "IApplVNodes.h"
#include "IMessageStack.h"
#include "Updater.h"

#include "VLogWindow.h"

using namespace std;

namespace inscore
{

extern SIMessageStack gMsgStack;

//--------------------------------------------------------------------------
IApplDebug::IApplDebug(IObject * parent) : IObjectDebug(parent), fOSCDebug(true)
{
	fMsgHandlerMap[kosc_GetSetMethod]		= TSetMethodMsgHandler<IApplDebug,bool>::create(this, &IApplDebug::setOSCDebug);
	fGetMsgHandlerMap[kosc_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fOSCDebug);

	fGetMsgHandlerMap[kmap_GetSetMethod]	= 0;
	fGetMsgHandlerMap[kname_GetSetMethod]	= 0;
	fGetMsgHandlerMap[ksignal_GetMethod]	= 0;
}

//--------------------------------------------------------------------------
void IApplDebug::accept (Updater* u)
{
	u->updateTo(this);
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
SIMessageList IApplDebug::getSetMsg () const
{
	SIMessageList outMsgs = IObjectDebug::getSetMsg();
	SIMessage msg = IMessage::create(getOSCAddress(), kosc_GetSetMethod);
	*msg << fOSCDebug;
	outMsgs->list().push_back (msg);
	return outMsgs;
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IApplDebug::print (ostream& out) const
{
	IObjectDebug::print(out);
	out << "  debug osc: " << fOSCDebug;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const SIApplDebug& o)
{
	if (o) o->print(out);
	return out;
}

//--------------------------------------------------------------------------
// IAppl statistics
//--------------------------------------------------------------------------
SIMessageList IApplStat::getSetMsg () const
{
	SIMessageList outMsgs = IMessageList::create();
	SIMessage msg = IMessage::create (getOSCAddress(), "");
	*msg << string("osc") << fMsgCount << string("udp") << gMsgStack->stat();
	outMsgs->list().push_back(msg);
	return outMsgs;
}

//--------------------------------------------------------------------------
void IApplStat::accept (Updater* u)
{
	u->updateTo(this);
}

//--------------------------------------------------------------------------
void IApplStat::reset()				{ fMsgCount = 0; gMsgStack->reset(); }

//--------------------------------------------------------------------------
IApplStat::IApplStat(IObject * parent) : IVNode("stats", parent), fMsgCount(0)
{
	fMsgHandlerMap[kreset_SetMethod]	= TMethodMsgHandler<IApplStat, void (IApplStat::*)(void)>::create(this, &IApplStat::reset);
}


//--------------------------------------------------------------------------
// IAppl log window
//--------------------------------------------------------------------------
IApplLog::IApplLog(IObject * parent) : IVNode("log", parent)
{
	fWindow = new VLogWindow ("INScore log");
	fMsgHandlerMap[kclear_SetMethod]	= TMethodMsgHandler<IApplLog, void (IApplLog::*)(void)>::create(this, &IApplLog::clear);
	fMsgHandlerMap[kwrap_GetSetMethod]	= TSetMethodMsgHandler<IApplLog,bool>::create(this, &IApplLog::setWrap);
	positionAble();
	setVisible(false);
}
IApplLog::~IApplLog()
{
	fWindow->close();
	delete fWindow;
}


//--------------------------------------------------------------------------
void IApplLog::accept (Updater* u)
{
	u->updateTo(this);
}

void IApplLog::clear()
{
	fWindow->clear();
}

void IApplLog::setWrap(bool state)
{
	fWindow->wrap (state);
}

void IApplLog::print(const char* str)
{
	fWindow->append (str);
}

}
