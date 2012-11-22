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

#include "IFileWatcher.h"
#include "IMessage.h"
#include "Updater.h"
#include "IAppl.h"

using namespace std;

namespace inscore
{

const string IFileWatcher::kFileWatcherType("fileWatcher");

//--------------------------------------------------------------------------
IFileWatcher::IFileWatcher(IObject * parent) : IVNode(kFileWatcherType, parent)
{ 
	fMsgHandlerMap["add"]		= TMethodMsgHandler<IFileWatcher>::create(this, &IFileWatcher::addMsg);
	fMsgHandlerMap["remove"]	= TMethodMsgHandler<IFileWatcher>::create(this, &IFileWatcher::removeMsg);
	fMsgHandlerMap["clear"]		= TMethodMsgHandler<IFileWatcher>::create(this, &IFileWatcher::clearMsg);
	fMsgHandlerMap["watch"]		= 0L;
	fMsgHandlerMap["watch+"]	= 0L;
}

//--------------------------------------------------------------------------
void IFileWatcher::print (ostream& out) const
{
	IObject::print (out);
}

//--------------------------------------------------------------------------
SIMessage IFileWatcher::buildMessage(const IMessage* source)
{
	std::string oscAddress, message;
	if (!source->param(1, oscAddress) || !source->param(2, message))
		return 0;

	SIMessage outMsg = IMessage::create(oscAddress, message);
	for (int i= 3; i<source->size(); i++)
		outMsg->add (source->param(i));
	return outMsg;


//	outMsg = source;
//
//	std::string oscAddress, message;
//	if (!source.param(1, oscAddress) || !source.param(2, message))
//		return false;
//
//	outMsg.setAddress( oscAddress );	// moves the address from params to address field
//	outMsg.setMessage( message );		// moves the message from params to message field
//	
//	// and removes the file, address and message from the parameters list
//	IMessage::argslist::iterator first = outMsg.params().begin();
//	outMsg.params().erase(first, first + 3);
//	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::addMsg (const IMessage* msg )	
{
	// the 'add' message expects the following parameters: 'filePath' OSCMessage
	// where OSCMessage format is: 'address' 'msg' <opt parameters>
	// thus a minimum of 3 parameters is expected
//	if (msg->size() >= 3) {
//		std::string fileName;
//		if (!msg->param(0, fileName)) return MsgHandler::kBadParameters;
//		if ( fileName.size() ) {
//			SIMessage watcherMessage = IMessage::create();
//			if (IFileWatcher::buildMessage (msg, watcherMessage)) {
//				addAssociation( WatcherAssociation( IAppl::absolutePath(fileName) , watcherMessage ) );
//				return MsgHandler::kProcessed;
//			}
//		}
//	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::removeMsg (const IMessage* msg )	
{
//	if (msg->size() == 1) {
//		string oscAddress;
//		if (!msg->param(0, oscAddress)) return MsgHandler::kBadParameters;
//		if ( oscAddress.size() ) {
//			remove( oscAddress );
//			return MsgHandler::kProcessed;
//		}
//	}	
//	else if (msg->size() >= 3) {
//		std::string fileName;
//		if (!msg->param(0, fileName)) return MsgHandler::kBadParameters;
//		if ( fileName.size() ) {
//			SIMessage watcherMessage = buildMessage(msg);
//			if (watcherMessage) {
//				remove( IAppl::absolutePath(fileName), watcherMessage );
//				return MsgHandler::kProcessed;
//			}
//		}
//	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::clearMsg (const IMessage* msg)
{
	if (msg->size() == 0) {
		fWatchList.clear();
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
SIMessageList IFileWatcher::getMsgs (const IMessage* msg) const
{
	SIMessageList outMsgs = IMessageList::create();
	for ( TWatchList::const_iterator i = fWatchList.begin(); i != fWatchList.end() ; i++ ) {
		SIMessage msg = IMessage::create(getOSCAddress(), "add");
		*msg << i->first << i->second;
		outMsgs->list().push_back(msg);
	}
	return outMsgs;
}

}

