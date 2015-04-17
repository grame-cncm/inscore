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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __testreader__
#define __testreader__

#include <iostream>
#include "../mapreader.h"

namespace libmapping 
{

//______________________________________________________________________________
class testreader : public mapreader
{
	public:
		virtual ~testreader() {}

		virtual bool map(const TSegment<long,2>& s1, const TSegment<rational,1>& s2) 
			{ std::cout << "map <long,2>: " << s1 << " to " << s2 << std::endl; return true; }

		virtual bool map(const TSegment<float,2>& s1, const TSegment<rational,1>& s2) 
			{ std::cout << "map <float,2>: " << s1 << " to " << s2 << std::endl; return true; }

		virtual bool map(const TSegment<long,1>& s1, const TSegment<rational,1>& s2) 
			{ std::cout << "map <long,1>: " << s1 << " to " << s2 << std::endl; return true; }

		virtual bool map(const TSegment<float,1>& s1, const TSegment<rational,1>& s2) 
			{ std::cout << "map <float,1: " << s1 << " to " << s2 << std::endl; return true; }
		
		virtual void error(const char * msg, int lineno)  
			{ std::cerr << "error line: " << lineno << " : " << msg << std::endl; }
};

} // namespace

#endif
