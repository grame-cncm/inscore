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
#include <QDebug>


#include "MapTools.h"
#include "ITLError.h"
#include "VGuidoItemView.h"
#include "VApplView.h"

#include "IGuidoCode.h"
#include "QGuidoGraphicsItem.h"
#include "QGuidoImporter.h"

#include "GuidoMapCollector.h"

#include "benchtools.h"

using namespace std;


const QString kVoiceMap	 ("voice");
const QString kStaffMap	 ("staff");
const QString kSystemMap ("system");
const QString kSystemFlatMap ("systemflat");
const QString kSliceMap	 ("systemSlice");
const QString kPageMap	 ("page");
const QString kMeasureMap("measure");

using namespace libmapping;

namespace inscore
{

float VGuidoItemView::fCm2GuidoUnit = 0;

//----------------------------------------------------------------------
class RolledUnrolledCollector: public TimeMapCollector
{
	public:
		typedef std::map<RelativeTimeSegment, RelativeTimeSegment> T2TMap;
		
	private:
		QGuidoGraphicsItem* fItem;
		T2TMap*		fMap;	// Unrolled -> Rolled
		rational	fLastDate;
	
	public:
				 RolledUnrolledCollector(QGuidoGraphicsItem* item) : fItem(item) , fMap(0), fLastDate(0,4) {}
		virtual ~RolledUnrolledCollector() {}

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
			return RelativeTimeSegment( rational( dates.first.num , dates.first.denom ) , rational( dates.second.num , dates.second.denom ) );
		}

};

#define USEPIXMAP
//----------------------------------------------------------------------
void QCachedGuidoGraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	__is_uint64 time = getTime();
	QRectF rect = boundingRect();
	QSize size (rect.width(), rect.height());
//qDebug() << "QCachedGuidoGraphicsItem::paint rect" << rect;
//qDebug() << "QCachedGuidoGraphicsItem::paint clipBoundingRect" << painter->clipBoundingRect();
#if 0
	if (fInvalide) {
		delete fCache;
# ifdef USEPIXMAP
		fCache = new QPixmap (size);
# else
		fCache = new QImage (size, QImage::Format_ARGB32);
# endif
		QPainter cachepainter (fCache);
		cachepainter.setRenderHints (QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
		QGuidoGraphicsItem::paint (&cachepainter, option, widget);
		fInvalide = false;
	}
	painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
# ifdef USEPIXMAP
	painter->drawPixmap(0, 0, *fCache);
# else
	painter->drawImage(0, 0, *fCache);
# endif
#else
	QGuidoGraphicsItem::paint (painter, option, widget);
#endif
	cout << "QCachedGuidoGraphicsItem::paint elapsed: " << (getTime() - time) / 1000 << endl;
}

//----------------------------------------------------------------------
VGuidoItemView::VGuidoItemView(QGraphicsScene * scene, const IGuidoCode* h)
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
    guidoCode->cleanupSync();
	gmnUpdate(guidoCode);
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
    IGuidoStream * guidoStream = dynamic_cast<IGuidoStream *>(guidoCode);    
    
    if(guidoStream)
    {
        if(fGuidoItem->setGMNStream(guidoStream->getGuidoStream())) return true;
		ITLErr << guidoCode->getOSCAddress() << "invalid gmn code:" << fGuidoItem->getLastErrorMessage().toUtf8().data() << ITLEndl;
        return false;
    }
    else
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
        ITLErr << guidoCode->getOSCAddress() << "invalid gmn code:" << fGuidoItem->getLastErrorMessage().toUtf8().data() << ITLEndl;
        return false;
    }
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
void VGuidoItemView::timeMapUpdate (SRelativeTime2RelativeTimeMapping& map)
{
	RolledUnrolledCollector timeCollector( fGuidoItem );
	RolledUnrolledCollector::T2TMap t2tmap;
	timeCollector.process(&t2tmap);

	RolledUnrolledCollector::T2TMap::const_iterator timeIter = t2tmap.begin();	// Iterates thru the map
																				// Map is 'unrolled' to 'rolled', so: time -> local.	
	while (timeIter != t2tmap.end()) {
		map->add ( timeIter->second , timeIter->first );	// Put the rolled -> unrolled relation in the mapping.
		timeIter++;
	}
}

//----------------------------------------------------------------------
void VGuidoItemView::graphMapUpdate (IGuidoCode* guidoCode, SRelativeTime2RelativeTimeMapping& ttmap)
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

			GuidoMapCollector::Time2GraphicMap map;
			collector->process (&map);

			for ( GuidoMapCollector::Time2GraphicMap::const_iterator iter = map.begin(); iter != map.end(); iter++) {
				GraphicSegment transformedGraphicSegment( 2*iter->second.xinterval().first()/itemWidth -1 , 
									2*iter->second.yinterval().first()/itemHeight -1,
									2*iter->second.xinterval().second()/itemWidth -1 , 
									2*iter->second.yinterval().second()/itemHeight -1);	// Transform from QGraphicsItem space to IObject space.
				
				g2l_mapping->add ( transformedGraphicSegment , iter->first);	// Put the time -> graphic relation in the mapping.
			}

			// the steps below are required to make sure that the time to time and the time to graphic mappings
			// share the same time segmentation, which is  not the case for system map for example
			ttmap = MapTools::reduce(ttmap);			// reduce the time to time mapping
			guidoCode->localMappings()->setMapping( mapNames[i], ttmap );	// Add mapping to the IGuidoCode.
			// Add the composed mapping to the IGuidoCode.
			VGraphicsItemView::setMapping<rational,1>( guidoCode , guidoCode->requestedMappings()[i] , g2l_mapping , ttmap, true );
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
	SRelativeTime2RelativeTimeMapping l2t_mapping = TMapping<rational,1, rational,1>::create();	// Create the 'rolled -> unrolled' mapping.
	timeMapUpdate (l2t_mapping);

	// Build the time->graphic mapping.
	graphMapUpdate (guidoCode, l2t_mapping);

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
		mb = new GuidoSystemCollector(fGuidoItem);
	else if ( name == kSystemFlatMap )
		mb = new GuidoSystemCollector(fGuidoItem, true);
	else if ( name == kPageMap )
		mb = new GuidoMapCollector(fGuidoItem, kGuidoPage);
	else if ( name == kSliceMap )
		mb = new GuidoMapCollector(fGuidoItem, kGuidoSystemSlice);
	else if ( name.startsWith( kMeasureMap ) )
		mb = new GuidoStaffCollector ( fGuidoItem, getMapNum (name, kMeasureMap.size()) );
	else ITLErr << "unknwown guido mapping name" << mapName << "requested" << ITLEndl;
	
	return mb;
}

} // end namespoace
