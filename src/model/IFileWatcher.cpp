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
	fMsgHandlerMap["watch"]		= 0L;
	fMsgHandlerMap["watch+"]	= 0L;
}

//--------------------------------------------------------------------------
void IFileWatcher::print (ostream& out) const
{
	IObject::print (out);
}

//--------------------------------------------------------------------------
bool IFileWatcher::buildMessage(const IMessage& source, IMessage& outMsg)
{
	outMsg = source;

	const std::string err = "";
	const std::string oscAddress	= source.params()[1]->value<std::string>(err);
	const std::string message		= source.params()[2]->value<std::string>(err);
	if ( ( oscAddress == err ) || ( message == err ) )
		return false;

	outMsg.setAddress( oscAddress );	// moves the address from params to address field
	outMsg.setMessage( message );		// moves the message from params to message field
	
	// and removes the file, address and message from the parameters list
	IMessage::argslist::iterator first = outMsg.params().begin();
	outMsg.params().erase(first, first + 3);
	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::addMsg (const IMessage* msg )	
{
	// the 'add' message expects the following parameters: 'filePath' OSCMessage
	// where OSCMessage format is: 'address' 'msg' <opt parameters>
	// thus a minimum of 3 parameters is expected
	if (msg->params().size() >= 3) {
		const std::string fileName	= msg->params()[0]->value<std::string>("");
		if ( fileName.size() ) {
			IMessage watcherMessage;
			if (IFileWatcher::buildMessage(*msg,watcherMessage)) {
				add( WatcherAssociation( IAppl::absolutePath(fileName) , watcherMessage ) );
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::removeMsg (const IMessage* msg )	
{
	if (msg->params().size() == 1) {
		const std::string oscAddress	= msg->params()[0]->value<std::string>("");
		if ( oscAddress.size() ) {
			remove( oscAddress );
			return MsgHandler::kProcessed;
		}
	}	
	else if (msg->params().size() >= 3) {
		const std::string fileName	= msg->params()[0]->value<std::string>("");
		if ( fileName.size() ) {
			IMessage watcherMessage;
			if (IFileWatcher::buildMessage(*msg,watcherMessage)) {
				remove( WatcherAssociation(IAppl::absolutePath(fileName) , watcherMessage) );
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::clearMsg (const IMessage* msg)
{
	if (msg->params().size() == 0) {
		clear();
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
IMessageList IFileWatcher::getMsgs (const IMessage* msg) const
{
	IMessageList outMsgs;

	vector<WatcherAssociation> associations;
	getList(associations);
	
	for ( unsigned int i = 0 ; i < associations.size() ; i++ ) {
		const IMessage * cmsg = &(associations[i].mMessage);
		IMessage* msg = new IMessage(getOSCAddress(), "add");
		*msg << associations[i].mFileName << cmsg;
		outMsgs += msg;
	}
	return outMsgs;
}

}

