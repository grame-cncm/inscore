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

#include "IShape.h"
#include "IMessage.h"
#include "IAppl.h"
#include "Updater.h"
#include "segment2relativetimereader.h"

using namespace std;

namespace inscore
{

const std::string IShape::kSolidStyle = SOLID_STYLE;
const std::string IShape::kDashStyle = DASH_STYLE;
const std::string IShape::kDotStyle = DOT_STYLE;
const std::string IShape::kDashDotStyle = DASH_DOT_STYLE;
const std::string IShape::kDashDotDotStyle = DASH_DOT_DOT_STYLE;

//--------------------------------------------------------------------------
IShape::IShape( const std::string& name, IObject* parent ) : IObject(name, parent)
{ 
	fPenWidth = 0;
	fPenColor = IColor(0,0,0,255);
	fPenStyle = kSolidStyle;

	fMsgHandlerMap["penColor"]	= TMethodMsgHandler<IColor>::create(&fPenColor, &IColor::set);
	fMsgHandlerMap["penWidth"]	= TSetMethodMsgHandler<IShape, float>::create(this, &IShape::setPenWidth);
	fMsgHandlerMap["penStyle"]  = TSetMethodMsgHandler<IShape, string>::create(this, &IShape::setPenStyle);

	fGetMsgHandlerMap["penWidth"]	= TGetParamMsgHandler<float>::create(fPenWidth);
	fGetMsgHandlerMap["penColor"]	= TGetParamMsgHandler<IColor>::create(fPenColor);
	fGetMsgHandlerMap["penStyle"]	= TGetParamMsgHandler<std::string>::create(fPenStyle);	
}

//--------------------------------------------------------------------------
void IShape::accept (Updater* u)
{
	u->updateTo (SIShape(this));
}

//--------------------------------------------------------------------------
void IShape::print (ostream& out) const
{
	IObject::print (out);
	out << "  penWidth: " << fPenWidth << endl;
	out << "  penStyle: " << fPenStyle << endl;
	out << "  penColor: [" << fPenColor.getR() << "," << fPenColor.getG() << "," << fPenColor.getB() << "]" << endl;
}

}
