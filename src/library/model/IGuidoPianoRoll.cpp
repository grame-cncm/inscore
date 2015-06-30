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
    fType = kSimplePianoRoll;
	fKeyboard = false;
	fAutoVoiceColor = false;
	fMeasureBars = false;
	fPitchLines = kAutoLines;

	fGetMsgHandlerMap[ktype_GetSetMethod]	= TGetParamMethodHandler<IGuidoPianoRoll, string (IGuidoPianoRoll::*)() const>::create(this, &IGuidoPianoRoll::getPianoRollType);
	fMsgHandlerMap[ktype_GetSetMethod]		= TMethodMsgHandler<IGuidoPianoRoll>::create(this, &IGuidoPianoRoll::setPianoRollType);

	//setLimits

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
MsgHandler::msgStatus IGuidoPianoRoll::setPianoRollType(const IMessage* msg)
{
	if(msg->size() != 1)
		return MsgHandler::kBadParameters;

	string type;
	if (msg->param(0, type)) {
		if(type == "simple")
			fType = kSimplePianoRoll;
		else if(type == "trajectory")
			fType = kTrajectoryPianoRoll;
		else return MsgHandler::kBadParameters;
	} else {
		return MsgHandler::kBadParameters;
	}
	GuidoDestroyPianoRoll(fPianoRoll);
	fPianoRoll = GuidoAR2PianoRoll(fType, fArHandler);
	applyAllSettings();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
string IGuidoPianoRoll::getPianoRollType() const
{
	if(fType == kTrajectoryPianoRoll)
		return "trajectory";
	return "simple";
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::setLimits(LimitParams lp)
{
	fLimits = lp;
	GuidoPianoRollSetLimits(fPianoRoll, fLimits);
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
			GuidoPianoRollSetRGBColorToVoice(fPianoRoll, i, 0, 0, 0, 255);
		}
		return MsgHandler::kProcessed;
	}

	if(size == 1) {
		// reset color of the specified voice
		int voice;
		if (!msg->param(0, voice)) return MsgHandler::kBadParameters;
		fVoicesColor.erase(voice);
		GuidoPianoRollSetRGBColorToVoice(fPianoRoll, voice, 0, 0, 0, 255);
		return MsgHandler::kProcessed;
	}

	if(size % 5 != 0)
		return MsgHandler::kBadParameters;
	int voice;
	if (!msg->param(0, voice)) return MsgHandler::kBadParameters;
	int r;
	if (!msg->param(1, r)) return MsgHandler::kBadParameters;
	int g;
	if (!msg->param(2, g)) return MsgHandler::kBadParameters;
	int b;
	if (!msg->param(3, b)) return MsgHandler::kBadParameters;
	int a;
	if (!msg->param(4, a)) return MsgHandler::kBadParameters;

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

	fPianoRoll = GuidoAR2PianoRoll(fType, fArHandler);
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
}

}
