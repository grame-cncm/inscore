/*

  INScore Project

  Copyright (C) 2015  Grame

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

#include "QColorTool.h"

#define MAX(a,b)		( (a)>(b) ? (a) : (b) )
#define MIN(a,b)		( (a)<(b) ? (a) : (b) )

namespace inscore
{

#define minVal	-1.f
#define maxVal	1.f

#define TO_0_1(a) ((a/2.0f)+0.5f)
//--------------------------------------------------------------------------
QColor HSBA2QColor( const HSBAColor& color )
{
	float hue = color.getHue();
	if ( hue < 0 ) hue += 2;
	float clippedH = hue / 2.0f;
	float clippedS = TO_0_1(color.getSaturation());
	float clippedB = TO_0_1(color.getBrightness());
	float clippedA = TO_0_1(color.getTransparency());
	clippedH = MAX( MIN( clippedH , 1 ) , 0 );
	clippedS = MAX( MIN( clippedS , 1 ) , 0 );
	clippedB = MAX( MIN( clippedB , 1 ) , 0 );
	clippedA = MAX( MIN( clippedA , 1 ) , 0 );
	return QColor::fromHsvF( clippedH , clippedS , clippedB , clippedA );
}

} // end namespoace
