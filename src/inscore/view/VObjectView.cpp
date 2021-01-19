/*

  INScore Project

  Copyright (C) 2015  Grame

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


#include "Modules.h"
#include "VObjectView.h"

#if QTView
#include "MouseEventAble.h"
#endif

namespace inscore
{

float VObjectView::relative2SceneX(float x, VObjectContext context ) const
{
	const TFloatRect& r = referenceRect(context);
	// inscore graphic space is between -1 and 1
	return (( x + 1 ) * r.width()) / 2.0f + r.x();
}

float VObjectView::relative2SceneY(float y, VObjectContext context ) const {
	const TFloatRect& r = referenceRect(context);
	// inscore graphic space is between -1 and 1
	return (( y + 1 ) *  r.height()) / 2.0f  + r.y();
}

float VObjectView::relative2SceneWidth(float width, VObjectContext context ) const {
	return (referenceRect(context).width() * width)/2.0f;
}

float VObjectView::relative2SceneHeight(float height, VObjectContext context ) const {
	return (referenceRect(context).height() * height)/2.0f;
}

float VObjectView::scene2RelativeWidth(float width, VObjectContext context ) const {
	return 2.0f * width / referenceRect(context).width();
}

float VObjectView::scene2RelativeHeight(float height, VObjectContext context ) const {
	return 2.0f * height / referenceRect(context).height();
}

float VObjectView::scene2RelativeX(float x, VObjectContext context ) const {
	const TFloatRect& r = referenceRect(context);
	return ( x - r.x() ) / ( r.width() / 2.0f ) - 1 ;
}

float VObjectView::scene2RelativeY(float y, VObjectContext context ) const {
	const TFloatRect& r = referenceRect(context);
	return ( y - r.y() ) / ( r.height() / 2.0f ) - 1 ;
}

#if QTView
void VObjectView::handleEvent (const IObject* obj, float x, float y, EventsAble::eventype type)
{ 	_MouseEventAble::handleEvent(obj, x, y, type); }

#else
void VObjectView::handleEvent (const IObject* obj, float x, float y, EventsAble::eventype type) {}

#endif

const AbstractData VObjectView::getImage(const char *)
{
	AbstractData data;
	data.data = 0;
	data.size = 0;
	return data;
}

}

