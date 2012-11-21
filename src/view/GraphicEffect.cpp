/*

  INScore Project

  Copyright (C) 2011  Grame

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


#include <string>

#include <QColor>
#include <QGraphicsEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsDropShadowEffect>

#include "GraphicEffect.h"

using namespace std;

namespace inscore
{

static const char * kNone		= "none";
static const char * kBlur		= "blur";
static const char * kColorize	= "colorize";
static const char * kShadow		= "shadow";

static const char * kPerformanceHint	= "performance";
static const char * kQualityHint		= "quality";
static const char * kAnimationHint		= "animation";

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::buildBlurEffect (const IMessage* msg)
{
	int radius = 5;
	string hintStr;
	if ((msg->size() > 1) && (!msg->param(1, radius))) return 0;
	if ((msg->size() > 2) && (!msg->param(2, hintStr))) return 0;
	QGraphicsBlurEffect::BlurHints hint = QGraphicsBlurEffect::PerformanceHint;
	if (hintStr == kPerformanceHint)
		hint = QGraphicsBlurEffect::PerformanceHint;
	else if (hintStr == kQualityHint)
		hint = QGraphicsBlurEffect::QualityHint;
	else if (hintStr == kAnimationHint)
		hint = QGraphicsBlurEffect::AnimationHint;

	QGraphicsBlurEffect * effect = new QGraphicsBlurEffect;
	effect->setBlurRadius (qreal(radius));
	effect->setBlurHints (hint);
	return effect;
}

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::buildColorizeEffect (const IMessage* msg)
{
	QColor color(0, 0, 192);
	float strength = 1.0;

	if ((msg->size() > 1) && (!msg->param(1, strength))) return 0;
	if (msg->size() > 4) {
		int r, g, b;
		if (!msg->param(2, r)) return 0;
		if (!msg->param(3, g)) return 0;
		if (!msg->param(4, b)) return 0;
		color.setRgb (r, g, b);
	}

	QGraphicsColorizeEffect * effect = new QGraphicsColorizeEffect;
	effect->setColor (color);
	effect->setStrength (strength);
	return effect;
}

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::buildShadowEffect (const IMessage* msg)
{
	QColor color(63, 63, 63, 180);
	int radius = 1;
	int xoffset = 8, yoffset = 8;

	if (msg->size() > 2) {
		if (!msg->param(1, xoffset)) return 0;
		if (!msg->param(2, yoffset)) return 0;
	}
	if (msg->size() > 6) {
		int r, g, b, a;
		if (!msg->param(3, r)) return 0;
		if (!msg->param(4, g)) return 0;
		if (!msg->param(5, b)) return 0;
		if (!msg->param(6, a)) return 0;
		color.setRgb (r, g, b, a);
	}
	if ((msg->size() > 7) && (!msg->param(7, radius))) return 0;

	QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect;
	effect->setOffset (qreal(xoffset), qreal(yoffset));
	effect->setColor (color);
	effect->setBlurRadius (qreal(radius));
	return effect;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus GraphicEffect::set (const IMessage* msg)
{
	if (msg->size() >= 1) {
		std::string effect;
		if (msg->param(0, effect)) return MsgHandler::kBadParameters;
		if ( effect == kNone) return MsgHandler::kProcessed;
		
		if ( effect == kBlur)			fEffect = buildBlurEffect (msg);
		else if ( effect == kColorize) 	fEffect = buildColorizeEffect (msg);
		else if ( effect == kShadow) 	fEffect = buildShadowEffect (msg);
		if (fEffect) return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::get () const			{ return fEffect; }

//--------------------------------------------------------------------------
static string blurHint2string ( QGraphicsBlurEffect::BlurHints hint)
{
	switch (hint) {
		case QGraphicsBlurEffect::QualityHint:		return kQualityHint;
		case QGraphicsBlurEffect::AnimationHint:	return kAnimationHint;
		default: return kPerformanceHint;
	}
}

//--------------------------------------------------------------------------
static void putColor ( const QColor& color, IMessage* msg, bool alpha)
{
	msg->add (color.red());
	msg->add (color.green());
	msg->add (color.blue());
	if (alpha)	msg->add (color.alpha());
}

//--------------------------------------------------------------------------
void GraphicEffect::get (IMessage* msg) const
{
	if (fEffect) {
		QGraphicsBlurEffect * blur = dynamic_cast<QGraphicsBlurEffect*> (fEffect);
		if (blur) {
			msg->add (string(kBlur));
			msg->add (int(blur->blurRadius()));
			msg->add (blurHint2string(blur->blurHints()));
			return;
		}
		QGraphicsDropShadowEffect * shadow = dynamic_cast<QGraphicsDropShadowEffect*> (fEffect);
		if (shadow) {
			msg->add (string(kShadow));
			msg->add (int(shadow->xOffset()));
			msg->add (int(shadow->yOffset()));
			putColor (shadow->color(), msg, true);
			msg->add (int(shadow->blurRadius()));
			return;
		}
		QGraphicsColorizeEffect * col = dynamic_cast<QGraphicsColorizeEffect*> (fEffect);
		if (col) {
			msg->add (string(kColorize));
			msg->add (float(col->strength()));
			putColor (col->color(), msg, false);
			return;
		}
	}
	msg->add (string(kNone));
}

IMessage& operator <<(IMessage& msg, const GraphicEffect& effect)
{
	effect.get (&msg);
	return msg;
}

} // end namespoace
