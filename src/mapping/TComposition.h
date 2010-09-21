/*

  Interlude Project
  Copyright (C) 2009  Grame

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


#ifndef __TComposition__
#define __TComposition__

#include "TMapping.h"

namespace interlude
{

/*!
\addtogroup ITLMapping
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief relations composition
*/
template<typename T1, typename T2, typename T3> class TComposition : public TMapping<T1,T3>
{
	protected:
		typedef typename TRelation<T1,T2>::const_iterator	const_iterator;

				TComposition(const TRelation<T1,T2>& r1,  const TRelation<T2,T3>& r2) {
					for (const_iterator i = r1.begin(); i != r1.end(); i++) {
						add ( i->first, r2.get(i->second));
					}
				}
		virtual ~TComposition() {}
	
	public:
		/// creates a new composition
//		static SMARTP<TComposition<T1,T2,T3> >create(const TRelation<T1,T2>& r1,  const TRelation<T2,T3>& r2)		
//			{ return new TComposition<T1,T2,T3>(r1, r2); }
		static SMARTP<TMapping<T1,T3> >create(const TRelation<T1,T2>& r1,  const TRelation<T2,T3>& r2)		
			{ return new TComposition<T1,T2,T3>(r1, r2); }
};

/*! @} */

} // end namespoace

#endif
