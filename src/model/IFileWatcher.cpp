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
//void IFileWatcher::set (const std::string& file, const IMessage* msg)
//{
//	SIMessageList list = IMessageList::create();
//	fWatchList[file] = list;
//	list->list().push_back (IMessage::create (*msg));
//}

//--------------------------------------------------------------------------
void IFileWatcher::set (const std::string& file, SIMessageList msgs)
{
	fWatchList[file] = msgs;
}

//--------------------------------------------------------------------------
void IFileWatcher::add (const std::string& file, SIMessageList msgs)
{
	SIMessageList target = fWatchList[file];
	if (!target)
		fWatchList[file] = msgs;
	else
		target->list().push_back (msgs->list());
}

//--------------------------------------------------------------------------
//void IFileWatcher::add (const std::string& file, const IMessage* msg)
//{
//	SIMessageList target = fWatchList[file];
//	if (!target) {
//		target = IMessageList::create();
//		fWatchList[file] = target;
//	}
//	target->list().push_back (IMessage::create (*msg));
//}

//--------------------------------------------------------------------------
void IFileWatcher::clear (const string& file)
{
	TWatchList::iterator i = fWatchList.find (file);
	if (i != fWatchList.end()) fWatchList.erase(i);
}

//--------------------------------------------------------------------------
void IFileWatcher::trigger (const string& file) const
{
	TWatchList::const_iterator item = fWatchList.find (file);
	if (item != fWatchList.end()) {
		const IMessageList* l = item->second;
		if (l) {
			for (unsigned int i=0; i < l->list().size(); i++) {
				const IMessage * msg = l->list()[i];
				if (msg->extendedAddress())
					OSCStream::sendEvent (msg, msg->url().fHostname, msg->url().fPort);
				else {
					SIMessage copy = IMessage::create(*msg);
					if (copy) gMsgStack->push(new SIMessage(copy));
				}
			}
		}
	}
}

//--------------------------------------------------------------------------
SIMessageList IFileWatcher::buildMessage(const IMessage* source)
{
	SIMessageList list;
	if (source->param(1, list))			// message already built by the parser
		return list;
	
	std::string oscAddress, message;
	if (!source->param(1, oscAddress) || !source->param(2, message))
		return 0;

	SIMessageList outMsgs = IMessageList::create();
	SIMessage msg = IMessage::create(oscAddress, message);
	for (int i= 3; i<source->size(); i++)
		msg->add (source->param(i));
	outMsgs->list().push_back( msg );
	return outMsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::addWatchMsg (const IMessage* msg )	
{
	if (msg->size() < 4) return MsgHandler::kBadParameters;

	std::string filename;				// a file name is expected as first argument
	if (!msg->param(0, filename) || !filename.size()) return MsgHandler::kBadParameters;

	SIMessageList watchmsgs = buildMessage (msg);
	if ( watchmsgs ) add ( IAppl::absolutePath(filename), watchmsgs);
	else return MsgHandler::kBadParameters;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFileWatcher::watchMsg (const IMessage* msg )	
{
	// the 'watch' message expects the following parameters: 'filePath' OSCMessage
	// where OSCMessage format is: 'address' 'msg' <opt parameters>
	// thus a minimum of 3 parameters is expected
	int n = msg->size();
	// 'watch' message without argument clear the watch list
	if (n == 0) clear();
	else {
		std::string filename;				// a file name is expected as first argument
		if (!msg->param(0, filename) || !filename.size()) return MsgHandler::kBadParameters;
		
		if (n == 1)							// 'watch' message with 1 argument: clear a file associated watch list			
			clear (IAppl::absolutePath(filename));
		else {								// more parameters: build the message and associates it to filename
			SIMessageList watchmsgs = buildMessage (msg);
			if ( watchmsgs ) set ( IAppl::absolutePath(filename), watchmsgs);
			else return MsgHandler::kBadParameters;
		}
	}
	return MsgHandler::kProcessed;
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

