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
	fMsgHandlerMap[kwatch_GetSetMethod]		= 0L;
	fMsgHandlerMap[kwatchplus_SetMethod]	= 0L;
	fGetMultiMsgHandlerMap[kwatch_GetSetMethod]	= 0L;
}

//--------------------------------------------------------------------------
void ISceneSync::accept (Updater* u)
{
	u->updateTo (SISceneSync(this));
}

//--------------------------------------------------------------------------
SMaster ISceneSync::getMaster(SIObject o) const
{
    if(fSync.hasMaster(o))
        return fSync.getMasters(o).front();
	return 0;
}
//--------------------------------------------------------------------------
vector<SMaster> ISceneSync::getMasters(SIObject o, const std::string& master, const std::string& map) const
																	{ return fSync.getMasters(o, master, map); }

//--------------------------------------------------------------------------
vector<SMaster>		ISceneSync::getMasters(SIObject o) const		{ return fSync.getMasters(o); }
vector<SIObject>	ISceneSync::getSlaves(const SIObject o) const	{ return fSync.getSlaves(o); }

//--------------------------------------------------------------------------
IObject::subnodes ISceneSync::sort (IObject::subnodes& nodes)			{ return fSync.topologicalSort (nodes); }
IObject::subnodes ISceneSync::invertedSort (IObject::subnodes& nodes)	{ return fSync.invertedTopologicalSort (nodes); }

//--------------------------------------------------------------------------
static SIMessage buildSyncMsg (const string& address, SIObject o, const SMaster master)
{
	string target = o->name();
	if (master) {
		const string& smap = master->getSlaveMapName();
		if (smap.size()) target += ":" + smap;
		SIMessage msg = IMessage::create(address);
		if (msg) {
			*msg << target;
			*msg << *master;
		}
		return msg;
	}
	return IMessage::create(address, target);
}

//--------------------------------------------------------------------------
SIMessageList ISceneSync::getMsgs (const IMessage* msg) const
{
	SIMessageList outMsgs = IObject::getMsgs (msg);
	if (outMsgs->list().size()) return outMsgs;

	const string& address = getOSCAddress();
	if (msg->size() == 1) {
		string who = msg->param(0)->value<string>("-");
		string name, mapname;
		name2mapName (who, name, mapname);
		subnodes list;
		if (fParent->find(name, list)) {
			for (subnodes::const_iterator i = list.begin(); i != list.end(); i++) {
                vector<SMaster> masters = getMasters(*i);
                for(vector<SMaster>::iterator j = masters.begin(); j != masters.end(); j++)
                {
                    SIMessage msg = buildSyncMsg (address, *i, *j);
                    outMsgs->list().push_back (msg);
                }
			}
		}
	}
	else if (msg->size() == 0) {
        map<SIObject, vector<SMaster> > s2m = fSync.getSlaves2Masters();
        ISync::const_slave_iterator it = s2m.begin();
        while(it != s2m.end())
        {
			for (unsigned int i = 0; i < it->second.size(); i++) {
                SIMessage msg = buildSyncMsg (address, it->first,  it->second[i]);
                outMsgs->list().push_back (msg);
            }
            it++;
		}
	}
	return outMsgs;	
}

//--------------------------------------------------------------------------
// propagates modification state from masters to slaves
//--------------------------------------------------------------------------
void ISceneSync::ptask ()
{
    fSync.ptask();
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
		map = str.substr( sepPos+1, str.length()-name.size());
		return true;
	}
	name = str;
	map = "";
	return false;
}

//--------------------------------------------------------------------------
// removes the synchronization between objects
// when master is empty, removes all synchronizations for slave
// otherwise removes the slave - master sync only
//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const string& slave, const string& master, const string& masterMapName)
{
	subnodes so;
	if (!fParent->find(slave, so) )
		return MsgHandler::kBadParameters;		// no target objects for slave

	if (master.empty()) {						// this is the delete form #3 i.e. identifier with no other param
        for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
            delsync(*i);						// delete all the
            (*i)->setState (kMasterModified);
        }
		return MsgHandler::kProcessed;
	}

	for (subnodes::iterator i = so.begin(); i != so.end(); i++) {	// for each slave
		SIObject obj = *i;
		vector<SMaster> mlist = fParent->getMasters (obj, master, masterMapName);
		size_t n = mlist.size();
		if (!n) return MsgHandler::kBadParameters;

		for (size_t i=0; i< n; i++)
			delsync(obj, mlist[i]);
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
// creates a synchronization between objects
//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const string& slave, const string& slaveMap, const string& master, const string& masterMap,
											Master::StretchType stretch, Master::SyncType syncmode, Master::VAlignType align)
{
	subnodes sobj, mobj;
	if (!fParent->find(slave, sobj) || !fParent->find(master, mobj))
		return MsgHandler::kBadParameters;						// no target objects for slave or for master

	for (subnodes::iterator i = sobj.begin(); i != sobj.end(); i++) {	// for each slave
		SIObject so = *i;
		bool exist = false;

																		// look for existing sync
		vector<SMaster> mlist = fParent->getMasters (so, master, masterMap);
		size_t n = mlist.size();
		for (size_t i = 0; i < n; i++) {
			Master* m = mlist[i];
			if ( m->getSlaveMapName() == slaveMap )  {			// there is already a sync between both that are using the same maps
				m->setSyncOptions (align, stretch, syncmode);	// update the sync options
				exist = true;
			}
		}
		if (!exist) {											// no existing sync
			for (size_t i = 0; i < mobj.size(); i++) {			// create the sync for each master
				sync(so, Master::create(mobj[i], align, stretch, syncmode, masterMap , slaveMap ));
			}
		}
		so->setState (kMasterModified);
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
// looks for optional parameters in a string
// one of align, stretch or syncType may be modified on output with the corresponding option
// returns true when the string is an option, false otherwise
//--------------------------------------------------------------------------
bool ISceneSync::scanOption (const string& option, Master::VAlignType& align, Master::StretchType& stretch, Master::SyncType& syncType) const
{
	Master::VAlignType va = Master::string2syncalign(option);
	if (va != Master::kUnknown) {
		align = va;
		return true;
	}

	Master::StretchType vs = Master::string2stretchmode(option);
	if (vs != Master::kStretchUnknown) {
		stretch = vs;
		return true;
	}

	Master::SyncType vt = Master::string2synctype(option);
	if (vt != Master::kTypeUnknown)	{
		syncType = vt;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
// look for the slave name in a message
// due to historical reasons: the slave name could be stored in the message string
// or as first parameter
// returns the index of the next parameter to scan or -1 in case of error
//--------------------------------------------------------------------------
int ISceneSync::scanSlave (const IMessage* msg, string& name, string& mapName) const
{
	// when the message string is not empty, assumes it's the slave name
	if (msg->message().size()) {
		name2mapName (msg->message(), name, mapName);
		return 0;
	}

	// otherwise looks for the slave in the first parameter
	if (msg->size()) {
		string slave;
		if (msg->param(0, slave)) {
			name2mapName (slave, name, mapName);
			return 1;
		}
	}
	return -1;
}

//--------------------------------------------------------------------------
// the main entry point for messages adressed to the sync node
// the global form is the following:
//   1) identifier identifier [opt. syncmode]
//   2) identifier identifier del
//   3) identifier
// where identifier is an object name [opt. : mapname]
// 1) creates a slave master synchronization with the optional synchronisation modes
// 2) and 3) deletes a sync relation (2) or all sync relations (3) for an object
//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const IMessage* msg)
{
	int n = msg->size();
	string slave, slaveMapName;

	int index = scanSlave (msg, slave, slaveMapName);
	if (index < 0) return MsgHandler::kBadParameters;
	
	// we've already reached the end of the parameters
	// this is the delete form #3
	if (index == n) return syncMsg (slave);

	string str;
	// at this point, the master name is expected
	if (!msg->param(index++, str))	return MsgHandler::kBadParameters;
	string master, masterMapName;
	name2mapName (str, master, masterMapName);

	// sets the default values for stretch, alignment and sync type
	Master::VAlignType align = Master::kDefaultSyncAlign;
	Master::StretchType stretch = Master::kDefaultStretch;
	Master::SyncType syncType = Master::kDefaultSync;
	if (index == n) 	// we've reached the end of the parameters: creates the sync using default values
        return syncMsg (slave, slaveMapName, master, masterMapName, stretch, syncType, align);

	if (msg->param(index++, str)) {	// look for the next parameter
		if(str == kdel_SetMethod) 	// and check for the delete form #2
			return syncMsg(slave, master, masterMapName);
	}
	else return MsgHandler::kBadParameters;		// only strings are expected as parameters

	do {
		if (!scanOption (str, align, stretch, syncType))	return MsgHandler::kBadParameters;
		if (index < n) {
			if (!msg->param(index++, str))					return MsgHandler::kBadParameters;
		} else break;
	} while (true);
	// eventually sets the synchonization with the optional parameters
    return syncMsg (slave, slaveMapName, master, masterMapName, stretch, syncType, align);
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all the objects parameters
SIMessageList ISceneSync::getAllParams() const
{
	SIMessageList outMsgs = 	IObject::getAllParams();
    map<SIObject, vector<SMaster> > s2m = fSync.getSlaves2Masters();
	ISync::const_slave_iterator i = s2m.begin();
	// and distribute the message to synced nodes
	while (i != s2m.end()) {
		const SIObject& elt = i->first;
		SIMessage msg = IMessage::create(getOSCAddress(), kget_SetMethod);
		msg->add (elt->name());
		outMsgs->list().push_back (getMsgs(msg)->list());
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
