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

#include "VIntPointObjectView.h"

#include "IGraphicBasedObject.h"

#include "maptypes.h"

namespace inscore
{
//-------------------------------------------------------------------------
void VIntPointObjectView::updateLocalMapping (IGraphicBasedObject* object)
{
	// Update mapping
	TLocalMapping<IntPointSegment>::const_iterator i = object->localMappings()->namedMappings().begin();
	
	for ( ; i != object->localMappings()->namedMappings().end() ; i++ )
	{
		SGraphic2IntPointMapping g2l_mapping = TMapping<GraphicSegment,IntPointSegment>::create();	// Build a Graphic -> local mapping.
		SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment( -1 , -1 , 1 , 1 ) );

		const SIntPoint2RelativeTimeMapping & l2t_mapping = i->second.fLocal2Time;	// Get the 'local -> time' mapping.
		TRelation<IntPointSegment,RelativeTimeSegment>::const_iterator iter = l2t_mapping->direct().begin();	
		while (iter != l2t_mapping->direct().end()) {	// Parse each 'local' element of the 'local -> time' mapping.
			bool ok;
			GraphicSegment gs = getGraphicSegment( iter->first , object , ok );	// Asks the view object to find the GraphicSegment corresponding to the
																				// local segment.
			if ( ok )
			{
				g2l_mapping->add ( gs , iter->first);	// Put the 'graphic -> local' relation into the mapping.
				graphicSegmentation->add( gs );
			}

			iter++;
		}
		object->localMappings()->setMapping( i->first , g2l_mapping , l2t_mapping );
		object->setGraphicSegmentation( i->first , graphicSegmentation );

		VGraphicsItemView::setMapping<IntPointSegment>( object , i->first , g2l_mapping , l2t_mapping );		
	}
	VGraphicsItemView::buildDefaultMapping( object );
}


} // end namespoace
