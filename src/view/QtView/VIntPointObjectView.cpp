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

#include "VIntPointObjectView.h"

#include "IGraphicBasedObject.h"
#include "maptypes.h"
#include "TLocalMapping.h"

using namespace libmapping;

namespace inscore
{
//-------------------------------------------------------------------------
void VIntPointObjectView::updateLocalMapping (IGraphicBasedObject* object)
{
	for ( auto named: object->localMappings()->namedMappings() ) {
		SGraphic2IntPointMapping g2l_mapping = TMapping<float,2, long,2>::create();	// Build a Graphic -> local mapping.
		SGraphicSegmentation graphicSegmentation = GraphicSegmentation::create( GraphicSegment( -1 , -1 , 1 , 1 ) );

		const SIntPoint2RelativeTimeMapping & l2t_mapping = named.second;	// Get the 'local -> time' mapping.
		TRelation<long,2, rational,1>::const_iterator iter = l2t_mapping->direct().begin();
		for (auto direct: l2t_mapping->direct()) {							// Parse each 'local' element of the 'local -> time' mapping.
			bool ok;
			GraphicSegment gs = getGraphicSegment( direct.first, object, ok );	// Asks the view object to find the GraphicSegment corresponding to the
																				// local segment.
			if ( ok ) {
				g2l_mapping->add ( gs, direct.first);							// add the 'graphic -> local' relation into the mapping.
				graphicSegmentation->add( gs );
			}
		}
		object->localMappings()->setMapping( named.first, l2t_mapping );
		VGraphicsItemView::setMapping<long,2>( object , named.first , g2l_mapping , l2t_mapping );
	}
	TDefaultLocalMapping::buildDefaultMapping( object );
}

} // end namespoace
