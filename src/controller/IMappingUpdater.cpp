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
#include <vector>

#include "float.h"
#include "ITLError.h"
#include "IModel.h"
#include "IShapeMap.h"
#include "TComposition.h"
#include "TRelation.h"
#include "TVirtualRelation.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "IMappingUpdater.h"
#include "MapTools.h"
#include "maptypes.h"

#include "VGraphicsItemView.h"

using namespace std;

namespace inscore
{

#define kUnknownLocation 99999.f

template <typename T>	std::ostream& operator << (std::ostream& out, const std::set<T>& s)
{
	typedef typename std::set<T>::const_iterator const_iterator;
	for (const_iterator i = s.begin(); i != s.end(); i++) 
		out << *i << " ";
	return out; 
}

//--------------------------------------------------------------------------
void IMappingUpdater::VStretch (IObject* o, const GraphicSegment& gseg)	
{ 
	float h = gseg.yinterval().size();		// get the graphic segment height
//	o->graphicView()->updateObjectSize (o);
	float oh = o->getHeight();
//	if (oh) o->setSyncScale ( h / oh);		// and scale the slave object accordingly
	if (oh) o->setScale ( h / oh);			// and scale the slave object accordingly
}

//---------------------------------------------------------------------------------------
float IMappingUpdater::getYPos (IObject* o, const GraphicSegment& masterSeg, Master::VAlignType align) const
{
	float y = 0;
	float displacement = o->getHeight() * o->getScale() / 2;
	switch (align) {						//  computes the slave y coordinate according to the alignment mode
		case Master::kSyncTop:
			y = masterSeg.yinterval().first() - displacement;
			break;
		case Master::kSyncBottom:
			y = masterSeg.yinterval().second() + displacement;
			break;
		case Master::kSyncOver:
		default:
			y = masterSeg.yinterval().center();
			break;
	}
	return y;
}

//---------------------------------------------------------------------------------------
bool IMappingUpdater::date2point (const rational& date, const SRelativeTime2GraphicMapping& map, GraphicSegment& outSeg, float& x) const
{
	RelativeTimeSegment t = MapTools::find (date, map->direct());		// get the time segment containing the date
	set<GraphicSegment> v = map->direct().get(t);						// get the corresponding graphic segments

	if (v.size())  {
		outSeg = *(v.begin());
		x = outSeg.xinterval().first();						// get the graphic segment first x coordinate
		float ratio = MapTools::relativepos(date, t.interval());		// get the relative position of date within the time segment
		x += outSeg.xinterval().size() * ratio;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------
// Update when no horizontal stretch is required
// The strategy consists in aligning the date location of the slave with the corresponding
// location of the master;
// when the slave date is outside the master map, then the master date is taken and the 
// system looks for the corresponding location in the slave map.
//---------------------------------------------------------------------------------------
GraphicSegment IMappingUpdater::updateNoStretch (IObject* slave, const Master* m)	
{ 
	GraphicSegment masterSeg;

	const SIObject& master = m->getMaster();
	const string& mapName = m->getMasterMapName();
	Master::VAlignType align = m->getAlignment();

	// get the master graphic and time mapping
	rational mdate = master->getDate();
	rational date = slave->getDate();
	const SRelativeTime2GraphicMapping& map = timeshift(master->getMapping( mapName ), mdate);
	const SRelativeTime2GraphicMapping& slavemap = timeshift(slave->getMapping( "" ), date);
	if ( !map ) {
		ITLErr << slave->getOSCAddress() << ": mapping is missing." << ITLEndl;
		return masterSeg;
	}

	slave->UseGraphic2GraphicMapping (false);						// don't use the object graphic segmentation and mapping
	float x, xs; bool found = false;
	GraphicSegment slaveSeg;

	if (date2point (date, map, masterSeg, x)) {						// do the slave date exists in the master map ?
		if (date2point (date, slavemap, slaveSeg, xs))				// yes but retrieve the corresponding location in the slave map too
			x -= slave->getWidth() * (1+xs) / 2;					// converts the corresponding amount in displacement n the master space
		found = true;
	}
	else if (date2point (mdate, slavemap, slaveSeg, xs)) {			// look for the master date in the slave map
		if (date2point (mdate, map, masterSeg, x)) {				// this is mainly to retrieve the master segment
			x -= slave->getWidth() * (1+xs) / 2;
			found = true;
		}
	}
	if (found) {
		slave->setXPos( x);										//  set the slave x coordinate
		float y = getYPos (slave, masterSeg, align);
		slave->setYPos( y + m->getDy());						// set the slave y coordinate 
		return masterSeg;
	}
	slave->setXPos( kUnknownLocation );			// puts the object away when no mapping available or missing resources
	slave->setYPos( kUnknownLocation );	
	return masterSeg;
}

//--------------------------------------------------------------------------
void IMappingUpdater::updateVStretch (IObject* o, const Master* m)	
{ 
	GraphicSegment gseg = updateNoStretch (o, m);
	VStretch (o, gseg);
}

//--------------------------------------------------------------------------
bool IMappingUpdater::updateNOHStretch (IObject* o, const Master* m)	
{ 
	if (m &&  m->getMaster()) {
		switch (m->getStretch()) {
			case Master::kNoStretch:
				updateNoStretch (o, m);
				break;
			case Master::kStretchV:
				updateVStretch (o, m);
				break;
			default:
				return false;
		}
	}
	return true;
}

//--------------------------------------------------------------------------
void IMappingUpdater::updateIObject (IObject* object)	
{
	const SIScene scene = object->getScene();
	const Master* master = scene ? scene->getMaster(object) : 0;
	if (!master) return;

	if (object->localMapModified() || object->dateModified() || (master->getMaster()->localMapModified() || master->modified())) {
		if (!updateNOHStretch ( object, master))
			hstretchUpdate (object, master);
	}
}

//--------------------------------------------------------------------------
// mapping reduction
//--------------------------------------------------------------------------
static set<GraphicSegment> unite (const set<GraphicSegment>& s1, const set<GraphicSegment>& s2)
{
	set<GraphicSegment> outset;
	if (s1.size() != s2.size()) return outset;

	set<GraphicSegment>::const_iterator i1 = s1.begin();
	set<GraphicSegment>::const_iterator i2 = s2.begin();
	while (i1 != s1.end()) {
		GraphicSegment  inter = *i1 & *i2;
		GraphicSegment  u = i1->unite(*i2, 0.00001f);
		if (u.empty() || inter.size()) {
			outset.clear();
			break;
		}
		outset.insert (u);
		i1++; i2++;
	}
	return outset;
}

//--------------------------------------------------------------------------------
static SRelativeTime2GraphicMapping reduce( const SRelativeTime2GraphicMapping& map)
{
	SRelativeTime2GraphicMapping outmap = RelativeTime2GraphicMapping::create();
	RelativeTimeSegment timeseg; 
	set<GraphicSegment> graphsegs;
	const RelativeTime2GraphicRelation& rel = map->direct();
	for (RelativeTime2GraphicRelation::const_iterator i = rel.begin(); i != rel.end(); i++) {
		if (!graphsegs.size()) {		// first time (just entering the loop)
			timeseg = i->first;
			graphsegs = i->second;
		}
		else {
			RelativeTimeSegment u1 = timeseg.unite(i->first);
			set<GraphicSegment> u2 = unite (graphsegs, i->second);
			if (u1.empty() || !u2.size()) {
				outmap->add (timeseg, graphsegs);
				timeseg = i->first;
				graphsegs = i->second;
			}
			else {
				timeseg = u1;
				graphsegs = u2;
			}
		}
	}
	if (graphsegs.size())
		outmap->add (timeseg, graphsegs);
	return outmap;
}

//--------------------------------------------------------------------------------
static SRelativeTime2GraphicMapping getsubmap( const SRelativeTime2GraphicMapping& map, const RelativeTimeSegment& seg)
{
	SRelativeTime2GraphicMapping outmap = RelativeTime2GraphicMapping::create();
	const RelativeTime2GraphicRelation& rel = map->direct();
	TVirtualRelation<RelativeTimeSegment,GraphicSegment> vrel( rel );
	for (RelativeTime2GraphicRelation::const_iterator i = rel.begin(); i != rel.end(); i++) {
		RelativeTimeSegment inter = i->first & seg;
		if (inter == i->first)	// current segment is included
			outmap->add (i->first, i->second);
		else if (inter.size())
			outmap->add (inter, vrel.get(inter));
	}
	return outmap;
}

//--------------------------------------------------------------------------------
static void addmap( const SRelativeTime2GraphicMapping& map, SRelativeTime2GraphicMapping& dstmap)
{
	const RelativeTime2GraphicRelation& rel = map->direct();
	for (RelativeTime2GraphicRelation::const_iterator i = rel.begin(); i != rel.end(); i++) {
		dstmap->add (i->first, i->second);
	}
}

//--------------------------------------------------------------------------------
static SRelativeTime2GraphicMapping groupmap( const SRelativeTime2GraphicMapping& map, const SRelativeTime2GraphicMapping& framemap)
{
	SRelativeTime2GraphicMapping outmap = RelativeTime2GraphicMapping::create();
	const RelativeTime2GraphicRelation& rel = framemap->direct();
	for (RelativeTime2GraphicRelation::const_iterator i = rel.begin(); i != rel.end(); i++) {
		addmap (reduce(getsubmap(map, i->first)), outmap);
	}
	return outmap;
}

//---------------------------------------------------------------------------------------
// time shift a time to graphic mapping
//---------------------------------------------------------------------------------------
SRelativeTime2GraphicMapping IMappingUpdater::timeshift (const SRelativeTime2GraphicMapping& map, const rational& date) const
{
	if (!map ) return 0;
	SRelativeTime2GraphicMapping smap =  RelativeTime2GraphicMapping::create();
	typedef TRelation<RelativeTimeSegment,GraphicSegment>::const_iterator const_iterator;
	
	for (const_iterator i = map->direct().begin(); i != map->direct().end(); i++) {
			TSegment<rational,1> shifted (i->first.interval() + date);
			smap->add ( shifted, i->second);
	}
	return smap;
}

//---------------------------------------------------------------------------------------
// compute the intersection of two time segmentations
//---------------------------------------------------------------------------------------
void IMappingUpdater::intersect (const RelativeTime2GraphicRelation& r1, const RelativeTime2GraphicRelation& r2, std::set<RelativeTimeSegment>& outlist) const
{
	for (RelativeTime2GraphicRelation::const_iterator i = r1.begin(); i != r1.end(); i++) {
		for (RelativeTime2GraphicRelation::const_iterator j = r2.begin(); j != r2.end(); j++) {
			RelativeTimeSegment inter = i->first & j->first;
			if (inter.size() || (inter == i->first) || (inter == j->first))
				outlist.insert(inter);
		}
	}
}

//---------------------------------------------------------------------------------------
// check adjacent segments and make sure the end and begin of successive
// segments match at an epsilon value approximate
//---------------------------------------------------------------------------------------
SGraphic2GraphicMapping IMappingUpdater::relink (const Graphic2GraphicRelation& rel, float epsilon) const
{
	SGraphic2GraphicMapping g2gm = TMapping<GraphicSegment,GraphicSegment>::create();
	Graphic2GraphicRelation::const_iterator previous, i = rel.begin();
	if (i == rel.end()) return g2gm;

	previous = i;
	for (++i; i != rel.end(); i++) {
		const TInterval<float>& previoux = previous->first.xinterval();
		const TInterval<float>& currentx = i->first.xinterval();
		const TInterval<float>& currenty = i->first.yinterval();

		GraphicSegment current = i->first;
		
		float gap = currentx.first() - previoux.second();
		if (gap < -epsilon)				// nothing to do, the gap is outside epsilon approximate
			g2gm->add (previous->first, previous->second);
		else if (gap < 0) {				// negative gap - warning! could lead to incorrect segment
			if (previoux.first() > currentx.first())
				cout << "=== WARNING === IMappingUpdater::relink: gap makes wrong interval" << gap << endl; 
			TInterval<float> xi (previoux.first(), currentx.first());
			g2gm->add (GraphicSegment(xi, currenty), previous->second); 
		}
		else if (gap == 0)				// nothing to do, no gap
			g2gm->add (previous->first, previous->second);
		else if (gap < epsilon)	{		// positive gap: corrects the previous segment
			TInterval<float> xi (previoux.first(), currentx.first());
			g2gm->add (GraphicSegment(xi, currenty), previous->second);
		}
		else	g2gm->add (previous->first, previous->second);	// outside epsilon approximation
		previous = i;			
	}
	g2gm->add (previous->first, previous->second);
	return g2gm;
}

//---------------------------------------------------------------------------------------
// adjust the segments vertical dimension and position
//---------------------------------------------------------------------------------------
static void adjustset (const set<GraphicSegment>& seg, set<GraphicSegment>& outsegs, float size, Master::VAlignType valign, float dy)
{
	for (set<GraphicSegment>::const_iterator i = seg.begin(); i != seg.end(); i++) {
		float ssize = size ? size : i->yinterval().size();
		float start = 0;
		switch (valign) {
			case Master::kSyncTop:		start = i->yinterval().first() - ssize;
				break;
			case Master::kSyncBottom:	start = i->yinterval().second();
				break;
			default:					start = i->yinterval().center() - (ssize / 2);
				break;
		}
		TInterval<float> y(start+dy, start + ssize + dy);
		outsegs.insert (GraphicSegment(i->xinterval(), y));
	}
}

SGraphic2GraphicMapping IMappingUpdater::verticalAdjust (const SGraphic2GraphicMapping& map, IObject* o, const Master* master) const
{
	Master::VAlignType	valign = master->getAlignment();
	Master::StretchType	stretch = master->getStretch();
	if ( (valign == Master::kSyncOver) && (stretch & Master::kStretchV) && TFloat::eq(master->getDy(),0))
		return map;			// nothing to do

	SGraphic2GraphicMapping g2gr = TMapping<GraphicSegment,GraphicSegment>::create();
	const TRelation<GraphicSegment,GraphicSegment>& rmap = map->direct();

	bool vstretch = stretch & Master::kStretchV;
	for (Graphic2GraphicRelation::const_iterator i =rmap.begin(); i !=rmap.end(); i++) {
		float size = vstretch ? 0.f : o->getHeight() * o->getScale() * i->first.yinterval().size() / 2;
		set<GraphicSegment> hsized;
		adjustset (i->second, hsized, size, valign, master->getDy());
		g2gr->add (i->first, hsized);
	}
	return g2gr;
}

//--------------------------------------------------------------------------
void IMappingUpdater::hstretchUpdate (IObject* o, const Master* master)
{
	SRelativeTime2GraphicMapping slavemap = timeshift (o->getMapping(master->getSlaveMapName()), o->getDate());
	SRelativeTime2GraphicMapping mastermap = master->getMaster()->getMapping( master->getMasterMapName() );
	if (master->getStretch() & Master::kStretchHH)
		mastermap = groupmap(mastermap, slavemap);
	SGraphic2GraphicMapping g2gr = TMapping<GraphicSegment,GraphicSegment>::create();

	if (!slavemap) {
		ITLErr << o->getOSCAddress() << ": time to graphic mapping is missing (slave map)." << ITLEndl;
		return;
	}
	else if (!mastermap) {
		ITLErr << master->getMaster()->getOSCAddress() << ": time to graphic mapping is missing (master map)." << ITLEndl;
		return;
	}
	else if (!g2gr) {
		ITLErr << "IMappingUpdater: memory allocation failed." << ITLEndl;
		return;
	}

	const TRelation<RelativeTimeSegment, GraphicSegment>& slavet2gr = slavemap->direct();
	const TRelation<RelativeTimeSegment, GraphicSegment>& mastert2gr = mastermap->direct();
	
	set<RelativeTimeSegment> timeIntersection;
	intersect(slavet2gr, mastert2gr, timeIntersection);

	TVirtualRelation<RelativeTimeSegment,GraphicSegment> vrs( slavet2gr);
	TVirtualRelation<RelativeTimeSegment,GraphicSegment> vrm( mastert2gr);
	// iterate thru the time segments intersection
	for (set<RelativeTimeSegment>::const_iterator i = timeIntersection.begin(); i != timeIntersection.end(); i++) {
		set<GraphicSegment> gslave = vrs.get(*i);
		set<GraphicSegment> gmaster = vrm.get(*i);
		for (set<GraphicSegment>::const_iterator j = gslave.begin(); j != gslave.end(); j++) {
			g2gr->add(*j, gmaster);
		}
	}

	g2gr = verticalAdjust( g2gr, o, master);	// graphic segments adjustment according to vertical pos and stretch
	g2gr = relink (g2gr->direct(), 0.0001f);	// check adjacent segments and make sure the end and begin match
	TMapable* m = o;
	m->setSlave2MasterMapping (g2gr);			// create the slave graphic to master graphic composition
	m->UseGraphic2GraphicMapping (true);	
}

} // end namespoace
