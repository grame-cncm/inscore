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

#ifndef __TRelation__
#define __TRelation__

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "TSegment.h"
#include "lmsmartpointer.h"

namespace libmapping
{

/*!
\addtogroup Relations
@{
*/

template<typename T, unsigned int D> class TSegmentation;

//--------------------------------------------------------------------------
/*!
	\brief relation between objects
	
	A relation is a simple map between an object and related objects.
	It is a one way description of a 'mathematical' relation which is implemented by TMapping.
	\note objects of the relation must support the \c < operator.
*/
template<typename T1, unsigned int D1, typename T2, unsigned int D2> class TRelation
{
	public:
		typedef TSegment<T1,D1>		segmtype1;
		typedef TSegment<T2,D2>		segmtype2;
		typedef typename std::set<segmtype2>				relationList;

	protected:
		typedef typename std::map<segmtype1,relationList>	relationsMap;
		typedef typename relationsMap::iterator				iterator;

		relationsMap	fMap;

	public:
				 TRelation() {}
		virtual ~TRelation() {}
	
		typedef typename relationsMap::const_iterator		const_iterator;
		typedef typename relationList::const_iterator		const_iterator_rel;

		/// \brief first map iteration utility
		const_iterator begin() const						{ return fMap.begin(); }
		/// \brief first map iteration utility
		const_iterator end() const							{ return fMap.end(); }
		/// \brief relation map size
		unsigned int size() const							{ return fMap.size(); }

		/*! \brief add a relation between two objects
		
			\param s1 the first objects of the relation
			\param s2 the second objects of the relation
		*/
		virtual void add (const segmtype1& s1, const segmtype2& s2)		{ fMap[s1].insert(s2); }

		/*! \brief add a relation between an object and a set of objects
		
			\param s1 the first object of the relation
			\param s2 a set of second objects of the relation
		*/
		virtual void add (const segmtype1& s1, const std::set<segmtype2>& s2)  {
			for (const_iterator_rel j = s2.begin(); j != s2.end(); j++)
				add (s1, *j);
		}

		/*! \brief gives the relations of an object
		
			\param s an object to look for in the relation set
			\return a reference to the relations list
		*/
		virtual relationList get (const segmtype1& s) const { 
			const_iterator found = fMap.find(s);
			if (found != fMap.end())	return found->second;
			return std::set<segmtype2>();
		}

		/*! \brief gives the relations of a set of objects		
			\param s a set of objects
			\return a relations list
		*/
		virtual relationList get(const std::set<segmtype1>& s) const {
			relationList relations;
			typedef typename std::set<segmtype1>::const_iterator const_t1Iterator;
			for (const_t1Iterator i = s.begin(); i != s.end(); i++) {
				const relationList& tmp = get(*i);
				for (const_iterator_rel j = tmp.begin(); j != tmp.end(); j++)
					relations.insert( *j );
			};
			return relations;
		}

		/*! \brief gives the primary set of the relation
			\return the list of the map first elements
		*/
		virtual SMARTP<TSegmentation<T1,D1> > getPrimarySet () const { 
			SMARTP<TSegmentation<T1,D1> > s = TSegmentation<T1,D1>::create();
			for (const_iterator i = fMap.begin(); i != fMap.end(); i++)
				s->add (i->first);
			s->setResource();
			return s;
		}
		
		//--------------------------------------------------------------------------------------------
		virtual void print(std::ostream& out) const {
			for (const_iterator i = fMap.begin(); i != fMap.end(); i++) {
				const relationList& relations = get (i->first);
				for (const_iterator_rel j = relations.begin(); j != relations.end(); j++)
					out << i->first << " " << *j << " " << std::endl;
			}
		}
};

template<typename T1, unsigned int D1, typename T2, unsigned int D2>
std::ostream& operator << (std::ostream& out, const TRelation<T1, D1, T2, D2>& s) { s.print(out); return out; }

/*! @} */

} // end namespoace

#endif
