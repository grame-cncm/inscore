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

using namespace std;

namespace inscore
{

extern SIMessageStack gMsgStask;

const char* kXVar		= "$x";
const char* kYVar		= "$y";
const char* kAbsXVar	= "$absx";
const char* kAbsYVar	= "$absy";
const char* kDateVar	= "$date";


//----------------------------------------------------------------------
EventMessage::EventMessage (const IMessage* msg, int startindex) : fMessage(0), fPort(kDefaultUPDPort)
{
	decodeMessage (msg, startindex);
}

//----------------------------------------------------------------------
EventMessage::~EventMessage () { delete fMessage; }

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
void EventMessage::decodeMessage (const IMessage* msg, int startindex)
{
	if ((msg->size() - startindex) < 2) return;
	string address;
//	if (msg->param (startindex, address) && msg->param (startindex+1, msgStr)) {
	if (msg->param (startindex, address)) {
		string oscAddress;
		if (decodeAddress (address, oscAddress, fDest, fPort)) {
			string msgStr;
			int offset = 1;
			if ( msg->param (startindex+1, msgStr) ) offset = 2;
			fMessage = new IMessage (oscAddress, msgStr);
			for (int i = startindex+2; i < msg->size(); i++) {
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
void EventMessage::checkvariable (IMessage& msg, const string& param, 
			float x, float y, float relx, float rely, const rational& date, bool setmsg) const
{
	if (param[0] == '$') {
		if (param == kXVar)			msg << relx;
		else if (param == kYVar)	msg << rely;
		else if (param == kAbsXVar)	msg << x;
		else if (param == kAbsYVar)	msg << y;
		else if (param == kDateVar)	msg << date;
		else if (setmsg) msg.setMessage (param);
		else msg << param;
	}
	else if (setmsg) msg.setMessage (param);
	else msg << param;
}

//----------------------------------------------------------------------
void EventMessage::send(float x, float y, float relx, float rely, const rational& date) const
{
	if (fMessage) {
		int n = fMessage->size();
		IMessage msg (fMessage->address());
		checkvariable (msg, fMessage->message(), x, y, relx, rely, date, true);
		for (int i=0; i<n; i++) {
			string str;
			if (fMessage->param(i, str)) {
				checkvariable (msg, str, x, y, relx, rely, date);				
			}
			else msg.add(fMessage->params()[i]);
		}
		if (fDest.empty())	localSend (&msg);
		else				sockSend (&msg, fDest, fPort);
	}
}

} // end namespoace

