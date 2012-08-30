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

#ifndef __mapreader__
#define __mapreader__

#include <iostream>
#include "TSegment.h"
#include "rational.h"

namespace libmapping 
{

/*!
\addtogroup PARSER Parsing
@{
*/

//______________________________________________________________________________
/*!
\brief	An abstract class for building relations.

The mapreader interface is intended to be used by the mapparser.
*/
class mapreader
{
	public:
		virtual ~mapreader() {}

		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param gsegm an int-point segment
			\param rtsegm a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					an absolute to relative time to relation should return false.
		*/
		virtual bool map(const TSegment<long,2>& gsegm, const TSegment<rational,1>& rtsegm) = 0;

		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param gsegm a graphic segment
			\param rtsegm a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					an absolute to relative time to relation should return false.
		*/
		virtual bool map(const TSegment<float,2>& gsegm, const TSegment<rational,1>& rtsegm) = 0;
		
		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param f an absolute segment expressed in frames
			\param r a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					a graphic to relative time to relation should return false.
		*/
		virtual bool map(const TSegment<long,1>& f, const TSegment<rational,1>& r) = 0;

		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param f an absolute segment expressed in floats
			\param r a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					a graphic to relative time to relation should return false.
		*/
		virtual bool map(const TSegment<float,1>& f, const TSegment<rational,1>& r) = 0;
		
		virtual void error(const char * msg, int lineno) = 0;	///< error management

		virtual const char* maperror() { return ""; }			///< incorrect map type handler
};

/*! @} */

} // namespace

#endif
