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
bool IObjectAdapter::_getPenBrush (const IShape* obj, JSBrush& brush)
{
	brush.penWidth = obj->getPenWidth();
	brush.penColor = color2htmlColor(obj->getPenColor(), true);
	brush.penStyle = fPenStyles[obj->getPenStyle()];
	brush.brushStyle = fBrushStyles[obj->getBrushStyle()];
	return obj->modified();
}

//--------------------------------------------------------------------------
bool IObjectAdapter::_getPosition (const IPosition* obj, JSPosition& pos)
{
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
	return obj->modified();
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
bool IObjectAdapter::_getLine (const ILine* obj, JSLineInfos& infos)
{
	if (obj) {
		TFloatPoint p = obj->getPoint();
		infos.x = p.x();
		infos.y = p.y();
		infos.arrowLeft		= obj->getArrowLeft();
		infos.arrowRight	= obj->getArrowRight();
		infos.arrowLeftSize = obj->getArrowSizeLeft();
		infos.arrowRightSize= obj->getArrowSizeRight();
		return true;
	}
	return false;
}

std::map<string, int> IObjectAdapter::fPenStyles;
std::map<string, int> IObjectAdapter::fBrushStyles;
//--------------------------------------------------------------------------
// public methods
//--------------------------------------------------------------------------
IObjectAdapter::IObjectAdapter() : fObject(0)
{
	if (fPenStyles.empty()) {
		fPenStyles[SOLID_STYLE] 		= kSolid;
		fPenStyles[DASH_STYLE] 			= kDash;
		fPenStyles[DOT_STYLE] 			= kDot;
		fPenStyles[DASH_DOT_STYLE] 		= kDashDot;
		fPenStyles[DASH_DOT_DOT_STYLE]	= kDashDotDot;

		fBrushStyles[DENSE1_BRUSH_STYLE]	= kDense1;
		fBrushStyles[DENSE2_BRUSH_STYLE]	= kDense2;
		fBrushStyles[DENSE3_BRUSH_STYLE]	= kDense3;
		fBrushStyles[DENSE4_BRUSH_STYLE]	= kDense4;
		fBrushStyles[DENSE5_BRUSH_STYLE]	= kDense5;
		fBrushStyles[DENSE6_BRUSH_STYLE]	= kDense6;
		fBrushStyles[DENSE7_BRUSH_STYLE]	= kDense7;
		fBrushStyles[NO_BRUSH_STYLE]	= kNoBrush;
		fBrushStyles[HOR_BRUSH_STYLE]	= kBrushHor;
		fBrushStyles[VER_BRUSH_STYLE]	= kBrushVer;
		fBrushStyles[CROSS_BRUSH_STYLE]	= kCross;
		fBrushStyles[BDIAG_BRUSH_STYLE]	= kBDiag;
		fBrushStyles[FDIAG_BRUSH_STYLE]	= kFDiag;
		fBrushStyles[DIAG_CROSS_BRUSH_STYLE] = kDiagCross;
	}
}

//--------------------------------------------------------------------------
JSTextInfos IObjectAdapter::getTextInfos () const
{
	JSTextInfos infos;
	if (!_getText (dynamic_cast<const IText*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getTextInfos: unexpected null object!" << endl;
	return infos;
}

//--------------------------------------------------------------------------
JSLineInfos IObjectAdapter::getLineInfos () const
{
	JSLineInfos infos;
	if (!_getLine (dynamic_cast<const ILine*>((IObject*)fObject), infos))
		cerr << "IObjectAdapter::getLineInfos: unexpected null object!" << endl;
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
		infos.updatebrush = _getPenBrush (fObject, infos.brush);
	}
	return infos;
}

}
