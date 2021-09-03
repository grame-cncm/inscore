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
#include <regex>

#include "AudioNode.h"
#include "IMessage.h"
#include "IObject.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
void AudioNode::cleanup (AudioNodeCnxList& list)
{
//cerr << "AudioNode::cleanup list " << list.size() << endl;
	AudioNodeCnxList::iterator i = list.begin();
	while (i != list.end()) {
		if (i->obj->getDeleted())
			i = list.erase (i);
		else i++;
	}
	fNotifyNew.clear();
	fNotifyDel.clear();
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioNode::connect (const IMessage* msg)
{
	AudioNodeCnxList list;
	MsgHandler::msgStatus status = getAudioNodes(msg, list);
//cerr << "AudioNode::connect " << list.size() << " " << fNotifyNew.size() << " " << msg << endl;
	if (status == MsgHandler::kProcessed) {
		for (auto elt: list) {
			AudioNode * anode = dynamic_cast<AudioNode*>((IObject*)elt.obj);
			if (!fNumOutputs || !anode->getInputs()) {
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
		stringstream str;
		if (elt.from && elt.to)
			str << elt.from << ":" << elt.obj->name() << ":" << elt.to;
		else str << elt.obj->name();
		out.push_back (str.str());
	}
	return out;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioNode::disconnect (const IMessage* msg)
{
	AudioNodeCnxList list;
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
bool AudioNode::remove(const AudioConnection& elt, AudioNodeCnxList& list)
{
	AudioNodeCnxList::iterator i = find (list.begin(), list.end(), elt);
	if (i != list.end()) {
		list.erase(i);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
// scan for channel specification i.e. name in the form n:nodeName:m
// where 'n' and 'm' are channel indexes
AudioNode::_AudioConnection	AudioNode::getAudioConnection (std::string desc) const
{
	std::regex e ("([0-9]+):([^:]+):([0-9]+)");
	smatch m;

	_AudioConnection cnx;
	if (regex_search (desc, m, e)) {
		cnx.name = m[2];
		cnx.from = std::stoi(m[1]);
		cnx.to 	 = std::stoi(m[3]);
	}
	else {
		cnx.name = desc;
		cnx.from = cnx.to = 0;
	}
	return cnx;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioNode::getAudioNodes(const IMessage* msg, AudioNodeCnxList& list)
{
	int n = msg->size();
	if (!n) return MsgHandler::kBadParameters;

	IObject* obj = dynamic_cast<IObject*>(this);
	for (int i=0; i<n; i++) {
		string dest;
		IObject::subnodes objlist;
		if (!msg->param(i, dest))
			return MsgHandler::kBadParameters;

		_AudioConnection cnx = getAudioConnection (dest);
		
		if (!obj->getParent()->find(cnx.name, objlist)) {
			ITLErr << cnx.name << " no such object" << ITLEndl;
			return MsgHandler::kBadParameters;
		}
		for (auto elt: objlist) {
			AudioNode * anode = dynamic_cast<AudioNode*>((IObject*)elt);
			if (anode) list.push_back (AudioConnection(elt, cnx.from, cnx.to));
			else {
				ITLErr << cnx.name << " is not an audio node" << ITLEndl;
				return MsgHandler::kBadParameters;
			}
		}
	}
	return MsgHandler::kProcessed;
}


} // end namespoace
