/*

  INScore Project

  Copyright (C) 2015  Grame

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
#include <QDebug>


#include "MapTools.h"
#include "ITLError.h"
#include "VPianoRollView.h"
#include "VApplView.h"

#include "IGuidoPianoRoll.h"
#include "IGuidoPianoRollStream.h"
#include "QPRollGraphicsItem.h"
#include "QGuidoImporter.h"

#include "benchtools.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//----------------------------------------------------------------------
VPianoRollView::VPianoRollView(QGraphicsScene * scene, const IGuidoPianoRoll* h)
					: VGraphicsItemView( scene , new IQPRollGraphicsItem(h) )
{
}

//----------------------------------------------------------------------
void VPianoRollView::updateCommon( IGuidoPianoRoll * proll )
{
    proll->cleanupSync();
	item()->setRect (0, 0, relative2SceneWidth(proll->getWidth()), relative2SceneHeight(proll->getHeight()));
	item()->setPianoRoll(proll->getPianoRoll());

	QColor color (proll->getR(), proll->getG(), proll->getB(), proll->getA());
	const IColor& c = proll->getPenColor();
	QColor pencolor (c.getR(), c.getG(), c.getB(), c.getA());
	item()->setBrush(color);
	item()->setPen(QPen(pencolor));
}

//----------------------------------------------------------------------
void VPianoRollView::updateView( IGuidoPianoRollStream * proll  )
{
    updateCommon(proll);
	VGraphicsItemView::updateView (proll);
}

//----------------------------------------------------------------------
void VPianoRollView::updateView( IGuidoPianoRoll * proll  )
{
    updateCommon(proll);
	VGraphicsItemView::updateView (proll);
}

//----------------------------------------------------------------------
void VPianoRollView::updateMappingCommon (IGuidoPianoRoll* proll)
{
	float itemWidth  = relative2SceneWidth(proll->getWidth());
	float itemHeight = relative2SceneHeight(proll->getHeight());

	Time2GraphicMap map;
	item()->setRect (0, 0, relative2SceneWidth(proll->getWidth()), relative2SceneHeight(proll->getHeight()));

    GuidoErrCode err = GuidoPianoRollGetMap(proll->getPianoRoll(), itemWidth, itemHeight, map);
	if (err != guidoNoErr) {
		ITLErr << proll->getOSCAddress() << "can't get piano roll map:" <<  GuidoGetErrorString(err) << ITLEndl;
		VGraphicsItemView::buildDefaultMapping (proll);
		return;
	}
	if (map.empty()) {
		ITLErr << proll->getOSCAddress() << "unexpected empty piano roll map" << ITLEndl;
		VGraphicsItemView::buildDefaultMapping (proll);
		return;
	}
	SRelativeTime2GraphicMapping t2g_mapping = TMapping<rational,1,float,2>::create();
	for (Time2GraphicMap::const_iterator i = map.begin(); i != map.end(); i++) {
		const TimeSegment t = i->first;
		RelativeTimeSegment timesegm( rational(t.first.num, t.first.denom) , rational(t.second.num, t.second.denom) );
		const FloatRect& r = i->second;
//		GraphicSegment		graphsegm( (r.left * 2) / itemWidth - 1 , r.top/itemHeight -1 , r.right/itemWidth, r.bottom/itemHeight );
		// optimized version
		GraphicSegment		graphsegm( (r.left * 2) / itemWidth - 1, -1 , 1, 1 );
		t2g_mapping->add (timesegm , graphsegm );
	}
	proll->setMapping( "" , t2g_mapping);
	proll->localMapModified(true);
}

//----------------------------------------------------------------------
void VPianoRollView::updateLocalMapping (IGuidoPianoRollStream* proll)
{
	if (proll->getPianoRoll() == 0) return;
	updateMappingCommon (proll);
}

//----------------------------------------------------------------------
void VPianoRollView::updateLocalMapping (IGuidoPianoRoll* proll)
{
	if (proll->getPianoRoll() == 0) return;
	updateMappingCommon (proll);
//
//	float itemWidth  = relative2SceneWidth(proll->getWidth());
//	float itemHeight = relative2SceneHeight(proll->getHeight());
//
//	Time2GraphicMap map;
//	item()->setRect (0, 0, relative2SceneWidth(proll->getWidth()), relative2SceneHeight(proll->getHeight()));
//
//    GuidoErrCode err = GuidoPianoRollGetMap(proll->getPianoRoll(), itemWidth, itemHeight, map);
//	if (err != guidoNoErr) {
//		ITLErr << proll->getOSCAddress() << "can't get piano roll map:" <<  GuidoGetErrorString(err) << ITLEndl;
//		VGraphicsItemView::buildDefaultMapping (proll);
//		return;
//	}
//	if (map.empty()) {
//		ITLErr << proll->getOSCAddress() << "unexpected empty piano roll map" << ITLEndl;
//		VGraphicsItemView::buildDefaultMapping (proll);
//		return;
//	}
//	SRelativeTime2GraphicMapping t2g_mapping = TMapping<rational,1,float,2>::create();
//	for (Time2GraphicMap::const_iterator i = map.begin(); i != map.end(); i++) {
//		const TimeSegment t = i->first;
//		RelativeTimeSegment timesegm( rational(t.first.num, t.first.denom) , rational(t.second.num, t.second.denom) );
//		const FloatRect& r = i->second;
////		GraphicSegment		graphsegm( (r.left * 2) / itemWidth - 1 , r.top/itemHeight -1 , r.right/itemWidth, r.bottom/itemHeight );
//		// optimized version
//		GraphicSegment		graphsegm( (r.left * 2) / itemWidth - 1, -1 , 1, 1 );
//		t2g_mapping->add (timesegm , graphsegm );
//	}
//	proll->setMapping( "" , t2g_mapping);
//	proll->localMapModified(true);
}

} // end namespoace
