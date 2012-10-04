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

#include "TInterval.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "TRelation.h"
#include "TMapping.h"

namespace inscore
{
/* 
	typedefs for the commonly used relations and segmentations
*/

typedef libmapping::TInterval<long>							LongInterval;
typedef libmapping::TInterval<libmapping::rational>			RationalInterval;
typedef libmapping::TInterval<float>						FloatInterval;

typedef libmapping::TSegment<long,1>						FrameSegment;
typedef libmapping::TSegment<libmapping::rational,1>		RelativeTimeSegment;
typedef libmapping::TSegment<float,2>						GraphicSegment;
typedef libmapping::TSegment<float,1>						FloatSegment;
typedef libmapping::TSegment<long,2>						IntPointSegment;

typedef libmapping::TSegmentation<long,1>					FrameSegmentation;
typedef libmapping::TSegmentation<libmapping::rational,1>	RelativeTimeSegmentation;
typedef libmapping::TSegmentation<float,2>					GraphicSegmentation;
typedef libmapping::TSegmentation<long,2>					IntPointSegmentation;
typedef libmapping::TSegmentation<float,1>					FloatSegmentation;

typedef libmapping::SMARTP<RelativeTimeSegmentation>		SRelativeTimeSegmentation;
typedef libmapping::SMARTP<GraphicSegmentation>				SGraphicSegmentation;

typedef libmapping::TRelation<float,2,float,2>						Graphic2GraphicRelation;
typedef libmapping::TRelation<libmapping::rational,1,float,2>		RelativeTime2GraphicRelation;
typedef libmapping::TRelation<float,2,libmapping::rational,1>		Graphic2RelativeTimeRelation;
typedef libmapping::TRelation<libmapping::rational,1,libmapping::rational,1> RelativeTime2RelativeTimeRelation;

typedef libmapping::TMapping<float,2,float,2>						Graphic2GraphicMapping;
typedef libmapping::TMapping<libmapping::rational,1,float,2>		RelativeTime2GraphicMapping;
typedef libmapping::TMapping<float,2,libmapping::rational,1>		Graphic2RelativeTimeMapping;
typedef libmapping::TMapping<float,2,long,2>						Graphic2IntPointMapping;
typedef libmapping::TMapping<long,2,libmapping::rational,1>			IntPoint2RelativeTimeMapping;
typedef libmapping::TMapping<float,2,long,1>						Graphic2FrameMapping;
typedef libmapping::TMapping<long,1,libmapping::rational,1>			Frame2RelativeTimeMapping;
typedef libmapping::TMapping<float,1,libmapping::rational,1>		Float2RelativeTimeMapping;
typedef libmapping::TMapping<libmapping::rational,1,libmapping::rational,1>	RelativeTime2RelativeTimeMapping;

typedef libmapping::SMARTP<Graphic2GraphicMapping>					SGraphic2GraphicMapping;
typedef libmapping::SMARTP<RelativeTime2GraphicMapping>				SRelativeTime2GraphicMapping;
typedef libmapping::SMARTP<Graphic2RelativeTimeMapping>				SGraphic2RelativeTimeMapping;
typedef libmapping::SMARTP<RelativeTime2RelativeTimeMapping>		SRelativeTime2RelativeTimeMapping;
typedef libmapping::SMARTP<Graphic2IntPointMapping>					SGraphic2IntPointMapping;
typedef libmapping::SMARTP<IntPoint2RelativeTimeMapping>			SIntPoint2RelativeTimeMapping;
typedef libmapping::SMARTP<Float2RelativeTimeMapping>				SFloat2RelativeTimeMapping;
typedef libmapping::SMARTP<Graphic2FrameMapping>					SGraphic2FrameMapping;
typedef libmapping::SMARTP<Frame2RelativeTimeMapping>				SFrame2RelativeTimeMapping;

}

#endif
