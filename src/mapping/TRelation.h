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

namespace inscore
{

/*!
\addtogroup ITLMapping
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief relation between objects
	
	A relation is a simple map between an object and related objects.
	It is a one way description of a 'mathematical' relation which is implemented by TMapping.
	\note objects of the relation must support the \c < operator.
*/
template<typename T1, typename T2> class TRelation
{
	protected:
		typedef typename std::set<T2>				relationList;
		typedef typename std::map<T1,relationList>	relationsMap;
		typedef typename relationsMap::iterator		iterator;
		typedef typename relationList::const_iterator	const_iterator2;

		relationsMap	fMap;

	public:
				 TRelation() {}
		virtual ~TRelation() {}
	
		typedef typename relationsMap::const_iterator	const_iterator;

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
		virtual void add (const T1& s1, const T2& s2)		{ fMap[s1].insert(s2); }

		/*! \brief add a relation between an object and a set of objects
		
			\param s1 the first object of the relation
			\param s2 a set of second objects of the relation
		*/
		virtual void add (const T1& s1, const std::set<T2>& s2)  {
			for (const_iterator2 j = s2.begin(); j != s2.end(); j++)
				add (s1, *j);
		}

		/*! \brief gives the relations of an object
		
			\param s an object to look for in the relation set
			\return a reference to the relations list
		*/
		virtual relationList get (const T1& s) const { 
			const_iterator found = fMap.find(s);
			if (found != fMap.end())	return found->second;
			return std::set<T2>();
		}

		/*! \brief gives the relations of a set of objects		
			\param s a set of objects
			\return a relations list
		*/
		virtual relationList get(const std::set<T1>& s) const {
			relationList relations;
			typedef typename std::set<T1>::const_iterator const_t1Iterator;
			for (const_t1Iterator i = s.begin(); i != s.end(); i++) {
				const relationList& tmp = get(*i);
				for (const_iterator2 j = tmp.begin(); j != tmp.end(); j++)
					relations.insert( *j );
			};
			return relations;
		}

		//--------------------------------------------------------------------------------------------
		virtual void print(std::ostream& out) const {
			for (const_iterator i = fMap.begin(); i != fMap.end(); i++) {
				const relationList& relations = get (i->first);
				for (const_iterator2 j = relations.begin(); j != relations.end(); j++)
					out << i->first << " " << *j << " " << std::endl;
			}
		}
};

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const TRelation<T1, T2>& s) { s.print(out); return out; }

/*! @} */

} // end namespoace

#endif
