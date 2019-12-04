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

#include "TComposition.h"
#include "VGraphicsItemView.h"
#include "VSceneView.h"
#include "maptypes.h"
#include "TSegment.h"
#include "TRect.h"

#include <QtDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "QStretchTilerItem.h"

#include "IObject.h"
#include "Events.h"
#include "VExport.h"

#include "MouseEventAble.h"

#define NB_OF_COLORS 12

using namespace libmapping;

namespace inscore
{

// Array of colors of mapping debug items.
QColor brushColors[NB_OF_COLORS] = {	Qt::darkBlue , Qt::darkRed , Qt::darkYellow , Qt::darkCyan , Qt::darkGreen , Qt::darkMagenta , 
										Qt::blue , Qt::red , Qt::yellow , Qt::cyan , Qt::green , Qt::magenta };

//------------------------------------------------------------------------------------------------------------
//												Member functions
//------------------------------------------------------------------------------------------------------------
VGraphicsItemView::VGraphicsItemView( QGraphicsScene * scene , QGraphicsItem * item )
{
	fItem = item;
	setMouseEventSensibility(false);
	scene->addItem( item );
    fScene = scene;
    fParent = 0;
    fNbMasters = 0;
	fBrushColorStartIndex = 0;
	fBoundingBox = 0;
}

//------------------------------------------------------------------------------------------------------------
VGraphicsItemView::~VGraphicsItemView()
{
	deleteDebugItems();
	delete fBoundingBox;

	QList<QGraphicsItem*> children = fItem->childItems();	// Break all links with children
	for (int i = 0 ; i < children.size() ; i++ )
		children[i]->setParentItem(0);
    
    std::map<SMaster, QStretchTilerItem*>::iterator it = fTilerItems.begin();
    while(it != fTilerItems.end())
    {
        std::map<SMaster, QStretchTilerItem*>::iterator toErase = it;
        it++;
        if(toErase->second->scene())
            fScene->removeItem(toErase->second);
        delete toErase->second;
    }
    fTilerItems.clear();
    
    if(fItem->scene())
        fItem->scene()->removeItem( fItem );					// Remove the QGraphicsItem from the scene.
	delete fItem;
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::deleteDebugItems()
{
	for ( int i = 0 ; i < fDebugItems.size() ; i++ )		// Delete object's debug items
		delete fDebugItems[i];
		
	fDebugItems.clear();
}

//------------------------------------------------------------------------------------------------------------
// Map debug: parse all the object's mapping and add colored rectangles to show the mapped zones.
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::drawMapping(IObject* o)
{	
	//if (fIsStretchOn) return;		// don't know where to draw

	int count = 0;
	// For each time<->graphic mapping.
	for (TMapable::const_iterator i = o->namedMappings().begin() ; i != o->namedMappings().end() ; i++, count++ )
	{
		QColor mapColor1 = brushColors[(count++ + fBrushColorStartIndex)%NB_OF_COLORS];
		QColor mapColor2 = brushColors[(count + fBrushColorStartIndex)%NB_OF_COLORS];
		mapColor1.setAlpha (90);
		mapColor2.setAlpha (90);
		
		float z = 0;
		int colorindex = 0;
		const RelativeTime2GraphicRelation& rt2g = i->second->direct();
		// For each time segment in the mapping, draw its corresponding GraphicSegment.
		for (RelativeTime2GraphicRelation::const_iterator j = rt2g.begin(); j != rt2g.end() ; j++ )
		{
			RelativeTimeSegment timeSegment = j->first;
			QString timeString = ((std::string)timeSegment.interval()).c_str();
			const std::set<GraphicSegment>& related = j->second;
			// For each master segment corresponding to the slave segment.
			for ( std::set<GraphicSegment>::const_iterator j=related.begin() ; j != related.end(); j++ )
			{
				const QColor& color = (colorindex & 1) ? mapColor2 : mapColor1;
				QRectF qtRect = iObject2QGraphicsItem( *j );
				QGraphicsRectItem * mappingSegment = new QGraphicsRectItem( qtRect , item() );
				mappingSegment->setPen( QPen( color ) );
				mappingSegment->setBrush( QBrush( color) );
				mappingSegment->setZValue( ++z );
				fDebugItems << mappingSegment;

				if (o->mapDebug() > 1 && fTilerItems.empty()) {	// check if dates should be printed
					// Add dates
					QGraphicsTextItem * textItem = new QGraphicsTextItem( timeString , mappingSegment );
					textItem->setDefaultTextColor( Qt::black );
					float scale = 4.0f;
					textItem->setScale(1.0f/scale);
					if (colorindex & 1)
						textItem->setPos( qtRect.x() , qtRect.y() + qtRect.height()); // + textItem->boundingRect().height()/scale );
					else
						textItem->setPos( qtRect.x() , qtRect.y() - textItem->boundingRect().height()/scale );
					textItem->setZValue(z);
				}
			}
			colorindex++;
		}
	}
}

//------------------------------------------------------------------------------------------------------------
// pen style and brush control
//------------------------------------------------------------------------------------------------------------
#define DOT_LENGTH		0.5f
#define DASH_LENGTH		3.0f
#define SPACE_LENGTH	3.0f

//----------------------------------------------------------------------
void VGraphicsItemView::setQPenStyle(const std::string& penStyle , QPen& pen) const
{
	if ( penStyle == IShape::kSolidStyle )
		pen.setStyle( Qt::SolidLine );
	else if ( penStyle == IShape::kDotStyle ) {
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DOT_LENGTH << SPACE_LENGTH );
	}
	else if ( penStyle == IShape::kDashStyle ) {
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DASH_LENGTH << SPACE_LENGTH );
	}
	else if ( penStyle == IShape::kDashDotStyle ) {
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DASH_LENGTH << SPACE_LENGTH << DOT_LENGTH << SPACE_LENGTH );
	}
	else if ( penStyle == IShape::kDashDotDotStyle ) {
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DASH_LENGTH << SPACE_LENGTH << DOT_LENGTH << SPACE_LENGTH << DOT_LENGTH << SPACE_LENGTH );
	}
	else
		pen.setStyle( Qt::SolidLine );
}

void VGraphicsItemView::setQBrushStyle(const std::string& brushStyle , QBrush& brush) const
{
    if ( brushStyle == IShape::kSolidBrushStyle )
        brush.setStyle( Qt::SolidPattern );
    else if ( brushStyle == IShape::kDense1BrushStyle )
        brush.setStyle( Qt::Dense1Pattern );
    else if ( brushStyle == IShape::kDense2BrushStyle )
        brush.setStyle( Qt::Dense2Pattern );
    else if ( brushStyle == IShape::kDense3BrushStyle )
        brush.setStyle( Qt::Dense3Pattern );
    else if ( brushStyle == IShape::kDense4BrushStyle )
        brush.setStyle( Qt::Dense4Pattern );
    else if ( brushStyle == IShape::kDense5BrushStyle )
        brush.setStyle( Qt::Dense5Pattern );
    else if ( brushStyle == IShape::kDense6BrushStyle )
        brush.setStyle( Qt::Dense6Pattern );
    else if ( brushStyle == IShape::kDense7BrushStyle )
        brush.setStyle( Qt::Dense7Pattern );
    else if ( brushStyle == IShape::kNoBrushStyle )
        brush.setStyle( Qt::NoBrush );
    else if ( brushStyle == IShape::kHorBrushStyle )
        brush.setStyle( Qt::HorPattern );
    else if ( brushStyle == IShape::kVerBrushStyle )
        brush.setStyle( Qt::VerPattern );
    else if ( brushStyle == IShape::kCrossBrushStyle )
        brush.setStyle( Qt::CrossPattern );
    else if ( brushStyle == IShape::kBDiagBrushStyle )
        brush.setStyle( Qt::BDiagPattern );
    else if ( brushStyle == IShape::kFDiagBrushStyle )
        brush.setStyle( Qt::FDiagPattern );
    else if ( brushStyle == IShape::kDiagCrossBrushStyle )
        brush.setStyle( Qt::DiagCrossPattern );
    else
        brush.setStyle( Qt::SolidPattern );
}

//------------------------------------------------------------------------------------------------------------
// Debug graphic feedback : displays the bounding rectangle and the object name for all the items
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::drawName(IObject* o)
{	
	if(fTilerItems.empty())
        drawName(o, item());
    else {
        std::map<SMaster, QStretchTilerItem *>::iterator i;
        for(i = fTilerItems.begin(); i != fTilerItems.end(); i++)
            drawName(o, i->second);
    }
}

void VGraphicsItemView::drawBoundingBox(IObject* o)
{	
	if(fTilerItems.empty())
        drawBoundingBox(o, item());
    else {
        std::map<SMaster, QStretchTilerItem *>::iterator i;
        for(i = fTilerItems.begin(); i != fTilerItems.end(); i++)
            drawBoundingBox(o, i->second);
    }
}

//------------------------------------------------------------------------------------------------------------
// Debug graphic feedback : displays the bounding rectangle and the object name for a given item
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::drawName(IObject* o, QGraphicsItem* item)
{
        // Add an item for the bounding rect
        QRectF bboxRectQt = fItem->boundingRect();

        // Add an item for the name.
        QGraphicsTextItem * textItem = new QGraphicsTextDebugItem( o->name().c_str() , item );
        textItem->setDefaultTextColor( Qt::red );
		textItem->setPos( bboxRectQt.x() , bboxRectQt.y() - textItem->boundingRect().height() );
		fDebugItems << textItem;
}


//------------------------------------------------------------------------------------------------------------
// Debug graphic feedback : displays the bounding rectangle and the object name for a given item
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::drawBoundingBox(IObject* o, QGraphicsItem* item)
{
	float w = o->getPenWidth();
	if (w) {
		w /= 2;
		QRectF bboxRectQt = fItem->boundingRect();
		bboxRectQt += QMarginsF(w,w,w,w);
		if (!fBoundingBox) fBoundingBox = new QGraphicsRectItem( bboxRectQt, item);
		QPen pen( QColor(o->getPenColor().getR(), o->getPenColor().getG(), o->getPenColor().getB() , o->getPenColor().getA()) , o->getPenWidth() );
		setQPenStyle( o->getPenStyle() , pen );
        pen.setCapStyle( Qt::RoundCap );
		pen.setJoinStyle( Qt::RoundJoin );

		fBoundingBox->setPen( pen );
		fBoundingBox->setBrush( QBrush(Qt::NoBrush) );
	}
	else if (fBoundingBox) {
		delete fBoundingBox;
		fBoundingBox = 0;
	}
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateObjectSize(IObject* o)
{	
	o->setWidth( getIObjectWidth() );
	o->setHeight( getIObjectHeight() );
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateTransform(IObject* o, QGraphicsItem* item)
{
//	fItem->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
	QTransform matrix;
	TFloatSize shear = o->getShear();
	if (shear)
		matrix.shear(shear.width(), shear.height());
	if (o->getRotateX())
		matrix.rotate(o->getRotateX(), Qt::XAxis);
	if (o->getRotateY())
		matrix.rotate(o->getRotateY(), Qt::YAxis);
	if (o->getRotateZ())
		matrix.rotate(o->getRotateZ(), Qt::ZAxis);
	item->setTransform (matrix);
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItemHStretch(QStretchTilerItem * item, const SGraphic2GraphicMapping& slave2Master)
{
    item->setStretch(true);
    item->setRect(item->parentItem() ? item->parentItem()->boundingRect():item->scene()->sceneRect());
    float x = item->boundingRect().center().x();
    float y = item->boundingRect().center().y();
    item->setPos( x, y);
    
    item->resetTransform();
    item->setTransform(QTransform::fromTranslate(-x, -y), true);
    Graphic2GraphicRelation::const_iterator iter;
    for ( iter = slave2Master->direct().begin() ; iter != slave2Master->direct().end() ; iter++ )	// For each slave segment.
    {
        if ( !iter->first.size() )	// Skip empty segments.
            continue;

        QRectF slaveSourceRect = iObject2QGraphicsItem( iter->first, item->boundingRect() );
			
        const std::set<GraphicSegment>& related = iter->second;
        // For each master segment corresponding to the slave segment.
        for ( std::set<GraphicSegment>::const_iterator i=related.begin() ; i != related.end(); i++ )
        {
            if ( !i->size() )	// Skip empty segments.
                continue;

            QRectF masterDestRect = iObject2QGraphicsItem( *i, item->parentItem()->boundingRect() );
            item->addSegment( slaveSourceRect , masterDestRect );
        }
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::getFrame (const IObject* o, std::vector<float>& out)
{
	QRectF r = item()->boundingRect();
	QTransform m = item()->transform();
	m.scale(o->getScale(), o->getScale());
	QPolygon po = m.mapToPolygon(r.toRect());
	for (int i=0; i < po.size(); i++) {
		QPoint p = po[i];
		out.push_back(scene2RelativeX(p.x()) + o->getXPos());
		out.push_back(scene2RelativeY(p.y()) + o->getYPos());
	}
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::setMouseEventSensibility(bool mouseSensible)
{
	if(!fItem)
		return;

	if(mouseSensible){
		fItem->setAcceptedMouseButtons(Qt::AllButtons);
		fItem->setAcceptHoverEvents(true);
		fItem->setAcceptTouchEvents(true);
	}else{
		fItem->setAcceptedMouseButtons(Qt::NoButton);
		fItem->setAcceptHoverEvents(false);
		fItem->setAcceptTouchEvents(false);
	}
}

#define kUnknownLocation 999999.f
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItemSyncFrame(QStretchTilerItem* item, IObject* o, SMaster master)
{
    item->setStretch(false);
	TFloatPoint p;
	IObject* m = master->getMaster();
	rational d = o->getDate();
	if (master->getMode() == Master::kSyncRelative)
		d -= master->getMaster()->getDate();
	if (m->date2FramePoint(d, p)) {
		double width = relative2SceneWidth(o->getWidth());
		double height = relative2SceneHeight(o->getHeight());

		double mw = relative2SceneWidth(m->getWidth());
		double mh = relative2SceneHeight(m->getHeight());
		double x = p.fX * mw;
		double y = p.fY * mh  + mh*(master->getDy());

		item->setRect(QRectF(0,0,width,height));
		item->setPos(x, y);
		item->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
		updateTransform (o, item);
		QRectF bbrect = item->boundingRect();
		double xo = bbrect.width() / 2;
		double yo = bbrect.height() / 2;
		item->setTransform(QTransform::fromTranslate(-xo, -yo), true);
	}
	else {
		item->setPos(kUnknownLocation, kUnknownLocation);
	}
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItemNoStretch(QStretchTilerItem* item, IObject* o, SMaster master)
{
    item->setStretch(false);
	
    std::string mapName = master->getMaster()->name() + ":" + master->getMasterMapName();
    double width = relative2SceneWidth(o->getSyncWidth(mapName), item);
    double height = relative2SceneHeight(o->getSyncHeight(mapName), item);
    
    double x = relative2SceneX( o->getSyncPos(mapName).x(), item );
    double y = relative2SceneY( o->getSyncPos(mapName).y(), item );
 
    item->setRect(QRectF(0,0,width,height));
    item->setPos(x, y);
    item->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
    updateTransform (o, item);
    QRectF bbrect = item->boundingRect();
    double xo = bbrect.width() / 2;
    double yo = bbrect.height() / 2;
    item->setTransform(QTransform::fromTranslate(-xo, -yo), true);
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateGeometry(QGraphicsItem* item, IObject* o, float x, float y)
{
    //	Sets the item position in the QGraphicsScene, using 'relative coordinate -> QGraphicsScene coordinate'
    //	mapping functions.
    item->setPos(x, y);
    item->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
    updateTransform (o, item);
    QRectF bbrect = getBoundingRect(o);
    double xo = bbrect.width()  * (o->getXOrigin() + 1) * o->getScale() / 2;
    double yo = bbrect.height() * (o->getYOrigin() + 1) * o->getScale() / 2;
    item->setTransform(QTransform::fromTranslate(-xo, -yo), true);
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItem(QGraphicsItem* item, IObject* o)
{
    // Visibility
    item->setVisible(  o->getVisible() );

    // Z order. A negative 'z' value puts the object behind its parent - if it has one.
    item->setFlag( QGraphicsItem::ItemStacksBehindParent , (o->getZOrder() < 0) );
    item->setZValue(  o->getZOrder() );
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateView(IObject* o)
{
	setSlave(o);

	// firt update the object shape
	drawBoundingBox (o);
	// slave mode: setup and use of fTilerItem
    for(std::map<SMaster, QStretchTilerItem*>::iterator i = fTilerItems.begin(); i != fTilerItems.end(); i++)
    {
        SMaster master = i->first;
		
        QStretchTilerItem * fTilerItem = fTilerItems.find(master)->second;
        fTilerItem->clearSegments();
            
        fTilerItem->setOpacity (o->getA() / 255.f);
		
		if (master->getAlignment() == Master::kSyncFrame) {
			updateItemSyncFrame (fTilerItem, o, master);
		}
		else {
			std::string masterMapName = master->getMaster()->name() + ":" + master->getMasterMapName();
			const SGraphic2GraphicMapping& slave2Master = o->getSlave2MasterMapping(masterMapName);
			bool isHStretch =  o->UseGraphic2GraphicMapping(masterMapName);
				
			if(slave2Master && isHStretch)
				updateItemHStretch(fTilerItem, slave2Master);
			else
				updateItemNoStretch(fTilerItem, o, master);
        }
        updateItem(fTilerItem, o);
        fTilerItem->update();
    }
    // the item is not slaved
	if(fTilerItems.empty())
	{
        fItem->setScale(  o->getScale() );
	    updateGeometry(fItem, o, relative2SceneX(o->getXPos()), relative2SceneY(o->getYPos()));
        updateItem(fItem, o);
    }


	//Exports the item if necessary.
	std::pair<std::string, bool> myExport = o->getNextExportFlag();

	while ( myExport.first.length() ) {
		VExport::exportItem( item() , myExport.first.c_str() ,  o->getScale() ,  o->getScale(), myExport.second);
		o->checkEvent(kExportEvent, rational(0,1), o);
		myExport = o->getNextExportFlag();
	}

	//	Debug mapping mode:
	//		- erase mapping QGraphicsRectItem anyways
	//		- create new mapping QGraphicsRectItems if "Debug Mapping Mode" is on.
	deleteDebugItems();

	// ----------------------------------------------------------------------------------------------
	// Map debug: parse all the object's mapping and add colored rectangles to show the mapped zones.
	if ( o->mapDebug() ) drawMapping (o);
	// ----------------------------------------------------------------------------------------------
	// Debug graphic feedback : displays the bounding rectangle and the object name
	if ( o->nameDebug() ) drawName (o);
	
	// ----------------------------------------------------------------------------------------------
	// and eventually check if an 'edit' request is pending
	if (o->getEdit()) {
		VSceneView* scene = o->getScene()->getSceneView();
		if (scene) scene->edit(o);
    }
}

//------------------------------------------------------------------------------------------------------------
// check if automatic mapping (build from object duration) needs to be refreshed
//------------------------------------------------------------------------------------------------------------
static bool checkAutoRefresh (IObject* object, const RelativeTime2GraphicRelation& )
{
	return object->fAutoMap && object->durationModified();
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::buildDefaultMapping (IObject* object)
{
//	if ((object->namedMappings().size() == 1) && ()) return;  // no need to build the default mapping
	
	const SRelativeTime2GraphicMapping& map = object->getMapping("");
	// Check if the un-named mapping exists or if it needs to be refreshed. 
	if ( !map ||  checkAutoRefresh(object, map->direct()))	
	{	
		// If not, build a default mapping : the current [0 ; duration[ <-> the whole graphic space of the object.
		RelativeTimeSegment wholeTimeSegment( rational(0,1) , object->getDuration() );
		GraphicSegment		wholeGraphicSegment( -1 , -1 , 1 , 1 );
		
		SRelativeTime2GraphicMapping t2g_mapping = TMapping<rational,1,float,2>::create();
		t2g_mapping->add ( wholeTimeSegment , wholeGraphicSegment );
		object->setMapping( "" , t2g_mapping);
		object->fAutoMap = true;
		object->localMapModified(true);
	}
}

//------------------------------------------------------------------------------------------------------------
QStretchTilerItem* VGraphicsItemView::buildTiler(SIObject o)
{
    MouseEventAble<QStretchTilerItem>* item = new MouseEventAble<QStretchTilerItem>( o );
    item->setOriginItem(fItem);
    return item;
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::itemChanged()
{
    for(std::map<SMaster, QStretchTilerItem*>::iterator it = fTilerItems.begin(); it != fTilerItems.end(); it++)
    {
        it->second->needUpdate(true);
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::findNewSync(SMaster master, SIObject slave)
{
    //std::map<SMaster, QStretchTilerItem*>::iterator it = fTilerItems.find(master);
    bool found = false;
    for(std::map<SMaster, QStretchTilerItem*>::iterator i = fTilerItems.begin(); i != fTilerItems.end(); i++)
    {
        if(i->first->getMaster() == master->getMaster() && i->first->getMasterMapName() == master->getMasterMapName())
            found = true;
    }
    QStretchTilerItem * fTilerItem;
    if(!found && master->getMaster()->getView())
    {
        fTilerItem = buildTiler(slave);
        VGraphicsItemView * masterView = dynamic_cast<VGraphicsItemView*>(master->getMaster()->getView());
        fTilerItem->setParentItem(masterView->item());
        fTilerItems.insert(std::pair<SMaster, QStretchTilerItem*>(master,fTilerItem));
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::findObsoleteSync(std::vector<SMaster> masters)
{
    std::map<SMaster, QStretchTilerItem*>::iterator it = fTilerItems.begin();

    while(it != fTilerItems.end())
    {
        bool found = false;
        for(std::vector<SMaster>::iterator i = masters.begin(); i != masters.end(); i++)
            if((*i)->getMaster() == it->first->getMaster() && (*i)->getMasterMapName() == it->first->getMasterMapName())
                found = true;
        if(!found)
        {
            if(it->second->scene())
                fScene->removeItem(it->second);
            else
                it->second->setParentItem(0);
            
            std::map<SMaster, QStretchTilerItem*>::iterator toErase = it;
            it++;
            fTilerItems.erase(toErase);
        }
        else
            it++;
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::setSlave(SIObject o )
{
    std::vector<SMaster> masters = o->getParent()? o->getParent()->getMasters(o) : o->getScene()->getMasters(o);
    
	for(unsigned int i = 0; i < masters.size(); i++)    // we first look for new masters, in order to add new representation
    {
        SMaster master = masters[i];
        findNewSync(master, o);
    }
    
    findObsoleteSync(masters); // Then we check if some representation could be obsolete (master/slave relation deleted)
    
    if(fNbMasters == masters.size()) return; //there is no master-slave relation to add or remove
    
    if(!fNbMasters)    // this is the first master added, so we have to remove the classic fItem and switch to the slaved verison
    {
        if(fItem->scene())
            fScene->removeItem(fItem);
    }
    if(masters.empty() && !fItem->scene())
    {
        fScene->addItem(fItem);
        fItem->setParentItem(fParent);
    }
    fNbMasters = (unsigned int)masters.size(); // finally we update the number of masters
}


//------------------------------------------------------------------------------------------------------------
//											Conversion methods
//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::referenceRect(QGraphicsItem * specItem) const
{
    if(specItem)
        return specItem->parentItem() ? specItem->parentItem()->boundingRect() : fScene->sceneRect();
    else
    {
        if (fParent)
        {
            float l = std::min(fParent->boundingRect().width(), fParent->boundingRect().height());
			float left = fParent->boundingRect().center().x() - l/2;
            float top = fParent->boundingRect().center().y() - l/2;
            QRectF rect ( left, top, l, l);
            return rect;
        }
        else {
           return fScene->sceneRect();
		}
    }
}

//------------------------------------------------------------------------------------------------------------
float VGraphicsItemView::relative2SceneX(float x, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	// inscore graphic space is between -1 and 1
	return (( x + 1 ) * refRect.width()) / 2.0f + refRect.x();
}

//------------------------------------------------------------------------------------------------------------
float VGraphicsItemView::relative2SceneY(float y, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	// inscore graphic space is between -1 and 1
	return (( y + 1 ) *  refRect.height()) / 2.0f  + refRect.y();
}

//--------------------------------------------------------------------------
float VGraphicsItemView::relative2SceneWidth(float width, QGraphicsItem * specItem) const
{
	return (referenceRect(specItem).width() * width)/2.0f;
}

//--------------------------------------------------------------------------
float VGraphicsItemView::relative2SceneHeight(float height, QGraphicsItem * specItem) const
{
	return (referenceRect(specItem).height() * height)/2.0f;
}

//--------------------------------------------------------------------------
float VGraphicsItemView::scene2RelativeWidth(float width, QGraphicsItem * specItem) const
{
	return 2.0f * width / referenceRect(specItem).width();
}

//--------------------------------------------------------------------------
float VGraphicsItemView::scene2RelativeHeight(float height, QGraphicsItem * specItem) const
{
	return 2.0f * height / referenceRect(specItem).height();
}

//------------------------------------------------------------------------------------------------------------
float VGraphicsItemView::scene2RelativeX(float x, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	return ( x - refRect.x() ) / ( refRect.width() / 2.0f ) - 1 ;
}

//------------------------------------------------------------------------------------------------------------
float VGraphicsItemView::scene2RelativeY(float y, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	return ( y - refRect.y() ) / ( refRect.height() / 2.0f ) - 1 ;
}

//------------------------------------------------------------------------------------------------------------
TFloatPoint VGraphicsItemView::qGraphicsItem2IObject(const QPointF& point) const
{
	return qGraphicsItem2IObject( point , item()->boundingRect() );
}

//------------------------------------------------------------------------------------------------------------
TFloatPoint VGraphicsItemView::qGraphicsItem2IObject(const QPointF& point, const QRectF& rect) const
{
	double x = (point.x() - rect.x()) / (rect.width()/2.0f) - 1;
	double y = (point.y() - rect.y()) / (rect.height()/2.0f) - 1;
	return TFloatPoint(x,y);
}

//------------------------------------------------------------------------------------------------------------
QPointF VGraphicsItemView::iObject2QGraphicsItem(const TFloatPoint& point) const
{
	return iObject2QGraphicsItem(point, item()->boundingRect());
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const TFloatRect& rect) const
{
	return iObject2QGraphicsItem(rect, item()->boundingRect());
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const GraphicSegment& s) const
{
	TFloatRect r ( TFloatPoint(s.left(), s.top()), TFloatPoint(s.right(), s.bottom()) );
	return iObject2QGraphicsItem( r );
}

//------------------------------------------------------------------------------------------------------------
QPointF VGraphicsItemView::iObject2QGraphicsItem(const TFloatPoint& point, const QRectF& qrect) const
{
	double x = (( point.x() + 1 ) * qrect.width())  / 2.0f + qrect.x();
	double y = (( point.y() + 1 ) * qrect.height()) / 2.0f + qrect.y();
	return QPointF( x,y );
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const GraphicSegment& s, const QRectF& qrect) const
{
	QPointF a = iObject2QGraphicsItem(TFloatPoint(s.xinterval().first(), s.yinterval().first()), qrect);
	QPointF b = iObject2QGraphicsItem(TFloatPoint(s.xinterval().second(), s.yinterval().second()), qrect);
	return QRectF( a.x() , a.y() , b.x() - a.x() , b.y() - a.y() );
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const TFloatRect& rect, const QRectF& qrect) const
{
	QPointF a = iObject2QGraphicsItem(rect.pos(), qrect);
	QPointF b = iObject2QGraphicsItem(rect.brpos(), qrect);
	return QRectF( a.x() , a.y() , b.x() - a.x() , b.y() - a.y() );
}

} // end namespoace
