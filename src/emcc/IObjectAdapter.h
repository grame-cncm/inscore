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

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

#include "IObject.h"
#include "ILine.h"


namespace inscore
{

struct JSPen {
	float  penWidth;
	std::string penColor;
	int penStyle;
	int brushStyle;
};

struct JSPosition {
	float x;
	float y;
	float width;
	float height;
	float xorigin;
	float yorigin;
	float scale;
	bool  hidden;
	float xangle;
	float yangle;
	float zangle;
	float zorder;
	JSPen pen;
};

enum TPenStyle 		{ kSolid, kDash, kDot, kDashDot, kDashDotDot };
enum TBrushStyle 	{ kDense1, kDense2, kDense3, kDense4, kDense5, kDense6, kDense7,
					  kNoBrush, kBrushHor, kBrushVer, kCross, kBDiag, kFDiag, kDiagCross };

struct JSColor {
	std::string rgb;
	std::string rgba;
	float alpha;
};

struct JSUpdateInfos {
	JSPosition 	position;
	JSColor  	color;
	bool updatepos = false;
	bool updatebrush = false;
	bool updatecolor = false;
	bool deleted = false;
	bool newdata = false;
};

struct JSTextInfos {
	std::string	text;
	int 		size;
	std::string family;
	std::string weight;
	std::string style;
};

struct JSLineInfos {
	float 	x1;
	float 	y1;
	float 	x2;
	float 	y2;
	int		arrowLeft;
	int		arrowRight;
	float	arrowLeftSize;
	float	arrowRightSize;
};

class IText;
class ILine;

//--------------------------------------------------------------------------
/*! \brief the interface for iobjects
*/
class inscore_export IObjectAdapter
{
	SIObject fObject;
	
	static std::map<std::string, int> fBrushStyles;
	static std::map<std::string, int> fPenStyles;
	static std::string color2htmlColor (const IColor& color, bool withalpha);
	static void _updateWidth (IPosition* pos, float w);
	static void _updateHeight (IPosition* pos, float h);
	static bool _getPosition (const IPosition* obj, JSPosition& pos);
	static bool _getColor (const IColor* obj, JSColor& color);
	static bool _getPenBrush (const IShape* obj, JSPen& brush);
	static bool _getText  (const IText* obj, JSTextInfos& infos);
	static bool _getLine  (ILine* obj, JSLineInfos& infos);


	public:
		typedef const std::string	jsString;
	
				 IObjectAdapter();
				 IObjectAdapter(const SIObject& object) : fObject(object) {}
		virtual ~IObjectAdapter() {}
		
		JSUpdateInfos getUpdateInfos () const;
		JSTextInfos   getTextInfos () const;
		JSLineInfos   getLineInfos () const;

		libmapping::rational getDate () const		{ return fObject->getDate(); }
		libmapping::rational getDuration () const	{ return fObject->getDuration(); }

		void	updateWidth(float w)		{ _updateWidth (fObject, w); }
		void	updateHeight(float h)		{ _updateHeight(fObject, h); }

	IObjectAdapter* create(int id) 				{ return new IObjectAdapter((IObject*)id); }
	void 			del(IObjectAdapter* obj) 	{ delete obj; }
};

}
