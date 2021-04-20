/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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

#include <iostream>

#include "IObject.h"
#include "IProportionalAsyncDims.h"

using namespace std;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
void IProportionalAsyncDims::checkPending(IObject* obj)
{
	if (!obj->getWidth() || !obj->getHeight()) return;

//cerr << "IProportionalAsyncDims::checkPending " << fRequestedWidth << " " << fRequestedHeight << endl;
	if (fRequestedWidth) setPropWidth (obj, fRequestedWidth);
	else if (fRequestedHeight) setPropHeight (obj, fRequestedHeight);
	fRequestedWidth = fRequestedHeight = 0;
}

//--------------------------------------------------------------------------
void IProportionalAsyncDims::setDimensions(IObject* obj, float width, float height)
{
	obj->setWidth(width);
	obj->setHeight(height);	
}

//--------------------------------------------------------------------------
void IProportionalAsyncDims::setPropWidth(IObject* obj, float width)
{
	if (!width) return;
	float aw = obj->getWidth();
	obj->setWidth(width);
	if (aw) {
		obj->setHeight( obj->getHeight() * (width / aw));
		fUserDims = true;
	}
	else {
		fRequestedWidth = width;
		fRequestedHeight = 0;
	}
}

//--------------------------------------------------------------------------
void IProportionalAsyncDims::setPropHeight(IObject* obj, float height)
{
	if (!height) return;
	float ah = obj->getHeight();
	obj->setHeight(height);
	if (ah) {
		obj->setWidth( obj->getWidth() * (height / ah));
		fUserDims = true;
	}
	else {
		fRequestedWidth = 0;
		fRequestedHeight = height;
	}
}

/*! @} */

} // end namespoace
