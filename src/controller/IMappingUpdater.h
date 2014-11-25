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


#ifndef __IMappingUpdater__
#define __IMappingUpdater__

#include "Updater.h"
#include "IObject.h"
#include "IRect.h"
#include "IEllipse.h"
#include "ILine.h"
#include "ICurve.h"
#include "IVideo.h"
#include "IPolygon.h"
#include "IScene.h"
#include "ISVG.h"
#include "ISVGFile.h"
#include "ISync.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

class IShapeMap;
//--------------------------------------------------------------------------
/*!
	\brief an updater that computes a mapping according to a sync relation
*/
class IMappingUpdater : public SlaveMapUpdater
{
	/*!
		\brief converts a date into a graphic segment and an x position using a time to graphic mapping
		\param date the input date
		\param map the time to graphic mapping to use for the conversion
		\param outSeg on output, the graphic segment that contains the date
		\param x on output, the x position in the segment, corresponding to the date
		\return a boolean value that indicates the conversion status
	*/
	bool	date2point (const libmapping::rational& date, const SRelativeTime2GraphicMapping& map, GraphicSegment& outSeg, float& x) const;

	/*!
		\brief computes an object y coordinate according to the alignment mode
		\param height the object height
		\param masterSeg the segment the object should be aligned to
		\param align the object alignment mode
		\return a y coordinate
	*/
	float	getYPos (float height, const GraphicSegment& masterSeg, Master::VAlignType align) const;

	/*!
		\brief computes a graphic segment expressed in an object's master coordinates
		
		Actually the method takes the object dimensions and position and takes account of the rotations on the 3 axis.
		The resulting graphic segment is then translated into the master coordnates.
		\param o an object
		\param seg the object graphic segment
		\return a graphic segment expressed in the master coordinates space.
	*/
    GraphicSegment      computeSegmentWithChildren(IObject* o, const GraphicSegment seg);

	/*!
		\brief translates a graphic segment expressed in an object's master coordinates
		\param o an object
		\param h the segment height
		\param w the segment width
		\param x the segment x coordinate
		\param y the segment y coordinate
		\return a graphic segment expressed in the master coordinates space.
	*/
	GraphicSegment      offsetSegment(const IObject* o, float h, float w, float x, float y);

	/*!
		\brief computes dimensions according to an object rotation
		\param o an object
		\param w a width, on output the modified width
		\param h the height, on output, the modified height
	*/
    void				rotateSegment(const IObject* o, float& w, float& h);

	/*!
		\brief computes a graphic segment expressed in an object's master coordinates
		\param o an object
		\return a graphic segment expressed in the master coordinates space.
	*/
    GraphicSegment      computeSegment(const IObject* o);

    protected:
				void			hstretchUpdate (IObject* o, const Master* m);				
				bool			updateNOHStretch (IObject* o, SMaster m);
				
				GraphicSegment	updateNoStretch (IObject*, SMaster master, bool isVStretch = false);
				
		/// check adjacent segments and make sure the end and begin of successives egments match at an epsilon approximate
		SGraphic2GraphicMapping			relink (const Graphic2GraphicRelation& rel, float epsilon) const;
		/// time shift a time to graphic mapping
		SRelativeTime2GraphicMapping	timeshift (const SRelativeTime2GraphicMapping& map, const libmapping::rational& date) const;
		/// adjust the segments vertical dimension and position
		SGraphic2GraphicMapping			verticalAdjust (const SGraphic2GraphicMapping& map, IObject* o, const Master* master) const;

	public:
		using Updater::updateTo;
		
				 IMappingUpdater() {}
		virtual ~IMappingUpdater() {}
		
				void updateIObject (IObject* o);

		inline  void updateTo (IText* o)			{ updateIObject ( (IObject*)o); }
		inline  void updateTo (ITextFile* o)		{ updateIObject ( (IObject*)o); }
		inline  void updateTo (ISVG* o)				{ updateIObject ( (IObject*)o); }
		inline  void updateTo (ISVGFile* o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IGuidoCode* o)		{ updateIObject ( (IObject*)o); }
		inline  void updateTo (IGuidoFile* o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IGraphicSignal* o)	{ updateIObject ( (IObject*)o); }
        inline	void updateTo (IRect * o)			{ updateIObject ( (IObject*)o); }
        inline	void updateTo (ILayer * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IEllipse * o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IPolygon * o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (ICurve * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (ILine * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IVideo * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IImage* o)			{ updateIObject ( (IObject*)o); }

		inline	void updateTo (IHtml* o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IHtmlFile* o)		{ updateIObject ( (IObject*)o); }
};
typedef class libmapping::SMARTP<IMappingUpdater>	SIMappingUpdater;


/*!@} */

} // end namespoace

#endif
