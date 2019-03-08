/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#include <sstream>

#include "inscorev1converter.h"
#include "pathsList.h"

using namespace std;
using namespace inscore;

namespace inscore2
{

//------------------------------------------------------------
class v1Msg {
	IMessage::TUrl  fUrl;		// the msg address url prefix
	string			fAddress;	// the msg osc address
	string			fMethod;	// the msg method string
	SINode			fPParams;	// parent node of the parameters

	const SINode	getAddress (const SINode& node);
	const SINode	getMethod (const SINode& node);
	SIMessage		getParams (const SINode& node, SIMessage msg) const;

	public :
				 v1Msg(SINode node) {
				 	fPParams = getMethod ( getAddress (node));
				 }
		virtual ~v1Msg() {}

		SIMessage toMessage () const;
};

//------------------------------------------------------------
SIMessage v1Msg::toMessage () const
{
	SIMessage msg;
	if (fMethod.empty()) msg = IMessage::create (fAddress);
	else msg = IMessage::create (fAddress, fMethod);
	if (fUrl.fPort) msg->setUrl (fUrl);
	for (auto n: fPParams->childs())
		getParams (n, msg);
	return msg;
}

//------------------------------------------------------------
const SINode v1Msg::getAddress (const SINode& node)
{
	if (!node) return node;
	const SINode next = node->size() ? node->childs()[0] : 0;
	if (node->address()) {
		if (node->getType() == INode::kURLPrefix)
			fUrl.parse (node->getValue());
		else {
			fAddress += "/";
			fAddress += node->getValue();
		}
		return next ? getAddress (next) : 0;
	}
	else return node;
}

//------------------------------------------------------------
const SINode v1Msg::getMethod (const SINode& node)
{
	if (node && (node->getType() == INode::kText)) {
		fMethod = node->getValue();
	}
	return node;
}

//------------------------------------------------------------
SIMessage v1Msg::getParams (const SINode& node, SIMessage msg) const
{
	if (!node) return 0;
	if (node->address()) {
		v1Msg msgnode (node);
		return msgnode.toMessage ();
	}
	else {
		string prefix;
		switch (node->getType()) {
			case INode::kText:
				msg->add (node->getValue()); break;
			case INode::kInt:
				msg->add (std::stoi(node->getValue())); break;
			case INode::kFloat:
				msg->add (std::stof(node->getValue())); break;
			case INode::kVariable:
				prefix = "$";
				msg->add (prefix + node->getValue()); break;
			default:
				cerr << "v1Msg::getParams: unexpected node type " << node->getTypeStr() << endl;
		}
		SIMessageList msgs = IMessageList::create();
		for (auto n: node->childs()) {
			SIMessage msgparam = getParams (n, msg);
			if (msgparam) msgs->list().push_back (msgparam);
		}
		if (msgs->list().size()) msg->add (msgs);
	}
	return 0;
}

//------------------------------------------------------------
void inscorev1converter::tov1 (SIMessageList msgs, const SINode& node) const
{
	if( node->getType() == INode::kForest) {
		for (auto n: node->childs()) tov1(msgs, n);
	}
	else {
		v1Msg msg (node);
		msgs->list().push_back(msg.toMessage());
	}
}

//------------------------------------------------------------
SIMessageList inscorev1converter::convert (const SINode& node) const
{
	SIMessageList msgs = IMessageList::create();
	tov1 (msgs, pathsList::eval(node));
	return msgs;
}


} // end namespace
