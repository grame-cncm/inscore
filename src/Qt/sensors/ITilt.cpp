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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include <cmath>

#include <QTiltSensor>
#include <QTiltReading>

#include "ITilt.h"
#include "INScore.h"

using namespace std;

namespace inscore
{

const string ITilt::kTiltType = "tilt";

//------------------------------------------------------------------------
ITilt::ITilt(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kTiltType;
	if (isSignal()) fDefaultScale = 1 / 90.f;
	setScale ( fDefaultScale );
}
ITilt::~ITilt() {}

//------------------------------------------------------------------------
bool ITilt::read (float& x, float& y, float& z)
{
	QTiltReading*	reader = sensor()->reading();
	if (reader) {
		x = reader->xRotation();
		y = reader->yRotation();
		z = 0;
		return true;
	}
	else return false;
}

//------------------------------------------------------------------------
void ITilt::calibrate ()	{ sensor()->calibrate(); }

//------------------------------------------------------------------------
void ITilt::setHandlers()
{
	ISensor::setHandlers();
	fMsgHandlerMap[kcalibrate_SetMethod]	= TMethodMsgHandler<ITilt, void (ITilt::*)(void)>::create(this, &ITilt::calibrate);
}

} // end namespace


