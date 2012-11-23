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

#include <iostream>

#include "IOSCListener.h"
#include "IMessageStack.h"
#include "IMessage.h"

#include "osc/OscReceivedElements.h"
#include "ip/IpEndpointName.h"

using namespace std;
using namespace osc;

namespace inscore
{

//--------------------------------------------------------------------------
IOSCListener::IOSCListener(SIMessageStack& stack, int port) 
		: fSocket(IpEndpointName( IpEndpointName::ANY_ADDRESS, port ), this), fMsgStack(stack), fRunning(false) {}
IOSCListener::~IOSCListener()	{ stop(); }

//--------------------------------------------------------------------------
void IOSCListener::run()
{ 
	fRunning = true;
//	while (fRunning) {
		try {
			fSocket.Run(); 
		}
		catch (osc::Exception e) {
			cerr << "osc error: " << e.what() << endl;
		}
//	}
	fRunning = false;
}

//--------------------------------------------------------------------------
void IOSCListener::stop()	
{ 
	fSocket.AsynchronousBreak();
}

//--------------------------------------------------------------------------
void IOSCListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& src )
{
	IMessage* msg = new IMessage(m.AddressPattern());
	msg->setSrcIP (src.address);
	ReceivedMessageArgumentIterator i = m.ArgumentsBegin();
	bool first = true;		// used to handle the message string
	while (i != m.ArgumentsEnd()) {
		if (i->IsString()) {
			// the message string is expected to be the first parameter
			if (first) msg->setMessage(i->AsStringUnchecked());
			else msg->add<string>(i->AsStringUnchecked());			
		}
		else if (i->IsInt32()) {
			msg->add<int>(i->AsInt32Unchecked());			
		}
		else if (i->IsFloat()) {
			msg->add<float>(i->AsFloatUnchecked());			
		}
		if (first) first = false;
		i++;
	}
	fMsgStack->push (msg);
	fMsgStack->inc();
}

} // end namespoace
