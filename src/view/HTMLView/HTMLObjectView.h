/*

  INScore Project

  Copyright (C) 2009,2020  Grame

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


#pragma once

#include <iostream>

#include "IObject.h"
#include "VObjectView.h"


namespace inscore
{

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief the HTML graphic view of an IObject.
*/
class HTMLObjectView :  public VObjectView
{
	HTMLObjectView* fParent;

	public :
				  HTMLObjectView(HTMLObjectView* parent=0) : fParent(parent) {}
		virtual ~HTMLObjectView()  {}
		
		virtual void updateView(IObject * object);
		virtual void updateObjectSize( IObject *  )		{} // default do nothing
		virtual void setParentItem( VObjectView* obj )	{ fParent = dynamic_cast<HTMLObjectView*>(obj); }
		virtual void setEffect (const IEffect* effect );

		virtual TFloatRect referenceRect(VObjectContext item) const;
};

/*!@} */

} // end namespoace
