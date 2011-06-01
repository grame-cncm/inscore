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


#include "MapTools.h"
#include "TVirtualRelation.h"
#include "ITLError.h"
#include "VGuidoItemView.h"
#include "VApplView.h"

#include "IGuidoCode.h"
#include "QGuidoGraphicsItem.h"
#include "QGuidoImporter.h"

#include "GuidoMapCollector.h"

using namespace std;


namespace inscore
{

//----------------------------------------------------------------------
void GuidoMapCollector::Graph2TimeMap( const FloatRect& box, const TimeSegment& dates, const GuidoElementInfos& infos )
{
	// Guido mapping filtering: the Guido map doesn't fit the Interlude mapping constraints and should be reworked.
	if (fFilter && !(*fFilter)(infos))	return;		// element is filtered by the filter

	RelativeTimeSegment tseg = relativeTimeSegment(dates);
	if ( tseg.empty() )	return;						// empty time segments are filtered

	GraphicSegment gseg = graphicSegment(box, fCurrentPageOrigin);
	if ( gseg.empty() )	return;						// empty graphic segments are filtered

	for (Time2GraphicMap::const_iterator i = fOutMap->begin(); i != fOutMap->end(); i++) {
		if ( tseg.intersect( i->first ) )
			return;									// intersecting segments are filtered
		if ( gseg.intersect( i->second ) )
			return;
	}
	(*fOutMap)[tseg] = gseg;
}

//----------------------------------------------------------------------
void GuidoMapCollector::process (Time2GraphicMap* outmap)
{
	fOutMap = outmap;
	if (!fItem || !fOutMap) return;

	for ( int page = fItem->firstVisiblePage() ; page <= fItem->lastVisiblePage() ; page++ ) {
		fCurrentPageOrigin = fItem->pageManager()->pagePos(page);
		float w = fItem->pageManager()->pageSize(page).width();
		float h = fItem->pageManager()->pageSize(page).height();
		GuidoGetMap( fItem->getGRHandler(), page, w, h, fSelector, *this );
	}
}

//----------------------------------------------------------------------
void GuidoStaffCollector::process (Time2GraphicMap* outmap)
{
	GuidoMapCollector staffCollector(fItem, kGuidoStaff, fFilter);
	GuidoMapCollector eventsCollector(fItem, kGuidoEvent, fFilter);

	Time2GraphicMap staffMap, evtsMap;
	staffCollector.process (&staffMap);
	eventsCollector.process(&evtsMap);

	Time2GraphicMap::const_iterator eventsIter = evtsMap.begin();
	Time2GraphicMap::const_iterator staffIter = staffMap.begin();
	
	while (eventsIter != evtsMap.end()) {
		if (staffIter == staffMap.end()) {
			cerr << "unexpected staff segmentation end while collecting staff map" << endl;
			break;
		}

		Time2GraphicMap::const_iterator current = eventsIter;
		Time2GraphicMap::const_iterator next = ++eventsIter;
		RelativeTimeSegment evTime = current->first;
		while ( !staffIter->first.include(evTime) && (staffIter != staffMap.end())) {
			staffIter++;
		}
		if (staffIter == staffMap.end()) {
			cerr << "unexpected staff segmentation end while while looking for evTime " << evTime << endl;
			break;
		}

		Time2GraphicMap::const_iterator currstaff = staffIter;
		Time2GraphicMap::const_iterator nextstaff = currstaff;
		nextstaff++;

		float startx = current->second.xinterval().first();
		float endx = 0;
		if (next == evtsMap.end())								// last event ?
			endx = currstaff->second.xinterval().second();		// end zone is end staff

		else {
			RelativeTimeSegment nextTime = next->first;			// is the event on the same staff ?
			if (staffIter->first.include(nextTime) || 
				(nextstaff == staffMap.end()) ||
				( currstaff->second.yinterval().first() == nextstaff->second.yinterval().first())) {
				endx = next->second.xinterval().first();		// end zone is next event start
			}
			else 
				endx = currstaff->second.xinterval().second(); // end zone is end staff
		}
		(*outmap)[current->first] = GraphicSegment(FloatInterval( startx, endx ), currstaff->second.yinterval());
	}
}

//----------------------------------------------------------------------
// computes the system map using staves subdivisions
//----------------------------------------------------------------------
void GuidoSystemCollector::process (Time2GraphicMap* outmap)
{
//	Time2GraphicMap sysmap;
	processNoDiv (outmap);
	return; 
	
	int i = 0;
	while (true) {
		Time2GraphicMap staffmap;
		GuidoStaffCollector staffcollector (fItem, i++);
		staffcollector.process(&staffmap);
		if (!staffmap.size()) break;
	}
}

//----------------------------------------------------------------------
// computes the system map without subdivision
//----------------------------------------------------------------------
void GuidoSystemCollector::processNoDiv (Time2GraphicMap* outmap)
{
	int M,m,s;
	GuidoGetVersionNums (&M, &m, &s);
	if (GuidoCheckVersionNums (1, 4, 2) != guidoNoErr)
		ITLErr << "correct system map requires GUIDOEngine version 1.4.2 or greater - current version is "
				<< M << "." << m << "." << s << ITLEndl;

	GuidoMapCollector systemCollector(fItem, kGuidoSystem);
	GuidoMapCollector slicesCollector(fItem, kGuidoSystemSlice);

	Time2GraphicMap systemMap, slicesMap;
	systemCollector.process (&systemMap);
	slicesCollector.process(&slicesMap);

	Time2GraphicMap::const_iterator slicesIter = slicesMap.begin();
	Time2GraphicMap::const_iterator systemIter = systemMap.begin();
	
	while (systemIter != systemMap.end()) {
		if (slicesIter == slicesMap.end()) {
			cerr << "unexpected slices segmentation end while collecting system map" << endl;
			break;
		}

		GraphicSegment gs = systemIter->second;
		FloatInterval slicexi = slicesIter->second.xinterval();
		GraphicSegment adjusted (FloatInterval(slicexi.first(), gs.xinterval().second()), gs.yinterval());
		(*outmap)[systemIter->first] = adjusted;

		// skip the remaining slices until the next line
		float prevx = slicexi.first();
		float sysy = systemIter->second.yinterval().first();
		while (slicesIter != slicesMap.end()) {
			float x = slicesIter->second.xinterval().first();
			float y = slicesIter->second.yinterval().first();
			if ((x < prevx) || (y < sysy)) break;			
			prevx = x;
			slicesIter++;
		}
		systemIter++;
	}
}

} // end namespoace
