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


#ifndef __MouseEventAble__
#define __MouseEventAble__

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include "EventsAble.h"
#include "EventMessage.h"

namespace inscore
{
class IObject;

class _MouseEventAble
{
	public:
		static void handleEvent (const IObject * obj, QPointF pos,  EventsAble::eventype type);
		static rational point2date (const IObject * obj, float x, float y, const std::string& mapname, int n);
};

//----------------------------------------------------------------------
template <typename T> class MouseEventAble : public T
{
	public:
			MouseEventAble(const IObject* h) : fEventsHandler(h)	{ T::setAcceptHoverEvents(true); }

	protected:
		const IObject * fEventsHandler;
		
		void handleEvent (QPointF pos,  EventsAble::eventype type) const	{ _MouseEventAble::handleEvent(fEventsHandler, pos, type); }
//		{
//		qDebug() << "handle event pos" << pos ;
//			VGraphicsItemView*	view = graphicView();
//			QPoint rel (view->scene2RelativeX(pos.x()), view->scene2RelativeY(pos.y()));
//		qDebug() << "handle event rel" << pos ;
//			const std::vector<SEventMessage>& msgs = fEventsHandler->getMouseMsgs (type);
//			for (unsigned int i=0; i<msgs.size(); i++)
//				msgs[i]->send();
//		}

		void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseDoubleClick); }
		void mouseMoveEvent		( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseMove); }
		void mousePressEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos(), EventsAble::kMouseDown); }
		void mouseReleaseEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos(), EventsAble::kMouseUp); }
		void hoverEnterEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseEnter); }
		void hoverLeaveEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseLeave); }
};

} // end namespoace

#endif
