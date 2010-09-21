/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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

#include <iostream>

#include "IProxy.h"
#include "IMessage.h"
#include "IObjectFactory.h"
#include "ISignalNode.h"
#include "ISignal.h"
#include "Tools.h"

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
int IProxy::signal (const IMessage* msg, const std::string& objName, SIObject parent)
{
	if (msg->message() == "get") return MsgHandler::kBadParameters;

	SIObject obj = IObjectFactory::create(objName, ISignal::kSignalType, parent);
	if (obj) {
		int status = obj->execute(msg);
		if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) parent->add(obj);
		return MsgHandler::kProcessed;
//		done = obj->execute(msg);
//		if (done) parent->add(obj);
	}
	return MsgHandler::kCreateFailure;
}

//--------------------------------------------------------------------------
int IProxy::execute (const IMessage* msg, const std::string& objName, SIObject parent)
{
	if (parent && (parent->name() == ISignalNode::kName))
		return signal (msg, objName, parent);

	if (msg->message() != "set") return MsgHandler::kBadAddress;
	if (msg->params().size() == 0) return MsgHandler::kBadParameters;
	if (Tools::regexp(objName)) return MsgHandler::kBadAddress;
	
	string objType = msg->params()[0]->value<string>("");
	SIObject obj = IObjectFactory::create(objName, objType, parent);
	if (obj) {
		int status = obj->execute(msg);
		if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) {
			parent->add(obj);
			obj->setState(IObject::kModified);
			return MsgHandler::kProcessed;
		}
		return status;
	}
	return MsgHandler::kCreateFailure;
}


}
