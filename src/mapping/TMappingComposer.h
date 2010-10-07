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


#ifndef __TMappingComposer__
#define __TMappingComposer__

#include <vector>
#include "TComposition.h"
#include "TReverseComposition.h"
#include "TRelation.h"

namespace interlude
{

/*!
\addtogroup ITLMapping
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief a mapping composer
	
	Transforms a TComposition into a TRelation
*/
template<typename T1, typename T2, typename T3> class TMappingComposer
{
	typedef TRelation<T1,T2> FR;
	typedef TRelation<T2,T1> FRR;
	typedef TRelation<T2,T3> SR;
	typedef typename std::map<T1, std::vector<T2> >::const_iterator const_fr_iterator;
	typedef typename std::map<T3, std::vector<T2> >::const_iterator const_sr_iterator;
		
	public:
				 TMappingComposer() {}
		virtual ~TMappingComposer() {}

		/// creates a new composition
		void compose(const SMARTP<TComposition<T1, T2, T3> >& c, SMARTP<TRelation<T1,T3> > outrelation) {
			const SMARTP<FR>& r = c->firstRelation();
			for (const_fr_iterator i = r->begin(); i != r->end(); i++) {
				std::vector<T3> v;
				outrelation->addRelation(i->first, c->directRelation(i->first, v));
			}
		}

		void compose(const SMARTP<TReverseComposition<T1, T2, T3> >& c, SMARTP<TRelation<T1,T3> > outrelation) {
			const SMARTP<FRR>& r = c->firstRelation();
			for (const_sr_iterator i = r->revbegin(); i != r->revend(); i++) {
				std::vector<T3> v;
				outrelation->addRelation(i->first, c->directRelation(i->first, v));
			}
		}

		/// creates a new reversed composition
		void reverseCompose(const SMARTP<TComposition<T1, T2, T3> >& c, SMARTP<TRelation<T3,T1> > outrelation) {
			const SMARTP<SR>& r = c->secondRelation();
			for (const_sr_iterator i = r->revbegin(); i != r->revend(); i++) {
				std::vector<T1> v;
				outrelation->addRelation(i->first , c->reverseRelation(i->first, v));
			}
		}
};

/*! @} */

} // end namespoace

#endif
