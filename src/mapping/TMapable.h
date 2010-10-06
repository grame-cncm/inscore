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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __TMapable__
#define __TMapable__

#include <map>
#include <string>

#include "maptypes.h"
#include "TMapping.h"

namespace interlude {

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
	
		typedef struct {
			SRelativeTimeSegmentation		fTimeSegm;
			SGraphicSegmentation			fGraphicSegm;
			SRelativeTime2GraphicMapping	fTime2Graphic;
		} MapSet;
		typedef std::map<std::string,MapSet> namedMapping;
		typedef std::map<std::string,MapSet>::const_iterator	const_iterator;
		typedef std::map<std::string,MapSet>::iterator			iterator;

	private:
	
	const MapSet* find (const std::string& name) const;
		  MapSet* find (const std::string& name);

	namedMapping	fMappings;
	MapSet			fNullSet;
	bool			fUseMapping;
	bool			fLocalMapModified;
	
	SGraphic2GraphicMapping fSlave2Master;
	
	public:
		bool fAutoMap;		// a flag to indicate mappings automatically build from object duration

				 TMapable() : fUseMapping(false), fLocalMapModified(false), fAutoMap(false) {}
		virtual ~TMapable() {}
		
		const SRelativeTime2GraphicMapping& getMapping(const std::string& name) const;
		const SGraphicSegmentation&			getGraphicSegmentation(const std::string& name) const;
		const SRelativeTimeSegmentation&	getTimeSegmentation(const std::string& name) const;
		const SGraphic2GraphicMapping&		getSlave2MasterMapping() const		{ return fSlave2Master; }
		
		const namedMapping& namedMappings() const { return fMappings; }

		bool removeMapping(const std::string& name);	/// <brief Returns true if the specified 'name' has been found and removed.

		void setMapping				(const std::string& name, SRelativeTime2GraphicMapping m);
		void setMapping				(const std::string& name, SRelativeTime2GraphicMapping, SRelativeTimeSegmentation, SGraphicSegmentation);
		void setTimeSegmentation	(const std::string& name, SRelativeTimeSegmentation s);
		void setGraphicSegmentation (const std::string& name, SGraphicSegmentation s);

		void setSlave2MasterMapping (const SGraphic2GraphicMapping& map)		{ fSlave2Master = map; }
		
		void	UseGraphic2GraphicMapping (bool val)		{ fUseMapping = val; }
		bool	UseGraphic2GraphicMapping () const			{ return fUseMapping; }
		void	localMapModified (bool val)					{ fLocalMapModified = val; }
		bool	localMapModified () const					{ return fLocalMapModified; }
};

/*! @} */

}

#endif
