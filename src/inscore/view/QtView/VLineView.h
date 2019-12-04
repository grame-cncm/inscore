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


#ifndef __VLineView__
#define __VLineView__

#include "VMappedShapeView.h"
#include "MouseEventAble.h"

#include <QGraphicsPathItem>

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a ILine.
*/
class VLineView: public VMappedShapeView
{
	typedef MouseEventAble<QGraphicsPathItem> IQGraphicsPathItem;
	IQGraphicsPathItem* item() const	{ return (IQGraphicsPathItem*)fItem; }

	static const float		sArrowHeadSize;

	public :
		using VMappedShapeView::updateView;

				 VLineView(QGraphicsScene * scene, const ILine* h);
		virtual ~VLineView() {}
		
		virtual void updateView( ILine * Line );
        virtual void updateObjectSize(IObject* o);
};

/**
 * @brief The ArrowHeadFactory class. A factory to create head arrow for line.
 */
class ArrowHeadFactory {
	public:
		ArrowHeadFactory();
		virtual ~ArrowHeadFactory();
		/*!
		 * \brief addArrowHead Add arrow head to the line p0 p1.
		 * \param myPath The current path of the line.
		 * \param type Type of arrow head
		 * \param p0 The start point
		 * \param p1 The end Point
		 * \param arrowSize The size of the arrow head.
		 * \param isLeft true to add arrow head at p0, false to add to p1.
		 */
		void addArrowHead(QPainterPath &myPath, enum ILine::ArrowHeadType type, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft);

	private:
		void addTriangleArrowHead(QPainterPath &myPath, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft);
		void addDiamondArrowHead(QPainterPath &myPath, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft);
		void addDiskArrowHead(QPainterPath &myPath, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft);

		/*!
		 * \brief getAngle Calculate angle of the line to draw the arrow head.
		 * \param p0 The start point
		 * \param p1 The end Point
		 * \param isLeft true to add arrow head at p0, false to add to p1.
		 * \return Angle in radian.
		 */
		double getAngle(const QPointF &p0, const QPointF &p1, bool isLeft);
};

/*!@} */

} // end namespoace

#endif
