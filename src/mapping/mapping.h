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


#ifndef __mapping__
#define __mapping__

#include "TRelation.h"
#include "smartpointer.h"

namespace inscore {

/*!
*	\brief A Mapping is an encapsulation of a relation and a version number. Each instance
*	has a unique version number.
*/
template<typename T1, typename T2>
class mapping : public TRelation<T1,T2>
{
		static int fVersionCount;
		int fVersion;

		mapping() : TRelation<T1,T2>() { fVersion = fVersionCount++; }

	public:
	
		/// creates a new mapping
		static SMARTP<mapping<T1,T2> >create()	{ return new mapping<T1,T2>(); }
		
		const int& getVersion() const			{ return fVersion; } 

};

template<typename T1, typename T2> int mapping<T1,T2>::fVersionCount = 0;

}

#endif
