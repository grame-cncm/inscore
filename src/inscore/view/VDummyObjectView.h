/*

  INScore Project

  Copyright (C) 2009,2011  Grame

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

#include "VObjectView.h"

namespace inscore
{

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a dummy graphic view of a IObject.
*/
class VDummyObjectView : public VObjectView
{
	public :
		virtual ~VDummyObjectView()	{}

		virtual void updateView(IObject * )			{}
		virtual void updateObjectSize( IObject *  )	{}
		virtual void setParentItem( VObjectView*  )	{}

		virtual void setEffect (const IEffect* effect )	{}
		virtual TFloatRect referenceRect(VObjectContext item) const			{ return TFloatRect (TFloatPoint(-1,-1), TFloatPoint(1,1)); }
};

/*!@} */

} // end namespoace
