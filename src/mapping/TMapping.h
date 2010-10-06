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

#ifndef __TMapping__
#define __TMapping__

#include "TRelation.h"
#include "smartpointer.h"

namespace interlude
{

/*!
\addtogroup ITLMapping
@{
*/

template<typename T1, typename T2> class TMapping;

//--------------------------------------------------------------------------
/*!
	\brief a mapping: a mathematical relation between elements
	
	A mapping is actually composed of a direct relation (from type T1 to T2)
	and a reverse relation (from type T2 to T1).
*/
template<typename T1, typename T2> class TMapping : public smartable
{
	protected:
		TRelation<T1,T2>	fDirect;
		TRelation<T2,T1>	fReverse;

				 TMapping() {}
		virtual ~TMapping() {}

	public:
		/// creates a new mapping
		static SMARTP<TMapping<T1,T2> >create()		{ return new TMapping<T1,T2>(); }
	
		/*! \brief add a relation between two objects
		
			\param s1 the first objects of the relation
			\param s2 the second objects of the relation
		*/
		virtual void add (const T1& s1, const T2& s2)		{ fDirect.add (s1, s2); fReverse.add (s2, s1); }

		/*! \brief add a relation between an object and a set of objects
		
			\param s1 the first object of the relation
			\param s2 a set of second objects of the relation
		*/
		virtual void add (const T1& s1, const std::set<T2>& s2)  { 
			typedef typename std::set<T2>::const_iterator	const_iterator;
			for (const_iterator i = s2.begin(); i != s2.end(); i++)
				add (s1, *i);
		}
		
		/// \brief gives the direct relation (from T1 to T2)
		const TRelation<T1,T2>& direct() const		{ return fDirect; }
		/// \brief gives the reverse relation (from T2 to T1)
		const TRelation<T2,T1>& reverse() const		{ return fReverse; }

		//--------------------------------------------------------------------------------------------
		virtual void print(std::ostream& out) const { 
			out << "direct relation:\n";
			fDirect.print (out); 
			out << "reverse relation:\n";
			fReverse.print(out); 
		}
};

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const TMapping<T1, T2>& s) { s.print(out); return out; }

/*! @} */

} // end namespoace

#endif
