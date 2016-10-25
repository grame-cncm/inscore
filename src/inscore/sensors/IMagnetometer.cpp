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

#include <QMagnetometer>
#include <QMagnetometerReading>

#include "IMagnetometer.h"

using namespace std;

namespace inscore
{

const string IMagnetometer::kMagnetometerType = "magnetometer";

//------------------------------------------------------------------------
IMagnetometer::IMagnetometer(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kMagnetometerType;
	fCalibration = 10000;
	fCalibrating = false;
}

//------------------------------------------------------------------------
IMagnetometer::~IMagnetometer()
{
}

static float max (double v1, double v2, double v3, double v4) {
	return std::max(v1, std::max(v2, std::max(v3, v4)));
}

//------------------------------------------------------------------------
bool IMagnetometer::read (float& x, float& y, float& z)
{
	QMagnetometerReading*	reader = sensor()->reading();
	if (reader) {
		if (fCalibrating) {
			fCalibration = max(std::abs(reader->x()), std::abs(reader->y()), std::abs(reader->z()), fCalibration);
			if (fCalRunning) {
				x = reader->x() * fCalibration;
				y = reader->y() * fCalibration;
				z = reader->z() * fCalibration;
			}
		}
		else {
			x = reader->x() * fCalibration;
			y = reader->y() * fCalibration;
			z = reader->z() * fCalibration;
		}
		return true;
	}
	else return false;
}

//------------------------------------------------------------------------
void IMagnetometer::calibrate (bool state)
{
	if (fCalibrating == state)	return;		// nothing to do, already in the requested mode
	fCalibrating = state;
	if (state) {
		fCalibration = 10000;
		fCalRunning = running();
		if (!fCalRunning) activate(true);
	}
	else {
		if (!fCalRunning) activate(false);
	}
}

//------------------------------------------------------------------------
void IMagnetometer::setHandlers()
{
	ISensor::setHandlers();
	
	fMsgHandlerMap[kcalibrate_SetMethod]	= TSetMethodMsgHandler<IMagnetometer,bool>::create(this, &IMagnetometer::calibrate);
	fMsgHandlerMap[kmax_GetSetMethod]		= TSetMethodMsgHandler<IMagnetometer,float>::create(this, &IMagnetometer::setMax);

	fGetMsgHandlerMap[kmax_GetSetMethod]		= TGetParamMsgHandler<float>::create(fCalibration);
	fAltGetMsgHandlerMap[kcalibrate_SetMethod]	= TGetParamMsgHandler<bool>::create(fCalibrating);
}

} // end namespace


