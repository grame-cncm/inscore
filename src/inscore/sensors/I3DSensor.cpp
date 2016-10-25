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

#include "I3DSensor.h"


using namespace std;

namespace inscore
{

//------------------------------------------------------------------------
I3DSensor::I3DSensor(const std::string& name, IObject * parent)
	: ISensor (name, parent)	{}

I3DSensor::~I3DSensor() {}


//------------------------------------------------------------------------
void I3DSensor::createVirtualNodes ()
{
	if (isSignal()) {
		fXSig = TSignal::create (name() + "/x", 1);
		fYSig = TSignal::create (name() + "/y", 1);
		fZSig = TSignal::create (name() + "/z", 1);
		*this << fXSig;
		*this << fYSig;
		*this << fZSig;
	}
}

//--------------------------------------------------------------------------
// 3D sensors generates 3 signals, available at
// sensorname/x, sensorname/y and sensorname/z
//--------------------------------------------------------------------------
bool I3DSensor::findSubNode (std::string name, subnodes& outlist)
{
	STSignal sig;
	if (name == "x")		sig = fXSig;
	else if (name == "y")	sig = fYSig;
	else if (name == "z")	sig = fZSig;
	else	return false;
	
	string node = this->name() + "/" + name;
	SISignal s = ISignal::create(node, getParent());	// create a signal using the whole name
	*s << sig;											// put it into the parent node
	outlist.push_back(s);								// push the node to the output list
	return true;										// and set the return code to true
}

//------------------------------------------------------------------------
void I3DSensor::cleanup ()
{
	IObject::cleanup();
	done();
}

//------------------------------------------------------------------------
void I3DSensor::readData ()
{
#ifdef SENSORDEBUG
	float x = (rand() / (RAND_MAX * 0.5) ) - 1;
	float y = (rand() / (RAND_MAX * 0.5) ) - 1;
	float z = (rand() / (RAND_MAX * 0.5) ) - 1;
	setXPos		( smooth (x, getXPos()) );
	setYPos		( smooth (y, getYPos()) );
	setZOrder	( smooth (z, getZOrder()) );
	if (fIsSignal) {
		*fXSig << getXPos();
		*fYSig << getYPos();
		*fZSig << getZOrder();
	}
	else newData (true);
	setModified();
#else
	float x, y, z;
	if (read(x, y, z)) {
		setXPos		( smooth (x, getXPos()) );
		setYPos		( smooth (y, getYPos()) );
		setZOrder	( smooth (z, getZOrder()) );
		if (fIsSignal) {
			*fXSig << getXPos();
			*fYSig << getYPos();
			*fZSig << getZOrder();
		}
		else newData (true);
		setModified();
	}
#endif
}

//------------------------------------------------------------------------
void I3DSensor::setHandlers()
{
	ISensor::setHandlers();
	// x, y and z attributes of 3D sensors are used to store the sensor values
	// and are available to 'get' messages
	fGetMsgHandlerMap[kx_GetSetMethod]	= TGetParamMsgHandler<float>::create(fXPos);
	fGetMsgHandlerMap[ky_GetSetMethod]	= TGetParamMsgHandler<float>::create(fYPos);
	fGetMsgHandlerMap[kz_GetSetMethod]	= TGetParamMsgHandler<float>::create(fZOrder);
}

} // end namespace


