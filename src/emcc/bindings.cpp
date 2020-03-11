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

/*
 * Structure and enum binding.
 * This structures can be created and manipulated in javascript side like json object and passed to C++ method.
 */
EMSCRIPTEN_BINDINGS(CStruct) {
	
//	value_object<Guido2MidiParams>("Guido2MidiParams")
//			.field("fTempo", &Guido2MidiParams::fTempo)
//			.field("fTicks", &Guido2MidiParams::fTicks)
//			.field("fChan", &Guido2MidiParams::fChan)
//			.field("fIntensity", &Guido2MidiParams::fIntensity)
//			.field("fAccentFactor", &Guido2MidiParams::fAccentFactor)
//			.field("fMarcatoFactor", &Guido2MidiParams::fMarcatoFactor)
//			.field("fDFactor", &Guido2MidiParams::fDFactor)
//			.field("fStaccatoFactor", &Guido2MidiParams::fStaccatoFactor)
//			.field("fSlurFactor", &Guido2MidiParams::fSlurFactor)
//			.field("fTenutoFactor", &Guido2MidiParams::fTenutoFactor)
//			.field("fFermataFactor", &Guido2MidiParams::fFermataFactor);
//
//	value_object<GuidoLayoutSettings>("GuidoLayoutSettings")
//			.field("systemsDistance", &GuidoLayoutSettings::systemsDistance)
//			.field("systemsDistribution", &GuidoLayoutSettings::systemsDistribution)
//			.field("systemsDistribLimit", &GuidoLayoutSettings::systemsDistribLimit)
//			.field("force", &GuidoLayoutSettings::force)
//			.field("spring", &GuidoLayoutSettings::spring)
//			.field("neighborhoodSpacing", &GuidoLayoutSettings::neighborhoodSpacing)
//			.field("optimalPageFill", &GuidoLayoutSettings::optimalPageFill)
//			.field("resizePage2Music", &GuidoLayoutSettings::resizePage2Music)
//			.field("proportionalRenderingForceMultiplicator", &GuidoLayoutSettings::proportionalRenderingForceMultiplicator)
//			.field("checkLyricsCollisions", &GuidoLayoutSettings::checkLyricsCollisions);
//
//
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
//	// Pitch constants
//	constant("kCLine", kCLine);
//	constant("kCSharpLine", kCSharpLine);
//	constant("kDLine", kDLine);
//	constant("kDSharpLine", kDSharpLine);
//	constant("kELine", kELine);
//	constant("kFLine", kFLine);
//	constant("kFSharpLine", kFSharpLine);
//	constant("kGLine", kGLine);
//	constant("kGSharpLine", kGSharpLine);
//	constant("kALine", kALine);
//	constant("kASharpLine", kASharpLine);
//	constant("kBLine", kBLine);
//	constant("kAutoLines", kAutoLines);
//	constant("kNoLine", kNoLine);
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
