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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>
#ifdef EMCC
#include <emscripten.h>
#include "IObjectAdapter.h"
#endif

#include "HTMLObjectView.h"

using namespace std;

namespace inscore
{

class IObject;

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
HTMLObjectView::HTMLObjectView(int id, HTMLObjectView* parent) :
	fParent(parent), fID (id)
{
}

//--------------------------------------------------------------------------
void HTMLObjectView::updateView(IObject * object)
{
#ifdef EMCC
	EM_ASM( { JSObjectView.updateObjectView($0, $1, $3);}, getID(), int(object->getAdapter()), false);
#endif
}

//--------------------------------------------------------------------------
void HTMLObjectView::setEffect (const IEffect* effect )	{}

//--------------------------------------------------------------------------
TFloatRect HTMLObjectView::referenceRect(VObjectContext item) const { return TFloatRect(TFloatPoint(-1,-1), TFloatPoint(1,1)); };


/*!@} */

} // end namespoace
