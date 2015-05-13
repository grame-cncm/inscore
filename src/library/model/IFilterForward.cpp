/*

  INScore Project

  Copyright (C) 2015  Grame

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
#include "IFilterForward.h"
#include "IMessage.h"
#include "Tools.h"
#include "OSCRegexp.h"
#include <sstream>


using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
IFilterForward::IFilterForward(IObject *parent) : IVNode("filter", parent)
{
	fGetMsgHandlerMap[kaccept_GetSetMethod]	= TGetParamMethodHandler<IFilterForward, string (IFilterForward::*)() const>::create(this, &IFilterForward::getAcceptMsg);
	fMsgHandlerMap[kaccept_GetSetMethod]	= TMethodMsgHandler<IFilterForward>::create(this, &IFilterForward::setAcceptMsg);

	fGetMsgHandlerMap[kreject_GetSetMethod]	= TGetParamMethodHandler<IFilterForward, string (IFilterForward::*)() const>::create(this, &IFilterForward::getRejectMsg);
	fMsgHandlerMap[kreject_GetSetMethod]	= TMethodMsgHandler<IFilterForward>::create(this, &IFilterForward::setRejectMsg);
}

//--------------------------------------------------------------------------
IFilterForward::~IFilterForward()
{
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFilterForward::setAcceptMsg(const IMessage* msg)
{
	return IFilterForward::setListMsg(fAcceptList, msg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFilterForward::setRejectMsg(const IMessage* msg)
{
	return IFilterForward::setListMsg(fRejectList, msg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFilterForward::setListMsg(std::vector<FilterItem> &aList, const IMessage* msg)
{
	// Reset the list
	aList.clear();

	// If no parameter, nothing to do
	if(msg->size() == 0) {
		return MsgHandler::kProcessed;
	}

	for(int i = 0; i < msg->size(); i++) {
		string item;
		if (!msg->param(i, item)) {
			return MsgHandler::kBadParameters;
		}
		aList.push_back(FilterItem(item));
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
std::string IFilterForward::getAcceptMsg() const
{
	return getListMsg(fAcceptList);
}

//--------------------------------------------------------------------------
std::string IFilterForward::getRejectMsg() const
{
	return getListMsg(fRejectList);
}

//--------------------------------------------------------------------------
std::string IFilterForward::getListMsg(const std::vector<FilterItem> &aList)
{
	stringstream stream;
	bool notfirst = false;
	for(std::vector<FilterItem>::const_iterator i = aList.begin(); i != aList.end(); i++) {
		if(notfirst) {
			stream << " ";
		} else {
			notfirst = true;
		}
		stream << i->value();
	}

	return stream.str();
}

bool IFilterForward::applyFilter(const IMessage* msg) const
{
	// Filter forward message itself.
	if (msg->message() == kforward_GetSetMethod) return true;

	// Apply accept pattern first
	for(std::vector<FilterItem>::const_iterator i = fAcceptList.begin(); i != fAcceptList.end(); i++) {
		if(i->isOscAddress()) {
			string address = msg->address();
			if(i->match(address)) return false;
		} else {
			string message = msg->message();
			if(i->match(message)) return false;
		}
	}

	// Reject pattern
	for(std::vector<FilterItem>::const_iterator i = fRejectList.begin(); i != fRejectList.end(); i++) {
		if(i->isOscAddress()) {
			string address = msg->address();
			if(i->match(address)) return true;
		} else {
			string message = msg->message();
			if(i->match(message)) return true;
		}
	}
	return false;
}

FilterItem::FilterItem(const string &str) : fValue(str)
{
	if(this->isOscAddress() && Tools::regexp(fValue))
		fRexp = new OSCRegexp(fValue.c_str());
	else fRexp = 0;
}

FilterItem::FilterItem(const FilterItem &item) : fValue(item.fValue)
{
	if(item.fRexp)
		fRexp = new OSCRegexp(fValue.c_str());
	else fRexp = 0;
}

FilterItem::~FilterItem()
{
	delete fRexp;
}

bool FilterItem::match(const string &str) const
{
	if(fRexp)
		return fRexp->match(str.c_str());
	return fValue == str;
}


bool FilterItem::isOscAddress() const
{
	return fValue[0] == '/';
}

}
