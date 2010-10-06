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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include "VMappedShapeView.h"

#include "TVirtualRelation.h"

namespace interlude
{

//----------------------------------------------------------------------
void VMappedShapeView::updateGraphic2GraphicMapping (IShapeMap* object)
{
	// Update mapping
	TLocalMapping<GraphicSegment>::const_iterator i = object->localMappings()->namedMappings().begin();
	
	for ( ; i != object->localMappings()->namedMappings().end() ; i++ )
	{
		const SGraphic2RelativeTimeMapping & l2t_mapping = i->second.fLocal2Time;
		Graphic2RelativeTimeRelation::const_iterator iter = l2t_mapping->direct().begin();
		
		SGraphic2GraphicMapping g2l_mapping = TMapping<GraphicSegment,GraphicSegment>::create();	// Create the local -> graphic mapping.
																									// (which is here a 'graphic -> graphic' identity mapping)
		SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment(-1,-1,1,1) );	// Create the graphic segmentation.
		
		while (iter != l2t_mapping->direct().end()) {
			g2l_mapping->add ( iter->first , iter->first);			// Identity mapping.
			graphicSegmentation->add( iter->first );				// Also fill the graphic segmentation.
			iter++;
		}
		object->localMappings()->setMapping( i->first , g2l_mapping , l2t_mapping );	// Finally, affect the mapping to object.
		object->setGraphicSegmentation( i->first , graphicSegmentation );				// Also affect the graphic segmentation.
		
		VGraphicsItemView::setMapping<GraphicSegment>( object , i->first , g2l_mapping , l2t_mapping );
	}
	
	VGraphicsItemView::buildDefaultMapping(object);
}

} // end namespoace
