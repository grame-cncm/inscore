/*

  INScore Library
  Copyright (C) 2020  Grame

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

#include <emscripten.h>
#include <emscripten/bind.h>

#include "IObjectAdapter.h"

using namespace emscripten;
using namespace inscore;

/*
 * Structure and enum binding.
 * This structures can be created and manipulated in javascript side like json object and passed to C++ method.
 */
EMSCRIPTEN_BINDINGS(CStruct) {
	
	value_object<JSRadius>("JSRadius")
		.field("x",    &JSRadius::x)
		.field("y",    &JSRadius::y);

	value_object<JSPen>("JSPen")
		.field("penWidth",   &JSPen::penWidth)
		.field("penColor",   &JSPen::penColor)
		.field("penStyle",   &JSPen::penStyle)
		.field("brushStyle", &JSPen::brushStyle)
		.field("color",      &JSPen::color)
		.field("alpha",  	 &JSPen::alpha);

	value_object<JSPosition>("JSPosition")
		.field("x", 	  &JSPosition::x)
		.field("y", 	  &JSPosition::y)
		.field("width",   &JSPosition::width)
		.field("height",  &JSPosition::height)
		.field("xorigin", &JSPosition::xorigin)
		.field("yorigin", &JSPosition::yorigin)
		.field("scale",   &JSPosition::scale)
		.field("hidden",  &JSPosition::hidden)
		.field("xangle",  &JSPosition::xangle)
		.field("yangle",  &JSPosition::yangle)
		.field("zangle",  &JSPosition::zangle)
		.field("zorder",  &JSPosition::zorder)
		.field("pen",     &JSPosition::pen);

	value_object<JSBlur>("JSBlur")
		.field("radius",  &JSBlur::radius)
		.field("hint", 	  &JSBlur::hint);
	value_object<JSColorize>("JSColorize")
		.field("strength",  &JSColorize::strength)
		.field("color", 	&JSColorize::color);
	value_object<JSShadow>("JSShadow")
		.field("xOffset",  &JSShadow::xOffset)
		.field("yOffset",  &JSShadow::yOffset)
		.field("color",    &JSShadow::color)
		.field("blur",     &JSShadow::blur);
	value_object<JSEffect>("JSEffect")
		.field("type",  	&JSEffect::type)
		.field("blur",  	&JSEffect::blur)
		.field("colorize",	&JSEffect::colorize)
		.field("shadow",	&JSEffect::shadow);
	value_object<JSEvents>("JSEvents")
		.field("watchMouseEnter",  	&JSEvents::watchMouseEnter)
		.field("watchMouseLeave",  	&JSEvents::watchMouseLeave)
		.field("watchMouseMove",	&JSEvents::watchMouseMove)
		.field("watchMouseDown",	&JSEvents::watchMouseDown)
		.field("watchMouseUp",		&JSEvents::watchMouseUp)
		.field("watchMouseDClick",	&JSEvents::watchMouseDClick);

	value_object<JSColor>("JSColor")
		.field("rgb",   &JSColor::rgb)
		.field("rgba",  &JSColor::rgba)
		.field("alpha", &JSColor::alpha);

	value_object<JSUpdateInfos>("JSUpdateInfos")
		.field("position",  &JSUpdateInfos::position)
		.field("color",   	&JSUpdateInfos::color)
		.field("effect",   	&JSUpdateInfos::effect)
		.field("events",   	&JSUpdateInfos::events)
		.field("updatepos", &JSUpdateInfos::updatepos)
		.field("updatebrush", &JSUpdateInfos::updatebrush)
		.field("updatecolor", &JSUpdateInfos::updatecolor)
		.field("updateeffect", &JSUpdateInfos::updateeffect)
		.field("updateevents", &JSUpdateInfos::updateevents)
		.field("showmap", 	&JSUpdateInfos::showmap)
		.field("deleted", 	&JSUpdateInfos::deleted)
		.field("newdata", 	&JSUpdateInfos::newdata);
	
	value_object<JSTextInfos>("JSTextInfos")
		.field("text",  	&JSTextInfos::text)
		.field("size",   	&JSTextInfos::size)
		.field("family",   	&JSTextInfos::family)
		.field("weight",   	&JSTextInfos::weight)
		.field("style", 	&JSTextInfos::style);
	
	value_object<JSLineInfos>("JSLineInfos")
		.field("x1",  	&JSLineInfos::x1)
		.field("y1",   	&JSLineInfos::y1)
		.field("x2",  	&JSLineInfos::x2)
		.field("y2",   	&JSLineInfos::y2)
		.field("x",  	&JSLineInfos::x)
		.field("y",   	&JSLineInfos::y)
		.field("angle",   &JSLineInfos::angle)
		.field("width",   &JSLineInfos::width)
		.field("arrowLeft",   	&JSLineInfos::arrowLeft)
		.field("arrowRight",   	&JSLineInfos::arrowRight)
		.field("arrowLeftSize",   	&JSLineInfos::arrowLeftSize)
		.field("arrowRightSize", 	&JSLineInfos::arrowRightSize);
	
	value_object<JSArcInfos>("JSArcInfos")
		.field("width",  	&JSArcInfos::width)
		.field("height",   	&JSArcInfos::height)
		.field("start",  	&JSArcInfos::start)
		.field("range",   	&JSArcInfos::range)
		.field("closed",  	&JSArcInfos::closed);
	
	value_object<JSScoreInfos>("JSScoreInfos")
		.field("code",  &JSScoreInfos::code)
		.field("page",  &JSScoreInfos::page)
		.field("mappings",  &JSScoreInfos::mappings);

	value_object<JSDate>("JSDate")
		.field("num",  	&JSDate::num)
		.field("denum", &JSDate::denum);

	value_object<JSRect>("JSRect")
		.field("x",  	&JSRect::x)
		.field("y", 	&JSRect::y)
		.field("width", &JSRect::width)
		.field("height",&JSRect::height);
	
	value_object<JSPRollLimits>("JSPRollLimits")
		.field("start",  	&JSPRollLimits::start)
		.field("end",  		&JSPRollLimits::end)
		.field("lowpitch",  &JSPRollLimits::lowpitch)
		.field("highpitch", &JSPRollLimits::highpitch);
	
	value_object<JSPianorollInfos>("JSPianorollInfos")
		.field("code",  	&JSPianorollInfos::code)
		.field("keyboard",  &JSPianorollInfos::keyboard)
		.field("autovoicecolor", &JSPianorollInfos::autovoicecolor)
		.field("bars",  	&JSPianorollInfos::bars)
		.field("limits",  	&JSPianorollInfos::limits);
	
	value_object<JSMediaInfos>("JSMediaInfos")
		.field("playing",  	&JSMediaInfos::playing)
		.field("volume",  &JSMediaInfos::volume)
		.field("rate", &JSMediaInfos::rate)
		.field("mdate",  	&JSMediaInfos::mdate);
	
	value_object<JSGMNStreamInfos>("JSGMNStreamInfos")
		.field("stream",  	&JSGMNStreamInfos::stream)
		.field("reset",  	&JSGMNStreamInfos::reset);
}
