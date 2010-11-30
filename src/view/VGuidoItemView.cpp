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

#include "GUIDOScoreMap.h"

using namespace std;


const QString kVoiceMap	 ("voice");
const QString kStaffMap	 ("staff");
const QString kSystemMap ("system");
const QString kSliceMap	 ("systemSlice");
const QString kPageMap	 ("page");
const QString kMeasureMap("measure");


namespace inscore
{

float VGuidoItemView::fCm2GuidoUnit = 0;


//----------------------------------------------------------------------
/*!
	\brief a class to collect guido graphic maps
*/
class GuidoMapCollector: public MapCollector
{
	public :
		typedef std::map<RelativeTimeSegment, GraphicSegment> Time2GraphicMap;
		struct Filter { virtual ~Filter() {} virtual bool operator() (const GuidoElementInfos& infos) const { return true; } } ;

	protected:
		const QGuidoGraphicsItem *	fItem;
		GuidoeElementSelector	fSelector;
		const Filter*			fFilter;
		Time2GraphicMap*		fOutMap;		
		QPointF					fCurrentPageOrigin;

	public :
				 GuidoMapCollector(const QGuidoGraphicsItem* item, GuidoeElementSelector selector, const Filter* filter=0) 
					: fItem(item), fSelector(selector), fFilter(filter), fOutMap(0) {}
		virtual ~GuidoMapCollector() {}

		///< the method called by guido for each graphic segment
		virtual void Graph2TimeMap( const FloatRect& box, const TimeSegment& dates,  const GuidoElementInfos& infos );
		virtual void process (Time2GraphicMap* outmap);

				
		static RelativeTimeSegment	relativeTimeSegment(const TimeSegment& dates)
			{ return RelativeTimeSegment( rational(dates.first.num , dates.first.denom) , rational(dates.second.num , dates.second.denom) ); }
		static GraphicSegment		graphicSegment(const FloatRect& box, QPointF offset = QPointF(0,0))
			{ return GraphicSegment( box.left + offset.x(), box.top + offset.y(), box.right + offset.x(), box.bottom + offset.y()); }
};

//----------------------------------------------------------------------
/*!
	\brief a guido map collector filtering voice events
*/
class GuidoVoiceCollector: public GuidoMapCollector
{
	private:
		struct AcceptVoicePredicat : public Filter { int fNum;
			virtual bool operator() (const GuidoElementInfos& infos) const { return infos.voiceNum == fNum; }
		} fVoiceFilter;
		void	setFilter(int num)			{ fVoiceFilter.fNum = num; fFilter = &fVoiceFilter; }

	public :
				 GuidoVoiceCollector(const QGuidoGraphicsItem* item, int num) 
					: GuidoMapCollector(item, kGuidoEvent) { if (num) setFilter(num); }
		virtual ~GuidoVoiceCollector() {}
};


//----------------------------------------------------------------------
/*!
	\brief a guido map collector that combines a guido events and staff mappings
*/
class GuidoStaffCollector: public GuidoMapCollector
{
	private:
		struct AcceptStaffPredicat : public Filter {
			int	fNum;
			virtual bool operator() (const GuidoElementInfos& infos) const { return infos.staffNum == fNum; }
		} fStaffFilter;
		void	setFilter(int num)			{ fStaffFilter.fNum = num; fFilter = &fStaffFilter; }

	public :
				 GuidoStaffCollector (const QGuidoGraphicsItem* item, int num) 
					: GuidoMapCollector(item, kGuidoStaff) { if (num) setFilter(num); }
		virtual ~GuidoStaffCollector()	{}

		virtual void process (Time2GraphicMap* outmap);
};

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
//			ITLErr << "unexpected staff segmentation end while collecting staff map" << ITLEndl;
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
//			ITLErr << "unexpected staff segmentation end while while looking for evTime" << ITLEndl;
			cerr << "unexpected staff segmentation end while while looking for evTime " << evTime << endl;
			break;
		}

//		float startx = current->second.xinterval().first();
		float endx = 0;
		if (next == evtsMap.end())							// last event ?
			endx = staffIter->second.xinterval().second();	// end zone is end staff

		else {
			RelativeTimeSegment nextTime = next->first;
			if (staffIter->first.include(nextTime))		// not the last last staff event ?
				endx = next->second.xinterval().first();		// end zone is next event start

			else												// next event is on another staff
				endx = staffIter->second.xinterval().second();
		}

//		float endx = (next == evtsMap.end()) ? staffIter->second.xinterval().second() 
//						: (next->second.xinterval().first() > startx) ? next->second.xinterval().first()
//						: staffIter->second.xinterval().second();
		(*outmap)[current->first] = GraphicSegment(FloatInterval( current->second.xinterval().first(), endx ), 
													staffIter->second.yinterval());
	}
}

//----------------------------------------------------------------------
class RolledEnrolledCollector: public TimeMapCollector
{
	public:
		typedef std::map<RelativeTimeSegment, RelativeTimeSegment> T2TMap;
		
	private:
		QGuidoGraphicsItem* fItem;
		T2TMap*		fMap;	// Unrolled -> Rolled
		rational	fLastDate;
	
	public:
				 RolledEnrolledCollector(QGuidoGraphicsItem* item) : fItem(item) , fMap(0), fLastDate(0,4) {}
		virtual ~RolledEnrolledCollector() {}

		rational lastDate() const		{ return fLastDate; }

		void process(T2TMap* map) {
			if (map) {
				fMap = map;
				GuidoGetTimeMap( fItem->getARHandler() , *this );
			}
		}

		/** \brief a method called by the GuidoGetTimeMap function

			\param from a time segment expressed in score time i.e. rolled time.
			\param to a time segment expressed in unrolled time
		*/
		virtual void Time2TimeMap( const TimeSegment& from, const TimeSegment& to )
		{
			RelativeTimeSegment unrolledSegment = relativeTimeSegment(to);
			(*fMap)[ unrolledSegment ] = relativeTimeSegment(from);
			fLastDate = ( unrolledSegment.end() > fLastDate ) ? unrolledSegment.end() : fLastDate;
		}

		RelativeTimeSegment relativeTimeSegment(const TimeSegment& dates) const
		{
			rational segmentStart( dates.first.num , dates.first.denom );
			rational segmentEnd( dates.second.num , dates.second.denom );
			return RelativeTimeSegment( segmentStart , segmentEnd );
		}

};

//----------------------------------------------------------------------
VGuidoItemView::VGuidoItemView(QGraphicsScene * scene, const EventsAble* h)
					: VGraphicsItemView( scene , new IQGuidoGraphicsItem(h) )
{
	fGuidoItem = (IQGuidoGraphicsItem*)(fItem);
	
	GuidoLayoutSettings s = fGuidoItem->guidoLayoutSettings();
	s.optimalPageFill = true;	// incorrect mapping generated when set to false 
	fGuidoItem->setGuidoLayoutSettings(s);

	if ( !VGuidoItemView::fCm2GuidoUnit )
		VGuidoItemView::fCm2GuidoUnit = 1.0f/GuidoUnit2CM(1.0f);
}

//----------------------------------------------------------------------
void VGuidoItemView::updateView( IGuidoCode * guidoCode  )
{
	// 2. Update Score color
	QColor color(guidoCode->getR(), guidoCode->getG(), guidoCode->getB() , guidoCode->getA());
	if ( fGuidoItem->getScoreColor() != color )
	{
		fGuidoItem->setScoreColor( QColor(guidoCode->getR(), guidoCode->getG(), guidoCode->getB() , guidoCode->getA()) );
		itemChanged();
	}
	VGraphicsItemView::updateView (guidoCode);
}

//----------------------------------------------------------------------
bool VGuidoItemView::gmnUpdate (IGuidoCode* guidoCode)
{
	QString gmnCode = VApplView::toQString( guidoCode->getGMN().c_str() );
	if ( fGuidoItem->gmnCode() == gmnCode ) return true;		// no gmn code change, nothing to do
	
	if (fGuidoItem->setGMNCode( gmnCode ) ) 	return true;	// gmn code update done
	if (QGuidoImporter::musicxmlSupported()) {					// try to import file as MusicXML file
		std::stringstream converted;
																// first convert musicxml to guido
		if ( QGuidoImporter::musicxmlString2Guido ( guidoCode->getGMN().c_str(), true, converted) )
																// and next try to set the converted gmn code
			if ( fGuidoItem->setGMNCode( VApplView::toQString( converted.str().c_str() ) ) )	
				return true;
	}
	ITLErr << guidoCode->getOSCAddress() << "invalid gmn code: " << fGuidoItem->getLastErrorMessage().toAscii().data() << ITLEndl;
	return false;
}

//----------------------------------------------------------------------
void VGuidoItemView::pageFormatUpdate (IGuidoCode* guidoCode)
{
	GuidoPageFormat format = fGuidoItem->guidoPageFormat();

	float w = fCm2GuidoUnit * guidoCode->getPageFormat().width();
	float h = fCm2GuidoUnit * guidoCode->getPageFormat().height();
	if ( ( format.width != w ) || ( format.height != h ) )
	{
		format.width = w;
		format.height = h;
		fGuidoItem->setGuidoPageFormat(format);
	}
	guidoCode->setPagesCount( fGuidoItem->pageCount() );

	GuidoDate date;
	GuidoDuration( fGuidoItem->getGRHandler(), &date );
	guidoCode->setDuration (rational(date.num, date.denom));
	guidoCode->setGRHandler (fGuidoItem->getGRHandler());

	// Update multiple-page layout
	if ( fGuidoItem->firstVisiblePage() != guidoCode->getPage() )
		fGuidoItem->setPage(guidoCode->getPage());
	fGuidoItem->setGridWidth( guidoCode->getNbOfPageColumns() );
	fGuidoItem->setGridHeight( guidoCode->getNbOfPageRows() );
}

//----------------------------------------------------------------------
SRelativeTimeSegmentation VGuidoItemView::timeMapUpdate (SRelativeTime2RelativeTimeMapping& map)
{
	RolledEnrolledCollector timeCollector( fGuidoItem );
	RolledEnrolledCollector::T2TMap t2tmap;
	timeCollector.process(&t2tmap);
	// Create the unrolled time segmentation.
	SRelativeTimeSegmentation segm = RelativeTimeSegmentation::create( RelativeTimeSegment(rational(0,1) , timeCollector.lastDate()) );	
	RolledEnrolledCollector::T2TMap::const_iterator timeIter = t2tmap.begin();	// Iterates thru the map 
																				// Map is 'unrolled' to 'rolled', so: time -> local.	
	while (timeIter != t2tmap.end()) {
		map->add ( timeIter->second , timeIter->first );	// Put the rolled -> unrolled relation in the mapping.
		segm->add(timeIter->first);							// Also put the unrolled segment in the time segmentation.			
		timeIter++;
	}
	return segm;
}

//----------------------------------------------------------------------
static SRelativeTime2RelativeTimeMapping intersect (const SRelativeTime2RelativeTimeMapping& t2t, const std::set<RelativeTimeSegment>& inter)
{
	SRelativeTime2RelativeTimeMapping outmap = RelativeTime2RelativeTimeMapping::create();
	TVirtualRelation<RelativeTimeSegment,RelativeTimeSegment> vrel(t2t->direct());
	for (std::set<RelativeTimeSegment>::const_iterator i = inter.begin(); i != inter.end(); i++) {
		std::set<RelativeTimeSegment> tsegs = vrel.get(*i);
		for (std::set<RelativeTimeSegment>::const_iterator j = tsegs.begin(); j != tsegs.end(); j++) {
			outmap->add (*i, *j);
		}	
	}
	return outmap;
}

//----------------------------------------------------------------------
static SGraphic2RelativeTimeMapping intersect (const SGraphic2RelativeTimeMapping& g2t, const std::set<RelativeTimeSegment>& inter)
{
	SGraphic2RelativeTimeMapping outmap = Graphic2RelativeTimeMapping::create();
	TVirtualRelation<RelativeTimeSegment,GraphicSegment> vrel(g2t->reverse());
	for (std::set<RelativeTimeSegment>::const_iterator i = inter.begin(); i != inter.end(); i++) {
		std::set<GraphicSegment> gsegs = vrel.get(*i);
		for (std::set<GraphicSegment>::const_iterator j = gsegs.begin(); j != gsegs.end(); j++) {
			outmap->add (*j, *i);
		}	
	}
	return outmap;
}

//----------------------------------------------------------------------
void VGuidoItemView::graphMapUpdate (IGuidoCode* guidoCode, SRelativeTime2RelativeTimeMapping& ttmap, SRelativeTimeSegmentation& timeseg)
{
	float itemWidth  = fGuidoItem->boundingRect().width();
	float itemHeight = fGuidoItem->boundingRect().height();	
	const vector<string>& mapNames = guidoCode->requestedMappings();

	for ( unsigned int i = 0 ; i < mapNames.size() ; i++ )
	{
		GuidoMapCollector * collector = getMapBuilder( mapNames[i] );		// Collect the time->graphic mapping from Guido API.
		if ( collector )
		{
			SGraphic2RelativeTimeMapping g2l_mapping = Graphic2RelativeTimeMapping::create();					// Build the 'graphic -> rolled relative time' mapping.
			SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment(-1,-1,1,1) );// Create the graphic segmentation.

			GuidoMapCollector::Time2GraphicMap map;
			collector->process (&map);

			for ( GuidoMapCollector::Time2GraphicMap::const_iterator iter = map.begin(); iter != map.end(); iter++) {
				GraphicSegment transformedGraphicSegment( 2*iter->second.xinterval().first()/itemWidth -1 , 
									2*iter->second.yinterval().first()/itemHeight -1,
									2*iter->second.xinterval().second()/itemWidth -1 , 
									2*iter->second.yinterval().second()/itemHeight -1);	// Transform from QGraphicsItem space to IObject space.
				
				g2l_mapping->add ( transformedGraphicSegment , iter->first);	// Put the time -> graphic relation in the mapping.
				graphicSegmentation->add(transformedGraphicSegment);			// Also put the graphic segment in the graphic segmentation.
			}

			// the steps below are required to make sure that the time to time and the time to graphic mappings
			// share the same time segmentation, which is  not the case for system map for example
			ttmap = MapTools::reduce(ttmap);			// reduce the time to time mapping
			std::set<RelativeTimeSegment> inter;		// computes the intersection with the time to graphic segmentation
			MapTools::intersect(ttmap->direct(), g2l_mapping->reverse(), inter);
			g2l_mapping = intersect(g2l_mapping, inter);// rebuilds the time to graphic mapping with the intersection
			ttmap = intersect(ttmap, inter);			// rebuilds the time to mapping with the intersection

			guidoCode->localMappings()->setMapping( mapNames[i] , g2l_mapping , ttmap );	// Add the both mappings to the IGuidoCode.
			guidoCode->setGraphicSegmentation( mapNames[i] , graphicSegmentation );			// Add the graphic segmentation to the IGuidoCode.
			guidoCode->setTimeSegmentation( mapNames[i] , timeseg );						// Add the time segmentation to the IGuidoCode.
			// Add the composed mapping to the IGuidoCode.
			VGraphicsItemView::setMapping<RelativeTimeSegment>( guidoCode , guidoCode->requestedMappings()[i] , g2l_mapping , ttmap );	
			delete collector;
		}
	}
}

//----------------------------------------------------------------------
void VGuidoItemView::updateLocalMapping (IGuidoCode* guidoCode)
{
	if (!gmnUpdate (guidoCode) ) return;
	pageFormatUpdate (guidoCode);
		
	// Build the Rolled->Unrolled mapping
	SRelativeTime2RelativeTimeMapping l2t_mapping = TMapping<RelativeTimeSegment,RelativeTimeSegment>::create();	// Create the 'rolled -> unrolled' mapping.
	SRelativeTimeSegmentation unrolledTimeSegmentation = timeMapUpdate (l2t_mapping);

	// Build the time->graphic mapping.
	graphMapUpdate (guidoCode, l2t_mapping, unrolledTimeSegmentation);

	// checks for default mapping (should be useless for guido code)
	VGraphicsItemView::buildDefaultMapping (guidoCode);
}

//----------------------------------------------------------------------
static int getMapNum ( const QString& name, int baseSize)
{
	QString num = name.right(name.length() - baseSize);
	return num.size() ? QVariant( num ).toInt() : 1;
}

//----------------------------------------------------------------------
GuidoMapCollector* VGuidoItemView::getMapBuilder(const string& mapName) const
{
	GuidoMapCollector * mb = 0;
	QString name = mapName.size() ? mapName.c_str() : kStaffMap + "1";

	if ( name.startsWith (kVoiceMap) )
		mb = new GuidoVoiceCollector ( fGuidoItem, getMapNum (name, kVoiceMap.size()) );
	else if ( name.startsWith (kStaffMap) )
		mb = new GuidoStaffCollector ( fGuidoItem, getMapNum (name, kStaffMap.size()) );
	else if ( name == kSystemMap )
		mb = new GuidoMapCollector(fGuidoItem, kGuidoSystem);
	else if ( name == kPageMap )
		mb = new GuidoMapCollector(fGuidoItem, kGuidoPage);
	else if ( name == kSliceMap )
		mb = new GuidoMapCollector(fGuidoItem, kGuidoSystemSlice);
	else if ( name.startsWith( kMeasureMap ) )
		mb = new GuidoStaffCollector ( fGuidoItem, getMapNum (name, kMeasureMap.size()) );
	else cerr << "unknwown guido mapping name \"" << mapName << "\" requested" << endl;
	
	return mb;
}

} // end namespoace
