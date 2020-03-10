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

#include "IObject.h"
#include "HTMLObjectView.h"
#ifdef EMCC
#include <emscripten.h>
#include "wasmglue.h"
#endif

using namespace std;

namespace inscore
{

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
	int id = getID();
	int oid = int((void*)object);
cout << "HTMLObjectView::updateView " << (void*)object << " oid: " << oid << endl;
	EM_ASM( { JSObjectView.updateView($0, $1);}, id, oid);
#endif
}

//--------------------------------------------------------------------------
void HTMLObjectView::setEffect (const IEffect* effect )	{}

//--------------------------------------------------------------------------
TFloatRect HTMLObjectView::referenceRect(VObjectContext item) const { return TFloatRect(TFloatPoint(-1,-1), TFloatPoint(1,1)); };


/*!@} */

} // end namespoace
