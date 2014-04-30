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
//#include "segment2relativetimereader.h"

using namespace std;

namespace inscore
{

const std::string IShape::kSolidStyle = SOLID_STYLE;
const std::string IShape::kDashStyle = DASH_STYLE;
const std::string IShape::kDotStyle = DOT_STYLE;
const std::string IShape::kDashDotStyle = DASH_DOT_STYLE;
const std::string IShape::kDashDotDotStyle = DASH_DOT_DOT_STYLE;
    
const std::string IShape::kSolidBrushStyle = SOLID_STYLE;
const std::string IShape::kDense1BrushStyle = DENSE1_BRUSH_STYLE;
const std::string IShape::kDense2BrushStyle = DENSE2_BRUSH_STYLE;
const std::string IShape::kDense3BrushStyle = DENSE3_BRUSH_STYLE;
const std::string IShape::kDense4BrushStyle = DENSE4_BRUSH_STYLE;
const std::string IShape::kDense5BrushStyle = DENSE5_BRUSH_STYLE;
const std::string IShape::kDense6BrushStyle = DENSE6_BRUSH_STYLE;
const std::string IShape::kDense7BrushStyle = DENSE7_BRUSH_STYLE;
const std::string IShape::kNoBrushStyle = NO_BRUSH_STYLE;
const std::string IShape::kHorBrushStyle = HOR_BRUSH_STYLE;
const std::string IShape::kVerBrushStyle = VER_BRUSH_STYLE;
const std::string IShape::kCrossBrushStyle = CROSS_BRUSH_STYLE;
const std::string IShape::kBDiagBrushStyle = BDIAG_BRUSH_STYLE;
const std::string IShape::kFDiagBrushStyle = FDIAG_BRUSH_STYLE;
const std::string IShape::kDiagCrossBrushStyle = DIAG_CROSS_BRUSH_STYLE;

    
//--------------------------------------------------------------------------
IShape::IShape( const std::string& name, IObject* parent ) : IObject(name, parent)
{ 
	fPenWidth = 0;
	fPenColor = IColor(0,0,0,255);
	fPenStyle = kSolidStyle;
    fBrushStyle = kSolidStyle;

	fMsgHandlerMap[kpenColor_GetSetMethod]	= TMethodMsgHandler<IColor>::create(&fPenColor, &IColor::set);
	fMsgHandlerMap[kpenAlpha_GetSetMethod]	= IColor::SetColorMsgHandler::create(&fPenColor, &IColor::setA, &IColor::setA);
	fMsgHandlerMap[kpendAlpha_SetMethod]	= IColor::SetColorMsgHandler::create(&fPenColor, &IColor::dA, &IColor::dA);
	fMsgHandlerMap[kpenWidth_GetSetMethod]	= TSetMethodMsgHandler<IShape, float>::create(this, &IShape::setPenWidth);
	fMsgHandlerMap[kpenStyle_GetSetMethod]  = TSetMethodMsgHandler<IShape, string>::create(this, &IShape::setPenStyle);
    fMsgHandlerMap[kbrushStyle_GetSetMethod]  = TSetMethodMsgHandler<IShape, string>::create(this, &IShape::setBrushStyle);

    fSigHandlerMap[kpenAlpha_GetSetMethod]	= IColor::SetColorSigHandler::create(&fPenColor, &IColor::setA, &IColor::setA);
	fSigHandlerMap[kpendAlpha_SetMethod]	= IColor::SetColorSigHandler::create(&fPenColor, &IColor::dA, &IColor::dA);
	fSigHandlerMap[kpenWidth_GetSetMethod]	= TSetMethodSigHandler<IShape, float>::create(this, &IShape::setPenWidth);
	
	fGetMsgHandlerMap[kpenWidth_GetSetMethod]	= TGetParamMsgHandler<float>::create(fPenWidth);
	fGetMsgHandlerMap[kpenColor_GetSetMethod]	= TGetParamMsgHandler<IColor>::create(fPenColor);
	fGetMsgHandlerMap[kpenAlpha_GetSetMethod]	= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(&fPenColor, &IColor::getA);
	fGetMsgHandlerMap[kpenStyle_GetSetMethod]	= TGetParamMsgHandler<std::string>::create(fPenStyle);
	fGetMsgHandlerMap[kbrushStyle_GetSetMethod]	= TGetParamMsgHandler<std::string>::create(fBrushStyle);
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
	out << "  brushStyle: " << fBrushStyle << endl;
	out << "  penColor: [" << fPenColor.getR() << "," << fPenColor.getG() << "," << fPenColor.getB() << "]" << endl;
}

}
