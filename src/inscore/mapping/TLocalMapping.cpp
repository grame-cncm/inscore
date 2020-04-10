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


#include "TMapping.h"
#include "TLocalMapping.h"
#include "IObject.h"
#include "IShapeMap.h"
#include "rational.h"

using namespace libmapping;


namespace inscore {

//------------------------------------------------------------------------------------------------------------
// check if automatic mapping (build from object duration) needs to be refreshed
//------------------------------------------------------------------------------------------------------------
static bool checkAutoRefresh (IObject* object, const RelativeTime2GraphicRelation& )
{
	return object->fAutoMap && object->durationModified();
}

//------------------------------------------------------------------------------------------------------------
void TDefaultLocalMapping::buildDefaultMapping (IObject* object)
{
	const SRelativeTime2GraphicMapping& map = object->getMapping("");
	// Check if the un-named mapping exists or if it needs to be refreshed.
	if ( !map ||  checkAutoRefresh(object, map->direct())) {

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

} // end namespace

