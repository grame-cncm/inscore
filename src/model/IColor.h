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


#ifndef __IColor__
#define __IColor__

#include <iostream>
#include <vector>

#include "OSCStream.h"
#include "IMessageStream.h"
#include "IMessageHandlers.h"

namespace inscore
{

class IMessage;
//--------------------------------------------------------------------------
/*!
	\brief a color description (RGBA model)
*/
class IColor
{	
	int fR, fG, fB;
	int fH, fS, fV;
	int fA;
	bool fModified;				///< the modification state

	void setParam( int& param , int value , int min , int max , bool isHSV );
	bool getRGBA( const IMessage* msg, int& r, int& g, int& b, int& a);
	bool getHSBA( const IMessage* msg, int& h, int& s, int& b, int& a);

	inline int floatRGB2int (float a)	{ return int((a+1)*255/2); }
	inline int floatH2int (float h)		{ h*=180; return int(h >=0 ? h : 360+h); }
	inline int floatSV2int (float v)	{ return int((v+1)*50); }

	public:		
				 IColor() : fR(0), fG(0), fB(0), fA(255), fModified(true) { updateHSV(); }
				 IColor(int r, int g, int b, int a = 255) : fR(r), fG(g), fB(b), fA(a), fModified(true) { updateHSV(); }
				 IColor( const IColor& c) : fR(c.fR), fG(c.fG), fB(c.fB), fA(c.fA), fModified(true) { updateHSV(); }
		virtual ~IColor() {}

		void cleanup()							{ fModified = false; }

		/// \brief sets the object color \param c a color
		virtual bool	setColor(const IColor& c)	{ 
			if (*this == c) return false; 
			*this = c;
			fModified = true;
			return true; 
		}

		/// \brief returns the object color
//		virtual const IColor&	getColor() const	{ return fColor; }
		
		bool operator == (const IColor& c) const	{ return (fR==c.fR) && (fG==c.fG) && (fB==c.fB) && (fA==c.fA); }
		bool operator != (const IColor& c) const	{ return !(*this == c); }
		IColor operator +(const IColor& c) const	{ IColor result(*this); result.dR(c.fR); result.dG(c.fG); result.dB(c.fB); result.dA(c.fA); return result; }
		IColor& operator +=(const IColor& c)		{ *this = *this + c; return *this; }

		MsgHandler::msgStatus set (const IMessage* msg);
		MsgHandler::msgStatus setHSV (const IMessage* msg);
		MsgHandler::msgStatus dcolorMsg (const IMessage* msg);
		MsgHandler::msgStatus dhsvMsg (const IMessage* msg);

		template <typename T> void print (T& out)	const { out << fR << fG << fB << fA; }
		
		int getR() const { return fR; }
		int getG() const { return fG; }
		int getB() const { return fB; }
		
		int getH() const { return fH; }
		int getS() const { return fS; }
		int getV() const { return fV; }

		int getA() const { return fA; }

		void setH(int h) { setParam(fH, h%360, 0,360, true); }
		void setS(int s) { setParam(fS, s, 0, 100, true); }
		void setV(int v) { setParam(fV, v, 0, 100, true); }
		
		void setH(float h) { setParam(fH, floatH2int(h)%360, 0, 360, true); }
		void setS(float s) { setParam(fS, floatSV2int(s), 0, 100, true); }
		void setV(float v) { setParam(fV, floatSV2int(v), 0, 100, true); }
		
		void setR(int r) { setParam(fR, r, 0, 255, false); }
		void setG(int g) { setParam(fG, g, 0, 255, false); }
		void setB(int b) { setParam(fB, b, 0, 255, false); }

		void setR(float r) { setParam(fR, floatRGB2int(r), 0, 255, false); }
		void setG(float g) { setParam(fG, floatRGB2int(g), 0, 255, false); }
		void setB(float b) { setParam(fB, floatRGB2int(b), 0, 255, false); }
		
		void setA(int a)	{ setParam(fA, a, 0, 255, false); }
		void setA(float a)	{ setParam(fA, floatRGB2int(a), 0, 255, false); }

		void dA(int a)		{ setA( getA()+a ); }
		void dR(int r)		{ setR( getR()+r ); }
		void dG(int g)		{ setG( getG()+g ); }
		void dB(int b)		{ setB( getB()+b ); }
		void dH(int h)		{ setH( getH()+h ); }
		void dS(int s)		{ setS( getS()+s ); }
		void dV(int v)		{ setV( getV()+v ); }

		void dA(float a)	{ setA( getA() + floatRGB2int(a) ); }
		void dR(float r)	{ setR( getR() + floatRGB2int(r) ); }
		void dG(float g)	{ setG( getG() + floatRGB2int(g) ); }
		void dB(float b)	{ setB( getB() + floatRGB2int(b) ); }
		void dH(float h)	{ setH( getH() + floatH2int(h) ); }
		void dS(float s)	{ setS( getS() + floatSV2int(s) ); }
		void dV(float v)	{ setV( getV() + floatSV2int(v) ); }
		
		void updateHSV();
		void updateRGB();

		void print (std::ostream& out) const;
	
		// R,G,B in [0,255], H in [0,360] and SV in [0,255]
		static void rgb2hsv(int ir , int ig , int ib , int* H, int* S, int* V);
		static void hsv2rgb( int  *r, int *g,int *b, int h, int s, int v );
		static void hsv2rgb( float h , float s, float v , float& r, float& g, float& b );

		class SetColorMsgHandler;
		typedef SMARTP<SetColorMsgHandler> SSetColorMsgHandler;
		class SetColorMsgHandler : public MsgHandler {
			public:
				typedef void (IColor::*setint)(int);
				typedef void (IColor::*setfloat)(float);
				virtual MsgHandler::msgStatus operator ()(const IMessage* msg);
				static SSetColorMsgHandler create(IColor* color, setint si, setfloat sf) { return new SetColorMsgHandler(color, si, sf); }
			protected:
				IColor*		fColor;
				setint		fSetInt;
				setfloat	fSetFloat;
				SetColorMsgHandler(IColor* color, setint si, setfloat sf) : fColor(color), fSetInt(si), fSetFloat(sf) {}
		};
		
};

inline OSCStream& operator << (OSCStream& out, const IColor& color)	{ color.print(out); return out; }
inline IMessage& operator << (IMessage& out, const IColor& color)	{ color.print(out); return out; }


} // end namespoace

#endif
