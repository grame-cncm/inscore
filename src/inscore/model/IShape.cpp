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
IShape::IShape()
{ 
	fPenWidth = 0;
	fPenColor = IColor(0,0,0,255);
	fPenStyle = kSolidStyle;
    fBrushStyle = kSolidStyle;
}

//--------------------------------------------------------------------------
void IShape::print (ostream& out) const
{
	out << "  penWidth: " << fPenWidth << endl;
	out << "  penStyle: " << fPenStyle << endl;
	out << "  brushStyle: " << fBrushStyle << endl;
	out << "  penColor: [" << fPenColor.getR() << "," << fPenColor.getG() << "," << fPenColor.getB() << "]" << endl;
}

}
