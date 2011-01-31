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

#include <stdlib.h>

#include "EventMessage.h"
#include "IMessage.h"
#include "IMessageStack.h"
#include "IMessageStream.h"
#include "OSCStream.h"
#include "deelx.h"

using namespace std;

namespace inscore
{

extern SIMessageStack gMsgStask;

const char* kXVar		= "$x";
const char* kYVar		= "$y";
const char* kSceneXVar	= "$sx";
const char* kSceneYVar	= "$sy";
const char* kAbsXVar	= "$absx";
const char* kAbsYVar	= "$absy";
const char* kDateVar	= "$date";
const char* kSelfVar	= "$self";


//----------------------------------------------------------------------
EventMessage::EventMessage (const string& objname, const IMessage* msg, int startindex) : fMessage(0), fPort(kDefaultUPDPort)
{
	decodeMessage (objname, msg, startindex);
}

//----------------------------------------------------------------------
EventMessage::~EventMessage () { delete fMessage; }

//----------------------------------------------------------------------
string EventMessage::checkVariableAddress (const string& address, const string& objname) const
{
	CRegexpT<char> regexp("\\$self", EXTENDED);
	char* tmp = regexp.Replace (address.c_str(), objname.c_str());
	string outAddress = tmp;
	regexp.ReleaseString (tmp);
	return outAddress;
}

//----------------------------------------------------------------------
bool EventMessage::decodeAddress (const std::string& address, std::string& oscAddress, std::string& host, int& port) const
{
	size_t startOsc = address.find_first_of('/');
	if (startOsc != string::npos) {
		port = kDefaultUPDPort;
		oscAddress = address.substr (startOsc);
		if (startOsc > 0) {
			size_t startPort = address.find_first_of(':');
			if ((startPort != string::npos) && (startPort < startOsc)) {
				host = address.substr (0, startPort);
				string portStr = address.substr (startPort+1, startOsc-1);
				port = atoi(portStr.c_str());
			}
			else host = address.substr (0, startOsc);
		}
		else host.clear();
//cout << "EventMessage::decodeAddress " << address << " => " << host << ":" << port << oscAddress << endl;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
void EventMessage::decodeMessage (const string& objname, const IMessage* msg, int startindex)
{
	if ((msg->size() - startindex) < 2) return;
	string address;
	if (msg->param (startindex++, address)) {
		string oscAddress;
		if (decodeAddress (address, oscAddress, fDest, fPort)) {
			fMessage = new IMessage (checkVariableAddress(oscAddress, objname));
			string msgStr;
			if ( msg->param (startindex, msgStr) ) {
				fMessage->setMessage (msgStr);
				startindex++;
			}
			for (int i = startindex; i < msg->size(); i++) {
				fMessage->params().push_back( msg->params()[i]);
			}
		}
	}
}

static 	UdpSocket gEvtSocket;
OSCStream gStream (&gEvtSocket);
//----------------------------------------------------------------------
void EventMessage::sockSend (const IMessage* msg, const string& dst, int port) const
{
	gStream.setAddress (dst);
	gStream.setPort(port);
//cout << "EventMessage::sockSend => " << dst << ":" << port << endl;
	msg->print(gStream);
}

//----------------------------------------------------------------------
void EventMessage::localSend (const IMessage* msg) const
{
	IMessage* copy = new IMessage (*msg);
	if (copy) gMsgStask->push(copy);
}

//----------------------------------------------------------------------
void EventMessage::send () const
{
	if (fMessage) {
		if (fDest.empty())	localSend (fMessage);
		else				sockSend (fMessage, fDest, fPort);
	}
}

//----------------------------------------------------------------------
bool EventMessage::isDateVar (const string& var, string& mapname) const
{
	string base (kDateVar);
	if (var == base) return true;
	if (var.compare (0, base.size(), base) == 0) {
		if (var[base.size()] == ':') {
			mapname = var.substr(base.size()+1);
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
bool EventMessage::hasDateVar (std::string& mapname) const
{
	if (isDateVar (fMessage->message(), mapname)) return true;
	int n = fMessage->size();
	for (int i=0; i<n; i++) {
		string str;
		if (fMessage->param(i, str))
			if (isDateVar (str, mapname))  return true;
	}
	return false;	
}

//----------------------------------------------------------------------
float EventMessage::checkrange (const string& param, float val) const
{
	float low, high;
	int n = sscanf (param.c_str(), "[%f,%f]", &low, &high);
	if (n == 2) return val * (high - low) - low;
	return val;
}

//----------------------------------------------------------------------
void EventMessage::checkvariable (IMessage& msg, const string& param, const MouseLocation& ml, const rational& date, bool setmsg) const
{
	string mapname;
	if (param[0] == '$') {
		if (param[1] == 'x')			msg << checkrange(param.substr(2), ml.fx);
		else if (param[1] == 'y')		msg << checkrange(param.substr(2), ml.fy);
		else if (param == kAbsXVar)		msg << ml.fabsx;
		else if (param == kAbsYVar)		msg << ml.fabsy;
		else if (param == kSceneXVar) 	msg << ml.fsx;
		else if (param == kSceneYVar)	msg << ml.fsy;
		else if (isDateVar (param, mapname))	msg << date;
		else if (setmsg) msg.setMessage (param);
		else msg << param;
	}
	else if (setmsg) msg.setMessage (param);
	else msg << param;
}

//----------------------------------------------------------------------
void EventMessage::send(const MouseLocation& ml, const rational& date) const
{
	if (fMessage) {
		int n = fMessage->size();
		IMessage msg (fMessage->address());
		checkvariable (msg, fMessage->message(), ml, date, true);
		for (int i=0; i<n; i++) {
			string str;
			if (fMessage->param(i, str)) {
				checkvariable (msg, str, ml, date);				
			}
			else msg.add(fMessage->params()[i]);
		}
		if (fDest.empty())	localSend (&msg);
		else				sockSend (&msg, fDest, fPort);
	}
}

} // end namespoace

