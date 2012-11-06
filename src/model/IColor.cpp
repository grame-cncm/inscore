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


#include "IColor.h"
#include "IMessage.h"
#include <algorithm>

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------------
bool IColor::getRGBA( const IMessage* msg, int& r, int& g, int& b, int& a)
{
	int n = msg->size();
	if ((n < 3) || (n > 4)) return false;
	float fr, fg, fb, fa = 1.;
	a = 255;
	if (msg->param(0, fr) && msg->param(1, fg) && msg->param(2, fb)) {
		if ((n == 4) && !msg->param(3, fa)) return false;
		r = floatRGB2int(fr);
		g = floatRGB2int(fg);
		b = floatRGB2int(fb);
		a = floatRGB2int(fa);
	}
	else {
		if (!msg->param(0, r) || !msg->param(1, g) || !msg->param(2, b)) return false;
		if ((n == 4) && !msg->param(3, a)) return false;
	}
	return true;
}

//--------------------------------------------------------------------------------
bool IColor::getHSBA( const IMessage* msg, int& h, int& s, int& b, int& a)
{
	int n = msg->size();
	if ((n < 3) || (n > 4)) return false;
	float fh, fs, fb, fa = 1.;
	a = 255;
	if (msg->param(0, fh) && msg->param(1, fs) && msg->param(2, fb)) {
		if ((n == 4) && !msg->param(3, fa)) return MsgHandler::kBadParameters;
		h = floatH2int(fh);
		s = floatSV2int(fs);
		b = floatSV2int(fb);
		a = floatRGB2int(fa);
	}
	else {
		if (!msg->param(0, h) || !msg->param(1, s) || !msg->param(2, b)) return false;
		if ((n == 4) && !msg->param(3, a)) return false;
	}
	return true;
}

//--------------------------------------------------------------------------------
MsgHandler::msgStatus IColor::set (const IMessage* msg)
{ 
	int r, g, b, a = 255;
	if (!getRGBA (msg, r, g, b, a)) return MsgHandler::kBadParameters;
	fR = std::max(0,std::min(r,255));
	fG = std::max(0,std::min(g,255));
	fB = std::max(0,std::min(b,255));
	fA = std::max(0,std::min(a,255));
	fModified = true;
	updateHSV();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------------
MsgHandler::msgStatus IColor::setHSV (const IMessage* msg) 
{ 
	int h, s, b, a = 255;
	if (!getHSBA (msg, h, s, b, a)) return MsgHandler::kBadParameters;
	fH = h % 360;
	fS = std::max(0,std::min(s,100));
	fV = std::max(0,std::min(b,100));
	fA = std::max(0,std::min(a,255));
	fModified = true;
	updateRGB();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IColor::dcolorMsg(const IMessage* msg)
{
	int r, g, b, a = 255;
	if (!getRGBA (msg, r, g, b, a)) return MsgHandler::kBadParameters;
	dR(r);
	dG(g);
	dB(b);
	dA(a);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IColor::dhsvMsg(const IMessage* msg)
{
	int h, s, v, a = 255;
	if (!getHSBA (msg, h, s, v, a)) return MsgHandler::kBadParameters;
	dH(h);
	dS(s);
	dV(v);
	dA(a);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------------
MsgHandler::msgStatus IColor::SetColorMsgHandler::operator ()(const IMessage* msg)
{
	if (msg->size() != 1) return MsgHandler::kBadParameters;
	int val; float fval;
	if (msg->param(0, val))			(fColor->*fSetInt) (val);
	else if (msg->param(0, fval))	(fColor->*fSetFloat)(fval);
	else return MsgHandler::kBadParameters;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------------
void IColor::setParam( int& param , int value , int min , int max , bool isHSV )
{
	param = std::max( min , std::min( value , max ) );
	fModified = true;
	if ( isHSV )
		updateRGB();
	else
		updateHSV();
}

//--------------------------------------------------------------------------------
void IColor::updateRGB()
{
	hsv2rgb(&fR,&fG,&fB,fH,fS,fV);
}

//--------------------------------------------------------------------------------
void IColor::updateHSV()
{
	rgb2hsv(fR,fG,fB,&fH,&fS,&fV);
}

//--------------------------------------------------------------------------------
void IColor::rgb2hsv(int ir , int ig , int ib , int* iH, int* iS, int* iV)
{
	float r = ir/255.0f;
	float g = ig/255.0f;
	float b = ib/255.0f;
	
	float H,S,V;

	// RGB are from 0..1, H is from 0..360, SV from 0..1
	float maxC = b;
	if (maxC < g) maxC = g;
	if (maxC < r) maxC = r;
	float minC = b;
	if (minC > g) minC = g;
	if (minC > r) minC = r;

	float delta = maxC - minC;

	H = 0;
	S = 0;
	V = maxC;

	if (delta == 0)
	{
		H = 0;
		S = 0;
	}
	else
	{
		S = delta / maxC;
		float dR = 60*(maxC - r)/delta + 180;
		float dG = 60*(maxC - g)/delta + 180;
		float dB = 60*(maxC - b)/delta + 180;
		if (r == maxC)
			H = dB - dG;
		else if (g == maxC)
			H = 120 + dR - dB;
		else
			H = 240 + dG - dR;
	}

	if (H<0)
		H+=360;
	if (H>=360)
		H-=360;
		
	*iH = int(H);
	*iS = int(S * 100);
	*iV = int(V * 100);
}

//--------------------------------------------------------------------------------
void IColor::hsv2rgb( int  *r, int *g,int *b, int h, int s, int v )
{
	float fr,fg,fb;
	fr = fg = fb = 0;

	hsv2rgb( h/360.0f , s/100.0f , v/100.0f , fr , fg , fb );
	*r = int(fr * 255);
	*g = int(fg * 255);
	*b = int(fb * 255);
}

void IColor::hsv2rgb( float h , float s, float v , float& r, float& g, float& b )
{
	float S, H, V, F, M, N, K;
   int   I;
   
   S = s;  /* Saturation */
   H = h;  /* Hue */
   V = v;  /* value or brightness */
   
   if ( S == 0.0 ) {
      /* 
       * Achromatic case, set level of grey 
       */
      r = V;
      g = V;
      b = V;
   } else {
      /* 
       * Determine levels of primary colours. 
       */
      if (H >= 1.0) {
         H = 0.0;
      } else {
         H = H * 6;
      } /* end if */
      I = (int) H;   /* should be in the range 0..5 */
      F = H - I;     /* fractional part */

      M = V * (1 - S);
      N = V * (1 - S * F);
      K = V * (1 - S * (1 - F));

      if (I == 0) { r = V; g = K; b = M; }
      if (I == 1) { r = N; g = V; b = M; }
      if (I == 2) { r = M; g = V; b = K; }
      if (I == 3) { r = M; g = N; b = V; }
      if (I == 4) { r = K; g = M; b = V; }
      if (I == 5) { r = V; g = M; b = N; }
   } /* end if */

}

void IColor::print (ostream& out) const
{
	out << "  color [" << getR() << "," << getG() << "," << getB() << "," << getA() << "]" << endl;
}

} // end namespoace

