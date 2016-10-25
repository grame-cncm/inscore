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

#include <QRotationSensor>
#include <QRotationReading>

#include "IRotation.h"

using namespace std;

namespace inscore
{

const string IRotation::kRotationType = "rotation";

//------------------------------------------------------------------------
IRotation::IRotation(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kRotationType;
	fHasZ = sensor()->hasZ();
	fax = fay = faz = 0;
}

//------------------------------------------------------------------------
IRotation::~IRotation()
{
}

//------------------------------------------------------------------------
bool IRotation::read (float& x, float& y, float& z)
{
	QRotationReading*	reader = sensor()->reading();
	if (reader) {
		if (fax) reader->setFromEuler(fax, fay, faz);
		x = reader->x() / 90;
		y = reader->y() / 180;
		z = reader->z() / 180;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IRotation::hasZ () const		{ return sensor()->hasZ(); }

//--------------------------------------------------------------------------
void IRotation::setFromEuler (float x, float y, float z)
{
	fax = x;
	fay = y;
	faz = z;
//	QRotationReading*	reader = sensor()->reading();
//	if (reader) reader->setFromEuler(x, y, z);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IRotation::setAngles (const IMessage* msg)
{
	if (msg->size() == 0) {
		setFromEuler (getXPos(), getYPos(), getZOrder());
		return MsgHandler::kProcessed;
	}
	else if (msg->size() == 3) {
		float x, y, z;
		if (msg->param(0,x) && msg->param(1,y) && msg->param(2,z)) {
			setFromEuler (x, y, z);
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

//------------------------------------------------------------------------
void IRotation::setHandlers()
{
	ISensor::setHandlers();
	
	fMsgHandlerMap[kangle_GetSetMethod]	= TMethodMsgHandler<IRotation>::create(this, &IRotation::setAngles);

//	fGetMsgHandlerMap[kangle_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fXPos);
	fGetMsgHandlerMap[khasZ_GetMethod]	= TGetParamMethodHandler<IRotation, bool(IRotation::*)() const>::create(this, &IRotation::hasZ);
}

} // end namespace


