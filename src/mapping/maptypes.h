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


#ifndef __maptypes__
#define __maptypes__

#include "rational.h"
#include "smartpointer.h"

namespace inscore
{

/* 
	typedefs for the commonly used relations and segmentations
*/
template<typename T, unsigned int D> class TSegment;
template<typename T> class TInterval;

typedef TInterval<long>		LongInterval;
typedef TInterval<rational>	RationalInterval;
typedef TInterval<float>	FloatInterval;

typedef TSegment<long,1>		FrameSegment;
typedef TSegment<rational,1>	RelativeTimeSegment;
typedef TSegment<float,2>		GraphicSegment;
typedef TSegment<float,1>		FloatSegment;
typedef TSegment<long,2>		IntPointSegment;

template<typename T1, typename T2> class TRelation;
template<typename T1, typename T2> class TMapping;
template<typename T1, typename T2, typename T3> class TComposition;

template<typename T> class TSegmentation;
typedef TSegmentation<FrameSegment>			FrameSegmentation;
typedef TSegmentation<RelativeTimeSegment>	RelativeTimeSegmentation;
typedef TSegmentation<GraphicSegment>		GraphicSegmentation;
typedef TSegmentation<IntPointSegment>		IntPointSegmentation;
typedef TSegmentation<FloatSegment>			FloatSegmentation;

typedef SMARTP<FloatSegmentation>			SFloatSegmentation;
typedef SMARTP<FrameSegmentation>			SFrameSegmentation;
typedef SMARTP<RelativeTimeSegmentation>	SRelativeTimeSegmentation;
typedef SMARTP<GraphicSegmentation>			SGraphicSegmentation;
typedef SMARTP<IntPointSegmentation>		SIntPointSegmentation;

typedef TRelation<GraphicSegment,GraphicSegment>			Graphic2GraphicRelation;
typedef TRelation<RelativeTimeSegment,GraphicSegment>		RelativeTime2GraphicRelation;
typedef TRelation<GraphicSegment,RelativeTimeSegment>		Graphic2RelativeTimeRelation;
typedef TRelation<GraphicSegment,IntPointSegment>			Graphic2IntPointRelation;
typedef TRelation<IntPointSegment,RelativeTimeSegment>		IntPoint2RelativeTimeRelation;
typedef TRelation<GraphicSegment,FrameSegment>				Graphic2FrameRelation;
typedef TRelation<FrameSegment,RelativeTimeSegment>			Frame2RelativeTimeRelation;
typedef TRelation<FloatSegment,RelativeTimeSegment>			Float2RelativeTimeRelation;
typedef TRelation<RelativeTimeSegment,FloatSegment>			RelativeTime2FloatRelation;
typedef TRelation<RelativeTimeSegment,RelativeTimeSegment>	RelativeTime2RelativeTimeRelation;

typedef TMapping<GraphicSegment,GraphicSegment>				Graphic2GraphicMapping;
typedef TMapping<RelativeTimeSegment,GraphicSegment>		RelativeTime2GraphicMapping;
typedef TMapping<GraphicSegment,RelativeTimeSegment>		Graphic2RelativeTimeMapping;
typedef TMapping<GraphicSegment,IntPointSegment>			Graphic2IntPointMapping;
typedef TMapping<IntPointSegment,RelativeTimeSegment>		IntPoint2RelativeTimeMapping;
typedef TMapping<GraphicSegment,FrameSegment>				Graphic2FrameMapping;
typedef TMapping<FrameSegment,RelativeTimeSegment>			Frame2RelativeTimeMapping;
typedef TMapping<FloatSegment,RelativeTimeSegment>			Float2RelativeTimeMapping;
typedef TMapping<RelativeTimeSegment,RelativeTimeSegment>	RelativeTime2RelativeTimeMapping;

typedef SMARTP<Graphic2GraphicMapping>					SGraphic2GraphicMapping;
typedef SMARTP<RelativeTime2GraphicMapping>				SRelativeTime2GraphicMapping;
typedef SMARTP<Graphic2RelativeTimeMapping>				SGraphic2RelativeTimeMapping;
typedef SMARTP<RelativeTime2RelativeTimeMapping>		SRelativeTime2RelativeTimeMapping;
typedef SMARTP<Graphic2IntPointMapping>					SGraphic2IntPointMapping;
typedef SMARTP<IntPoint2RelativeTimeMapping>			SIntPoint2RelativeTimeMapping;
typedef SMARTP<Float2RelativeTimeMapping>				SFloat2RelativeTimeMapping;
typedef SMARTP<Graphic2FrameMapping>					SGraphic2FrameMapping;
typedef SMARTP<Frame2RelativeTimeMapping>				SFrame2RelativeTimeMapping;


}

#endif
