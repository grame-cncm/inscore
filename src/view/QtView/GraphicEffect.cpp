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
#include "IEffect.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::buildBlurEffect (const IEffect* effect)
{
	QGraphicsBlurEffect::BlurHints hint = QGraphicsBlurEffect::PerformanceHint;
	switch (effect->fBlur.fHint) {
		case IEffect::kPerformance:	hint = QGraphicsBlurEffect::PerformanceHint;
			break;
		case IEffect::kAnimation:	QGraphicsBlurEffect::AnimationHint;
			break;
		case IEffect::kQuality:		QGraphicsBlurEffect::AnimationHint;
			break;
	}
	QGraphicsBlurEffect * qeffect = new QGraphicsBlurEffect;
	qeffect->setBlurRadius (qreal(effect->fBlur.fRadius));
	qeffect->setBlurHints (hint);
	return qeffect;
}

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::buildColorizeEffect (const IEffect* effect)
{
	const IColor& c = effect->fColorize.fColor;
	QColor color (c.getR(), c.getG(), c.getB());
	QGraphicsColorizeEffect * qeffect = new QGraphicsColorizeEffect;
	qeffect->setColor (color);
	qeffect->setStrength (effect->fColorize.fStrength);
	return qeffect;
}

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::buildShadowEffect (const IEffect* effect)
{
	const IColor& c = effect->fShadow.fColor;
	QColor color (c.getR(), c.getG(), c.getB(), c.getA());

	QGraphicsDropShadowEffect * qeffect = new QGraphicsDropShadowEffect;
	qeffect->setOffset (qreal(effect->fShadow.fXOffset), qreal(effect->fShadow.fYOffset));
	qeffect->setColor (color);
	qeffect->setBlurRadius (qreal(effect->fShadow.fBlur));
	return qeffect;
}

//--------------------------------------------------------------------------
QGraphicsEffect * GraphicEffect::set (const IEffect* effect)
{
	switch (effect->effectType()) {
		case IEffect::kNone: 		return 0;
		case IEffect::kBlur:		return buildBlurEffect	( effect );
		case IEffect::kShadow:		return buildShadowEffect( effect );
		case IEffect::kColorize:	return buildColorizeEffect( effect );
	}
	return 0;
}

} // end namespoace
