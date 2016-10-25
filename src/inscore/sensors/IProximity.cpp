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

#include <QProximitySensor>
#include <QProximityReading>

#include "IProximity.h"

using namespace std;

namespace inscore
{

const string IProximity::kProximityType = "proximity";
static const float gLux = 150;

//------------------------------------------------------------------------
IProximity::IProximity(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kProximityType;
	fValue = -1;
}

IProximity::~IProximity() {}

//------------------------------------------------------------------------
float IProximity::read ()
{
	QProximityReading* reader = sensor()->reading();
	return reader ? reader->close() : 0;
}

} // end namespace


