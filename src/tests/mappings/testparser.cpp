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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include "mapparser.h"
#include "mapreader.h"
#include "TSegment.h"
#include "TRect.h"

using namespace std;
using namespace inscore;


class testreader : public interlude::mapreader
{ 
	public:
		virtual bool initialize () { return true; }
		virtual bool map(const IntPointSegment& s1, const RelativeTimeSegment& s2) 
			{ cout << s1 << " -> " << s2 << endl; return true; }
		virtual bool map(const FrameSegment& s1, const RelativeTimeSegment& s2) 
			{ cout << s1 << " -> " << s2 << endl; return true; }
		virtual bool map(const GraphicSegment& gsegm, const RelativeTimeSegment& rtsegm)
			{ cout << gsegm << " -> " << rtsegm << endl; return true; }
		virtual bool map(const FloatSegment& f, const RelativeTimeSegment& r)
			{ cout << f << " -> " << r << endl; return true; }
		int  error (const char* msg, int lineno) 
			{ 	cerr << msg << " line " << lineno << endl; return 0; }
};

int main (int argc, char * argv[])
{
	if (argc > 1) {
		testreader r;
		mapparser p(&r);
		return p.readfile (argv[1]) ? 0 : 1;
	}
 	return 0;
}

