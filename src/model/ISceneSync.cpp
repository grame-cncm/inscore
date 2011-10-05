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

#include <iostream>


#include "ISceneSync.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string ISceneSync::fTypeString = "syncnode";

//--------------------------------------------------------------------------
ISceneSync::ISceneSync(IObject * parent) : IVNode("sync", parent)
{
	fMsgHandlerMap["*"]	= TMethodMsgHandler<ISceneSync>::create(this, &ISceneSync::syncMsg);
	fMsgHandlerMap["watch"]		= 0;
	fMsgHandlerMap["watch+"]	= 0;
}

//--------------------------------------------------------------------------
void ISceneSync::accept (Updater* u)
{
	u->updateTo (SISceneSync(this));
}

//--------------------------------------------------------------------------
SMaster ISceneSync::getMaster(SIObject o) const
{
	ISync::const_iterator found = fSync.find(o);
	return (found != fSync.end()) ? found->second : 0;
}

//--------------------------------------------------------------------------
void ISceneSync::sort (IObject::subnodes& nodes)
{
	if (fSync.modified()) {
//		fSync.topologicalSort (nodes);
		fSync.modified(false);
	}
}

//--------------------------------------------------------------------------
static IMessage* buildSyncMsg (const string& address, SIObject o, const SMaster master)
{
	string target = o->name();
	if (master) {
		const string& smap = master->getSlaveMapName();
		if (smap.size()) target += ":" + smap;
		IMessage * msg = new IMessage(address);
		if (msg) {
			*msg << target;
			*msg << *master;
		}
		return msg;
	}
	return new IMessage(address, target);
}

//--------------------------------------------------------------------------
IMessageList ISceneSync::getMsgs (const IMessage* msg) const
{
	IMessageList outMsgs = IObject::getMsgs (msg);
	if (outMsgs.size()) return outMsgs;

	const string& address = getOSCAddress();
	if (msg->params().size() == 1) {
		string who = msg->params()[0]->value<string>("-");
		string name, mapname;
		name2mapName (who, name, mapname);
		subnodes list;
		if (fParent->find(name, list)) {
			for (subnodes::const_iterator i = list.begin(); i != list.end(); i++) {				
				IMessage * msg = buildSyncMsg (address, *i,  getMaster(*i));
				outMsgs += msg;
			}
		}
	}
	else if (msg->params().size() == 0) {
		for (ISync::const_iterator i = fSync.begin(); i != fSync.end(); i++) {
			IMessage * msg = buildSyncMsg (address, i->first,  i->second);
			outMsgs += msg;
		}
	}
	return outMsgs;	
}

//--------------------------------------------------------------------------
// propagates modification state from masters to slaves
//--------------------------------------------------------------------------
void ISceneSync::ptask ()
{
	for (ISync::iterator i = fSync.begin(); i != fSync.end(); i++) {
		const SIObject& master = i->second->getMaster();
		if (master->getState() & kModified)
			i->first->setState(kMasterModified);
	}
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
#define MAP_NAME_SEPARATOR ':'
//--------------------------------------------------------------------------
bool ISceneSync::name2mapName (const string& str, string& name, string& map) const
{
	size_t sepPos = str.find_first_of(MAP_NAME_SEPARATOR);
	if ( sepPos != string::npos ) {
		name = str.substr(0, sepPos);
		map = str.substr( sepPos+1, name.length() + 1);		
		return true;
	}
	name = str;
	map = "";
	return false;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const std::string& slave)
{
	subnodes so;
	if (!fParent->find(slave, so)) return MsgHandler::kBadParameters;		// no target objects to be slave
	for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
		delsync(*i);
		(*i)->UseGraphic2GraphicMapping (false);
		(*i)->setState (kMasterModified);
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const std::string& slave, const std::string& slaveMap, 
									const std::string& master, const std::string& masterMap,
									Master::StretchType stretch, Master::VAlignType valign)
{
	subnodes so;
	if (!fParent->find(slave, so)) return MsgHandler::kBadParameters;		// no target objects to be slave
	subnodes mos;
	if (!fParent->exactfind(master, mos)) return MsgHandler::kBadParameters;

	for (unsigned int j = 0; j < mos.size(); j++) {
		SIObject mo = mos[j];
		for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
			SMaster m = Master::create(mo, valign, stretch, masterMap , slaveMap );
			sync(*i, m);
			(*i)->setState (kMasterModified);
		}
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const IMessage* msg)	
{
	int n = msg->params().size();
	string slave, slaveMapName;
	int nextindex = 0;
	if (msg->message().size()) {
		name2mapName (msg->message(), slave, slaveMapName);
		if (!n) return syncMsg (slave);
	}
	else if (n) {
		name2mapName (msg->params()[0]->value<string>(""), slave, slaveMapName);
		if (n > 1) nextindex = 1;
		else return syncMsg (slave);
	}
	else return MsgHandler::kBadParameters;
	
	string master, masterMapName;
	name2mapName (msg->params()[nextindex]->value<string>(""), master, masterMapName);
	Master::VAlignType align = Master::kDefaultSync;
	Master::StretchType stretch = Master::kDefaultStretch;
	for (int i=nextindex+1; i<n; i++) {
		string mode = msg->params()[i]->value<string>("");
		Master::VAlignType val = Master::string2syncmode(mode);
		if (val != Master::kUnknown) align = val;
		else {
			Master::StretchType sval = Master::string2stretchmode(mode);
			if (sval != Master::kStretchUnknown) stretch = sval;
		}
	}
	return syncMsg (slave, slaveMapName, master, masterMapName, stretch, align);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::oldsyncMsg (const IMessage* msg)	
{
	int n = msg->params().size();
	if (!n)  return MsgHandler::kBadParameters;

	string slave, slaveMapName;
	name2mapName (msg->params()[0]->value<string>(""), slave, slaveMapName);
//	name2mapName (msg->message(), slave, slaveMapName);

	subnodes so;
	if (!fParent->find(slave, so)) return MsgHandler::kBadParameters;		// no target objects to be slave
	
	MsgHandler::msgStatus result = MsgHandler::kBadParameters;
	if (n > 1) {
		string master, masterMapName;
		name2mapName (msg->params()[1]->value<string>(""), master, masterMapName);

		Master::VAlignType align = Master::kDefaultSync;
		Master::StretchType stretch = Master::kDefaultStretch;
		
		for (int i=2; i<n; i++) {
			string mode = msg->params()[i]->value<string>("");
			Master::VAlignType val = Master::string2syncmode(mode);
			if (val != Master::kUnknown) align = val;
			else {
				Master::StretchType sval = Master::string2stretchmode(mode);
				if (sval != Master::kStretchUnknown) stretch = sval;
			}
		}
		subnodes mos;
		if (fParent->exactfind(master, mos)) {
			for (unsigned int j = 0; j < mos.size(); j++) {
				SIObject mo = mos[j];
				for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
					SMaster m = Master::create(mo, align, stretch, /*syncOptions ,*/ masterMapName , slaveMapName );
					sync(*i, m);
					(*i)->setState (kMasterModified);
				}
			}
			result = MsgHandler::kProcessed;
		}
	}
	else for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
		delsync(*i);
		(*i)->UseGraphic2GraphicMapping (false);
		(*i)->setState (kMasterModified);
		result = MsgHandler::kProcessed;
	}
	return result;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all the objects parameters
IMessageList ISceneSync::getAllParams() const
{
	IMessageList outMsgs = 	IObject::getAllParams();
	ISync::const_iterator i = fSync.begin();
	// and distribute the message to synced nodes
	while (i != fSync.end()) {
		const SIObject& elt = i->first;
		IMessage msg (getOSCAddress(), "get");
		msg.add<string>(elt->name());
		outMsgs += getMsgs(&msg);
		i++;
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
void ISceneSync::print (ostream& out) const
{
	out << "  nodes synchronization :" << endl << fSync;	
}

}
