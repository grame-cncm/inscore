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
		out << i->second->getMaster()->name() << " -> " << i->second->getMaster()->name() 
			<< " align: " << Master::syncmode2string(i->second->getAlignment()) 
			<< " stretch: " << Master::stretchmode2string(i->second->getStretch()) 
			<< " dy: " << i->second->getDy() 
//			<< " interpolate:"<< Master::interpolatemode2string(i->second->getInterpolate())
			<< " masterMapName: " << i->second->getMasterMapName()
			<< " slaveMapName: " << i->second->getSlaveMapName();
			
//		if ( i->second->getCustomOptions().size() )
//		{
//			out << " custom options:";
//			for ( unsigned int j = 0 ; j < i->second->getCustomOptions().size() ; j++ )
//				out << i->second->getCustomOptions()[j] << ";";
//		}
		out << endl;
	}
}

//--------------------------------------------------------------------------
// looking for loops in the sync scheme
bool ISync::checkLoop(const IObject* slave, IObject* master)
{
	const_iterator i = this->find (master);				// look for possible master of the master
	if (i == this->end()) return false;					// there is none : no loop
	IObject* nextmaster = i->second->getMaster();
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
		ITLErr << "unexpected synchronization request:" << slave->name() << " -> " << slave->name() << ITLEndl;
		return;
	}

	if (!checkLoop (slave, master->getMaster())) {
		(*this)[slave] = master;
		slave->modify();
		slave->setState(IObject::kModified);
		slave->graphicView()->setParentItem(master->getMaster()->graphicView());
		slave->setdyMsgHandler(master);
		fModified = true;
	}
}

//--------------------------------------------------------------------------
void ISync::remove(SIObject slave) 
{
	if (this->erase(slave)) {
		slave->UseGraphic2GraphicMapping (false);
		slave->setdyMsgHandler();
		slave->modify();
		slave->setState(IObject::kModified);
		fModified = true;
		VGraphicsItemView * view = slave->graphicView();
		if (view) view->setParentItem(0);
	}
}

//--------------------------------------------------------------------------
void ISync::cleanup()
{
	iterator i = begin();
	while (i != end()) {
		if (i->first->getDeleted() || i->second->getMaster()->getDeleted()) {
			iterator d = i;
			i++;
			this->remove(d->first);
		}
		else i++;
	}
}

#define SYNC_OVER	"syncOver"
#define SYNC_TOP	"syncTop"
#define SYNC_BOTTOM	"syncBottom"
#define STRETCH_H	"h"
#define STRETCH_HH	"H"
#define STRETCH_V	"v"
#define STRETCH_HV	"hv"
#define STRETCH_HHV	"Hv"
#define INTERPOLATION_LINEAR	"linearInterpolatation"
#define INTERPOLATION_NO		"noInterpolation"


//--------------------------------------------------------------------------
std::string	Master::syncmode2string(int syncmode)
{
	switch (syncmode) {
		case kSyncOver:		return SYNC_OVER;
		case kSyncTop:		return SYNC_TOP;
		case kSyncBottom:	return SYNC_BOTTOM;
		default:			return "unknown";
	}
}

//--------------------------------------------------------------------------
std::string	Master::stretchmode2string(int stretchmode)
{
	switch (stretchmode) {
		case kStretchH:		return STRETCH_H;
		case kStretchHH:	return STRETCH_HH;
		case kStretchV:		return STRETCH_V;
		case kStretchHV:	return STRETCH_HV;
		case kStretchHHV:	return STRETCH_HHV;
		case kNoStretch:	return "";
		default:			return "unknown";
	}
}

std::map<std::string, Master::VAlignType> Master::fSyncStr;
std::map<std::string, Master::StretchType> Master::fStretchStr;
//std::map<std::string, int> Master::fInterpolationStr;
//--------------------------------------------------------------------------
void Master::initMap()
{
	if (!fSyncStr.size()) {
		fSyncStr[SYNC_OVER]		= kSyncOver;
		fSyncStr[SYNC_TOP]		= kSyncTop;
		fSyncStr[SYNC_BOTTOM]	= kSyncBottom;
		fStretchStr[STRETCH_H]	= kStretchH;
		fStretchStr[STRETCH_HH]	= kStretchHH;
		fStretchStr[STRETCH_V]	= kStretchV;
		fStretchStr[STRETCH_HV]	= kStretchHV;
		fStretchStr[STRETCH_HHV]= kStretchHHV;
//		fInterpolationStr[INTERPOLATION_LINEAR] = kLinearInterpolation;
//		fInterpolationStr[INTERPOLATION_NO] = kNoInterpolation;
	}
}

//--------------------------------------------------------------------------
Master::VAlignType Master::string2syncmode(std::string syncmode)
{
	map<string, Master::VAlignType>::const_iterator i = fSyncStr.find(syncmode);
	return (i == fSyncStr.end()) ? kUnknown : i->second;
}

//--------------------------------------------------------------------------
Master::StretchType	Master::string2stretchmode(std::string stretchmode)
{
	map<string, Master::StretchType>::const_iterator i = fStretchStr.find(stretchmode);
	return (i == fStretchStr.end()) ? kStretchUnknown : i->second;
}

//--------------------------------------------------------------------------
//std::string	Master::interpolatemode2string(int interpolateMode)
//{
//	switch (interpolateMode) {
//		case kLinearInterpolation:	return INTERPOLATION_LINEAR;
//		case kNoInterpolation:		return INTERPOLATION_NO;
//		default:					return "unknown";
//	}
//}

//--------------------------------------------------------------------------
//int Master::string2interpolatemode(std::string interpolateMode)
//{
//	map<string, int>::const_iterator i = fInterpolationStr.find(interpolateMode);
//	return (i == fInterpolationStr.end()) ? kUnknown : i->second;
//}
		
//--------------------------------------------------------------------------
//OSCStream&	operator << (OSCStream& out, const Master& m)
//{
//	out << m.getMaster()->name();
//	int syncMode = m.getAlignment();
//	if (syncMode != Master::kDefaultSync)
//		out <<  Master::syncmode2string(syncMode);
//	int stretchMode = m.getStretch();
//	if (stretchMode != Master::kDefaultStretch)
//		out <<  Master::stretchmode2string(stretchMode);
//	if (m.getDy() != 0)
//		out <<  " dy " << m.getDy();
//	if ( m.getInterpolate() != Master::kDefaultInterpolation )
//	out << " interpolate="<< Master::interpolatemode2string(m.getInterpolate()) ;
//	if ( m.getCustomOptions().size() )
//	{
//		out << " custom options:";
//		for ( unsigned int i = 0 ; i < m.getCustomOptions().size() ; i++ )
//			out << m.getCustomOptions()[i];
//	}
//	return out;
//}

//--------------------------------------------------------------------------
IMessage&	operator << (IMessage& out, const Master& m)
{
	string mname = m.getMaster()->name();
	const string& mmap = m.getMasterMapName();
	if (mmap.size())
		mname += ":" + mmap;
	out << mname;
	int syncMode = m.getAlignment();
	if (syncMode != Master::kDefaultSync)
		out <<  Master::syncmode2string(syncMode);
	int stretchMode = m.getStretch();
	if (stretchMode != Master::kDefaultStretch)
		out <<  Master::stretchmode2string(stretchMode);
//	if (m.getDy() != 0)
//		out <<  " dy " << m.getDy();
	return out;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const ISync& sync)
{
	sync.print(out);
	return out;
}


} //end namespace
