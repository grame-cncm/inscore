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

using namespace emscripten;

/*
 * Structure and enum binding.
 * This structures can be created and manipulated in javascript side like json object and passed to C++ method.
 */
//EMSCRIPTEN_BINDINGS(CStruct) {
//
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
//}

/*
 * C++ class binding.
 * This classes can be used in javascript side.
 */

using namespace inscore;
EMSCRIPTEN_BINDINGS(EngineAdapter) {

	// Binding C++ class adapter for guidoEngine
	class_<INScoreAdapter>("INScoreAdapter")
			//.smart_ptr_constructor("GuidoEngineAdapter",&std::make_shared<GuidoEngineAdapter>)
			.constructor<>()

			.function("start", 				&INScoreAdapter::start, allow_raw_pointers())
			.function("stop", 				&INScoreAdapter::stop, allow_raw_pointers())
			.function("restartNetwork", 	&INScoreAdapter::restartNetwork )
			.function("stopNetwork", 		&INScoreAdapter::stopNetwork )

			.function("postMessage", 		select_overload<void(const char*, INScore::MessagePtr)>(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStr", 	select_overload<void(const char*, const char*)>(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStrI", 	select_overload<void(const char*, const char*, int)>(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStrF", 	select_overload<void(const char*, const char*, float)>(&INScoreAdapter::postMessage), allow_raw_pointers())
			.function("postMessageStrStr", 	select_overload<void(const char*, const char*, const char*)>(&INScoreAdapter::postMessage), allow_raw_pointers())

			.function("delayMessage", 		&INScoreAdapter::delayMessage, allow_raw_pointers())
			.function("newMessage", 		select_overload<INScore::MessagePtr()>(&INScoreAdapter::newMessage), allow_raw_pointers())
			.function("newMessageM", 		select_overload<INScore::MessagePtr(const char*)>(&INScoreAdapter::newMessage), allow_raw_pointers())
			.function("delMessage", 		&INScoreAdapter::delMessage, allow_raw_pointers())

			.function("msgAddStr", 			select_overload<void(INScore::MessagePtr, const char*)>(&INScoreAdapter::add), allow_raw_pointers())
			.function("msgAddF", 			select_overload<void(INScore::MessagePtr, float)>(&INScoreAdapter::add), allow_raw_pointers())
			.function("msgAddI", 			select_overload<void(INScore::MessagePtr, int)>(&INScoreAdapter::add), allow_raw_pointers())

			.function("version", 			&INScoreAdapter::version )
			.function("versionStr", 		&INScoreAdapter::versionStr )
			.function("guidoversion", 		&INScoreAdapter::guidoversion )
			.function("musicxmlversion", 	&INScoreAdapter::musicxmlversion );

	// Black box object, just for passing argument pointer in method to and from javascript.
//	class_<inscore::INScore::MessagePtr>("MessagePtr");
//	class_<inscore::GraphicUpdateListener>("GraphicUpdateListener");
//	class_<inscore::INScoreGlue>("INScoreGlue");
//	class_<inscore::INScoreApplicationGlue>("INScoreApplicationGlue");
}

