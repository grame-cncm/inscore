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
		typedef SMARTP<TMapping<GraphicSegment, T> >		SGraphic2LocalMapping;
		typedef SMARTP<TMapping<T, RelativeTimeSegment> >	SLocal2TimeMapping;

		struct MapSet {
			SGraphic2LocalMapping	fGraphic2Local;
			SLocal2TimeMapping		fLocal2Time;
			MapSet () {}
			MapSet (const SGraphic2LocalMapping& g2l, const SLocal2TimeMapping& l2t)
				: fGraphic2Local(g2l), fLocal2Time(l2t) {}
		};
		typedef std::map<std::string,MapSet> namedMapping;
		typedef typename std::map<std::string,MapSet>::const_iterator	const_iterator;
		typedef typename std::map<std::string,MapSet>::iterator			iterator;

	private:

		namedMapping	fMappings;
		const MapSet	fNullSet;

		const MapSet* find (const std::string& name) const
				{
					const_iterator found = fMappings.find(name);
					return (found == fMappings.end()) ? 0 : &(found->second);
				}
			  MapSet* find (const std::string& name)
				{
					iterator found = fMappings.find(name);
					return (found == fMappings.end()) ? 0 : &(found->second);
				}

				 TLocalMapping() {}
		virtual ~TLocalMapping() {}
	
	public:
		static SMARTP<TLocalMapping<T> > create()	{ return new TLocalMapping; }

		const namedMapping& namedMappings() const { return fMappings; }

		const SGraphic2LocalMapping&	getGraphic2LocalMapping(const std::string& name) const 
			{ const MapSet* s = find(name); return s ? s->fGraphic2Local : fNullSet.fGraphic2Local; }
		const SLocal2TimeMapping&		getLocal2relTimeMapping(const std::string& name) const
			{ const MapSet* s = find(name); return s ? s->fLocal2Time : fNullSet.fLocal2Time; }
			
		bool remove(const std::string& name) { return fMappings.erase(name)==1; }	/// <brief Returns true if the specified 'name' has been found and removed.

		void setMapping	(const std::string& name, const SGraphic2LocalMapping& g2l, const SLocal2TimeMapping& l2t)
			{ 
				MapSet* s = find(name); 
				if (s) {
					s->fGraphic2Local = g2l;
					s->fLocal2Time = l2t;
				} 
				else fMappings[name] = MapSet(g2l, l2t);
			}

		void addMapping	(const std::string& name, const SGraphic2LocalMapping& g2l, const SLocal2TimeMapping& l2t)
			{ 
				MapSet* s = find(name); 
				if (s) {
					// it looks like s->fGraphic2Local is not used
					if (g2l) s->fGraphic2Local->add(*g2l);
					if (l2t) s->fLocal2Time->add(*l2t);
				} 
				else fMappings[name] = MapSet(g2l, l2t);
			}
};

/*! @} */

}

#endif
