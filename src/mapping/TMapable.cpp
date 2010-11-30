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

#include "TMapable.h"
#include "TSegment.h"
#include "TSegmentation.h"

using namespace std;

namespace inscore {

//______________________________________________________________________________
TMapable::MapSet* TMapable::find (const std::string& name)
{
	iterator found = fMappings.find(name);
	return (found == fMappings.end()) ? 0 : &(found->second);
}

const TMapable::MapSet* TMapable::find (const std::string& name) const
{
	const_iterator found = fMappings.find(name);
	return (found == fMappings.end()) ? 0 : &(found->second);
}

//______________________________________________________________________________
const SRelativeTime2GraphicMapping& TMapable::getMapping(const std::string& name) const
{
	const MapSet* m = find (name);
	return m ? m->fTime2Graphic : fNullSet.fTime2Graphic;
}

//______________________________________________________________________________
bool TMapable::removeMapping(const std::string& name) 
{ 
	if (name.empty()) fAutoMap = false;
	return fMappings.erase(name)==1; 
}

//______________________________________________________________________________
const SGraphicSegmentation&	TMapable::getGraphicSegmentation(const std::string& name) const
{
	const MapSet* m = find (name);
	return m ? m->fGraphicSegm : fNullSet.fGraphicSegm;
}

//______________________________________________________________________________
const SRelativeTimeSegmentation& TMapable::getTimeSegmentation(const std::string& name) const
{
	const MapSet* m = find (name);
	return m ? m->fTimeSegm : fNullSet.fTimeSegm;
}

//______________________________________________________________________________
void TMapable::setMapping (const std::string& name, SRelativeTime2GraphicMapping m)
{
	MapSet* found = find (name);
	if (!found) {
		MapSet s;
		s.fTime2Graphic = m;
		fMappings[name] = s; 
	}
	else
	{
		found->fTime2Graphic = m;
	}
}

//______________________________________________________________________________
void TMapable::setMapping (const std::string& name, SRelativeTime2GraphicMapping m, SRelativeTimeSegmentation st, SGraphicSegmentation sg)
{
	setMapping (name, m);
	setTimeSegmentation (name, st);
	setGraphicSegmentation (name, sg);
}

//______________________________________________________________________________
void TMapable::setTimeSegmentation	(const std::string& name, SRelativeTimeSegmentation s)
{
	MapSet* found = find (name);
	if (!found) {
		MapSet set;
		set.fTimeSegm = s;
		fMappings[name] = set; 
	}
	else found->fTimeSegm = s;
}

//______________________________________________________________________________
void TMapable::setGraphicSegmentation (const std::string& name, SGraphicSegmentation s)
{
	MapSet* found = find (name);
	if (!found) {
		MapSet set;
		set.fGraphicSegm = s;
		fMappings[name] = set; 
	}
	else found->fGraphicSegm = s;
}

}
