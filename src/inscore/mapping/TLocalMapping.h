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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#pragma once

#include <map>
#include <string>
#include <iostream>

#include "maptypes.h"
#include "smartpointer.h"

namespace inscore {

class IObject;

/*!
\addtogroup ITLMapping
@{
*/

/*!
	\brief local mapping description

	an object local mapping includes a mapping between the local space segmentation
	the time and the graphic segmentations
*/
template <typename T, unsigned int D> class TLocalMapping : public libmapping::smartable
{
	public:
		typedef libmapping::SMARTP<libmapping::TMapping<T, D, libmapping::rational, 1> >	SLocal2TimeMapping;

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
		static libmapping::SMARTP<TLocalMapping<T,D> > create()	{ return new TLocalMapping; }

		const namedMapping& namedMappings() const	{ return fMappings; }			
		bool remove(const std::string& name)		{ return fMappings.erase(name)==1; }	// Returns true if the specified 'name' has been found and removed.

		void setMapping	(const std::string& name, const SLocal2TimeMapping& l2t)	{ fMappings[name] = l2t; }
		void addMapping	(const std::string& name, const SLocal2TimeMapping& l2t)	{ fMappings[name] = l2t; }
};

//typedef TLocalMapping<float,2>					TFloat2DLocalMapping;

//template <typename T, unsigned int D>
//class TGraphic2LocalMap : public libmapping::TMapping<float,2,T,D> {};
//template <typename T, unsigned int D>
//class SGraphic2LocalMap : public libmapping::SMARTP<TGraphic2LocalMap<T, D> > {};
////libmapping::SMARTP<libmapping::TMapping<float,2,T,D> >
//
//template <typename T, unsigned int D>
//class TLocal2TimeMap : public libmapping::TMapping<T,D, libmapping::rational,1> {};
//template <typename T, unsigned int D>
//class SLocal2TimeMap : public libmapping::SMARTP<TLocal2TimeMap<T, D> > {};


class TDefaultLocalMapping {
	public:
	static void buildDefaultMapping (IObject* object);
};

//class TGraphic2GraphicMapping {
//	public:
//	static void update (IShapeMap* object);
//};

/*! @} */
}
