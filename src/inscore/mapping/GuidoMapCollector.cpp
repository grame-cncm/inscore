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

#include "GuidoMapCollector.h"
#include "ITLError.h"
#include "ScoreLayoutInfos.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//----------------------------------------------------------------------
static inline rational guidodate2rational (const GuidoDate& d)		{ return rational (d.num, d.denom); }

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
//	(*fOutMap)[tseg] = gseg;
	fOutMap->push_back(make_pair(tseg, gseg));
}

void GuidoMapCollector::CopyMap( const ::Time2GraphicMap& map )
{
	for (::Time2GraphicMap::const_iterator i=map.begin(); i!=map.end(); i++) {
		RelativeTimeSegment ts (guidodate2rational(i->first.first), guidodate2rational(i->first.second));
		GraphicSegment gs ( fCurrentPageOrigin.x()+i->second.left, fCurrentPageOrigin.y()+i->second.top, 
							fCurrentPageOrigin.x()+i->second.right, fCurrentPageOrigin.y()+i->second.bottom);
		fOutMap->push_back(make_pair(ts, gs));
	}
}

//----------------------------------------------------------------------
void GuidoMapCollector::process (const ScoreLayoutInfos& score, Time2GraphicMap* outmap)
{
	fOutMap = outmap;
	if (!fOutMap) return;

	for ( int page = score.firstPage() ; page <= score.lastPage() ; page++ ) {
		fCurrentPageOrigin = score.position(page);
		GuidoGetMap( score.handler(), page, score.pageWidth(page), score.pageHeight(page), fSelector, *this );
	}
}

//----------------------------------------------------------------------
void GuidoVoiceCollector::process (const ScoreLayoutInfos& score, Time2GraphicMap* outmap)
{
	fOutMap = outmap;
	if (!fOutMap) return;

	for ( int page = score.firstPage() ; page <= score.lastPage() ; page++ ) {
		fCurrentPageOrigin = score.position(page);
		::Time2GraphicMap map;
		GuidoErrCode err = GuidoGetVoiceMap( score.handler(), page, score.pageWidth(page), score.pageHeight(page), fVoiceNum, map );
		if (err == guidoNoErr) {
			CopyMap (map);
		}
		else {
			ITLErr << "error getting voice" << fVoiceNum << "map on page" << page << ": " << GuidoGetErrorString(err) << ITLEndl;
			break;
		}
	}
}

//----------------------------------------------------------------------
void GuidoStaffCollector::process (const ScoreLayoutInfos& score, Time2GraphicMap* outmap)
{
	if (!outmap) return;

	for ( int page = score.firstPage() ; page <= score.lastPage() ; page++ ) {
		fCurrentPageOrigin = score.position(page);
		::Time2GraphicMap map;
		GuidoErrCode err = GuidoGetStaffMap( score.handler(), page, score.pageWidth(page), score.pageHeight(page), fStaffNum, map );
		if (err == guidoNoErr) {
			for (::Time2GraphicMap::const_iterator i=map.begin(); i!=map.end(); i++) {
				RelativeTimeSegment ts (guidodate2rational(i->first.first), guidodate2rational(i->first.second));
				GraphicSegment gs ( fCurrentPageOrigin.x()+i->second.left, fCurrentPageOrigin.y()+i->second.top, 
									fCurrentPageOrigin.x()+i->second.right, fCurrentPageOrigin.y()+i->second.bottom);
				outmap->push_back(make_pair(ts, gs));
			}
		}
		else {
			ITLErr << "error getting staff" << fStaffNum << "map on page" << page << ":" << GuidoGetErrorString(err) << ITLEndl;
			break;
		}
	}
}



//----------------------------------------------------------------------
void GuidoSystemCollector::process (const ScoreLayoutInfos& score, Time2GraphicMap* outmap)
{
	if (!outmap) return;

	if (fFlatMode) processNoDiv (score, outmap);
	else for ( int page = score.firstPage() ; page <= score.lastPage() ; page++ ) {
		fCurrentPageOrigin = score.position(page);
		::Time2GraphicMap map;
		GuidoErrCode err = GuidoGetSystemMap( score.handler(), page, score.pageWidth(page), score.pageHeight(page), map );
		if (err == guidoNoErr) {
			for (::Time2GraphicMap::const_iterator i=map.begin(); i!=map.end(); i++) {
				RelativeTimeSegment ts (guidodate2rational(i->first.first), guidodate2rational(i->first.second));
				GraphicSegment gs ( fCurrentPageOrigin.x()+i->second.left, fCurrentPageOrigin.y()+i->second.top, 
									fCurrentPageOrigin.x()+i->second.right, fCurrentPageOrigin.y()+i->second.bottom);
				outmap->push_back(make_pair(ts, gs));
			}
		}
		else {
			ITLErr << "error getting system map on page" << page << ":" << GuidoGetErrorString(err) << ITLEndl;
			break;
		}
	}
}

//----------------------------------------------------------------------
// computes the system map without subdivision
//----------------------------------------------------------------------
void GuidoSystemCollector::processNoDiv (const ScoreLayoutInfos& score, Time2GraphicMap* outmap)
{
	int M,m,s;
	GuidoGetVersionNums (&M, &m, &s);
	if (GuidoCheckVersionNums (1, 4, 2) != guidoNoErr)
		ITLErr << "correct system map requires GUIDOEngine version 1.4.2 or greater - current version is" << GuidoGetVersionStr() << ITLEndl;

	GuidoMapCollector systemCollector (kGuidoSystem);
	GuidoMapCollector slicesCollector (kGuidoSystemSlice);

	Time2GraphicMap systemMap, slicesMap;
	systemCollector.process (score, &systemMap);
	slicesCollector.process (score, &slicesMap);

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
//		(*outmap)[systemIter->first] = adjusted;
		outmap->push_back(make_pair(systemIter->first, adjusted));

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
