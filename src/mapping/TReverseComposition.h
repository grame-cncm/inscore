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


#ifndef __TReverseComposition__
#define __TReverseComposition__

#include <vector>
#include "TRelation.h"


namespace INScore
{

/*!
\addtogroup ITLMapping
@{
*/

template<typename T1, typename T2> class TRelation;
template<typename T> class segment;

//--------------------------------------------------------------------------
/*!
	\brief relations composition
*/
template<typename T1, typename T2, typename T3> class TReverseComposition : public TRelation<T1,T3>
{
	public:
		typedef typename std::vector<T1> firstSet;
		typedef typename std::vector<T2> intermediateSet;
		typedef typename std::vector<T3> secondSet;

	protected:
		SMARTP<TRelation<T2,T1> > fRelation1;
		SMARTP<TRelation<T2,T3> > fRelation2;

				 TReverseComposition(SMARTP<TRelation<T2,T1> > r1, SMARTP<TRelation<T2,T3> > r2)
					: fRelation1(r1), fRelation2(r2) {}
		virtual ~TReverseComposition() {}
	
	public:
		/// creates a new composition
		static SMARTP<TReverseComposition<T1,T2,T3> >create(SMARTP<TRelation<T2,T1> > r1, SMARTP<TRelation<T2,T3> > r2)		
			{ return new TReverseComposition<T1,T2,T3>(r1, r2); }

		/// \brief gives the first relation of the composition
		virtual const SMARTP<TRelation<T2,T1> >& firstRelation() const { return fRelation1; }

		/// \brief gives the second relation of the composition
		virtual const SMARTP<TRelation<T2,T3> >& secondRelation() const { return fRelation2; }

		/// \brief gives the direct relation of an object
		virtual secondSet& directRelation(const T1& s, secondSet& relations) const {
			intermediateSet tmp;
			return fRelation2->directRelation (fRelation1->reverseRelation(s, tmp), relations);
		}

		/// \brief gives the reverse relation of an object
		virtual firstSet& reverseRelation(const T3& s, firstSet& relations) const {
			intermediateSet tmp;
			return fRelation1->directRelation (fRelation2->reverseRelation(s, tmp), relations);
		}

		/// \brief gives the direct relation of a set of objects		
		virtual secondSet& directRelation(const firstSet& s, secondSet& relations) const {
			intermediateSet tmp;
			return fRelation2->directRelation (fRelation1->reverseRelation(s, tmp), relations);
		}

		/// \brief gives the reverse relation of a set of objects
		virtual firstSet& reverseRelation(const secondSet& s, firstSet& relations) const {
			intermediateSet tmp;
			return fRelation1->directRelation (fRelation2->reverseRelation(s, tmp), relations);
		}
		
		/// \brief print utility
		virtual void print(std::ostream& out) const {
			if (!fRelation1) return;
			for (typename TRelation<T2,T1>::const_reverseIterator i = fRelation1->revbegin(); i != fRelation1->revend(); i++) {
				secondSet v;
				directRelation(i->first, v);
				out << i->first << " -> ";
				for (typename secondSet::const_iterator iv = v.begin(); iv != v.end(); iv++)
					out << *iv << " ";
				out << std::endl;
			}
		}
};

template<typename T1, typename T2, typename T3>
std::ostream& operator << (std::ostream& out, const TReverseComposition<T1, T2, T3>& c) { c.print(out); return out; }


/*! @} */

} // end namespoace

#endif
