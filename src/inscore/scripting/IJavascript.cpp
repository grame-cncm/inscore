/*

  INScore Project

  Copyright (C) 2013  Grame

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

#include <string>
#include <iostream>

#include "IJavascript.h"
#include "IGlue.h"
#include "OSCAddress.h"
#include "IAppl.h"

using namespace std;

namespace inscore
{

const char* IJavascript::kName = "javascript";
//--------------------------------------------------------------------------
IJavascript::IJavascript(IObject * parent) 
:	IVNode (kName, parent),
	fScripter (parent->getAppl())
{
	fMsgHandlerMap[krun_SetMethod]	= TMethodMsgHandler<IJavascript>::create(this, &IJavascript::runMsg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IJavascript::runMsg(const IMessage* msg)
{
	if (msg->size() == 1) {
		string code;
		if (!msg->param(0, code)) return MsgHandler::kBadParameters;
		if (code.size()) {
			SIMessageList msgs = fScripter.jsEval (code.c_str(), 1);
			if (msgs) {
				for (IMessageList::TMessageList::const_iterator i = msgs->list().begin(); i != msgs->list().end(); i++) {
					getAppl()->processMsg(*i);
				}
			}
		}
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IJavascript::_watchMsg(const IMessage* , bool )
{
    return MsgHandler::kProcessed;
}

} // end namespoace
