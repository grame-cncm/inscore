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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifdef WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdlib.h>
#include <sstream>

#include "IAppl.h"
#include "IApplVNodes.h"
#include "IGlue.h"
#include "IMessage.h"
#include "IObjectFactory.h"
#include "ITLparser.h"
#include "OSCAddress.h"
#include "Updater.h"
#include "ip/NetworkingUtils.h"
#include "interlude.h"
#include "ITLError.h"

#include <QDir>

#ifdef WIN32
#include <Winsock2.h>
#endif

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
// ip address utility
//--------------------------------------------------------------------------
static string getHostName()
{
	char name[512];
	int ret = gethostname(name, 512);
	if (ret == -1) return "";
	return name;
}

string getIP()
{
	string name = getHostName();
	stringstream ipStr;
	if (name.size()) {
		unsigned long ip = GetHostByName(name.c_str());
		ipStr	<< ((ip >> 24) & 0xff) << '.'
				<< ((ip >> 16) & 0xff) << '.'
				<< ((ip >> 8) & 0xff) << '.'
				<< (ip & 0xff);
	}
	return ipStr.str();
}

//--------------------------------------------------------------------------
const string IAppl::kApplType("appl");

#ifdef WIN32
#define _CRT_SECURE_NO_DEPRECATE
std::string IAppl::fRootPath = std::string(getenv("USERPROFILE")) + "\\";
#else
std::string IAppl::fRootPath = std::string(getenv("HOME")) + "/";
#endif


#ifdef RUNBENCH
//--------------------------------------------------------------------------
MsgHandler::msgStatus IAppl::writeBench(const IMessage* msg)
{
	if (msg->size() == 1) {
		string file = msg->params()[0]->value<string>("");
		if (file.size()) {
			bench::write (absolutePath(file));
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IAppl::resetBench()
{
	const char *benchnames[] = { "time", "model", "lmap", "smap", "view", "total", 0 };
	unsigned short size = 3000;
	bench::init (benchnames, size);
	oscerr << OSCStart("Bench initialized with buffer size = ") << size << OSCEnd();
}

#endif

bool IAppl::fDefaultShow(true);
//--------------------------------------------------------------------------
IAppl::IAppl(int udpport, int outport, int errport) 
	: IObject("ITL", 0), fRunning(true), fUDP(udpport,outport,errport), fView(0)
{
	fTypeString = kApplType;
	fVersion = Interlude::versionStr();

	fMsgHandlerMap["hello"]	= TMethodMsgHandler<IAppl, void (IAppl::*)() const>::create(this, &IAppl::helloMsg);
	fMsgHandlerMap["load"]	= TMethodMsgHandler<IAppl>::create(this, &IAppl::loadMsg);
	fMsgHandlerMap["quit"]	= TMethodMsgHandler<IAppl, void (IAppl::*)()>::create(this, &IAppl::quit);

	fGetMsgHandlerMap["version"]	= TGetParamMsgHandler<string>::create(fVersion);
	fGetMsgHandlerMap["rootPath"]	= TGetParamMsgHandler<string>::create(fRootPath);
	fGetMsgHandlerMap["port"]		= TGetParamMsgHandler<int>::create(fUDP.fInPort);
	fGetMsgHandlerMap["outport"]	= TGetParamMsgHandler<int>::create(fUDP.fOutPort);
	fGetMsgHandlerMap["errport"]	= TGetParamMsgHandler<int>::create(fUDP.fErrPort);
	fGetMsgHandlerMap["defaultShow"]= TGetParamMsgHandler<bool>::create(fDefaultShow);

	fMsgHandlerMap["rootPath"]		= TSetMethodMsgHandler<IAppl, string>::create(this, &IAppl::setRootPath);
	fMsgHandlerMap["port"]			= TSetMethodMsgHandler<IAppl,int>::create(this, &IAppl::setUDPInPort);
	fMsgHandlerMap["outport"]		= TSetMethodMsgHandler<IAppl,int>::create(this, &IAppl::setUDPOutPort);
	fMsgHandlerMap["errport"]		= TSetMethodMsgHandler<IAppl,int>::create(this, &IAppl::setUDPErrPort);
	fMsgHandlerMap["defaultShow"]	= TSetMethodMsgHandler<IAppl,bool>::create(this, &IAppl::setDefaultShow);

//	fMsgHandlerMap["rootPath"]	= TSetMsgHandler<string>::create(fRootPath);
//	fMsgHandlerMap["port"]		= TSetMsgHandler<int>::create(fUDP.fInPort);
//	fMsgHandlerMap["outport"]	= TSetMsgHandler<int>::create(fUDP.fOutPort);
//	fMsgHandlerMap["errport"]	= TSetMsgHandler<int>::create(fUDP.fErrPort);
//	fMsgHandlerMap["defaultShow"]= TSetMsgHandler<bool>::create(IObjectFactory::fDefaultShow);

	fGetMsgHandlerMap["date"]		= 0;
	fGetMsgHandlerMap["duration"]	= 0;

	fGetMsgHandlerMap["x"]		= 0;
	fGetMsgHandlerMap["y"]		= 0;
	fGetMsgHandlerMap["z"]		= 0;
	fGetMsgHandlerMap["angle"]	= 0;
	fGetMsgHandlerMap["scale"]	= 0;
	fGetMsgHandlerMap["show"]	= 0;
	fGetMsgHandlerMap["width"]	= 0;
	fGetMsgHandlerMap["height"] = 0;

	fGetMsgHandlerMap["color"]	= 0;
	fGetMsgHandlerMap["red"]	= 0;
	fGetMsgHandlerMap["green"]	= 0;
	fGetMsgHandlerMap["blue"]	= 0;
	fGetMsgHandlerMap["alpha"]	= 0;
	fGetMsgHandlerMap["hue"]	= 0;
	fGetMsgHandlerMap["saturation"] = 0;
	fGetMsgHandlerMap["brightness"]	= 0;

#ifdef RUNBENCH
	fMsgHandlerMap["startBench"]	= TMethodMsgHandler<IAppl, void (IAppl::*)()>::create(this, &IAppl::startBench);
	fMsgHandlerMap["stopBench"]		= TMethodMsgHandler<IAppl, void (IAppl::*)()>::create(this, &IAppl::stopBench);
	fMsgHandlerMap["resetBench"]	= TMethodMsgHandler<IAppl, void (IAppl::*)()>::create(this, &IAppl::resetBench);
	fMsgHandlerMap["writeBench"]	= TMethodMsgHandler<IAppl>::create(this, &IAppl::writeBench);
#endif
}

//--------------------------------------------------------------------------
IAppl::~IAppl() {}
bool IAppl::oscDebug() const								{ return fApplDebug->getOSCDebug(); }

//--------------------------------------------------------------------------
void IAppl::setRootPath(const std::string& s)
{
	if ( !QDir( s.c_str() ).exists() )
		ITLErr << "rootPath is an invalid location: " << s << ITLEndl;
	string root = s;
	char end = root[root.length()-1];
	if (end == '\\')   root[root.length()-1] = '/';
	else if (end != '/') root += '/';
	IAppl::fRootPath = root;
}

//--------------------------------------------------------------------------
void IAppl::print (ostream& out) const
{
	IObject::print (out);
	out << "  running: " << (running() ? "true" : "false") << endl;
	out << "  root path: " << fRootPath << endl;
	out << "  udp infos: " << fUDP << endl;
	out << "  debug: " << fApplDebug << endl;
}

//--------------------------------------------------------------------------
void IAppl::createVirtualNodes()
{
	fApplDebug = IApplDebug::create(this);
	fDebug = fApplDebug;
	add ( fDebug );
}

//--------------------------------------------------------------------------
void IAppl::accept (Updater* u)
{
	u->updateTo(SIAppl(this));
}

#define useiterator 0
//--------------------------------------------------------------------------
// the 'get' at root level
// applications parameters are flushed first since
// next messages may depend on the application state
IMessageList IAppl::getAll() const
{
	IMessageList outMsgs = getParams();
#if useiterator
	for (subnodes::const_iterator i = elements().begin(); i != elements().end(); i++) {
		if (!(*i)->getDeleted())
			outMsgs += (*i)->getAll();
	}
#else
	for (unsigned int i = 0; i < elements().size(); i++) {
		nodePtr elt = elements()[i];
		if (!elt->getDeleted())
			outMsgs += elt->getAll();
	}
#endif
	return outMsgs;
}

//--------------------------------------------------------------------------
// messages processing
//--------------------------------------------------------------------------
int IAppl::processMsg (const std::string& address, const std::string& addressTail, const IMessage* msg)
{
	if (addressTail.size()) 		// application is not the final destination of the message
		return IObject::processMsg(address,addressTail, msg);

	if (match(address)) {			// the message is for the application itself
		int status = execute(msg);
		if (status & MsgHandler::kProcessed)
			setState(IObject::kModified);
		return status;
	}
	return MsgHandler::kBadAddress;
}

//--------------------------------------------------------------------------
// messages handlers
//--------------------------------------------------------------------------
IMessage * IAppl::hello()	const
{
	IMessage* msg = new IMessage(getOSCAddress());
	*msg << getIP() << getUDPInPort() << getUDPOutPort() << getUDPErrPort();
	return msg;
}

//--------------------------------------------------------------------------
void IAppl::helloMsg() const
{
	IMessage * msg = hello();
	msg->print(oscout);
	delete msg;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IAppl::loadMsg(const IMessage* msg)
{
	if (msg->size() == 1) {
		string srcfile = msg->params()[0]->value<string>("");
		if (srcfile.size()) {
			ITLparser p;
			IMessageList* msgs = p.readfile(absolutePath(srcfile).c_str());
			if (msgs) {
				for (IMessageList::const_iterator i = msgs->begin(); i != msgs->end(); i++) {
					string beg  = OSCAddress::addressFirst((*i)->address());
					string tail = OSCAddress::addressTail((*i)->address());
					bool ret = processMsg(beg, tail, *i);
					if (oscDebug()) IGlue::trace(*i, ret);
				}
				msgs->clear();
				delete msgs;
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
std::string IAppl::absolutePath( const std::string& path )
{
	const string& rootPath = getRootPath();
	char ending = rootPath[rootPath.length()-1];
#ifdef WIN32
		const char* sep = (ending == '/') || (ending == '\\') ? "" : "/";
		return ( path[1] != ':') ? ( rootPath + sep + path ) : path ;
#else
		const char* sep = (ending == '/') ? "" : "/";
		return ( path[0] != '/' ) ? ( rootPath + sep + path ) : path ;
#endif
}
}
