/*
  Interlude Library
  Copyright (C) 2009  Grame

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

#include <algorithm>
#include "relativetimereader.h"

using namespace std;

namespace interlude 
{

//______________________________________________________________________________
bool relativetimereader::initialize () 
{
	fRelTimeSegments.clear();
	fRelTimeSegmentation = 0;
	return true;
}

//______________________________________________________________________________
int relativetimereader::getSegments(const set<RelativeTimeSegment>& s, relTimeSegmentsList& v) const
{
	for (set<RelativeTimeSegment>::const_iterator i = s.begin(); i != s.end(); i++)
		v.insert(*i);
	return v.size();
}

//______________________________________________________________________________
SRelativeTimeSegmentation relativetimereader::getRelativeTimeSegmentation()
{
	if (!fRelTimeSegmentation) {
		relTimeSegmentsList v;
		int n = getSegments (fRelTimeSegments, v);
		if (n) {
			relTimeSegmentsList::const_iterator first = v.begin();
			relTimeSegmentsList::const_iterator last = --v.end();
			RelativeTimeSegment resource(first->start(), last->end());
			fRelTimeSegmentation = RelativeTimeSegmentation::create(resource);
			if (fRelTimeSegmentation) fRelTimeSegmentation->add(v);
		}
	}
	return fRelTimeSegmentation;
}

} // namespace
