/*
  Interlude Library
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

#include <algorithm>
#include <iostream>
#include "ITLError.h"
#include "segment2relativetimereader.h"
#include "mapparser.h"
#include "TRect.h"

using namespace std;

namespace interlude 
{

//______________________________________________________________________________
template<> int segment2relativetimereader<IntPointSegment>::getSegments(const set<IntPointSegment>& s, 
		IntPointSegmentation::segmentsList& v) const
{
	for (set<IntPointSegment>::const_iterator i = s.begin(); i != s.end(); i++)
		v.insert(*i);
	return v.size();
}

//______________________________________________________________________________
template<> int segment2relativetimereader<GraphicSegment>::getSegments(const set<GraphicSegment>& s, 
		GraphicSegmentation::segmentsList& v) const
{
	for (set<GraphicSegment>::const_iterator i = s.begin(); i != s.end(); i++)
		v.insert(*i);
	return v.size();
}

//______________________________________________________________________________
template<> int segment2relativetimereader<FloatSegment>::getSegments(const set<FloatSegment>& s, 
		FloatSegmentation::segmentsList& v) const
{
	for (set<FloatSegment>::const_iterator i = s.begin(); i != s.end(); i++)
		v.insert(*i);
	return v.size();
}

//______________________________________________________________________________
template<> int segment2relativetimereader<FrameSegment>::getSegments(const set<FrameSegment>& s, 
		FrameSegmentation::segmentsList& v) const
{
	for (set<FrameSegment>::const_iterator i = s.begin(); i != s.end(); i++)
		v.insert(*i);
	return v.size();
}

//______________________________________________________________________________
// mapreader implementation
//______________________________________________________________________________
template<> bool segment2relativetimereader<IntPointSegment>::map(const IntPointSegment& gs, const RelativeTimeSegment& rs) 
{
	fBaseSegments.insert (gs);
	fRelTimeSegments.insert (rs);
	fMapping->add (gs, rs);
	return true;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<IntPointSegment>::map(const FrameSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected frame to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<IntPointSegment>::map(const GraphicSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected graphic to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<IntPointSegment>::map(const FloatSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected float segment to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
// FrameSegment
//______________________________________________________________________________
template<> bool segment2relativetimereader<FrameSegment>::map(const FrameSegment& ats, const RelativeTimeSegment& rs)
{
	fBaseSegments.insert (ats);
	fRelTimeSegments.insert (rs);
	fMapping->add (ats, rs);
	return true;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<FrameSegment>::map(const IntPointSegment& gs, const RelativeTimeSegment& rs) 
{
	ITLErr << "Unexpected int-point to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<FrameSegment>::map(const GraphicSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected graphic to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<FrameSegment>::map(const FloatSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected float segment to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
// FloatSegment
//______________________________________________________________________________
template<> bool segment2relativetimereader<FloatSegment>::map(const FloatSegment& fs, const RelativeTimeSegment& rs)
{
	fBaseSegments.insert (fs);
	fRelTimeSegments.insert (rs);
	fMapping->add (fs, rs);
	return true;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<FloatSegment>::map(const IntPointSegment& gs, const RelativeTimeSegment& rs) 
{
	ITLErr << "Unexpected IntPointSegment to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<FloatSegment>::map(const FrameSegment& gs, const RelativeTimeSegment& rs) 
{
	ITLErr << "Unexpected FrameSegment to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<FloatSegment>::map(const GraphicSegment& gs, const RelativeTimeSegment& rs) 
{
	ITLErr << "Unexpected GraphicSegment to relative time mapping!" << ITLEndl;
	return false;
}


//______________________________________________________________________________
// GraphicSegment
//______________________________________________________________________________
template<> bool segment2relativetimereader<GraphicSegment>::map(const GraphicSegment& ats, const RelativeTimeSegment& rs)
{
	fBaseSegments.insert (ats);
	fRelTimeSegments.insert (rs);
	fMapping->add (ats, rs);
	return true;
}


//______________________________________________________________________________
template<> bool segment2relativetimereader<GraphicSegment>::map(const IntPointSegment& gs, const RelativeTimeSegment& rs) 
{
	ITLErr << "Unexpected int-point to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<GraphicSegment>::map(const FrameSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected frame to relative time mapping!" << ITLEndl;
	return false;
}

//______________________________________________________________________________
template<> bool segment2relativetimereader<GraphicSegment>::map(const FloatSegment&, const RelativeTimeSegment&)
{
	ITLErr << "Unexpected float segment to relative time mapping!" << ITLEndl;
	return false;
}


} // namespace
