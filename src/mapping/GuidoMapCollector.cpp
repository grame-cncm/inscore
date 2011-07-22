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
void GuidoSystemCollector::process (Time2GraphicMap* outmap)
{
	Time2GraphicMap map, submap, merged;
	processNoDiv (&map);
	if (!fFlatMode) {
		int i = 1;
		while (true) {
			Time2GraphicMap staffmap;
			GuidoStaffCollector staffcollector (fItem, i++);
			staffcollector.process(&staffmap);
			if (!staffmap.size()) break;
			
			merge (map, staffmap, submap);
			map = submap;
		}
	}
	*outmap = map;
}

//----------------------------------------------------------------------
rational GuidoSystemCollector::add (const RelativeTimeSegment& ts, const FloatInterval& xi, const FloatInterval& yi, Time2GraphicMap& outmap)
{
	outmap[ts] = GraphicSegment(xi, yi);
	return ts.end();
}

//----------------------------------------------------------------------
// merge 2 maps using the smallest segmentation
// the principle of the merge is the following:
// the 2 maps are brwosed and 3 different cases are considered for each segments pair:
// let t1 and t2 be segments from map1 and map2
// 1) both segments t1 and t2 start at the same date:
//        t1 : |-------|
//        t2 : |---|......|
//    in this case we check the graphical position due to whole measure rests layout pb
//    when the position is (roughly) the same, inserts intersect t1 & t2 
//		   get next t2 and continue
//	  when the position is different, insert t1 and skip t2 until t2 > t1

// 2) the segment t1 starts before t2 and t2 starts in t1:
//        t1 : |-------|
//        t2 :   |---|......|
//    in this case, inserts intersect t1 & t2
//		   get next t2 and continue

// 3) the segment t2 starts after t1:
//        t1 : |-------|
//        t2 :           |---|
//    in this case, depending on the last date, inserts t1 
//			get next t1 and continue
//----------------------------------------------------------------------
void GuidoSystemCollector::merge (const Time2GraphicMap& map1, const Time2GraphicMap& map2, Time2GraphicMap& outmap)
{
	outmap.clear();
	Time2GraphicMap::const_iterator i1 = map1.begin();
	Time2GraphicMap::const_iterator i2 = map2.begin();
	
	rational rightdate;
	while (i1 != map1.end()) {				// browse each map1 relation
		RelativeTimeSegment t1 = i1->first;
		GraphicSegment s1 = i1->second;

		if (i2 != map2.end()) {	
			RelativeTimeSegment t2 = i2->first;
			GraphicSegment s2 = i2->second;
			
//bool trace = (t1.start() >= rational(19,4)) && (t1.start() <= rational(20,4));
//if (trace) {
//	cout << "at date: " << t1.start() << " - " << t2.start() << ": ";
//}
			if (t1.start() == t2.start()) {					// case 1: both segments at the same date
				float proximity = s2.xinterval().first() - s1.xinterval().first();
				if (proximity < 0) proximity = -proximity;
				if (proximity < 3.5) {						// check for graphic position
					// it (roughly) matches : inserts t1 and t2 intersection
					rightdate = add(t1 & t2, (s1 & s2).xinterval(), s1.yinterval(), outmap);
					i2++;									// and go to next t2
				}
				else {										// different positions: skip the rightmost segment
					if (s2.xinterval().first() > s1.xinterval().first()) {
						rightdate = add(t1, s1.xinterval(), s1.yinterval(), outmap);
						while (++i2 != map2.end()) {
							if (i2->first.start() >= t1.end()) break;
						}
						i1++;
					}
					else {
						rightdate = add(t2, s2.xinterval(), s1.yinterval(), outmap);
						i2++;
					}
				}
			}
			else if (t2.start() > t1.start()) {
				if (t2.start() < t1.end()) {				// case 2: t2 starts in t1
					RelativeTimeSegment inter = t1 & t2;
					FloatInterval xinter = s2.xinterval() & s1.xinterval();
					if (xinter.empty()) xinter = s2.xinterval();
					else xinter = FloatInterval(s2.xinterval().first(), xinter.second());

					if (inter.start() > rightdate) {		// check for missing t1 start segment
						RelativeTimeSegment beg = RelativeTimeSegment(t1.start(), inter.start());
						outmap[beg] = GraphicSegment(FloatInterval(s1.xinterval().first(), xinter.first()), s1.yinterval());
					}
					// inserts t1 and t2 intersection
					rightdate = add(inter, xinter, s1.yinterval(), outmap);
					i2++;									// and go to next t2
				}
				else {										// case 3: segment t2 starts after t1
					if (t1.start() == rightdate) 			// check for monotonicity
						rightdate = add(t1, s1.xinterval(), s1.yinterval(), outmap);
					i1++;									// and go to next t1
				}
			}			
			else if (t2.start() < t1.start()) {								// we should never go there
				ITLErr << "unexpected guido system map case"  << ITLEndl;	// but in case we do :-(
				if (t2.end() > t1.start()) i2++;							// try to continue 
				else i2++;
			}			
		}
		else {												// end of map2 (or map2 empty)
			if (t1.start() == rightdate) 					// check for monotonicity
				rightdate = add(t1, s1.xinterval(), s1.yinterval(), outmap);
			i1++;
		}
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
