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

static const float kNoWhere = -9999999.f;

//--------------------------------------------------------------------------
static TFloatPoint	date2FramePosition (const IObject* obj, const libmapping::rational& date)
{
	TFloatPoint pos;
	if (obj->date2FramePoint(date, pos)) {
		pos.fX = (pos.fX * 2) - 1;
		pos.fY = (pos.fY * 2) - 1;
		return pos;
	}
	return TFloatPoint (kNoWhere, kNoWhere);
}

//--------------------------------------------------------------------------
TFloatPoint	getSyncPosition (const IObject* obj, const SMaster& master)
{
	TFloatPoint location;
	libmapping::rational date = obj->getDate ();
	
	const SIObject& masterobj = master->getMaster();
	Master::VAlignType align = master->getAlignment();
	Master::StretchType	stretch = master->getStretch();
	Master::SyncType mode = master->getMode();
	float dy = master->getDy();

	if (mode == Master::kSyncAbsolute) date += masterobj->getDate();
	if (align == Master::kSyncFrame) {
		location = date2FramePosition (masterobj, date);
	}
	return location;
}

}
