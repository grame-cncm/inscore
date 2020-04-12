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
		float w = obj->getWidth();
		float h = obj->getHeight();
		if (w == 0) pos.fX = 0;
		if (h == 0) pos.fY = 0;
//cerr << "date2FramePosition " << obj->name() << " "  << date  << " -> pos: " << pos << " dims: " << w << " " << h << endl;
		if ((w < 0.000001) || (h < 0.00001)) w = h = 0;   // this is only for lines
		if (h && w) {
			if (w > h) pos.fX *= w / h;
			else if (w < h) pos.fY *= h / w;
		}
//cerr << "date2FramePosition out: " << pos << endl;
		return pos;
	}
	return TFloatPoint (kNoWhere, kNoWhere);
}

//--------------------------------------------------------------------------
static TFloatPoint date2MasterPosition (const SMaster& master, const IObject* slave, const libmapping::rational& date)
{
	TFloatPoint pos;

	std::string mapName = master->getMaster()->name() + ":" + master->getMasterMapName();
//	double width = relative2SceneWidth(o->getSyncWidth(mapName), item);
//	double height = relative2SceneHeight(o->getSyncHeight(mapName), item);

	pos = slave->getSyncPos(mapName);
cerr << "date2MasterPosition -> " << pos << endl;

	return pos;

//	item->setRect(QRectF(0,0,width,height));
//	item->setPos(x, y);
//	item->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
//	updateTransform (o, item);
//	QRectF bbrect = item->boundingRect();
//	double xo = bbrect.width() / 2;
//	double yo = bbrect.height() / 2;
//	item->setTransform(QTransform::fromTranslate(-xo, -yo), true);
}

//--------------------------------------------------------------------------
TFloatPoint	getSyncPosition (const IObject* obj, const SMaster& master)
{
	TFloatPoint location;

	libmapping::rational date = obj->getDate ();
	const SIObject& masterobj = master->getMaster();
	Master::VAlignType align = master->getAlignment();
//	Master::StretchType	stretch = master->getStretch(); // ignored
	Master::SyncType mode = master->getMode();
	float dy = master->getDy();

	if (mode == Master::kSyncAbsolute) date += masterobj->getDate();
	if (align == Master::kSyncFrame) {
		location = date2FramePosition (masterobj, date);
	}
	else {
		location = date2MasterPosition (master, obj, date);
	}

	location.fY += master->getDy();
	return location;
}

}
