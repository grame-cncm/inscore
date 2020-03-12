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

#include <string>
#include <emscripten.h>
#include <emscripten/bind.h>

#include "INScoreAdapter.h"
#include "INScoreGlue.h"
#include "IObjectAdapter.h"

using namespace emscripten;
using namespace inscore;

/*
 * Structure and enum binding.
 * This structures can be created and manipulated in javascript side like json object and passed to C++ method.
 */
EMSCRIPTEN_BINDINGS(CStruct) {
	
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
		.field("zorder",  &JSPosition::zorder);
	
	value_object<JSBrush>("JSBrush")
		.field("penWidth",   &JSBrush::penWidth)
		.field("penColor",   &JSBrush::penColor)
		.field("penStyle",   &JSBrush::penStyle)
		.field("brushStyle", &JSBrush::brushStyle);
	
	value_object<JSColor>("JSColor")
		.field("rgb",   &JSColor::rgb)
		.field("rgba",  &JSColor::rgba)
		.field("alpha", &JSColor::alpha);
	
	value_object<JSUpdateInfos>("JSUpdateInfos")
		.field("position",  &JSUpdateInfos::position)
		.field("brush",   	&JSUpdateInfos::brush)
		.field("color",   	&JSUpdateInfos::color)
		.field("updatepos", &JSUpdateInfos::updatepos)
		.field("updatebrush", &JSUpdateInfos::updatebrush)
		.field("updatecolor", &JSUpdateInfos::updatecolor)
		.field("deleted", 	&JSUpdateInfos::deleted)
		.field("newdata", 	&JSUpdateInfos::newdata);

	value_object<JSTextInfos>("JSTextInfos")
		.field("text",  	&JSTextInfos::text)
		.field("size",   	&JSTextInfos::size)
		.field("family",   	&JSTextInfos::family)
		.field("style", 	&JSTextInfos::style);

//	enum_<GuidoErrCode>("GuidoErrCode")
//			.value("guidoNoErr", GuidoErrCode::guidoNoErr)
//			.value("guidoErrParse", guidoErrParse)
//			.value("guidoErrMemory", GuidoErrCode::guidoErrMemory)
//			.value("guidoErrFileAccess", GuidoErrCode::guidoErrFileAccess)
//			.value("guidoErrUserCancel", GuidoErrCode::guidoErrUserCancel)
//			.value("guidoErrNoMusicFont", GuidoErrCode::guidoErrNoMusicFont)
//			.value("guidoErrNoTextFont", GuidoErrCode::guidoErrNoTextFont)
//			.value("guidoErrBadParameter", GuidoErrCode::guidoErrBadParameter)
//			.value("guidoErrInvalidHandle", GuidoErrCode::guidoErrInvalidHandle)
//			.value("guidoErrNotInitialized", GuidoErrCode::guidoErrNotInitialized)
//			.value("guidoErrActionFailed", GuidoErrCode::guidoErrActionFailed);
//
//
//	// Brush constants
	constant("kSolidStyle", 	IShape::kSolidStyle);
	constant("kDashStyle", 		IShape::kDashStyle);
	constant("kDotStyle", 		IShape::kDotStyle);
	constant("kDashDotStyle", 	IShape::kDashDotStyle);
	constant("kDashDotDotStyle", IShape::kDashDotDotStyle);

	constant("kSolidBrushStyle", 	IShape::kSolidBrushStyle);
	constant("kDense1BrushStyle", 	IShape::kDense1BrushStyle);
	constant("kDense2BrushStyle", 	IShape::kDense2BrushStyle);
	constant("kDense3BrushStyle", 	IShape::kDense3BrushStyle);
	constant("kDense4BrushStyle", 	IShape::kDense4BrushStyle);
	constant("kDense5BrushStyle", 	IShape::kDense5BrushStyle);
	constant("kDense6BrushStyle", 	IShape::kDense6BrushStyle);
	constant("kDense7BrushStyle", 	IShape::kDense7BrushStyle);
	constant("kNoBrushStyle", 		IShape::kNoBrushStyle);
	constant("kHorBrushStyle", 		IShape::kHorBrushStyle);
	constant("kVerBrushStyle", 		IShape::kVerBrushStyle);
	constant("kCrossBrushStyle", 	IShape::kCrossBrushStyle);
	constant("kBDiagBrushStyle", 	IShape::kBDiagBrushStyle);
	constant("kFDiagBrushStyle", 	IShape::kFDiagBrushStyle);
	constant("kDiagCrossBrushStyle",IShape::kDiagCrossBrushStyle);
}


/*
 * C++ class binding.
 * The javascript interface to inscore classes
 */
using namespace inscore;
EMSCRIPTEN_BINDINGS(EngineAdapter) {
	
	class_<TFloatPoint>("TFloatPoint")
		.function("x", 			&TFloatPoint::x)
		.function("y", 			&TFloatPoint::y);
	
	class_<TFloatSize>("TFloatSize")
		.function("width", 		&TFloatSize::width)
		.function("height", 	&TFloatSize::height);

	class_<IObjectAdapter>("IObjectAdapter")
		.constructor<>()

		.function("create", 		&IObjectAdapter::create, allow_raw_pointers())
		.function("del", 			&IObjectAdapter::del, allow_raw_pointers())

		.function("getUpdateInfos", &IObjectAdapter::getUpdateInfos, allow_raw_pointers())
		.function("getTextInfos",   &IObjectAdapter::getTextInfos, allow_raw_pointers())


		.function("getXPos", 		&IObjectAdapter::getXPos)
		.function("getYPos", 		&IObjectAdapter::getYPos)
		.function("getWidth", 		&IObjectAdapter::getWidth)
		.function("getHeight", 		&IObjectAdapter::getHeight)
		.function("getScale", 		&IObjectAdapter::getScale)
		.function("getZOrder", 		&IObjectAdapter::getZOrder)
		.function("getVisible", 	&IObjectAdapter::getVisible)
		.function("getXOrigin", 	&IObjectAdapter::getXOrigin)
		.function("getYOrigin", 	&IObjectAdapter::getYOrigin)
		.function("getRotateX", 	&IObjectAdapter::getRotateX)
		.function("getRotateY", 	&IObjectAdapter::getRotateY)
		.function("getRotateZ", 	&IObjectAdapter::getRotateZ)
		.function("getPos", 		&IObjectAdapter::getPos)
		.function("getColor", 		&IObjectAdapter::getColor, allow_raw_pointers())
		.function("getAlpha", 		&IObjectAdapter::getAlpha)
		.function("colorChanged", 	&IObjectAdapter::colorChanged)

		.function("getPenWidth", 	&IObjectAdapter::getPenWidth)
		.function("getPenColor", 	&IObjectAdapter::getPenColor, allow_raw_pointers())
		.function("getPenStyle", 	&IObjectAdapter::getPenStyle, allow_raw_pointers())
		.function("getBrushStyle", 	&IObjectAdapter::getBrushStyle, allow_raw_pointers())
		.function("brushChanged", 	&IObjectAdapter::brushChanged)

		.function("updateWidth", 	&IObjectAdapter::updateWidth)
		.function("updateHeight", 	&IObjectAdapter::updateHeight);


	// Binding C++ class adapter for INScore
	class_<INScoreAdapter>("INScoreAdapter")
			.constructor<>()

			.function("start", 				&INScoreAdapter::start, allow_raw_pointers())
			.function("stop", 				&INScoreAdapter::stop, allow_raw_pointers())
//			.function("restartNetwork", 	&INScoreAdapter::restartNetwork )
//			.function("stopNetwork", 		&INScoreAdapter::stopNetwork )

			.function("postMessage", 		select_overload<void( const std::string&, MessagePtr)> 					(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStr", 	select_overload<void( const std::string&, const std::string&)>			(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStrI", 	select_overload<void( const std::string&, const std::string&, int)>		(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStrF", 	select_overload<void( const std::string&, const std::string&, float)>	(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStrStr", 	select_overload<void( const std::string&, const std::string&,  const std::string&)>(&INScoreAdapter::postMessage), allow_raw_pointers())

			.function("loadInscore", 		&INScoreAdapter::loadInscore, allow_raw_pointers())
			.function("loadInscore2", 		&INScoreAdapter::loadInscore2, allow_raw_pointers())

			.function("delayMessage", 		&INScoreAdapter::delayMessage, allow_raw_pointers())
			.function("newMessage", 		&INScoreAdapter::newMessage, allow_raw_pointers())
			.function("newMessageM", 		&INScoreAdapter::newMessageM, allow_raw_pointers())
			.function("delMessage", 		&INScoreAdapter::delMessage, allow_raw_pointers())

			.function("msgAddStr", 			select_overload<void(MessagePtr, const std::string&)> 	(&INScoreAdapter::add), allow_raw_pointers())
			.function("msgAddF", 			select_overload<void(MessagePtr, float)>		(&INScoreAdapter::add), allow_raw_pointers())
			.function("msgAddI", 			select_overload<void(MessagePtr, int)>			(&INScoreAdapter::add), allow_raw_pointers())

			.function("version", 			&INScoreAdapter::version )
			.function("versionStr", 		&INScoreAdapter::versionStr )
			.function("guidoversion", 		&INScoreAdapter::guidoversion )
			.function("musicxmlversion", 	&INScoreAdapter::musicxmlversion );

	// Binding C++ class for INScoreGlue
	class_<INScoreJSGlue>("INScoreJSGlue")
			.constructor<>()

			.function("showMouse", 			&INScoreJSGlue::showMouse)
			.function("openUrl", 			&INScoreJSGlue::openUrl, allow_raw_pointers())
			.function("startView", 			&INScoreJSGlue::startView )
			.function("stopView", 			&INScoreJSGlue::stopView )
			.function("viewVersion", 		&INScoreJSGlue::viewVersion )
			.function("getIP", 				&INScoreJSGlue::getIP );

	class_<INScoreGlue>("INScoreGlue")
			.function("getRate", 			&INScoreGlue::getRate)
			.function("timeTask", 			&INScoreGlue::timeTask)
			.function("sorterTask", 		&INScoreGlue::sorterTask );

	// Black box object, just for passing argument pointer in method to and from javascript.
	class_<Message>("Message");
}
