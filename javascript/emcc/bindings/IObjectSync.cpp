/*

  INScore Library
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

#include "IObjectSync.h"
#include "ISync.h"

using namespace std;

namespace inscore
{

static const float kNoWhere = 99999.f;


//--------------------------------------------------------------------------
static TFloatPoint	scalePos (const IObject* obj, const TFloatPoint& pos)
{
	float x = pos.fX;
	float y = pos.fY;
	float w = obj->getWidth();
	float h = obj->getHeight();
	if ((w < 0.000001) || (h < 0.00001)) w = h = 0;   // this is only for lines
	if (h && w) {
		if (w > h) 		x *= w / h;
		else if (w < h) y *= h / w;
	}
	else {
		if (!w) x = 0;
		if (!h) y = 0;
	}
	return TFloatPoint (x, y);
}

//--------------------------------------------------------------------------
static TFloatPoint	date2FramePosition (const IObject* obj, const libmapping::rational& date)
{
	TFloatPoint pos;
	if (obj->date2FramePoint(date, pos)) {
		pos.fX = (pos.fX * 2) - 1;
		pos.fY = (pos.fY * 2) - 1;
		return scalePos(obj, pos);
	}
	return TFloatPoint (kNoWhere, kNoWhere);
}

//--------------------------------------------------------------------------
static TFloatPoint date2MasterPosition (const SMaster& master, const IObject* slave, const libmapping::rational& date)
{
	TFloatPoint pos;

	const IObject* mobj = master->getMaster();
	std::string mapName = mobj->name() + ":" + master->getMasterMapName();
	pos = slave->getSyncPos(mapName);
	return (pos.x() <= kNoWhere) ? scalePos(mobj, pos) : pos;
}

//--------------------------------------------------------------------------
TFloatPoint	getSyncPosition (const IObject* obj, const SMaster& master, float& vstretch)
{
	TFloatPoint location;

	libmapping::rational date = obj->getDate ();
	const SIObject& masterobj = master->getMaster();
	Master::VAlignType align = master->getAlignment();
	Master::SyncType mode = master->getMode();
	float dy = master->getDy();

	vstretch = 0;
	if (mode == Master::kSyncAbsolute) date += masterobj->getDate();
	if (align == Master::kSyncFrame) {
		location = date2FramePosition (masterobj, date);
	}
	else {
		if (master->getStretch() == Master::kStretchV) {
			vstretch = 2; //masterobj->getHeight();
//			cout << "getSyncPosition vstretch: " << vstretch << endl;
		}
		location = date2MasterPosition (master, obj, date);
	}

	location.fY += master->getDy();
	return location;
}

}
