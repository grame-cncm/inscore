/*

  INScore Library
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


#include "IObjectAdapter.h"
#include "IText.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
string IObjectAdapter::color2htmlColor (const IColor& color, bool withalpha) {
	std::stringstream sstr;
	sstr << "#" << std::setfill('0') << std::hex << std::setw(2) << color.getR() << std::setw(2) << color.getG() << std::setw(2) << color.getB();
	if (withalpha)
		sstr << std::setw(2) << color.getA();
	return sstr.str();
}
		
//--------------------------------------------------------------------------
void IObjectAdapter::_updateWidth (IPosition* pos, float w) {
	bool modified= pos->modified();
	pos->setWidth (w);
	if (!modified) pos->cleanup();
}
	
//--------------------------------------------------------------------------
void IObjectAdapter::_updateHeight (IPosition* pos, float h) {
	bool modified= pos->modified();
	pos->setHeight (h);
	if (!modified) pos->cleanup();
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getColor (const IColor* obj, JSColor& color)
{
	if (obj->modified()) {
		color.rgb		= color2htmlColor(*obj, false);
		color.rgba		= color2htmlColor(*obj, true);
		color.alpha		= obj->getA() / 255.f;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getPosition (const IPosition* obj, JSPosition& pos)
{
	if (obj->modified()) {
		pos.x 		= obj->getXPos();
		pos.y 		= obj->getYPos();
		pos.width 	= obj->getWidth();
		pos.height 	= obj->getHeight();
		pos.xorigin	= obj->getXOrigin();
		pos.yorigin	= obj->getYOrigin();
		pos.zorder	= obj->getZOrder();
		pos.scale	= obj->getScale();
		pos.hidden	= !obj->getVisible();
		pos.xangle	= obj->getRotateX();
		pos.yangle	= obj->getRotateY();
		pos.zangle	= obj->getRotateZ();
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getText (const IText* obj, JSTextInfos& infos)
{
	if (obj) {
		infos.text 	 = obj->getText();
		infos.size 	 = obj->getFontSize();
		infos.family = obj->getFontFamily();
		infos.weight = obj->getFontWeight();
		infos.style	 = obj->getFontStyle();
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
// public methods
//--------------------------------------------------------------------------
JSTextInfos IObjectAdapter::getTextInfos () const
{
	JSTextInfos infos;
	if (!_getText (dynamic_cast<const IText*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::_getText: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
JSUpdateInfos IObjectAdapter::getUpdateInfos () const
{
	JSUpdateInfos infos;
	if (fObject->getDeleted())
		infos.deleted = true;
	else {
		infos.newdata = fObject->newData();
		infos.updatepos = _getPosition (fObject, infos.position);
		infos.updatecolor = _getColor (fObject, infos.color);
	}
	return infos;
}

}
