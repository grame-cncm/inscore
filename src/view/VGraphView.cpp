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

#define newVersion 1

#include "VGraphView.h"
#include "maptypes.h"
#include "ITLError.h"

#include "IGraphicSignal.h"
#include "ISignalProfiler.h"

using namespace std;
using namespace libmapping;

namespace inscore
{


//----------------------------------------------------------------------
VSGraphView::VSGraphView(QGraphicsScene * scene, const IGraphicSignal* h) 
	: VGraphView( scene , h, new MouseEventAble<QGraphicsGraphItemNew>(h) )
    {}

void VSGraphView::updateView( IGraphicSignal * graph )
{
    graph->cleanupSync();
    if(!graph->getParent()->getMaster(graph) && !graph->getParent()->getDeleted())
    {
        if(graph->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(graph->getParent()->getView()?graph->getParent()->getView():0);
    }
	item()->setSignal( graph->getSignal() );
	item()->setRect( QRect( 0,0,  relative2SceneWidth(graph->getWidth()),relative2SceneHeight(graph->getHeight()) ) );
	VShapeView::updateView( graph );
	itemChanged();
}

//----------------------------------------------------------------------
VGraphView::VGraphView(QGraphicsScene * scene, const IGraphicSignal* h) 
	: VShapeView( scene , new MouseEventAble<QGraphicsGraphItem>(h) )
    {}

VGraphView::VGraphView(QGraphicsScene * scene, const IGraphicSignal* h, QAbstractGraphicsShapeItem * item) 
	: VShapeView( scene , item ) {}

void VGraphView::updateView( IGraphicSignal * graph )
{
    graph->cleanupSync();
    if(!graph->getParent()->getMaster(graph) && !graph->getParent()->getDeleted())
    {
        if(graph->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(graph->getParent()->getView()?graph->getParent()->getView():0);
    }
	item()->setRect( QRect( 0,0,  relative2SceneWidth(graph->getWidth()),relative2SceneHeight(graph->getHeight()) ) );
	float alpha = graph->getA() / 255.f;
	item()->setOpacity (alpha);

	int size = graph->getSignal()->ParallelSignal::size();

	// set the rendering engine settings
	item()->setSize( size );
	item()->setDefaultFillColor( QColor(graph->getR(), graph->getG(), graph->getB() , graph->getA()) );
	item()->setDefaultPenColor( QColor(graph->getPenColor().getR(), graph->getPenColor().getG(), graph->getPenColor().getB() , graph->getPenColor().getA()) );

	item()->clear();						// clear the engine data
	for ( int i = 0 ; i < size ; i++ )
		(*item()) << ( graph->getGraphicFrames(i) );		// fill the engine data
	int d;
	for ( d = 0 ; d < graph->getSignal()->dimension() ; d++ )	// for each graphic signal
	{
		// check for optimization when one of the graphic signal is constant
		item()->notifyConst( d/6 , d%6 , graph->getSignal()->signal( d )->isConst() );
	}
	if ( d%6 )	// For uncomplete signals (some of the 6 components don't exist), missing components are const.
		while ( d%6 )
		{
			item()->notifyConst( d/6 , d%6 , true );
			d++;
		}

	VShapeView::updateView( graph );
	itemChanged();
}

//----------------------------------------------------------------------
void VGraphView::updateLocalMapping (IGraphicSignal* object)
{
	// Update mapping
	TLocalMapping<long,1>::const_iterator i = object->localMappings()->namedMappings().begin();
	
	for ( ; i != object->localMappings()->namedMappings().end() ; i++ )	// For each local->time named mapping
	{
		SGraphic2FrameMapping g2l_mapping = TMapping<float,2,long,1>::create();	// Build a Graphic -> local mapping.
		SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment( -1 , -1 , 1 , 1 ) );
			
		const SFrame2RelativeTimeMapping & l2t_mapping = i->second;	// Get the 'local -> time' mapping.
		TRelation<long,1,rational,1>::const_iterator iter = l2t_mapping->direct().begin();	
		while (iter != l2t_mapping->direct().end()) {	// Parse each 'local' element of the 'local -> time' mapping.
			bool ok;
			GraphicSegment gs = getGraphicSegment( iter->first , object , ok );	// Asks the view object to find the GraphicSegment corresponding to the
																				// local segment.
			if ( ok )
			{
				g2l_mapping->add ( gs , iter->first);	// Put the 'graphic -> local' relation into the mapping.
				graphicSegmentation->add( gs );					// Put the graphic segment in the graphicSegmentation.
			}

			iter++;
		}
//		object->localMappings()->setMapping( i->first , g2l_mapping , l2t_mapping );
		object->localMappings()->setMapping( i->first, l2t_mapping );
		VGraphicsItemView::setMapping<long,1>( object , i->first , g2l_mapping , l2t_mapping );
	}
	VGraphicsItemView::buildDefaultMapping( object );
}

// Computes the GraphicSegment corresponding to the frameSegment of the signal.
// This is a simple interpolation between [ 0 , signal size ] -> [ -1 , 1 ] on the x axis. 
// The y interval of the GraphicSegment is always [-1,1].
//
//	Note that it only uses the IGraphicSignal model object. The Qt object 'QGraphicsGraphItem' is not used in the process.
//----------------------------------------------------------------------
GraphicSegment VGraphView::getGraphicSegment( const FrameSegment& frameSegment , const IGraphicSignal * graph , bool& mapOk ) const
{
	int signalSize = graph->getSignal()->ParallelSignal::size();
	if ( frameSegment.start() < 0 )
	{
		ITLErr << "frame mapping of object" << graph->getOSCAddress() << "refers to 'out of bounds' (< 0) frame:" << frameSegment.start() << ITLEndl;
		mapOk = false;
		return GraphicSegment();
	}		
	if ( frameSegment.end() > signalSize )
	{
		ITLErr << "frame mapping of object" << graph->getOSCAddress() << "refers to 'out of bounds' (> signal size) frame:" << frameSegment.end()
		<< "(note: signal size =" << signalSize << ")" << ITLEndl;
		mapOk = false;
		return GraphicSegment();
	}
	mapOk = true;
	
	float startX = 2 * frameSegment.start() / float(signalSize) - 1.0f;
	float endX   = 2 * frameSegment.end()   / float(signalSize) - 1.0f;
	return GraphicSegment( startX , -1 , endX , 1 );
}


} // end namespoace
