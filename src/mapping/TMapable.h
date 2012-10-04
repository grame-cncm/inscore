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


#ifndef __TMapable__
#define __TMapable__

#include <map>
#include <string>

//#include "libmapping/maptypes.h"
#include "maptypes.h"
#include "TMapping.h"

namespace inscore {

/*!
\addtogroup ITLMapping
@{
*/

/*!
	\brief a map-able object is an object that provides a mapping from relative time
	to graphic space
*/
class TMapable
{
	public:
		typedef std::map<std::string, SRelativeTime2GraphicMapping> namedMapping;	
		typedef std::map<std::string, SRelativeTime2GraphicMapping>::const_iterator	const_iterator;
		typedef std::map<std::string, SRelativeTime2GraphicMapping>::iterator		iterator;

	private:
	
	const SRelativeTime2GraphicMapping find (const std::string& name) const;
		  SRelativeTime2GraphicMapping find (const std::string& name);

	namedMapping					fMappings;					// intended to support different named mappings
	bool							fUseMapping;
	bool							fLocalMapModified;	
	SGraphic2GraphicMapping			fSlave2Master;
	
	public:
		bool fAutoMap;											// a flag to indicate mappings automatically build from object duration

				 TMapable() : fUseMapping(false), fLocalMapModified(false), fAutoMap(false) {}
		virtual ~TMapable() {}
		
		const SRelativeTime2GraphicMapping  getMapping(const std::string& name) const	{ return find (name); }

		const SGraphic2GraphicMapping&		getSlave2MasterMapping() const		{ return fSlave2Master; }		
		const namedMapping& namedMappings() const								{ return fMappings; }

		bool removeMapping(const std::string& name);			// Returns true if the specified 'name' has been found and removed.
		void setMapping				(const std::string& name, SRelativeTime2GraphicMapping m)	{ fMappings[name] = m; }
		void setSlave2MasterMapping (const SGraphic2GraphicMapping& map)						{ fSlave2Master = map; }
		
		void	UseGraphic2GraphicMapping (bool val)		{ fUseMapping = val; }
		bool	UseGraphic2GraphicMapping () const			{ return fUseMapping; }
		void	localMapModified (bool val)					{ fLocalMapModified = val; }
		bool	localMapModified () const					{ return fLocalMapModified; }
};

/*! @} */

}

#endif
