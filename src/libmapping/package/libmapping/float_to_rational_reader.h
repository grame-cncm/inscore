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

#ifndef __float_to_rational_reader__
#define __float_to_rational_reader__

#include "basicmapreader.h"
#include "TMapping.h"
#include "TSegmentation.h"

namespace libmapping 
{

/*!
\addtogroup PARSER Parsing
@{
*/

//______________________________________________________________________________
/*!
\brief	a reader for float to rational mapping 
*/
class float_to_rational_reader : public basicmapreader
{
	SMARTP<TMapping<float, 1, rational, 1> > fMapping;		
	public:
				 float_to_rational_reader() : basicmapreader("float to rational") { fMapping = TMapping<float, 1, rational, 1>::create(); }

		bool map(const TSegment<float,1>& s1, const TSegment<rational,1>& s2)		{ fMapping->add(s1, s2); return true; }
		SMARTP<TMapping<float, 1, rational, 1> > mapping ()							{ return fMapping; }
};

/*! @} */

} // namespace

#endif
