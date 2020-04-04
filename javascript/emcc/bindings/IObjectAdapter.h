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
#include <vector>

#include "IObject.h"
#include "ILine.h"
#include "IRect.h"


namespace inscore
{

struct JSPen {
	float  penWidth = 0;
	std::string penColor;
	int penStyle;
	int brushStyle;
	std::string color;
	float alpha;
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
enum TEffect 	{ kNone, kBlur, kColorize, kShadow };
enum TBlurhint	{ kPerformance, kQuality, kAnimation };

struct JSColor {
	std::string rgb;
	std::string rgba;
	float alpha;
};

struct JSBlur {
	int 	radius = 0;
	int		hint = TBlurhint::kPerformance;
};

struct JSColorize {
	float 		strength = 1.0;
	std::string	color;
};

struct JSShadow {
	int 		xOffset = 10;
	int 		yOffset = 10;
	std::string	color;
	int			blur = 8;
};

struct JSEffect {
	int 		type = TEffect::kNone;
	JSBlur 		blur;
	JSColorize 	colorize;
	JSShadow 	shadow;
};

struct JSEvents {
	bool watchMouseEnter;
	bool watchMouseLeave;
	bool watchMouseMove;
	bool watchMouseDown;
	bool watchMouseUp;
	bool watchMouseDClick;
};

struct JSUpdateInfos {
	JSPosition 	position;
	JSColor  	color;
	JSEffect	effect;
	JSEvents	events;
	bool updatepos = false;
	bool updatebrush = false;
	bool updatecolor = false;
	bool updateeffect= false;
	bool updateevents= false;
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

struct JSArcInfos {
	float width = 0;
	float height = 0;
	float 	start = 0;
	float 	range = 0;
	bool	closed = false;
};

struct JSRadius {
	float 	x = 0;
	float 	y = 0;
};

struct JSScoreInfos {
	std::string code;
	int    page;
};

class IText;
class ILine;
class ICurve;
class IEffect;
class IGuidoCode;
class IMusicXMLCode;

//--------------------------------------------------------------------------
/*! \brief the interface for iobjects
*/
class inscore_export IObjectAdapter
{
	SIObject fObject;
	
	static std::map<std::string, int> fBrushStyles;
	static std::map<std::string, int> fPenStyles;
	static std::string color2htmlColor (const IColor& color, bool withalpha);
	static std::string color2RGBAColor (const IColor& color);
	
	static void _updateWidth (IPosition* pos, float w);
	static void _updateHeight (IPosition* pos, float h);
	static bool _getPosition (const IPosition* obj, JSPosition& pos);
	static bool _getColor (const IColor* obj, JSColor& color);
	static bool _getPenBrush (const IShape* obj, JSPen& brush);
	static bool _getText  (const IText* obj, JSTextInfos& infos);
	static bool _getLine  (ILine* obj, JSLineInfos& infos);
	static bool _getEffect (const IEffect* obj, JSEffect& infos);
	static bool _getEvents (const EventsAble* obj, JSEvents& infos);
	static bool _getCurve  (const ICurve* obj, std::vector<float>& infos);
	static bool _getGuido  (const IGuidoCode* obj, JSScoreInfos& infos);
	static bool _getXML    (const IMusicXMLCode* obj, JSScoreInfos& infos);

	public:
		typedef const std::string	jsString;
	
				 IObjectAdapter();
				 IObjectAdapter(const SIObject& object) : fObject(object) {}
		virtual ~IObjectAdapter() {}
		
		JSUpdateInfos getUpdateInfos () const;
		JSTextInfos   getTextInfos () const;
		JSLineInfos   getLineInfos () const;
		std::string   getFile () const;			// for file based object (e.g. image)
		JSRadius      getRadius () const;		// for IRect
		JSArcInfos    getArcInfos() const;
	    std::vector<float> getPolygonInfos() const;
		std::vector<float> getCurveInfos() const;
		JSScoreInfos  getGuidoInfos() const;
		JSScoreInfos  getXMLInfos() const;

		libmapping::rational getDate () const		{ return fObject->getDate(); }
		libmapping::rational getDuration () const	{ return fObject->getDuration(); }

		std::string	getOSCAddress() const		{ return fObject->getOSCAddress(); }
		void	updateWidth(float w)			{ _updateWidth (fObject, w); }
		void	updateHeight(float h)			{ _updateHeight(fObject, h); }

	IObjectAdapter* create(int id) 				{ return new IObjectAdapter((IObject*)id); }
	void 			del(IObjectAdapter* obj) 	{ delete obj; }
};

}
