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
	for (const_iterator i = begin(); i != end(); i++)
	{
		out << (*i).second->getMaster()->name() << " -> " << (*i).second->getMaster()->name()
			<< " align: " << Master::syncalign2string(i->second->getAlignment())
			<< " stretch: " << Master::stretchmode2string((*i).second->getStretch())
			<< " dy: " << (*i).second->getDy()
			<< " masterMapName: " << (*i).second->getMasterMapName()
			<< " slaveMapName: " << (*i).second->getSlaveMapName();
		out << endl;
	}
}

//--------------------------------------------------------------------------
void ISync::topologicalSort(IObject::subnodes& nodes) const
{
    int i = 0;
    while( i != nodes.size())
    {
        SIObject node = nodes[i];
        IObject::subnodes slaves = node->getParent()->getSlaves(node);
        bool found = false;
        int j = i;
        SIObject slave;
        while( !slaves.empty() && j < nodes.size()-1 && !found)
        {
            j++;
            int it = 0; 
            while(it < slaves.size() && !found)
            {
                slave = slaves[it];
                if(nodes[j] == slave) found = true;
                it++;
            }
        }
        if(found)
        {
            nodes.at(i)=slave;
            nodes.at(j)=node;
        }
        else
            i++;
    }
}

//--------------------------------------------------------------------------
// looking for loops in the sync scheme
bool ISync::checkLoop(const IObject* slave, IObject* master)
{
	const_iterator i = this->find (master);				// look for possible master of the master
	if (i == this->end()) return false;					// there is none : no loop
	IObject* nextmaster = (*i).second->getMaster();
	if (slave == nextmaster) {							// loop detected !
//		IObject* node = i->first;
//		remove (node);
		ITLErr << "sync loop detected for object" << slave->name() << ITLEndl;
		return true;
	}
	return checkLoop (slave, nextmaster);
}

//--------------------------------------------------------------------------
void ISync::sync(const SIObject& slave, SMaster master) 
{
	if (slave == master->getMaster()) {
		ITLErr << "unexpected synchronization request:" << slave->name() << "->" << slave->name() << ITLEndl;
		return;
	}
    if (!checkLoop (slave, master->getMaster())) {
        // We have now a multimap to allow a slave to have several masters. But we don't want it to take into account
        // the different items of a same master..
        // -> So we look for the slave in the list
        bool alreadyExists = false;
        for (iterator it=equal_range(slave).first; it!=equal_range(slave).second; ++it)
        {
            // if we find it, we compare the master to the one we want to add
            if((*it).second->getMaster() == master->getMaster())
            {
                // and if they're the same, we erase the previous pair before adding the new one
                erase(it);
                alreadyExists = true;
            }
        }
        insert(std::pair<SIObject,SMaster>(slave, master));
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
    if(m && count(slave)) // if the master is specified, we just want to erase the pair <slave,master> and not all pairs corresponding to the slave
    {
        std::pair <std::multimap<SIObject,SMaster>::iterator, std::multimap<SIObject,SMaster>::iterator> ret;
        ret = equal_range(slave);
        for (iterator it=ret.first; it!=ret.second; ++it)
        {
            if((*it).second->getMaster() == m->getMaster())
            {
                erase(it);
                if(!count(slave))
                    slave->UseGraphic2GraphicMapping (false, m->getMaster()->name());
                slave->setdyMsgHandler();
                slave->modify();
                slave->setState(IObject::kModified);
                fModified = true;
                // There should not be more than one pair with the same slave and the same master (Cf sync)
                // so if we find it we can stop.
                return;
            }
        }
    }
	else if(this->erase(slave)) { // when the master is not specified, we delete all the possible pairs with the slave
        slave->UseGraphic2GraphicMapping (false);
		slave->setdyMsgHandler();
		slave->modify();
		slave->setState(IObject::kModified);
		fModified = true;
	}
}

//--------------------------------------------------------------------------
void ISync::cleanup()
{
	iterator i = begin();
	while (i != end()) {
		if ((*i).first->getDeleted() || (*i).second->getMaster()->getDeleted()) {
			iterator d = i;
			i++;
			this->remove((*d).first);
		}
		else {
			(*i).second->modified (false);
			i++;
		}
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
