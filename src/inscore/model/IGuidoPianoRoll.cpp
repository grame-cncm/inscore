/*

  INScore Project

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

#include "IGuidoPianoRoll.h"
#include "IGuidoStream.h"
#include "IScene.h"
#include "Updater.h"
#include "VGuidoItemView.h"
#include "rational.h"

#include <sstream>

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IGuidoPianoRoll::kGuidoPianoRollType("pianoroll");

//--------------------------------------------------------------------------
IGuidoPianoRoll::IGuidoPianoRoll( const std::string& name, IObject * parent )
	: IGuidoCode (name, parent), fArHandler(0), fPianoRoll(0)
{
	fTypeString = kGuidoPianoRollType;

	// Default parameters value
	fKeyboard = false;
	fAutoVoiceColor = false;
	fMeasureBars = false;
	fPitchLines = kAutoLines;
	fLimits.lowPitch = -1;
	fLimits.highPitch = -1;
	GuidoDate init;
	init.num = 0;
	init.denom = 0;
	fLimits.startDate = init;
	fLimits.endDate = init;
	setWidth(1);
	setHeight(0.5);
	setColor(IColor(0,0,0,255));

	fMsgHandlerMap[kwidth_GetSetMethod]		= TSetMethodMsgHandler<IObject, float>::create(this, &IObject::setWidth);
	fMsgHandlerMap[kheight_GetSetMethod]	= TSetMethodMsgHandler<IObject, float>::create(this, &IObject::setHeight);
	fMsgHandlerMap[kcliptime_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setClipTime);
	fMsgHandlerMap[kclippitch_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setClipPitch);
	fMsgHandlerMap[kclippitch_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setClipPitch);
	fMsgHandlerMap[kkeyboard_GetSetMethod]	= TSetMethodMsgHandler<IGuidoPianoRoll, bool>::create(this, &IGuidoPianoRoll::enableKeyboard);
	fMsgHandlerMap[kmeasureBars_GetSetMethod]= TSetMethodMsgHandler<IGuidoPianoRoll, bool>::create(this, &IGuidoPianoRoll::enableMeasureBars);
	fMsgHandlerMap[kvoiceColor_GetSetMethod] = TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setRGBColorToVoice);
	fMsgHandlerMap[kpitchLines_GetSetMethod] = TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setPitchLinesDisplayMode);
	fMsgHandlerMap[kautoVoicesColoration_GetSetMethod]	= TSetMethodMsgHandler<IGuidoPianoRoll, bool>::create(this, &IGuidoPianoRoll::enableAutoVoicesColoration);

	fGetMsgHandlerMap[kcliptime_GetSetMethod] = TGetParamMethodHandler<IGuidoPianoRoll, vector<int> (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getClipTime);
	fGetMsgHandlerMap[kclippitch_GetSetMethod]	= TGetParamMethodHandler<IGuidoPianoRoll, vector<int> (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getClipPitch);
	fGetMsgHandlerMap[kkeyboard_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fKeyboard);
	fGetMsgHandlerMap[kautoVoicesColoration_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fAutoVoiceColor);
	fGetMsgHandlerMap[kmeasureBars_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fMeasureBars);
	fGetMultiMsgHandlerMap[kvoiceColor_GetSetMethod]	= TGetParamMultiMethodHandler<IGuidoPianoRoll, SIMessageList (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getRGBColorToVoice);
	fGetMsgHandlerMap[kpitchLines_GetSetMethod]	= TGetParamMethodHandler<IGuidoPianoRoll, vector<string> (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getPitchLinesDisplayMode);
}

IGuidoPianoRoll::~IGuidoPianoRoll()
{
    GuidoDestroyPianoRoll(fPianoRoll);
	GuidoFreeAR(fArHandler);
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::accept (Updater* u)
{
	u->updateTo (SIGuidoPianoRoll(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRoll::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = IGuidoCode::set(msg);

	//updatePianoRoll();		//already called by newData
	return status;
}

//--------------------------------------------------------------------------
vector<int> IGuidoPianoRoll::getClipTime() const
{
	vector<int> limits;
	if(fLimits.startDate.num != 0 || fLimits.startDate.denom != 0 || fLimits.endDate.num != 0 || fLimits.endDate.denom != 0) {
		limits.push_back(fLimits.startDate.num);
		limits.push_back(fLimits.startDate.denom);
		limits.push_back(fLimits.endDate.num);
		limits.push_back(fLimits.endDate.denom);
	}
	return limits;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRoll::setClipTime(const IMessage *msg)
{
	const int size = msg->size();
	RationalInterval interval;
	if(size == 0) {
		// reset time limits
		GuidoDate init;
		init.num = 0;
		init.denom = 0;
		fLimits.startDate = init;
		fLimits.endDate = init;
		GuidoPianoRollSetLimits(fPianoRoll, fLimits);
		return MsgHandler::kProcessed;
	} else if(size == 2) {
		interval = Tools::readRationalInterval(msg, false);
	} else if(size == 4) {
		interval = Tools::readRationalInterval(msg, true);
	} else return MsgHandler::kBadParameters;

	if(interval.first().getDenominator() == 0 || interval.second().getDenominator() == 0 ) {
		return MsgHandler::kBadParameters;
	}

	GuidoDate guidoDate;
	guidoDate.num = interval.first().getNumerator();
	guidoDate.denom = interval.first().getDenominator();
	fLimits.startDate = guidoDate;

	guidoDate.num = interval.second().getNumerator();
	guidoDate.denom = interval.second().getDenominator();
	fLimits.endDate = guidoDate;

	GuidoPianoRollSetLimits(fPianoRoll, fLimits);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
vector<int> IGuidoPianoRoll::getClipPitch() const
{
	vector<int> pitch;
	if(fLimits.lowPitch != fLimits.highPitch) {
		pitch.push_back(fLimits.lowPitch);
		pitch.push_back(fLimits.highPitch);
	}
	return pitch;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRoll::setClipPitch(const IMessage *msg)
{
	const int size = msg->size();
	if(size == 0) {
		// reset pitch limit
		fLimits.lowPitch = -1;
		fLimits.highPitch = -1;
		GuidoPianoRollSetLimits(fPianoRoll, fLimits);
	} else if(size == 2) {
		int low, high;
		if(!msg->param(0, low)) return MsgHandler::kBadParameters;
		if(!msg->param(1, high)) return MsgHandler::kBadParameters;
		fLimits.lowPitch = low;
		fLimits.highPitch = high;
		GuidoPianoRollSetLimits(fPianoRoll, fLimits);
	} else return MsgHandler::kBadParameters;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::enableKeyboard(bool enable)
{
	if (fKeyboard == enable) return;
	fKeyboard = enable;
	GuidoPianoRollEnableKeyboard(fPianoRoll, fKeyboard);
	localMapModified (true);
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::enableAutoVoicesColoration(bool enable)
{
	fAutoVoiceColor = enable;
	GuidoPianoRollEnableAutoVoicesColoration(fPianoRoll, fAutoVoiceColor);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRoll::setRGBColorToVoice(const IMessage* msg)
{
	const int size = msg->size();

	if(size == 0) {
		// reset color of all voice to black
		fVoicesColor.clear();
		const int voices = GuidoCountVoices(fArHandler);
		for(int i = 1; i <= voices; i++) {
			GuidoPianoRollRemoveColorToVoice(fPianoRoll, i);
		}
		return MsgHandler::kProcessed;
	}

	if(size == 1) {
		// reset color of the specified voice
		int voice;
		if (!msg->param(0, voice)) return MsgHandler::kBadParameters;
		fVoicesColor.erase(voice);
		GuidoPianoRollRemoveColorToVoice(fPianoRoll, voice);
		return MsgHandler::kProcessed;
	}

	int voice;
	if (!msg->param(0, voice)) return MsgHandler::kBadParameters;

	int r, g, b, a;
	if(!IColor::getRGBA(msg, r, g, b, a, 1)) return MsgHandler::kBadParameters;

	fVoicesColor[voice] = IColor(r, g, b, a);
	GuidoPianoRollSetRGBColorToVoice(fPianoRoll, voice, r, g, b, a);

	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
SIMessageList IGuidoPianoRoll::getRGBColorToVoice() const
{
	SIMessageList list = IMessageList::create();

	for (map<int, IColor>::const_iterator i = fVoicesColor.begin(); i != fVoicesColor.end(); i++) {
		SIMessage msg = IMessage::create (getOSCAddress(), kvoiceColor_GetSetMethod);
		msg->add (i->first);
		msg->add (i->second.getR());
		msg->add (i->second.getG());
		msg->add (i->second.getB());
		msg->add (i->second.getA());
		list->list().push_back(msg);
	}
	return list;
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::enableMeasureBars(bool enable)
{
	fMeasureBars = enable;
	GuidoPianoRollEnableMeasureBars(fPianoRoll, fMeasureBars);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRoll::setPitchLinesDisplayMode(const IMessage* msg)
{
	const int size = msg->size();
	if(!size) {
		fPitchLines = kAutoLines;
	} else {
		int allLines = 0;
		int line;
		string str;

		for (int i = 0; i < size; i++) {
			if (msg->param(i, str)) {
				if(str== "empty") {
					allLines = kNoLine;
					break;
				}
				if(str == "C" || str == "c")
					line = kCLine;
				else if(str == "C#" || str == "c#")
					line = kCSharpLine;
				else if(str == "D" || str == "d")
					line = kDLine;
				else if(str == "D#" || str == "d#")
					line = kDSharpLine;
				else if(str == "E" || str == "e")
					line = kELine;
				else if(str == "F" || str == "f")
					line = kFLine;
				else if(str == "F#" || str == "f#")
					line = kFSharpLine;
				else if(str == "G" || str == "g")
					line = kGLine;
				else if(str == "G#" || str == "g#")
					line = kGSharpLine;
				else if(str == "A" || str == "a")
					line = kALine;
				else if(str == "A#" || str == "a#")
					line = kASharpLine;
				else if(str == "B" || str == "b")
					line = kBLine;
				else return MsgHandler::kBadParameters;
			}
			allLines |= line;
		}
		fPitchLines = allLines;
	}
	GuidoPianoRollSetPitchLinesDisplayMode(fPianoRoll, fPitchLines);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
vector<string> IGuidoPianoRoll::getPitchLinesDisplayMode() const
{
	vector<string> pitchs;

	if(fPitchLines == kNoLine) {
		pitchs.push_back("empty");
		return pitchs;
	}
	if(fPitchLines == kAutoLines) {
		return pitchs;
	}

	if(fPitchLines & kCLine)
		pitchs.push_back("c");
	if(fPitchLines & kCSharpLine)
		pitchs.push_back("c#");
	if(fPitchLines & kDLine)
		pitchs.push_back("d");
	if(fPitchLines & kDSharpLine)
		pitchs.push_back("d#");
	if(fPitchLines & kELine)
		pitchs.push_back("e");
	if(fPitchLines & kFLine)
		pitchs.push_back("f");
	if(fPitchLines & kFSharpLine)
		pitchs.push_back("f#");
	if(fPitchLines & kGLine)
		pitchs.push_back("g");
	if(fPitchLines & kGSharpLine)
		pitchs.push_back("g#");
	if(fPitchLines & kALine)
		pitchs.push_back("a");
	if(fPitchLines & kASharpLine)
		pitchs.push_back("a#");
	if(fPitchLines & kBLine)
		pitchs.push_back("b");

	return pitchs;
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::updatePianoRoll()
{
    GuidoParser * parser = GuidoOpenParser ();
    IGuidoStream * stream = dynamic_cast<IGuidoStream*>(this);
	GuidoDestroyPianoRoll(fPianoRoll);
	GuidoFreeAR(fArHandler);
    if(stream)
		fArHandler = GuidoStream2AR(parser, stream->getGuidoStream());
    else
		fArHandler = GuidoString2AR(parser, fGMN.c_str());

	if(!fArHandler){
		int line;
		int col;
		GuidoParserGetErrorCode(parser, line, col, 0);
		stringstream sstr;
		sstr << " (line " << line << ", col " << col << ")";
		ITLErr << getOSCAddress() << "invalid gmn code:" << sstr.str() << ITLEndl;
		return ;
	}
	GuidoCloseParser(parser);

	fPianoRoll = GuidoAR2PianoRoll(kSimplePianoRoll, fArHandler);
	applyAllSettings();
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::updatePianoRoll(string &midiFile)
{
	GuidoDestroyPianoRoll(fPianoRoll);
	GuidoFreeAR(fArHandler);
	fPianoRoll = GuidoMidi2PianoRoll(kSimplePianoRoll, midiFile.c_str());
	applyAllSettings();
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::applyAllSettings()
{
	GuidoPianoRollEnableKeyboard(fPianoRoll, fKeyboard);

	for (map<int, IColor>::const_iterator i = fVoicesColor.begin(); i != fVoicesColor.end(); i++) {
		GuidoPianoRollSetRGBColorToVoice(fPianoRoll, i->first, i->second.getR(), i->second.getG(), i->second.getB(), i->second.getA());
	}
	GuidoPianoRollEnableAutoVoicesColoration(fPianoRoll, fAutoVoiceColor);
	GuidoPianoRollEnableMeasureBars(fPianoRoll, fMeasureBars);
	GuidoPianoRollSetPitchLinesDisplayMode(fPianoRoll, fPitchLines);
	GuidoPianoRollSetLimits(fPianoRoll, fLimits);
}

}
