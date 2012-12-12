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
#include "IMessageStack.h"
#include "OSCStream.h"
#include "Updater.h"
#include "IAppl.h"

using namespace std;

namespace inscore
{

const string IFileWatcher::kFileWatcherType("fileWatcher");

//--------------------------------------------------------------------------
IFileWatcher::IFileWatcher(IObject * parent) : IVNode(kFileWatcherType, parent)
{ 
	fMsgHandlerMap["watch"]		= TMethodMsgHandler<IFileWatcher>::create(this, &IFileWatcher::watchMsg);
	fMsgHandlerMap["watch+"]	= TMethodMsgHandler<IFileWatcher>::create(this, &IFileWatcher::addWatchMsg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::addWatchMsg (const IMessage* msg )	
{
	if (msg->size() < 4) return MsgHandler::kBadParameters;

	std::string filename;				// a file name is expected as first argument
	if (!msg->param(0, filename) || !filename.size()) return MsgHandler::kBadParameters;

	SIMessageList watchmsgs = msg->watchMsg2Msgs(1);
	if ( watchmsgs && watchmsgs->list().size())
		add ( IAppl::absolutePath(filename), watchmsgs);
	else
		return MsgHandler::kBadParameters;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::watchMsg (const IMessage* msg )	
{
	int n = msg->size();
	// 'watch' message without argument clear the watch list
	if (n == 0) clear();
	else {
		std::string filename;				// a file name is expected as first argument
		if (!msg->param(0, filename) || !filename.size()) return MsgHandler::kBadParameters;
		
		if (n == 1)							// 'watch' message with 1 argument: clear a file associated watch list			
			clear (IAppl::absolutePath(filename));
		else {								// more parameters: build the message and associates it to filename
			SIMessageList watchmsgs = msg->watchMsg2Msgs(1);
			if ( watchmsgs && watchmsgs->list().size())
				set ( IAppl::absolutePath(filename), watchmsgs);
			else
				return MsgHandler::kBadParameters;
		}
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
SIMessageList IFileWatcher::getMsgs (const IMessage* msg) const
{
	SIMessageList outMsgs = IMessageList::create();
	bool doit = (msg->size() == 0);
	if (!doit) {				// look for a 'watch' parameters
		string what;
		for (int i=0; (i < msg->size()) && !doit; i++)
			doit = msg->param(i, what) && (what == "watch");
	}
	if (!doit)	return outMsgs;
	
	for ( TWatcher<string>::const_iterator i = list().begin(); i != list().end() ; i++ ) {
		SIMessage msg = IMessage::create(getOSCAddress(), "watch");
		*msg << i->first << i->second;
		outMsgs->list().push_back(msg);
	}
	if (outMsgs->list().empty()) outMsgs->list().push_back(IMessage::create(getOSCAddress(), "watch"));
	return outMsgs;
}

}

