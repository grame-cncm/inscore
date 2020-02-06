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

using namespace emscripten;

/*
 * C++ class binding.
 * The javascript interface to inscore classes
 */

using namespace inscore;
EMSCRIPTEN_BINDINGS(EngineAdapter) {

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
