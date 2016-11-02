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

#include "I1DSensor.h"
//#include "INScore.h"


using namespace std;

namespace inscore
{

//------------------------------------------------------------------------
I1DSensor::I1DSensor(const std::string& name, IObject * parent)
	: ISensor (name, parent), fDefaultValue(0.f)	{}

I1DSensor::~I1DSensor() {}


//------------------------------------------------------------------------
void I1DSensor::cleanup ()
{
	IObject::cleanup();
	done();
}

//------------------------------------------------------------------------
void I1DSensor::readData ()
{
#ifdef SENSORDEBUG
	float val = (rand() / (RAND_MAX * 0.5) ) - 1;
#else
	float val = smooth (read()*getScale(), getXPos());
#endif
	if (fIsSignal) {
//INScore::postMessage("192.168.1.21:7001/I1DSensor", "readData", sigvalue(val));
		*(signal(0)) << sigvalue(val);
	}
	if (val != getXPos())	{
		setXPos(val);
		if (!fIsSignal) newData (true);
	}
	setModified();
}

//------------------------------------------------------------------------
bool I1DSensor::activate(bool val)
{
	// the sensor starts, set the value to a default value
	// this default value should be overriden by derived class
	// the idea is to force the newData event at activation time.
	if (val) setXPos(fDefaultValue);
}

//------------------------------------------------------------------------
void I1DSensor::setHandlers()
{
	ISensor::setHandlers();
	// x is used to store the sensor values
	fAltGetMsgHandlerMap[kx_GetSetMethod]	= TGetParamMsgHandler<float>::create(fXPos);
}

} // end namespace


