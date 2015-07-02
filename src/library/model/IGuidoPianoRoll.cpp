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

	fGetMsgHandlerMap[kcliptime_GetSetMethod]	= TGetParamMethodHandler<IGuidoPianoRoll, string (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getClipTime);
	fMsgHandlerMap[kcliptime_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setClipTime);

	fGetMultiMsgHandlerMap[kclippitch_GetSetMethod]	= TGetParamMultiMethodHandler<IGuidoPianoRoll, SIMessageList (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getClipPitch);
	fMsgHandlerMap[kclippitch_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setClipPitch);

	fGetMsgHandlerMap[kkeyboard_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fKeyboard);
	fMsgHandlerMap[kkeyboard_GetSetMethod]		= TSetMethodMsgHandler<IGuidoPianoRoll, bool>::create(this, &IGuidoPianoRoll::enableKeyboard);

	fGetMsgHandlerMap[kautoVoicesColoration_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fAutoVoiceColor);
	fMsgHandlerMap[kautoVoicesColoration_GetSetMethod]		= TSetMethodMsgHandler<IGuidoPianoRoll, bool>::create(this, &IGuidoPianoRoll::enableAutoVoicesColoration);

	fGetMsgHandlerMap[kmeasureBars_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fMeasureBars);
	fMsgHandlerMap[kmeasureBars_GetSetMethod]		= TSetMethodMsgHandler<IGuidoPianoRoll, bool>::create(this, &IGuidoPianoRoll::enableMeasureBars);

	fGetMultiMsgHandlerMap[kvoiceColor_GetSetMethod]	= TGetParamMultiMethodHandler<IGuidoPianoRoll, SIMessageList (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getRGBColorToVoice);
	fMsgHandlerMap[kvoiceColor_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setRGBColorToVoice);

	fGetMsgHandlerMap[kpitchLines_GetSetMethod]	= TGetParamMethodHandler<IGuidoPianoRoll, string (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getPitchLinesDisplayMode);
	fMsgHandlerMap[kpitchLines_GetSetMethod]	= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setPitchLinesDisplayMode);
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

    updatePianoRoll();
	return status;
}

//--------------------------------------------------------------------------
string IGuidoPianoRoll::getClipTime() const
{
	libmapping::rational start(fLimits.startDate.num, fLimits.startDate.denom);
	libmapping::rational end(fLimits.endDate.num, fLimits.endDate.denom);
	return string(start) + " " + string(end);
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
SIMessageList IGuidoPianoRoll::getClipPitch() const
{
	SIMessageList list = IMessageList::create();
	SIMessage msg = IMessage::create (getOSCAddress(), kclippitch_GetSetMethod);
	IMessage::argslist values;
	values.push_back(new IMsgParam<int>(fLimits.lowPitch));
	values.push_back(new IMsgParam<int>(fLimits.highPitch));
	msg->add (values);
	list->list().push_back(msg);
	return list;
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
	fKeyboard = enable;
	GuidoPianoRollEnableKeyboard(fPianoRoll, fKeyboard);
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
		IMessage::argslist values;
		values.push_back(new IMsgParam<int>(i->first));
		values.push_back(new IMsgParam<int>(i->second.getR()));
		values.push_back(new IMsgParam<int>(i->second.getG()));
		values.push_back(new IMsgParam<int>(i->second.getB()));
		values.push_back(new IMsgParam<int>(i->second.getA()));
		msg->add (values);
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
		fPitchLines = kNoLine;
	} else {
		int allLines = 0;
		int line;
		string str;

		for (int i = 0; i < size; i++) {
			if (msg->param(i, str)) {
				if(str== "auto") {
					allLines = kAutoLines;
					break;
				}
				if(str == "C")
					line = kCLine;
				else if(str == "C#")
					line = kCSharpLine;
				else if(str == "D")
					line = kDLine;
				else if(str == "D#")
					line = kDSharpLine;
				else if(str == "E")
					line = kELine;
				else if(str == "F")
					line = kFLine;
				else if(str == "F#")
					line = kFSharpLine;
				else if(str == "G")
					line = kGLine;
				else if(str == "G#")
					line = kGSharpLine;
				else if(str == "A")
					line = kALine;
				else if(str == "A#")
					line = kASharpLine;
				else if(str == "B")
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
string IGuidoPianoRoll::getPitchLinesDisplayMode() const
{
	stringstream sstr;
	if(fPitchLines == kNoLine)
		return "";
	if(fPitchLines == kAutoLines)
		return "auto";

	if(fPitchLines & kCLine)
		sstr << "C";
	if(fPitchLines & kCSharpLine)
		sstr << " " << "C#";
	if(fPitchLines & kDLine)
		sstr << " " << "D";
	if(fPitchLines & kDSharpLine)
		sstr << " " << "D#";
	if(fPitchLines & kELine)
		sstr << " " << "E";
	if(fPitchLines & kFLine)
		sstr << " " << "F";
	if(fPitchLines & kFSharpLine)
		sstr << " " << "F#";
	if(fPitchLines & kGLine)
		sstr << " " << "G";
	if(fPitchLines & kGSharpLine)
		sstr << " " << "G#";
	if(fPitchLines & kALine)
		sstr << " " << "A";
	if(fPitchLines & kASharpLine)
		sstr << " " << "A#";
	if(fPitchLines & kBLine)
		sstr << " " << "B";

	return sstr.str();
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
	GuidoCloseParser(parser);

	fPianoRoll = GuidoAR2PianoRoll(kSimplePianoRoll, fArHandler);
	applyAllSettings();
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::applyAllSettings()
{
	//GuidoPianoRollSetLimits(fPianoRoll, fLimits);
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
