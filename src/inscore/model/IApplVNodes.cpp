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
#include <fstream>

#include "IApplVNodes.h"
#include "IAppl.h"
#include "IMessageStack.h"
#include "TPlugin.h"
#include "Updater.h"
#ifdef __MOBILE__
#include "VMobileQtInit.h"
#endif

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

	fGetMsgHandlerMap[kmap_GetSetMethod]	= SGetParamMsgHandler(0);
	fGetMsgHandlerMap[kname_GetSetMethod]	= SGetParamMsgHandler(0);
	fGetMsgHandlerMap[ksignal_GetMethod]	= SGetParamMsgHandler(0);
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
	fWindow = new VLogWindow ("/ITL/log", this);
	fMsgHandlerMap[kclear_SetMethod]	= TMethodMsgHandler<IApplLog, void (IApplLog::*)(void)>::create(this, &IApplLog::clear);
	fMsgHandlerMap[kwrap_GetSetMethod]	= TSetMethodMsgHandler<IApplLog,bool>::create(this, &IApplLog::setWrap);
	fMsgHandlerMap[ksave_SetMethod]		= TMethodMsgHandler<IApplLog, MsgHandler::msgStatus (IApplLog::*)(const IMessage*) const>::create(this, &IApplLog::saveMsg);
	fMsgHandlerMap[kwrite_SetMethod]	= TMethodMsgHandler<IApplLog, MsgHandler::msgStatus (IApplLog::*)(const IMessage*) const>::create(this, &IApplLog::writeMsg);
	fMsgHandlerMap[kx_GetSetMethod]			= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setXPos);
	fMsgHandlerMap[ky_GetSetMethod]			= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setYPos);
	fMsgHandlerMap[kshow_GetSetMethod]		= TSetMethodMsgHandler<IObject,bool>::create(this, &IObject::setVisible);
	fMsgHandlerMap[kwidth_GetSetMethod]		= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setWidth);
	fMsgHandlerMap[kheight_GetSetMethod]	= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setHeight);

	fGetMsgHandlerMap[kx_GetSetMethod]		= TGetParamMsgHandler<float>::create(fXPos);
	fGetMsgHandlerMap[ky_GetSetMethod]		= TGetParamMsgHandler<float>::create(fYPos);
	fGetMsgHandlerMap[kwidth_GetSetMethod]	= TGetParamMsgHandler<float>::create(fWidth);
	fGetMsgHandlerMap[kheight_GetSetMethod] = TGetParamMsgHandler<float>::create(fHeight);
	fGetMsgHandlerMap[kshow_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fVisible);

	fMsgHandlerMap[kforeground_SetMethod]		= TMethodMsgHandler<IApplLog, void (IApplLog::*)(void)>::create(this, &IApplLog::foreground);

	setVisible(false);
#ifndef WIN32
	setXPos (-0.9f);
	setYPos (-0.8f);
#endif
	setWidth (1.f);
	setHeight (0.3f);
}

IApplLog::~IApplLog()
{
	fWindow->close();
	delete fWindow;
}

//--------------------------------------------------------------------------
void IApplLog::foreground ()
{
	if (getVisible()) {
#ifdef __MOBILE__
		VMobileQtInit::getMainPanel()->switchToPanel(fWindow->windowTitle());
#else
		fWindow->raise();
		fWindow->activateWindow();
#endif
	}
}

//--------------------------------------------------------------------------
void IApplLog::setVisible (bool vis)
{
	IObject::setVisible(vis);
	foreground();
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplLog::saveMsg (const IMessage* msg) const
{
	if ((msg->size() == 1)) {
		string destfile = msg->param(0)->value<string>("");
		if (destfile.size()) {
			string path = IAppl::absolutePath(destfile);
			ofstream out (path.c_str(), ios_base::out);
			out << fWindow->getText();
			return MsgHandler::kProcessedNoChange;
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplLog::writeMsg (const IMessage* msg) const
{
	if ((msg->size() >= 1)) {
		stringstream sstr;
		
		for (int i=0; i < msg->size(); i++) {
			msg->print (sstr, i, 1);
			sstr << " ";
		}
		fWindow->append (sstr.str().c_str());
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IApplLog::setXPos (float x)			{ fXPos = x;  fWindow->imove(fXPos, fYPos); }
void IApplLog::setYPos (float y)			{ fYPos = y;  fWindow->imove(fXPos, fYPos); }

//--------------------------------------------------------------------------
void IApplLog::setWidth (float x)			{ fWidth = x;  fWindow->istretch(fWidth, fHeight); }
void IApplLog::setHeight (float y)			{ fHeight = y; fWindow->istretch(fWidth, fHeight); }

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



//--------------------------------------------------------------------------
// Plugins management
//--------------------------------------------------------------------------
IApplPlugin::IApplPlugin(IObject * parent) : IVNode("plugins", parent)
{
	fMsgHandlerMap[kpath_GetSetMethod]	= TMethodMsgHandler<IApplPlugin, MsgHandler::msgStatus (IApplPlugin::*)(const IMessage*) const>::create(this, &IApplPlugin::addPath);
	fMsgHandlerMap[kreset_SetMethod]	= TMethodMsgHandler<IApplPlugin, MsgHandler::msgStatus (IApplPlugin::*)(const IMessage*) const>::create(this, &IApplPlugin::reset);

	fGetMsgHandlerMap[kpath_GetSetMethod]= TGetParamMsgHandler<string>::create(TPlugin::fLocation);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplPlugin::addPath (const IMessage* msg) const
{
	if ((msg->size() == 1)) {
		string path = msg->param(0)->value<string>("");
		if (path.size()) {
			TPlugin::location(path);
			return MsgHandler::kProcessedNoChange;
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplPlugin::reset (const IMessage* msg) const
{
	if (!msg->size()) {
		TPlugin::resetlocation();
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}


}
