/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#include "IEffect.h"
#include "IMessage.h"
#include "IMessageStream.h"

using namespace std;

namespace inscore
{

static const char* kNoneStr 	= "none";
static const char* kBlurStr 	= "blur";
static const char* kColorizeStr = "colorize";
static const char* kShadowStr 	= "shadow";

static const char* kPerformanceHintStr 	= "performance";
static const char* kQualityHintStr 		= "quality";
static const char* kAnimationHintStr 	= "animation";

//--------------------------------------------------------------------------
// IEffect implementation
//--------------------------------------------------------------------------
bool IEffect::getColor (const IMessage* msg, int i, IColor& color)
{
	if (msg->size() > i + 2) {
		int r, g, b;
		if (msg->param(i, r) && msg->param(i+1, g) && msg->param(i+2, b))
			color.setColor (IColor(r, g, b));
		else return false;
	}
	else return false;
	if (msg->size() > i + 3) {
		int a;
		if (msg->param(i+3, a)) color.setA (a);
		else return false;
	}
	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IEffect::blurEffect (const IMessage* msg)
{
	string hintStr;
	
	if ((msg->size() > 1) && (!msg->cast_param(1, fBlur.fRadius))) 	return MsgHandler::kBadParameters;
	if (msg->size() > 2) {
		if (!msg->param(2, hintStr)) 		return MsgHandler::kBadParameters;
		if (hintStr == kPerformanceHintStr)
			fBlur.fHint = kPerformance;
		else if (hintStr == kQualityHintStr)
			fBlur.fHint = kQuality;
		else if (hintStr == kAnimationHintStr)
			fBlur.fHint = kAnimation;
		else return MsgHandler::kBadParameters;
	}
	fEffect = kBlur;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IEffect::colorizeEffect (const IMessage* msg)
{
	if ((msg->size() > 1) && (!msg->cast_param(1, fColorize.fStrength))) return MsgHandler::kBadParameters;
	fColorize.fColor.setColor( IColor(0, 0, 192));		// default value
	if (msg->size() > 4)
		if (!getColor(msg, 2, fColorize.fColor))	return MsgHandler::kBadParameters;
	fEffect = kColorize;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IEffect::shadowEffect (const IMessage* msg)
{
	if (msg->size() > 2) {
		if (!msg->param(1, fShadow.fXOffset)) return MsgHandler::kBadParameters;
		if (!msg->param(2, fShadow.fYOffset)) return MsgHandler::kBadParameters;
	}
	fShadow.fColor.setColor( IColor(100, 100, 100, 50));	// default color
	fShadow.fBlur = 1;										// default blur
	if (msg->size() > 6) {
		if (!getColor(msg, 3, fShadow.fColor))							return MsgHandler::kBadParameters;
		if ((msg->size() == 8) && (!msg->cast_param(7, fShadow.fBlur)))	return MsgHandler::kBadParameters;
	}
	fEffect = kShadow;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IEffect::setEffect (const IMessage* msg)
{
	if (msg->size() >= 1) {
		std::string effect;
		if (!msg->param(0, effect)) 		return MsgHandler::kBadParameters;
		if ( effect == kNoneStr) 			{ fEffect = kNone; return MsgHandler::kProcessed; }
		else if ( effect == kBlurStr)		return blurEffect (msg);
		else if ( effect == kColorizeStr) 	return colorizeEffect (msg);
		else if ( effect == kShadowStr) 	return shadowEffect (msg);
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
const char* IEffect::blurHint2str (TBlurhint hint) const
{
	switch (hint) {
		case kAnimation:
			return kAnimationHintStr;
		case kQuality:
			return kQualityHintStr;
		case kPerformance:
		default:
			return kPerformanceHintStr;
	}
}

//--------------------------------------------------------------------------
void IEffect::getEffect (IMessage* msg) const
{
	switch (fEffect) {
		case kBlur:
			(*msg) << kBlurStr << fBlur.fRadius << blurHint2str(fBlur.fHint);
			break;
		case kShadow:
			(*msg)  << kShadowStr << fShadow.fXOffset << fShadow.fYOffset
					<< fShadow.fColor.getR() << fShadow.fColor.getG() << fShadow.fColor.getB() << fShadow.fColor.getA()
					<< fShadow.fBlur;
			break;
		case kColorize:
			(*msg)  << kColorizeStr << fColorize.fStrength << fColorize.fColor.getR() << fColorize.fColor.getG() << fColorize.fColor.getB();
			break;
		default:
			msg->add (kNoneStr);
	}
}

IMessage& operator <<(IMessage& msg, const IEffect* effect)
{
	effect->getEffect (&msg);
	return msg;
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IEffect::print (ostream& out) const
{
	out << "  effect: " << endl;
}


//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const IEffect& o)
{
	o.print(out);
	return out;
}

}
