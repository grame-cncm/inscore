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

#ifndef __mapreader__
#define __mapreader__

#include <iostream>
#include "TSegment.h"
#include "maptypes.h"

namespace interlude 
{

//______________________________________________________________________________
/*!
\brief	An abstract class supporting the parser interface.
*/
class mapreader
{
	const char * fFileName;
	
	public:
		virtual ~mapreader() {}

		/*! \brief virtual initialization method 
		
			It is called by the \c read and \c readfile methods before parsing a mapping.
			\return true in case of success
		*/
		virtual bool initialize () = 0;

		/*! \brief reads a mapping from a string
			\param map the mapping string
			\return true in case of success
		*/
		virtual bool read (const std::string& map);

		/*! \brief reads a mapping from a file
			\param mapfile the mapping file path name
			\return true in case of success
		*/
		virtual bool readfile (const std::string& mapfile);

		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param gsegm an int-point segment
			\param rtsegm a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					an absolute to relative time to relation should return false.
		*/
		virtual bool map(const IntPointSegment& gsegm, const RelativeTimeSegment& rtsegm) = 0;

		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param gsegm a graphic segment
			\param rtsegm a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					an absolute to relative time to relation should return false.
		*/
		virtual bool map(const GraphicSegment& gsegm, const RelativeTimeSegment& rtsegm) = 0;
		
		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param f an absolute segment expressed in frames
			\param r a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					a graphic to relative time to relation should return false.
		*/
		virtual bool map(const FrameSegment& f, const RelativeTimeSegment& r) = 0;

		/*! \brief virtual method called by the parser.
		
			The map method is called for each segments pair part of a relation.
			\param f an absolute segment expressed in floats
			\param r a relative time segment
			\return a boolean value, it should be used to tell the parser that an 
					unexpected relation has been encountered e.g. a reader expecting
					a graphic to relative time to relation should return false.
		*/
		virtual bool map(const FloatSegment& f, const RelativeTimeSegment& r) = 0;
		
		virtual int error(const char * msg, int lineno);
};

} // namespace

#endif
