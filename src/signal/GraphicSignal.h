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


#ifndef __GraphicSignal__
#define __GraphicSignal__

#include <iostream>
#include <vector>
#include "TSignal.h"

namespace INScore
{
	
/*!
 \addtogroup ITLSignal
 @{
 */

//--------------------------------------------------------------------------
/*!
 \brief a frame base class 
 */
class Frame
{
	protected:
		std::vector<float> fData;
	public:
				 /* \brief the frame constructor
					
					A Frame is build with its values. 
				 */
				 Frame(const std::vector<float>& value) { fData = value; }
		virtual ~Frame() {}
};

//--------------------------------------------------------------------------
/*!
 \brief HSBA color  
 */
class HSBAColor : public Frame
{
	protected:
		enum { kHue, kSaturation, kBrightness, kTransparency, kDataCount };

	public:	
		HSBAColor (const std::vector<float>& value);

		float	getHue() const				{ return fData[kHue]; }
		float	getSaturation() const		{ return fData[kSaturation]; }
		float	getBrightness()	const		{ return fData[kBrightness]; }
		float	getTransparency() const		{ return fData[kTransparency]; }
		void	print(std::ostream& out) const;
};
	
//--------------------------------------------------------------------------
/*!
 \brief a graphic signal frame 
 
	A graphic signal is described by an \c y position, a thickness and a HSBA color.
 */
class GraphicFrame : public Frame
{
	protected:
		enum { kPos, kThickness, kHue, kSaturation, kBrightness, kTransparency, kDataCount };
	
	public :
				 GraphicFrame(const std::vector<float>& value);
		virtual ~GraphicFrame() {}
		
		float			getPos() const				{ return fData[kPos]; }
		float			getThickness() const		{ return fData[kThickness]; }
		float			getHue() const				{ return fData[kHue]; }
		float			getSaturation() const		{ return fData[kSaturation]; }
		float			getBrightness()	const		{ return fData[kBrightness]; }
		float			getTransparency() const		{ return fData[kTransparency]; }
		
		HSBAColor		getColor() const;
		void			print(std::ostream& out) const;
		
		static int		FrameSize()				{ return kDataCount; }
};

//--------------------------------------------------------------------------
/*!
 \brief parallel graphic signals frame 
 */
class GraphicFrames : public Frame
{
	unsigned int fSize;		///<  cached integral value of GraphicFrame count 
	public :
				 GraphicFrames(const std::vector<float>& value);
		virtual ~GraphicFrames() {}
		
		unsigned int				size() const		{ return fSize; }
		GraphicFrame	operator [] (unsigned int n) const;				
};

//--------------------------------------------------------------------------
/*!
 \brief a template parallel signal to specialize the \c get method return type
 */
template <typename T> class TypedParallelSignal : public ParallelSignal
{
	protected:
				 TypedParallelSignal() {}
		virtual ~TypedParallelSignal() {}
	public:	
		static SMARTP<TypedParallelSignal> create()	{ return new TypedParallelSignal<T>(); }		
		virtual T get(int n) const					{ return ParallelSignal::get<T> (n); }
};


std::ostream& operator << (std::ostream& out, const HSBAColor& color);
std::ostream& operator << (std::ostream& out, const GraphicFrame& gframe);

	
//--------------------------------------------------------------------------
typedef TypedParallelSignal<HSBAColor>		ColorSignal;
typedef SMARTP<ColorSignal>					SColorSignal;

typedef TypedParallelSignal<GraphicFrame>	GraphicSignal;
typedef SMARTP<GraphicSignal>				SGraphicSignal;

typedef TypedParallelSignal<GraphicFrames>	GraphicSignals;
typedef SMARTP<GraphicSignals>				SGraphicSignals;

/*! @} */
	
} // end namespace

#endif
