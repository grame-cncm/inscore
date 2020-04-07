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

#include "IShapeMap.h"
#include "TMapMsgHandler.h"
#include "TMapping.h"

namespace inscore
{

//--------------------------------------------------------------------------
IShapeMap::IShapeMap( const std::string& name, IObject* parent ) : IObject(name,parent)
{
	fLocalMappings = TLocalMapping<float,2>::create();

	fMsgHandlerMap[kmap_GetSetMethod]		= TMethodMsgHandler<IShapeMap>::create(this, &IShapeMap::mapMsg);
	fMsgHandlerMap[kmapplus_SetMethod]		= TMethodMsgHandler<IShapeMap>::create(this, &IShapeMap::mapAddMsg);
	fMsgHandlerMap[kmapf_SetMethod]			= TMethodMsgHandler<IShapeMap>::create(this, &IShapeMap::mapFileMsg);
}

//--------------------------------------------------------------------------
SIMessageList IShapeMap::__getMaps () const
{
	return TMapMsgHandler<float,2>::getMapMsgs( localMappings() , this );
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IShapeMap::mapFileMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<float,2>::mapFileMsg( msg , localMappings() , this );
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IShapeMap::mapMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<float,2>::mapMsg( msg , localMappings() , this); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IShapeMap::mapAddMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<float,2>::addMapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
//void IShapeMap::updateGraphic2GraphicMapping ()
//{
//	for (auto map: localMappings()->namedMappings()) {
//		const SGraphic2RelativeTimeMapping & local2time = map.second;
//		SGraphic2GraphicMapping g2l = libmapping::TMapping<float,2, float,2>::create();	// Create the local -> graphic mapping.
//																					// (which is here a 'graphic -> graphic' identity mapping)
//		for (auto rel: local2time->direct()) {
//			g2l->add ( rel.first , rel.first);			// Identity mapping.
//		}
//		localMappings()->setMapping( map.first, local2time );	// Finally, affect the mapping to object.
//		setLocalMapping<float,2> (map.first, g2l, local2time );
////		VGraphicsItemView::setMapping<float,2>( object , i->first , g2l_mapping , local2time_mapping );
//	}
//	TDefaultLocalMapping::buildDefaultMapping(object);
//}

void IShapeMap::updateGraphic2GraphicMapping ()
{
	TLocalMapping<float,2>::const_iterator i = localMappings()->namedMappings().begin();

	for ( ; i != localMappings()->namedMappings().end() ; i++ )
	{
		const SGraphic2RelativeTimeMapping & local2time_mapping = i->second;
		Graphic2RelativeTimeRelation::const_iterator iter = local2time_mapping->direct().begin();

		SGraphic2GraphicMapping g2l_mapping = libmapping::TMapping<float,2, float,2>::create();	// Create the local -> graphic mapping.
																					// (which is here a 'graphic -> graphic' identity mapping)
		while (iter != local2time_mapping->direct().end()) {
			g2l_mapping->add ( iter->first , iter->first);			// Identity mapping.
			iter++;
		}
		localMappings()->setMapping( i->first, local2time_mapping );	// Finally, affect the mapping to object.
//		VGraphicsItemView::setMapping<float,2>( this , i->first , g2l_mapping , local2time_mapping );
		setLocalMapping<float,2>(i->first, g2l_mapping, local2time_mapping );
	}
	TDefaultLocalMapping::buildDefaultMapping(this);
}

// Update mapping - implementation from VMappedShapeView
//TLocalMapping<float,2>::const_iterator i = object->localMappings()->namedMappings().begin();
//
//for ( ; i != object->localMappings()->namedMappings().end() ; i++ )
//{
//	const SGraphic2RelativeTimeMapping & local2time_mapping = i->second;
//	Graphic2RelativeTimeRelation::const_iterator iter = local2time_mapping->direct().begin();
//
//	SGraphic2GraphicMapping g2l_mapping = TMapping<float,2, float,2>::create();	// Create the local -> graphic mapping.
//																				// (which is here a 'graphic -> graphic' identity mapping)
//
//	while (iter != local2time_mapping->direct().end()) {
//		g2l_mapping->add ( iter->first , iter->first);			// Identity mapping.
//		iter++;
//	}
//	object->localMappings()->setMapping( i->first, local2time_mapping );	// Finally, affect the mapping to object.
//	VGraphicsItemView::setMapping<float,2>( object , i->first , g2l_mapping , local2time_mapping );
//}
//TDefaultLocalMapping::buildDefaultMapping(object);

} // end namespoace

