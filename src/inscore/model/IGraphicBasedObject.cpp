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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <sstream>

#include "IAppl.h"
#include "IGraphicBasedObject.h"
#include "IMessage.h"
#include "TComposition.h"
#include "Updater.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
IGraphicBasedObject::IGraphicBasedObject( const std::string& name, IObject * parent )
	: IObject(name, parent) 
{ 
	fLocalMappings = TLocalMapping<long,2>::create();

	fMsgHandlerMap[kmap_GetSetMethod]		= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapMsg);
	fMsgHandlerMap[kmapplus_SetMethod]		= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapAddMsg);
	fMsgHandlerMap[kmapf_SetMethod]			= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapFileMsg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapFileMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,2>::mapFileMsg( msg , localMappings() , this );
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapAddMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,2>::addMapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,2>::mapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//-------------------------------------------------------------------------
void IGraphicBasedObject::setBoundingRect(long x, long y, long w, long h)
{
	fBoundingRect.setX(x);
	fBoundingRect.setY(y);
	fBoundingRect.setWidth(w);
	fBoundingRect.setHeight(h);
}

//------------------------------------------------------------------------------------------------------------
TFloatPoint IGraphicBasedObject::view2ItemPoint(const TLongPoint& point) const
{
	if (!fBoundingRect.width() || !fBoundingRect.height()) return TFloatPoint(0,0);
	double x = (point.x() - fBoundingRect.x()) / (fBoundingRect.width()/2.0f) - 1;
	double y = (point.y() - fBoundingRect.y()) / (fBoundingRect.height()/2.0f) - 1;
	return TFloatPoint(x,y);
}


//-------------------------------------------------------------------------
//GraphicSegment IGraphicBasedObject::getGraphicSegment( const IntPointSegment& segment, bool& mapOk ) const
bool IGraphicBasedObject::getGraphicSegment( const IntPointSegment& segment, GraphicSegment& outSegment ) const
{
	const char* msg1 = "pixel mapping of object";
	const char* msg2 = "refers to 'out of bounds' position:";
	TLongPoint pa (segment.xinterval().first(),  segment.yinterval().first());
	TLongPoint pb (segment.xinterval().second(), segment.yinterval().second());
	
	if ( (pa.y() >= fBoundingRect.height()) || (pa.x() >= fBoundingRect.width()) ) {
		ITLErr << msg1 << getOSCAddress() << msg2 << "[" << pa.x() << ";" << pa.y() << "]" << ITLEndl;
		return false;
	}
	if ( (pb.y() >= fBoundingRect.height()) || (pb.x() > fBoundingRect.width()) ) {
		ITLErr << msg1 << getOSCAddress() << msg2 << "[" << pb.x() << ";" << pb.y() << "]" << ITLEndl;
		return false;
	}
	TFloatPoint startPoint = view2ItemPoint( pa );
	TFloatPoint endPoint   = view2ItemPoint( pb );	
	outSegment = GraphicSegment( startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y() );
	return true;
}

// VImageView implementation
//{
//	TLongPoint intPointA (intPointSegment.xinterval().first(), intPointSegment.yinterval().first());
//	TLongPoint intPointB (intPointSegment.xinterval().second(), intPointSegment.yinterval().second());
//
//	TLongPoint errPoint;
//	mapOk=true;
//	if ( (intPointA.y() >= fImageItem->image().height()) || (intPointA.x() >= fImageItem->image().width()) )
//	{
//		errPoint = intPointA;
//		mapOk = false;
//	}
//	if ( (intPointB.y() >= fImageItem->image().height()) || (intPointB.x() > fImageItem->image().width()) )
//	{
//		errPoint = intPointB;
//		mapOk = false;
//	}
//	if ( !mapOk )
//	{
//		const char* msg1 = "pixel mapping of object";
//		const char* msg2 = "refers to 'out of bounds' position:";
//		ITLErr << msg1 << object->getOSCAddress() << msg2 << "[" << errPoint.x() << ";" << errPoint.y() << "]" << ITLEndl;
//		return GraphicSegment();
//	}
//	TFloatPoint startPoint = qGraphicsItem2IObject( longPointToQPoint(intPointA) , fImageItem->boundingRect() );
//	TFloatPoint endPoint = qGraphicsItem2IObject( longPointToQPoint(intPointB) , fImageItem->boundingRect() );
//
//	return GraphicSegment( startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y() );
//}

//-------------------------------------------------------------------------
void IGraphicBasedObject::updateLocalMapping ()
{
	// Update mapping
	TLocalMapping<long,2>::const_iterator i = localMappings()->namedMappings().begin();
	
	for ( ; i != localMappings()->namedMappings().end() ; i++ )
	{
		SGraphic2IntPointMapping g2l_mapping = TMapping<float,2, long,2>::create();	// Build a Graphic -> local mapping.
		SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment( -1 , -1 , 1 , 1 ) );

		const SIntPoint2RelativeTimeMapping & l2t_mapping = i->second;	// Get the 'local -> time' mapping.
		TRelation<long,2, rational,1>::const_iterator iter = l2t_mapping->direct().begin();
		while (iter != l2t_mapping->direct().end()) {					// Parse each 'local' element of the 'local -> time' mapping.
			bool ok;
			GraphicSegment gs;
			if ( getGraphicSegment( iter->first, gs ) ) {				// find the GraphicSegment corresponding to the local segment.
				g2l_mapping->add ( gs , iter->first);					// Put the 'graphic -> local' relation into the mapping.
				graphicSegmentation->add( gs );
			}
			iter++;
		}
		localMappings()->setMapping( i->first, l2t_mapping );
		updateMappings<long,2> (i->first , g2l_mapping , l2t_mapping);
	}
	TDefaultLocalMapping::buildDefaultMapping( this );
}

// VIntPointObjectView implementation
//{
//	// Update mapping
//	TLocalMapping<long,2>::const_iterator i = localMappings()->namedMappings().begin();
//
//	for ( ; i != localMappings()->namedMappings().end() ; i++ )
//	{
//		SGraphic2IntPointMapping g2l_mapping = TMapping<float,2, long,2>::create();	// Build a Graphic -> local mapping.
//		SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment( -1 , -1 , 1 , 1 ) );
//
//		const SIntPoint2RelativeTimeMapping & l2t_mapping = i->second;	// Get the 'local -> time' mapping.
//		TRelation<long,2, rational,1>::const_iterator iter = l2t_mapping->direct().begin();
//		while (iter != l2t_mapping->direct().end()) {	// Parse each 'local' element of the 'local -> time' mapping.
//			bool ok;
//			GraphicSegment gs = getGraphicSegment( iter->first , object , ok );	// Asks the view object to find the GraphicSegment corresponding to the
//																				// local segment.
//			if ( ok )
//			{
//				g2l_mapping->add ( gs , iter->first);	// Put the 'graphic -> local' relation into the mapping.
//				graphicSegmentation->add( gs );
//			}
//			iter++;
//		}
//		localMappings()->setMapping( i->first, l2t_mapping );
//		VGraphicsItemView::setMapping<long,2>( object , i->first , g2l_mapping , l2t_mapping );
//	}
//	TDefaultLocalMapping::buildDefaultMapping( object );
//}


//--------------------------------------------------------------------------
void IGraphicBasedObject::accept (Updater* u)
{
	u->updateTo (SIGraphicBasedObject(this));
}

}
