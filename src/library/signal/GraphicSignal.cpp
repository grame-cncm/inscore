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


#include "GraphicSignal.h"

#include <math.h>
#include <iostream>
using namespace std;

namespace inscore
{


//--------------------------------------------------------------------------
// HSBAColor
//--------------------------------------------------------------------------
void HSBAColor::print (ostream& out) const
{
	out << "[" << getHue() << ", " << getSaturation() << ", " << getBrightness() << ", " << getTransparency() << "]";
}

//--------------------------------------------------------------------------
HSBAColor::HSBAColor(const vector<float>& value)
	: Frame (value)
{
	for (int i=value.size(); i < kDataCount;  i++)
		fData.push_back(0.f);
}

//--------------------------------------------------------------------------
// GraphicFrame
//--------------------------------------------------------------------------
GraphicFrame::GraphicFrame(const vector<float>& value)
	: Frame (value)
{
	for (int i=value.size(); i < kDataCount;  i++)
		fData.push_back(0.f);
}

//--------------------------------------------------------------------------
HSBAColor GraphicFrame::getColor() const
{
	vector<float> color;
	color.push_back(fData[kHue]);
	color.push_back(fData[kSaturation]);
	color.push_back(fData[kBrightness]);
	color.push_back(fData[kTransparency]);
	return HSBAColor (color); 
}

//--------------------------------------------------------------------------
void GraphicFrame::print (ostream& out) const
{
	out << "{" << getPos() << ", " << getThickness() << ", ";
	getColor().print(out);
	out << "}";
}

//--------------------------------------------------------------------------
// GraphicFrames
//--------------------------------------------------------------------------
GraphicFrames::GraphicFrames(const vector<float>& value)
	: Frame (value)
{
	fSize = int(ceil (float(value.size()) / GraphicFrame::FrameSize()));
	int fill = fSize * GraphicFrame::FrameSize();
	for (int i=value.size(); i < fill;  i++)
		fData.push_back(0.f);
}

//--------------------------------------------------------------------------
GraphicFrame GraphicFrames::operator [] (unsigned int n) const
{
	vector<float> data;
	if (n < fSize) {
		for (unsigned int i = n * GraphicFrame::FrameSize(); i < (n + 1) * GraphicFrame::FrameSize(); i++)
			data.push_back(fData[i]);
	}
	return GraphicFrame(data);
}

//--------------------------------------------------------------------------
// print utilities
ostream& operator << (ostream& out, const HSBAColor& color)
{
	color.print(out);
	return out;
}
ostream& operator << (ostream& out, const GraphicFrame& gframe)
{
	gframe.print(out);
	return out;
}
	
} // end namespace
