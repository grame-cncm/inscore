/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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

#include <iostream>

#include "AudioNode.h"
#include "IMessage.h"
#include "IObject.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
void AudioNode::cleanup (AudioNodeList& list)
{
//cerr << "AudioNode::cleanup list " << list.size() << endl;
	AudioNodeList::iterator i = list.begin();
	while (i != list.end()) {
		if ((*i)->getDeleted())
			i = list.erase (i);
		else i++;
	}
	fNotifyNew.clear();
	fNotifyDel.clear();
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioNode::connect (const IMessage* msg)
{
	AudioNodeList list;
	MsgHandler::msgStatus status = getAudioNodes(msg, list);
//cerr << "AudioNode::connect " << list.size() << " " << fNotifyNew.size() << " " << msg << endl;
	if (status == MsgHandler::kProcessed) {
		for (auto elt: list) {
			AudioNode * anode = dynamic_cast<AudioNode*>((IObject*)elt);
			if (fNumOutputs != anode->getInputs()) {
				ITLErr << "cannot connect a " << fNumOutputs << " outputs object to " << anode->getInputs() << " inputs" << ITLEndl;
				return MsgHandler::kBadParameters;
			}
			if (find (fOutputs.begin(), fOutputs.end(), elt) == fOutputs.end()) {
				fOutputs.push_back(elt);
				fNotifyNew.push_back(elt);
			}
		}
	}
	return status;
}

//--------------------------------------------------------------------------
vector<string> AudioNode::getconnect () const
{
//cerr << "AudioNode::getconnect " << endl;
	const IObject* obj = dynamic_cast<const IObject*>(this);
	vector<string> out;
	for (auto elt: fOutputs) {
		out.push_back (elt->name());
	}
	return out;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioNode::disconnect (const IMessage* msg)
{
	AudioNodeList list;
	MsgHandler::msgStatus status = getAudioNodes(msg, list);
//cerr << "AudioNode::disconnect " << list.size() << " " << fNotifyDel.size() << " "  << msg << endl;
	if (status == MsgHandler::kProcessed) {
		for (auto elt: list) {
			if (remove (elt, fOutputs)) {
				fNotifyDel.push_back(elt);
			}
		}
	}
	return status;
}

//--------------------------------------------------------------------------
bool AudioNode::remove(const IObject* node, AudioNodeList& list)
{
	AudioNodeList::iterator i = find (list.begin(), list.end(), node);
	if (i != list.end()) {
		list.erase(i);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioNode::getAudioNodes(const IMessage* msg, AudioNodeList& list)
{
	int n = msg->size();
	if (!n) return MsgHandler::kBadParameters;

	IObject* obj = dynamic_cast<IObject*>(this);
	for (int i=0; i<n; i++) {
		string address;
		IObject::subnodes objlist;
		if (!msg->param(i, address))
			return MsgHandler::kBadParameters;
		if (!obj->getParent()->find(address, objlist)) {
			ITLErr << address << " no such object" << ITLEndl;
			return MsgHandler::kBadParameters;
		}
		for (auto elt: objlist) {
			AudioNode * anode = dynamic_cast<AudioNode*>((IObject*)elt);
			if (anode) list.push_back (elt);
			else {
				ITLErr << address << " is not an audio node" << ITLEndl;
				return MsgHandler::kBadParameters;
			}
		}
	}
	return MsgHandler::kProcessed;
}


} // end namespoace
