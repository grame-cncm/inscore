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

#include "ifloat.h"
#include "ITLError.h"
#include "IModel.h"
#include "IShapeMap.h"
#include "TComposition.h"
#include "TRelation.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "IMappingUpdater.h"
#include "MapTools.h"
#include "maptypes.h"

#include "VGraphicsItemView.h"

using namespace std;
using namespace libmapping;

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

//---------------------------------------------------------------------------------------
float IMappingUpdater::getYPos (float height, const GraphicSegment& masterSeg, Master::VAlignType align) const
{
	float y = 0;
	float displacement = height / 2;
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
		RationalInterval pos(date, date);
		TAXBFunction<rational> f(t.interval(), pos);		// computes the linear interpolation function that goes from t to pos
		outSeg = *(v.begin());								// this is the graphic segment corresponding to date
		TSegmentVariety<float,2> v (outSeg, &f);			// create a variety of this segment using the previous linear interpolation function
		x = v.getx( f(date) );								// x is now the variety x pos et date relative pos regarding f		
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------
GraphicSegment IMappingUpdater::computeSegment(IObject* o, float h, float w, float x, float y)
{
    float x0 = x - (1 + o->getXOrigin()) * w/2;
    float x1 = x + (1 - o->getXOrigin()) * w/2;
    float y0 = y - (1 + o->getYOrigin()) * h/2;
    float y1 = y + (1 - o->getYOrigin()) * h/2;
    GraphicSegment seg(x0, y0, x1, y1);
    return seg;
}

//---------------------------------------------------------------------------------------
GraphicSegment IMappingUpdater::computeSegment(IObject* o)
{
    float h = o->getHeight() * o->getScale();
    float w = o->getWidth() * o->getScale();
    float x = o->getXPos();
    float y = o->getYPos();

    float x0 = x - (1 + o->getXOrigin()) * w/2;
    float x1 = x + (1 - o->getXOrigin()) * w/2;
    float y0 = y - (1 + o->getYOrigin()) * h/2;
    float y1 = y + (1 - o->getYOrigin()) * h/2;
    GraphicSegment seg(x0, y0, x1, y1);
    return seg;
}


//---------------------------------------------------------------------------------------
GraphicSegment IMappingUpdater::computeSegmentWithChildren(IObject* o, GraphicSegment seg)
{
    GraphicSegment gseg = seg;
    
    for(int i = 0; i < o->elements().size(); i++)
    {
        SIObject child = o->elements()[i];
        GraphicSegment cSeg = computeSegment(child); // in the current object's coordinates
        float ax = (cSeg.xinterval().first() + 1)/2;
        float bx = (cSeg.xinterval().second() + 1)/2;
        float ay = (cSeg.yinterval().first() + 1)/2;
        float by = (cSeg.yinterval().second() + 1)/2;
        cSeg = GraphicSegment(seg.xinterval().resize(ax, bx), seg.yinterval().resize(ay, by)); // relatively to the master's coordinates
        cSeg = computeSegmentWithChildren(child, cSeg);
        gseg = gseg | cSeg;
    }
    std::vector<SIObject> slaves = o->getParent()->getSlaves(o);
    for(int i = 0; i<slaves.size(); i++)
    {
        SIObject slave = slaves[i];
        float width = slave->getSyncWidth(o->name());
        float height = slave->getSyncHeight(o->name());
        float x = slave->getSyncPos(o->name()).x();
        float y = slave->getSyncPos(o->name()).y();
        GraphicSegment sSeg = GraphicSegment(x-width/2, y-height/2, x+width/2, y+height/2); // in object's coordinates
        gseg = gseg | sSeg;
    }
    return gseg;
}

//---------------------------------------------------------------------------------------
// Update when no horizontal stretch is required
// The strategy consists in aligning the date location of the slave with the corresponding
// location of the master;
// when the slave date is outside the master map, then the master date is taken and the 
// system looks for the corresponding location in the slave map.
//---------------------------------------------------------------------------------------
GraphicSegment IMappingUpdater::updateNoStretch (IObject* slave, SMaster m, bool isVStretch)
{
	GraphicSegment masterSeg;

	const SIObject& master = m->getMaster();
	const string& mapName = m->getMasterMapName();
	Master::VAlignType align = m->getAlignment();

	// get the master graphic and time mapping
	rational mdate = master->getDate();
	rational date = slave->getDate();
	const SRelativeTime2GraphicMapping& map = (m->getMode()==Master::kSyncRelative) ? timeshift(master->getMapping( mapName ), mdate)
																					: master->getMapping( mapName );
	const SRelativeTime2GraphicMapping& slavemap = timeshift(slave->getMapping( "" ), date);
	if ( !map ) {
		ITLErr << slave->getOSCAddress() << ": mapping is missing." << ITLEndl;
		return masterSeg;
	}

	slave->UseGraphic2GraphicMapping (false, master->name());						// don't use the object graphic segmentation and mapping
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
			x *= slave->getScale();								// update x according to the slave scale
			found = true;
		}
	}
    
	if (found) {
        float w = slave->getWidth()*slave->getScale();
        float h = isVStretch ? h = masterSeg.yinterval().size() : slave->getHeight()*slave->getScale();
        float y = getYPos (h, masterSeg, align) + m->getDy();
        
        GraphicSegment destSeg = computeSegment(slave, h, w, x, y); // this is the destination segment of the slave alone (in master's coordinate)
        
        GraphicSegment extendedSeg = computeSegmentWithChildren(slave, slaveSeg); //this is the source segment of the slave and its children (in slave's coordinate)
        TSegmentAXBVariety<float, 2> variety(extendedSeg, slaveSeg); // we define the segment slave as a variety of the segment slave+children
        const TAXBFunction<float> * xFunction = variety.xfunction(); // ... so that we can know the functions that bind them
        const TAXBFunction<float> * yFunction = variety.yfunction();
        
        TSegmentInvertedVariety<float, 2> invertedVariety (destSeg, xFunction, yFunction);
        GraphicSegment extendedDestSeg = invertedVariety.get(); // with the inverted variety we apply the inverted function to go from our destination segment (slave alone)
                                                                // to the destination segment of the slave and its children (in master's coordinate)
        x = invertedVariety.getx(0.5); // the center
        y = invertedVariety.gety(0.5);
        
		slave->setSyncPos(m->getMaster()->name(), QPointF(x,y));
        slave->setSyncHeight(m->getMaster()->name(), extendedDestSeg.yinterval().size());
        slave->setSyncWidth(m->getMaster()->name(), extendedDestSeg.xinterval().size());
        
		return masterSeg;
	}
    slave->setSyncPos(m->getMaster()->name(), QPointF(kUnknownLocation,kUnknownLocation)); // puts the object away when no mapping available or missing resources
	return masterSeg;
}


//--------------------------------------------------------------------------
bool IMappingUpdater::updateNOHStretch (IObject* o, SMaster m)
{ 
	if (m &&  m->getMaster()) {
		switch (m->getStretch()) {
			case Master::kNoStretch:
				updateNoStretch (o, m);
				break;
			case Master::kStretchV:
				updateNoStretch (o, m, true);
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
    const SIObject parent = object->getParent();
	const std::vector<SMaster> masters = parent ? parent->getMasters(object) : object->getScene()->getMasters(object);
    
	if (masters.empty()) return;
	
    for(int i = 0; i<masters.size(); i++)
    {
        const IObject* mobj = masters[i]->getMaster();
        if (object->localMapModified() || object->getState() || object->dateModified()
            || mobj->localMapModified() || masters[i]->modified() || mobj->dateModified()) {
            if (!updateNOHStretch ( object, masters[i]))
                hstretchUpdate (object, masters[i]);
        }
    }
}

//--------------------------------------------------------------------------
// segments set reduction
//--------------------------------------------------------------------------
static set<GraphicSegment> merge (const set<GraphicSegment>& s1, const set<GraphicSegment>& s2)
{
	set<GraphicSegment> outset;
	if (s1.size() != s2.size()) return outset;

	set<GraphicSegment>::const_iterator i1 = s1.begin();
	set<GraphicSegment>::const_iterator i2 = s2.begin();

	while (i1 != s1.end()) {
		GraphicSegment  u = i1->xmerge(*i2, 0.00001f);
		if (u.empty()) {
			outset.clear();
			break;
		}
		outset.insert (u);
		i1++; i2++;
	}
	return outset;
}

//--------------------------------------------------------------------------------
// group the adjacent segments of a mapping when possible
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
		else {							// here we have the previous segments
			RelativeTimeSegment u1 = timeseg.merge(i->first);		// merge the time segments
			set<GraphicSegment> u2 = merge (graphsegs, i->second);	// and merge the corresponding graphic segments
			if (u1.empty() || !u2.size()) {							// it fails: empty merged time segment of graphic segments set
				outmap->add (timeseg, graphsegs);					// add the relation as is
				timeseg = i->first;									// and set the current time and graphic segment
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
// gives the part of a mapping that corresponds to a time segment
//--------------------------------------------------------------------------------
static SRelativeTime2GraphicMapping getsubmap( const SRelativeTime2GraphicMapping& map, const RelativeTimeSegment& seg)
{
	// first put the time segment into a segmentation
	SRelativeTimeSegmentation rts = RelativeTimeSegmentation::create(seg);
	rts->add (seg);
	// and next we use a refined relation to get the corresponding map part
	TRefinedRelation<rational,1, float,2> refinedt2g (map->direct(), rts);

	// create a mapping to store the result
	SRelativeTime2GraphicMapping outmap = RelativeTime2GraphicMapping::create();
	outmap->add(refinedt2g);			// and add the refined relation
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
// group segments of a mapping according to a given 'frame' mapping
//--------------------------------------------------------------------------------
static SRelativeTime2GraphicMapping groupmap( const SRelativeTime2GraphicMapping& map, const SRelativeTime2GraphicMapping& framemap)
{
	// first create a time to graphic map that will hold the result
	SRelativeTime2GraphicMapping outmap = RelativeTime2GraphicMapping::create();
	// next we get the time to graphic relation of the frame map
	const RelativeTime2GraphicRelation& rel = framemap->direct();
	// and for each time segment of the frame map
	for (RelativeTime2GraphicRelation::const_iterator i = rel.begin(); i != rel.end(); i++) {
		// reduce the corresponding map segments and add the result to the 
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
	typedef TRelation<rational,1,float,2>::const_iterator const_iterator;
	
	for (const_iterator i = map->direct().begin(); i != map->direct().end(); i++) {
			TSegment<rational,1> shifted (i->first.interval() + date);
			smap->add ( shifted, i->second);
	}
	return smap;
}

//---------------------------------------------------------------------------------------
// check adjacent segments and make sure the end and begin of successive
// segments match at an epsilon value approximate
//---------------------------------------------------------------------------------------
SGraphic2GraphicMapping IMappingUpdater::relink (const Graphic2GraphicRelation& rel, float epsilon) const
{
	SGraphic2GraphicMapping g2gm = TMapping<float,2,float,2>::create();
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
				cerr << "=== WARNING === IMappingUpdater::relink: gap makes wrong interval" << gap << endl;
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

	SGraphic2GraphicMapping g2gr = TMapping<float,2,float,2>::create();
	const TRelation<float,2,float,2>& rmap = map->direct();

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
// computes the graphic to graphic mapping of an object according to its master
// and to the synchronization mode
void IMappingUpdater::hstretchUpdate (IObject* o, const Master* master)
{
	// first we get the slave map time shifted to the object current date
	SRelativeTime2GraphicMapping slavemap = timeshift (o->getMapping(master->getSlaveMapName()), o->getDate());
	// first we get the slave map time shifted to the object current date
	SRelativeTime2GraphicMapping mastermap = master->getMaster()->getMapping( master->getMasterMapName() );

	if (master->getStretch() & Master::kStretchHH)		// check if we need to avoid slave distortion
		mastermap = groupmap(mastermap, slavemap);		// then simplify the mapping

	// check the everything is ok up to now
	if (!slavemap) {
		ITLErr << o->getOSCAddress() << ": time to graphic mapping is missing (slave map)." << ITLEndl;
		return;
	}
	else if (!mastermap) {
		ITLErr << master->getMaster()->getOSCAddress() << ": time to graphic mapping is missing (master map)." << ITLEndl;
		return;
	}
	
	// the target is to compute the graphic to graphic mapping; we use a refined composition
	typedef TRefinedComposition <float,2, rational,1, float,2> G2GComposition;
	SGraphic2GraphicMapping g2gr = G2GComposition::create( slavemap->direct(), mastermap->direct() );

	if (!g2gr) {
		ITLErr << "IMappingUpdater: memory allocation failed." << ITLEndl;
		return;
	}

	g2gr = verticalAdjust( g2gr, o, master);	// graphic segments adjustment according to vertical pos and stretch
	g2gr = relink (g2gr->direct(), 0.0001f);	// check adjacent segments and make sure the end and begin match
	TMapable* m = o;
	m->setSlave2MasterMapping (master->getMaster()->name(), g2gr);			// create the slave graphic to master graphic composition
	m->UseGraphic2GraphicMapping (true, master->getMaster()->name());
}

} // end namespoace
