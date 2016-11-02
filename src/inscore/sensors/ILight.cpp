/*

  INScore Project

  Copyright (C) 2016  Grame

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

#include <iostream>
#include <cmath>

#include <QLightSensor>
#include <QLightReading>

#include "ILight.h"

using namespace std;

namespace inscore
{

const string ILight::kLightType = "light";
static const float gLux = 200.f;

//------------------------------------------------------------------------
ILight::ILight(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kLightType;
	fCalibration = 1/gLux;
	fCalibrating = false;
	fDefaultValue = 0.f;
	if (isSignal())
		setScale ( fCalibration );
}
ILight::~ILight() {}

//------------------------------------------------------------------------
float ILight::read ()
{
	QLightReading* reader = sensor()->reading();
	return reader ? reader->lux() : 0;
}

//------------------------------------------------------------------------
void ILight::calibrate (bool state)
{
	if (fCalibrating == state)	return;		// nothing to do, already in the requested mode
	fCalibrating = state;
	if (state) {
		fCalibration = 1;
		fCalRunning = running();
		if (!fCalRunning) activate(true);
	}
	else {
		if (!fCalRunning) activate(false);
	}
}

//------------------------------------------------------------------------
void ILight::setHandlers()
{
	I1DSensor::setHandlers();
	
	fMsgHandlerMap[kcalibrate_SetMethod]	= TSetMethodMsgHandler<ILight,bool>::create(this, &ILight::calibrate);
	fMsgHandlerMap[kmax_GetSetMethod]		= TSetMethodMsgHandler<ILight,float>::create(this, &ILight::setMax);

	fGetMsgHandlerMap[kmax_GetSetMethod]		= TGetParamMsgHandler<float>::create(fCalibration);
	fAltGetMsgHandlerMap[kcalibrate_SetMethod]	= TGetParamMsgHandler<bool>::create(fCalibrating);
}

} // end namespace


