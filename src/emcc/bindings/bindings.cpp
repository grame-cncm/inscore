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
#include "bindings.h"

using namespace emscripten;
using namespace std;
using namespace inscore;

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

		.function("adapter", 		&IObjectAdapter::adapter, allow_raw_pointers())
//		.function("create", 		&IObjectAdapter::create, allow_raw_pointers())
//		.function("del", 			&IObjectAdapter::del, allow_raw_pointers())

		.function("newData",  		&IObjectAdapter::newData)
		.function("deleted",  		&IObjectAdapter::deleted)
		.function("ready",  		&IObjectAdapter::ready)

		.function("updateWidth", 	&IObjectAdapter::updateWidth)
		.function("updateHeight", 	&IObjectAdapter::updateHeight)
		.function("updateViewBoundingRect", &IObjectAdapter::updateViewBoundingRect)
		.function("updateDuration", &IObjectAdapter::updateDuration)
		.function("updateTime2TimeMap", 	&IObjectAdapter::updateTime2TimeMap)
		.function("updateGraphic2TimeMap",	&IObjectAdapter::updateGraphic2TimeMap)

		.function("event",			&IObjectAdapter::event)
		.function("keyEvent",		&IObjectAdapter::keyEvent)

		.function("setAudioInOut",	&IObjectAdapter::setAudioInOut)
		.function("setFaustUI",		&IObjectAdapter::setFaustUI, allow_raw_pointers())

		.function("getMasters",  	&IObjectAdapter::getMasters, allow_raw_pointers())
		.function("getOSCAddress",  &IObjectAdapter::getOSCAddress, allow_raw_pointers())
		.function("getUpdateInfos", &IObjectAdapter::getUpdateInfos, allow_raw_pointers())
		.function("getTextInfos",   &IObjectAdapter::getTextInfos, allow_raw_pointers())
		.function("getLineInfos",   &IObjectAdapter::getLineInfos, allow_raw_pointers())
		.function("getFile",   		&IObjectAdapter::getFile, allow_raw_pointers())
		.function("getRadius",   	&IObjectAdapter::getRadius, allow_raw_pointers())
		.function("getArcInfos",   	&IObjectAdapter::getArcInfos, allow_raw_pointers())
		.function("getPolygonInfos",&IObjectAdapter::getPolygonInfos)
		.function("getCurveInfos",  &IObjectAdapter::getCurveInfos)
		.function("getGuidoInfos",  &IObjectAdapter::getGuidoInfos)
		.function("getGuidoStream",  &IObjectAdapter::getGuidoStream)
		.function("getPianorollInfos", &IObjectAdapter::getPianorollInfos)
		.function("getXMLInfos",    &IObjectAdapter::getXMLInfos)
		.function("getMediaInfos",  &IObjectAdapter::getMediaInfos)
		.function("getSceneInfos",  &IObjectAdapter::getSceneInfos)
		.function("getSVGInfos",    &IObjectAdapter::getSVGInfos)
		.function("getFaustInfos",  &IObjectAdapter::getFaustInfos)
		.function("getAudioInfos",  &IObjectAdapter::getAudioInfos)
		.function("getIOInfos",  	&IObjectAdapter::getIOInfos)
		.function("getMaps",    	&IObjectAdapter::getMaps);

	register_vector<float>		("vector<float>");
	register_vector<int>		("vector<int>");
	register_vector<string> 	("vector<string>");
	register_vector<JSRect> 	("vector<JSRect>");
	register_vector<JSMaster>	("vector<JSMaster>");
	register_vector<JSFaustParamValue> ("vector<JSFaustParamValue>");
	register_vector<JSFaustKeyValue>   ("vector<JSFaustKeyValue>");


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
