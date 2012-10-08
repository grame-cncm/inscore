/*
  Interlude Library
  Copyright (C) 2009,2012  Grame

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

#ifndef __imapreader__
#define __imapreader__

#include <istream>

#include "ITLError.h"

#include "mapparser.h"
#include "mapreader.h"

namespace inscore 
{

//______________________________________________________________________________
/*!
	\brief	A class to read a mapping from a stream
	
	imapreader decorates libmapping::mapreader to redirect error messages	
*/
class imapreader : public libmapping::mapparser, libmapping::mapreader
{	
	libmapping::mapreader* fReader;
	public:
				 imapreader(libmapping::mapreader* reader, std::istream* s) : libmapping::mapparser(this, s), fReader(reader) {}
		virtual ~imapreader() {}

		bool map(const libmapping::TSegment<long,2>& gsegm, const libmapping::TSegment<libmapping::rational,1>& r)	{ return fReader->map(gsegm, r); }
		bool map(const libmapping::TSegment<float,2>& gsegm, const libmapping::TSegment<libmapping::rational,1>& r)	{ return fReader->map(gsegm, r); }
		bool map(const libmapping::TSegment<long,1>& f, const libmapping::TSegment<libmapping::rational,1>& r)		{ return fReader->map(f, r); }
		bool map(const libmapping::TSegment<float,1>& f, const libmapping::TSegment<libmapping::rational,1>& r)		{ return fReader->map(f, r); }

		/// error management
		void error(const char * msg, int lineno)				{ ITLErr << "parse error line " << lineno << ": " << msg << ITLEndl; }
};

} // namespace

#endif
