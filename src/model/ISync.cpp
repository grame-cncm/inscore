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

#include <algorithm>
#include <iostream>
#include "ISync.h"
#include "ISceneSync.h"
#include "ITLError.h"
#include "VGraphicsItemView.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
void ISync::print (ostream& out) const
{
	for (const_slave_iterator i = fSlaves2Masters.begin(); i != fSlaves2Masters.end(); i++)
	{
        for(int j = 0; j<(*i).second.size(); j++)
        {
            out << (*i).first->name() << " -> " << (*i).second[j]->getMaster()->name()
                << " align: " << Master::syncalign2string(i->second[j]->getAlignment())
                << " stretch: " << Master::stretchmode2string((*i).second[j]->getStretch())
                << " dy: " << (*i).second[j]->getDy()
                << " masterMapName: " << (*i).second[j]->getMasterMapName()
                << " slaveMapName: " << (*i).second[j]->getSlaveMapName();
            out << endl;
        }
	}
}

//--------------------------------------------------------------------------
std::vector<SMaster> ISync::getMasters(SIObject slave) const
{
    const_slave_iterator it = fSlaves2Masters.find(slave);
    if(it != fSlaves2Masters.end())
        return it->second;
    else
        return std::vector<SMaster>();
}


//--------------------------------------------------------------------------
std::vector<SIObject> ISync::getSlaves(SIObject master) const
{
    const_master_iterator it = fMasters2Slaves.find(master);
    if(it != fMasters2Slaves.end())
        return it->second;
    else
        return std::vector<SIObject>();
}

//--------------------------------------------------------------------------
std::map<SIObject, std::vector<SMaster> > ISync::getSlaves2Masters() const
{
    return fSlaves2Masters;
}

//--------------------------------------------------------------------------
ISync::relation ISync::getRelation(SIObject o1, SIObject o2) const
{
    if(hasSlave(o1))
    {
        std::vector<SIObject> slaves = getSlaves(o1);
        if(std::find(slaves.begin(), slaves.end(), o2) != slaves.end())
            return kMaster;
    }
    else if(hasSlave(o2))
    {
        std::vector<SIObject> slaves = getSlaves(o2);
        if(std::find(slaves.begin(), slaves.end(), o1) != slaves.end())
            return kSlave;
    }
    
    return kNoRelation;
}

//--------------------------------------------------------------------------
IObject::subnodes ISync::topologicalSort(IObject::subnodes& nodes) const
{
    IObject::subnodes in = nodes;
    IObject::subnodes out;
    do
    {
        IObject::subnodes sameLevelOfSync;
        IObject::subnodes::iterator it = in.begin();
        while(it != in.end())
        {
            bool addToVector = true;
            if(hasSlave(*it))
            {
                std::vector<SIObject> slaves = getSlaves(*it);
                for(int i = 0; i<slaves.size(); i++)
                    if(std::find(out.begin(), out.end(), slaves[i]) == out.end())   // if one of the slaves of the node is not in the "already-sorted-nodes",
                        addToVector = false;                                        // we won't add the node to the final vector yet.
            }
            if(addToVector)
            {
                sameLevelOfSync.push_back(*it);
                in.erase(it);
            }
            else
                it++;
        }
        for(int j = 0; j<sameLevelOfSync.size(); j++)
            out.push_back(sameLevelOfSync[j]);
    }while(!in.empty());
   
    return out;
}

//--------------------------------------------------------------------------
IObject::subnodes ISync::invertedTopologicalSort(IObject::subnodes& nodes) const
{
    IObject::subnodes in = nodes;
    IObject::subnodes out;
    do
    {
        IObject::subnodes sameLevelOfSync;
        IObject::subnodes::iterator it = in.begin();
        while(it != in.end())
        {
            bool addToVector = true;
            if(hasMaster(*it))
            {
                std::vector<SMaster> masters = getMasters(*it);
                for(int i = 0; i<masters.size(); i++)
                    if(std::find(out.begin(), out.end(), masters[i]->getMaster()) == out.end()) // if one of the masters is not in the "already-sorted-nodes",
                        addToVector = false;                                                    // we won't add the node to the final vector yet.
            }
            if(addToVector)
            {
                sameLevelOfSync.push_back(*it);
                in.erase(it);
            }
            else
                it++;
        }
        for(int j = 0; j<sameLevelOfSync.size(); j++)
            out.push_back(sameLevelOfSync[j]);
    }while(!in.empty());
    
    return out;
}

//--------------------------------------------------------------------------
// looking for loops in the sync scheme
bool ISync::checkLoop(const SIObject slave, SIObject master)
{
	if(!hasMaster(master)) return false;
    if(getRelation(slave, master) == kMaster)
    {
        ITLErr << "sync loop detected for object" << slave->name() << ITLEndl;
        return true;
    }
    
    std::vector<SMaster> masters = getMasters(master);
    for(int i = 0; i<masters.size(); i++)
    {
        if(checkLoop(slave, masters[i]->getMaster()))
        {
            ITLErr << "sync loop detected for object" << slave->name() << ITLEndl;
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------------
void ISync::sync(const SIObject& slave, SMaster master) 
{
	if (slave == master->getMaster()) {
		ITLErr << "unexpected synchronization request:" << slave->name() << "->" << slave->name() << ITLEndl;
		return;
	}
    if(getRelation(slave, master->getMaster()) == kSlave) // already exists
        remove(slave, master);
    if (!checkLoop (slave, master->getMaster())) {
        if(hasMaster(slave))
            fSlaves2Masters.find(slave)->second.push_back(master);
        else
        {
            std::vector<SMaster> masters = std::vector<SMaster>();
            masters.push_back(master);
            fSlaves2Masters.insert(std::pair<SIObject, std::vector<SMaster> >(slave, masters));
        }
        if(hasSlave(master->getMaster()))
            fMasters2Slaves.find(master->getMaster())->second.push_back(slave);
        else
        {
            std::vector<SIObject> slaves = std::vector<SIObject>();
            slaves.push_back(slave);
            fMasters2Slaves.insert(std::pair<SIObject, std::vector<SIObject> >(master->getMaster(), slaves));
        }
		slave->modify();
		slave->setState(IObject::kModified);
	//	slave->getView()->setParentItem(master->getMaster()->getView());    // for now, we just change the parent of the Qt item, the view keeps one parent (and
                                                                            //  several masters)
		slave->setdyMsgHandler(master);
		fModified = true;
	}
}

//--------------------------------------------------------------------------
void ISync::remove(SIObject slave, SMaster m)
{
    if(m) // if the master is specified, we just want to erase the pair <slave,master> and not all pairs corresponding to the slave
    {
        if(getRelation(slave, m->getMaster()) == kSlave)
        {
            if(getMasters(slave).size()>1)
                fSlaves2Masters.find(slave)->second.erase(std::find(fSlaves2Masters.find(slave)->second.begin(), fSlaves2Masters.find(slave)->second.end(), m));
            else
            {
                fSlaves2Masters.erase(fSlaves2Masters.find(slave));
                slave->UseGraphic2GraphicMapping (false, m->getMaster()->name());
            }
            
            if(getSlaves(m->getMaster()).size()>1)
                fMasters2Slaves.find(m->getMaster())->second.erase(std::find(fMasters2Slaves.find(m->getMaster())->second.begin(), fMasters2Slaves.find(m->getMaster())->second.end(), slave));
            else
                fMasters2Slaves.erase(fMasters2Slaves.find(m->getMaster()));
        }
    }
	else {// when the master is not specified, we delete all the possible pairs with the slave
        std::vector<SMaster> masters = getMasters(slave);
        fSlaves2Masters.erase(fSlaves2Masters.find(slave));
        for(int i=0; i<masters.size(); i++)
        {
            if(hasSlave(masters[i]->getMaster()))
            {
                if(getSlaves(masters[i]->getMaster()).size()>1)
                    fMasters2Slaves.find(masters[i]->getMaster())->second.erase(std::find(fMasters2Slaves.find(masters[i]->getMaster())->second.begin(), fMasters2Slaves.find(masters[i]->getMaster())->second.end(), slave));
                else
                    fMasters2Slaves.erase(fMasters2Slaves.find(masters[i]->getMaster()));
            }
        }
        slave->UseGraphic2GraphicMapping (false);
	}
    
    slave->setdyMsgHandler();
    slave->modify();
    slave->setState(IObject::kModified);
    fModified = true;
}

//--------------------------------------------------------------------------
void ISync::cleanup()
{
	slave_iterator i = fSlaves2Masters.begin();
	while (i != fSlaves2Masters.end()) {
		if ((*i).first->getDeleted()) {
			slave_iterator d = i;
			i++;
			remove((*d).first);
		}
		else
        {
            slave_iterator d = i;
            i++;
            for(int j = 0; j<(*d).second.size(); j++)
            {
                if((*d).second[j]->getMaster()->getDeleted())
                    remove((*d).first, (*d).second[j]);
            }
        }
	}
}

//--------------------------------------------------------------------------
void ISync::ptask ()
{
    for(const_master_iterator it = fMasters2Slaves.begin(); it != fMasters2Slaves.end(); it++)
    {
        if(it->first->getState() && IObject::kModified)
            for(int i = 0; i<it->second.size(); i++)
                it->second[i]->setState(IObject::kMasterModified);
    }
}

static const char* kSyncOverStr		= "syncOver";
static const char* kSyncTopStr		= "syncTop";
static const char* kSyncBottomStr	= "syncBottom";
static const char* kSyncStretchHStr	= "h";
static const char* kSyncStretchHHStr= "H";
static const char* kSyncStretchVStr	= "v";
static const char* kSyncStretchHVStr= "hv";
static const char* kSyncStretchHHVStr="Hv";
static const char* kSyncRelativeStr	= "relative";
static const char* kSyncAbsoluteStr	= "absolute";


//--------------------------------------------------------------------------
std::string	Master::syncalign2string(int align)
{
	switch (align) {
		case kSyncOver:		return kSyncOverStr;
		case kSyncTop:		return kSyncTopStr;
		case kSyncBottom:	return kSyncBottomStr;
		default:			return "unknown";
	}
}

//--------------------------------------------------------------------------
std::string	Master::synctype2string(int sync)
{
	switch (sync) {
		case kSyncRelative:		return kSyncRelativeStr;
		case kSyncAbsolute:		return kSyncAbsoluteStr;
		default:			return "unknown";
	}
}

//--------------------------------------------------------------------------
std::string	Master::stretchmode2string(int stretchmode)
{
	switch (stretchmode) {
		case kStretchH:		return kSyncStretchHStr;
		case kStretchHH:	return kSyncStretchHHStr;
		case kStretchV:		return kSyncStretchVStr;
		case kStretchHV:	return kSyncStretchHVStr;
		case kStretchHHV:	return kSyncStretchHHVStr;
		case kNoStretch:	return "";
		default:			return "unknown";
	}
}

std::map<std::string, Master::VAlignType>	Master::fAlignStr;
std::map<std::string, Master::StretchType>	Master::fStretchStr;
std::map<std::string, Master::SyncType>		Master::fTypeStr;

//std::map<std::string, int> Master::fInterpolationStr;
//--------------------------------------------------------------------------
void Master::initMap()
{
	if (!fAlignStr.size()) {
		fAlignStr[kSyncOverStr]			= kSyncOver;
		fAlignStr[kSyncTopStr]			= kSyncTop;
		fAlignStr[kSyncBottomStr]		= kSyncBottom;

		fStretchStr[kSyncStretchHStr]	= kStretchH;
		fStretchStr[kSyncStretchHHStr]	= kStretchHH;
		fStretchStr[kSyncStretchVStr]	= kStretchV;
		fStretchStr[kSyncStretchHVStr]	= kStretchHV;
		fStretchStr[kSyncStretchHHVStr]	= kStretchHHV;

		fTypeStr[kSyncAbsoluteStr]		= kSyncAbsolute;
		fTypeStr[kSyncRelativeStr]		= kSyncRelative;
	}
}

//--------------------------------------------------------------------------
Master::VAlignType Master::string2syncalign(std::string align)
{
	map<string, Master::VAlignType>::const_iterator i = fAlignStr.find(align);
	return (i == fAlignStr.end()) ? kUnknown : i->second;
}

//--------------------------------------------------------------------------
Master::SyncType Master::string2synctype(std::string syncmode)
{
	map<string, Master::SyncType>::const_iterator i = fTypeStr.find(syncmode);
	return (i == fTypeStr.end()) ? kTypeUnknown : i->second;
}

//--------------------------------------------------------------------------
Master::StretchType	Master::string2stretchmode(std::string stretchmode)
{
	map<string, Master::StretchType>::const_iterator i = fStretchStr.find(stretchmode);
	return (i == fStretchStr.end()) ? kStretchUnknown : i->second;
}

//--------------------------------------------------------------------------
IMessage&	operator << (IMessage& out, const Master& m)
{
	string mname = m.getMaster()->name();
	const string& mmap = m.getMasterMapName();
	if (mmap.size())
		mname += ":" + mmap;
	out << mname;
	int syncAlign = m.getAlignment();
	if (syncAlign != Master::kDefaultSync)
		out <<  Master::syncalign2string(syncAlign);
	int stretchMode = m.getStretch();
	if (stretchMode != Master::kDefaultStretch)
		out <<  Master::stretchmode2string(stretchMode);
	int syncMode = m.getMode();
	if (syncMode != Master::kDefaultSync)
		out <<  Master::synctype2string(syncMode);
	return out;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const ISync& sync)
{
	sync.print(out);
	return out;
}


} //end namespace
