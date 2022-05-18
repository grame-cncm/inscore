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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
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
#if HASSSLSUPPORT
#include <QSslCertificate>
#include <QSslKey>
#include <QFile>
#endif

#include "VLogWindow.h"

using namespace std;

namespace inscore
{

extern SIMessageStack gMsgStack;

#if HASMIDISupport
//--------------------------------------------------------------------------
// ssl certificates management
//--------------------------------------------------------------------------
IApplMIDI::IApplMIDI(IObject * parent) : IVNode("midi", parent)
{
	fMsgHandlerMap[kinit_SetMethod]			= TMethodMsgHandler<IApplMIDI>::create(this, &IApplMIDI::init);
	fMsgHandlerMap[kverbose_GetSetMethod]	= TMethodMsgHandler<IApplMIDI>::create(this, &IApplMIDI::verbose);

	fGetMsgHandlerMap[kverbose_GetSetMethod]= TGetParamMsgHandler<int>::create(fVerbose);
	fGetMsgHandlerMap[kmap_GetSetMethod]	= SGetParamMsgHandler(0);
	fGetMsgHandlerMap[kname_GetSetMethod]	= SGetParamMsgHandler(0);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplMIDI::init (const IMessage* msg)
{
	if (msg->size())
		return MsgHandler::kBadParameters;
	init();
	return MsgHandler::kProcessedNoChange;
}
MsgHandler::msgStatus IApplMIDI::verbose (const IMessage* msg)
{
	int verb = 0;
	if ((msg->size() == 1) && msg->param(0,verb)) {
		verbose (verb);
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IApplMIDI::init ()
{
	ITLErr << "MIDI support is not available" << ITLEndl;
}

void IApplMIDI::verbose (int mode)	{ fVerbose = mode; }

#endif

#if HASSSLSUPPORT
//--------------------------------------------------------------------------
// ssl certificates management
//--------------------------------------------------------------------------
IApplSsl::IApplSsl(IObject * parent) : IVNode("ssl", parent)
{
	fMsgHandlerMap[kcert_GetSetMethod]		= TMethodMsgHandler<IApplSsl>::create(this, &IApplSsl::setCert);
	fMsgHandlerMap[kcacert_GetSetMethod]	= TMethodMsgHandler<IApplSsl>::create(this, &IApplSsl::setCA);
	fMsgHandlerMap[kkey_GetSetMethod]		= TMethodMsgHandler<IApplSsl>::create(this, &IApplSsl::setKey);
	
	fGetMsgHandlerMap[kcert_GetSetMethod]	= TGetParamMsgHandler<string>::create(fCertFile);
	fGetMsgHandlerMap[kcacert_GetSetMethod]	= TGetParamMsgHandler<string>::create(fCAFile);
	fGetMsgHandlerMap[kkey_GetSetMethod]	= TGetParamMsgHandler<string>::create(fKeyFile);

	fGetMsgHandlerMap[kmap_GetSetMethod]	= SGetParamMsgHandler(0);
	fGetMsgHandlerMap[kname_GetSetMethod]	= SGetParamMsgHandler(0);
}

//----------------------------------------------------------------------------
IApplSsl::~IApplSsl()
{
	delete fCA;
	delete fCert;
	delete fKey;
}

//----------------------------------------------------------------------------
IApplSsl::Ssl IApplSsl::getSslInfos () const
{
	IApplSsl::Ssl out;
	out.cert = fCert;
	out.cacert = fCA;
	out.key = fKey;
	return out;
}

//----------------------------------------------------------------------------
bool IApplSsl::readFile (const string& name, QByteArray& data) const
{
	string path = TILoader::makeAbsolutePath(IAppl::getHome() + ".ssh/", name);
    QFile file (path.c_str());
    if(file.open(QIODevice::ReadOnly)){
        data = file.readAll();
        file.close();
        return true;
    }
	ITLErr << "can't read file" << name << ITLEndl;
    return false;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplSsl::setCert (const IMessage* msg)
{
	string file;
	switch (msg->size()) {
		case 0:
			delCert();
			return MsgHandler::kProcessed;
		case 1:
			if (getFileName(msg, file) && setCert (file))
				return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

bool IApplSsl::getFileName  (const IMessage* msg, std::string& name) const { return msg->param(0, name); }

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplSsl::setCA (const IMessage* msg)
{
	string file;
	switch (msg->size()) {
		case 0:
			delCA();
			return MsgHandler::kProcessed;
		case 1:
			if (getFileName(msg, file) && setCA (file))
				return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplSsl::setKey (const IMessage* msg)
{
	string file;
	switch (msg->size()) {
		case 0:
			delKey();
			return MsgHandler::kProcessed;
		case 1:
			if (getFileName(msg, file) && setKey (file))
				return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
bool IApplSsl::setCert (const std::string& filename)
{
	QByteArray data;
	if (readFile (filename, data)) {
		fCertFile = filename;
		delete fCert;
		fCert = new QSslCertificate (data);
		return true;
	}
	return false;
}
bool IApplSsl::setCA (const std::string& filename)
{
	QByteArray data;
	if (readFile (filename, data)) {
		fCAFile = filename;
		delete fCA;
		fCA = new QSslCertificate (data);
		return true;
	}
	return false;
}
bool IApplSsl::setKey (const std::string& filename)
{
	QByteArray data;
	if (readFile (filename, data)) {
		fKeyFile = filename;
		delete fKey;
		fKey = new QSslKey (data, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "localhost");
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
void IApplSsl::delCert () 	{ fCertFile.clear(); delete fCert; fCert = nullptr; }
void IApplSsl::delCA ()		{ fCAFile.clear(); delete fCA; fCA = nullptr; }
void IApplSsl::delKey ()	{ fKeyFile.clear(); delete fKey; fKey = nullptr; }

#endif 

//--------------------------------------------------------------------------
// debug node
//--------------------------------------------------------------------------
IApplDebug::IApplDebug(IObject * parent) : IObjectDebug(parent), fOSCDebug(true)
{
	fMsgHandlerMap[kosc_GetSetMethod]		= TSetMethodMsgHandler<IApplDebug,bool>::create(this, &IApplDebug::setOSCDebug);
	fGetMsgHandlerMap[kosc_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fOSCDebug);

	fGetMsgHandlerMap[kmap_GetSetMethod]	= SGetParamMsgHandler(0);
	fGetMsgHandlerMap[kname_GetSetMethod]	= SGetParamMsgHandler(0);
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
	fLogLevel = kLogMsg;
	
	fMsgHandlerMap[kclear_SetMethod]	= TMethodMsgHandler<IApplLog, void (IApplLog::*)(void)>::create(this, &IApplLog::clear);
	fMsgHandlerMap[kwrap_GetSetMethod]	= TSetMethodMsgHandler<IApplLog,bool>::create(this, &IApplLog::setWrap);
	fMsgHandlerMap[ksave_SetMethod]		= TMethodMsgHandler<IApplLog, MsgHandler::msgStatus (IApplLog::*)(const IMessage*) const>::create(this, &IApplLog::saveMsg);
	fMsgHandlerMap[kwrite_SetMethod]	= TMethodMsgHandler<IApplLog, MsgHandler::msgStatus (IApplLog::*)(const IMessage*) const>::create(this, &IApplLog::writeMsg);
	fMsgHandlerMap[kx_GetSetMethod]			= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setXPos);
	fMsgHandlerMap[ky_GetSetMethod]			= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setYPos);
	fMsgHandlerMap[kshow_GetSetMethod]		= TSetMethodMsgHandler<IObject,bool>::create(this, &IObject::setVisible);
	fMsgHandlerMap[kwidth_GetSetMethod]		= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setWidth);
	fMsgHandlerMap[kheight_GetSetMethod]	= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setHeight);
	fMsgHandlerMap[klevel_GetSetMethod]		= TSetMethodMsgHandler<IApplLog,int>::create(this, &IApplLog::setLevel);
	fMsgHandlerMap[kscale_GetSetMethod]		= TSetMethodMsgHandler<IApplLog,float>::create(this, &IApplLog::setZoom);

	fGetMsgHandlerMap[kshow_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fVisible);
	fGetMsgHandlerMap[klevel_GetSetMethod]	= TGetParamMsgHandler<int>::create(fLogLevel);
	fGetMsgHandlerMap[kscale_GetSetMethod]	= TGetParamMsgHandler<int>::create(fZoom);

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
#if EMCC
	fWindow->setVisible(getVisible());
#else
	if (getVisible()) {
#ifdef __MOBILE__
		if(VMobileQtInit::getMainPanel()->switchToPanel(fWindow->windowTitle()))
			VMobileQtInit::hideMenu();
#else
		fWindow->raise();
		fWindow->activateWindow();
#endif
	}
#endif
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
void IApplLog::write(const string& msg)
{
	fWindow->append (msg.c_str());
}

//--------------------------------------------------------------------------
void IApplLog::write(const SIMessageList& msgs)
{
	for (size_t i=0; i< msgs->list().size(); i++) {
		stringstream sstr;
		msgs->list()[i]->print (sstr);
		fWindow->append (sstr.str().c_str());
	}
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IApplLog::writeMsg (const IMessage* msg) const
{
	if ((msg->size() >= 1)) {
		stringstream sstr;
		
		for (int i=0; i < msg->size(); i++) {
			msg->print (sstr, i, 1, ", ");
			sstr << " ";
		}
		fWindow->append (sstr.str().c_str());
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IApplLog::setXPos (float x)			{ _setXPos(x);  fWindow->imove(_getXPos(), _getYPos()); }
void IApplLog::setYPos (float y)			{ _setYPos(y);  fWindow->imove(_getXPos(), _getYPos()); }

//--------------------------------------------------------------------------
void IApplLog::setWidth (float w)			{ _setWidth(w);  fWindow->istretch(w, getHeight()); }
void IApplLog::setHeight (float h)			{ _setHeight(h); fWindow->istretch(getWidth(), h); }
void IApplLog::setZoom (float zoom)			{ fZoom = zoom; fWindow->izoom(zoom); }

//--------------------------------------------------------------------------
void IApplLog::accept (Updater* u)			{ u->updateTo(this); }
void IApplLog::clear()						{ fWindow->clear(); }
void IApplLog::setWrap(bool state) 			{ fWindow->wrap (state); }
void IApplLog::print(const char* str)		{ fWindow->append (str); }



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
