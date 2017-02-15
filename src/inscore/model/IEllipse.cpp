/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

#include "IEllipse.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string IEllipse::kEllipseType("ellipse");

//--------------------------------------------------------------------------
IEllipse::IEllipse( const std::string& name, IObject* parent ) : IRectShape(name, parent)
{
	fTypeString = kEllipseType;
}

//--------------------------------------------------------------------------
bool IEllipse::date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const
{
	const libmapping::rational dur = getDuration();
	if ((date < 0.) || (date > dur))	return false;

	double angle = float(date) / float(dur) * 2 * M_PI + M_PI;
	double r1 = getWidth() / 2;
	double r2 = getHeight() / 2;
	if (r1 > r2) {
		p.fX = (r1*cos(angle) + r1) / (r1*2);
		p.fY = (r2*sin(angle) + r2) / (r2*2);
	}
	else {
		p.fX = (r2*cos(angle) + r2) / (r2*2);
		p.fY = (r1*sin(angle) + r1) / (r1*2);
	}
//cout << "IEllipse::date2FramePoint angle: " << angle << " -> " << p << " (" << r1 << " " << r2 << " )" << endl;
	return true;
}

//--------------------------------------------------------------------------
void IEllipse::accept (Updater* u)
{
	u->updateTo (SIEllipse(this));
}

//--------------------------------------------------------------------------
void IEllipse::print (ostream& out) const
{
	IShape::print (out);
	out << " ellipse" << endl;
}

}
