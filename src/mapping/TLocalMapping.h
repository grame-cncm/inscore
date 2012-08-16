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


#ifndef __TLocalMapping__
#define __TLocalMapping__

#include <map>
#include <string>
#include <iostream>

#include "maptypes.h"
#include "smartpointer.h"

namespace inscore {

/*!
\addtogroup ITLMapping
@{
*/

/*!
	\brief local mapping description

	an object local mapping includes a mapping between the local space segmentation
	the time and the graphic segmentations
*/
template <typename T> class TLocalMapping : public smartable
{
	public:
		typedef SMARTP<TMapping<T, RelativeTimeSegment> >	SLocal2TimeMapping;

		typedef std::map<std::string,SLocal2TimeMapping> namedMapping;
		typedef typename std::map<std::string,SLocal2TimeMapping>::const_iterator	const_iterator;
		typedef typename std::map<std::string,SLocal2TimeMapping>::iterator			iterator;

	private:
		namedMapping				fMappings;

		const SLocal2TimeMapping find (const std::string& name) const
				{
					const_iterator found = fMappings.find(name);
					return (found == fMappings.end()) ? 0 : &(found->second);
				}
			  SLocal2TimeMapping find (const std::string& name)
				{
					iterator found = fMappings.find(name);
					return (found == fMappings.end()) ? 0 : &(found->second);
				}

				 TLocalMapping() {}
		virtual ~TLocalMapping() {}
	
	public:
		static SMARTP<TLocalMapping<T> > create()	{ return new TLocalMapping; }

		const namedMapping& namedMappings() const	{ return fMappings; }			
		bool remove(const std::string& name)		{ return fMappings.erase(name)==1; }	// Returns true if the specified 'name' has been found and removed.

		void setMapping	(const std::string& name, const SLocal2TimeMapping& l2t)	{ fMappings[name] = l2t; }
		void addMapping	(const std::string& name, const SLocal2TimeMapping& l2t)	{ fMappings[name] = l2t; }
};

/*! @} */

}

#endif
