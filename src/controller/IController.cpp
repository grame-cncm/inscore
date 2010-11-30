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

#include "IController.h"
#include "IMessage.h"
#include "IMessageStack.h"
#include "IObject.h"
#include "IProxy.h"
#include "OSCAddress.h"
#include "OSCStream.h"

using namespace std;

namespace inscore
{

#define kAddressSep	'/'

//--------------------------------------------------------------------------
IController::IController() : fListener(0)	{}
IController::~IController()	{}

//--------------------------------------------------------------------------
void IController::processOn(SIMessageStack& msgs, SIObject& obj)
{
	IMessage* msg = msgs->pop();
	while (msg) {
		oscout.setAddress(msg->src());
		oscerr.setAddress(msg->src());
		int status = processMsg (msg, obj);
		if (fListener) fListener->msgReceived (msg, status);
		delete msg;
		msg = msgs->pop();
	}
}

//--------------------------------------------------------------------------
int IController::processMsg (const IMessage* msg, SIObject& obj)
{
	const std::string& address = msg->address();
	string beg  = OSCAddress::addressFirst(address);
	string tail = OSCAddress::addressTail(address);
	return obj->processMsg (beg, tail, msg);
}

} // end namespoace
