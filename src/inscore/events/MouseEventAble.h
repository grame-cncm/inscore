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

#include <QGraphicsSceneMouseEvent>
#include <QTouchEvent>
#include "EventsAble.h"

namespace inscore
{

class IObject;
class IMessage;
class IMessageList;
struct EventContext;

class _MouseEventAble
{
	static SIMessageList eval (const IMessageList* msgs, float x, float y, EventContext& env);

	public:
		
		static void handleEvent (const IObject * obj, QPointF pos,  EventsAble::eventype type);
		// converts a point to a date in the context of an object and a given map
		static libmapping::rational point2date (const IObject * obj, float x, float y, const std::string& mapname, int n);
		// retrieves a touch event coordinates
		static QPointF touchPos	( QTouchEvent* event );
};

//----------------------------------------------------------------------
template <typename T> class MouseEventAble : public T
{
	bool fClicked;
	public:
			MouseEventAble(const IObject* h) : fClicked(false), fEventsHandler(h)
					{ T::setAcceptHoverEvents(true); T::setAcceptTouchEvents(true); }

	protected:
		const IObject * fEventsHandler;
		
		void handleEvent (QPointF pos,  EventsAble::eventype type) const	{ _MouseEventAble::handleEvent(fEventsHandler, pos, type); }

		bool sceneEvent			(QEvent * event) {
			switch (event->type()) {
				case QEvent::TouchBegin:
					touchBegin (static_cast<QTouchEvent *>(event));
					return true;
				case QEvent::TouchEnd:
					touchEnd (static_cast<QTouchEvent *>(event));
					return true;
				case QEvent::TouchUpdate:
					touchUpdate (static_cast<QTouchEvent *>(event));
					return true;
				default:
					return T::sceneEvent(event);
			}
		}
		void touchBegin		( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), EventsAble::kTouchBegin); }
		void touchEnd		( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), EventsAble::kTouchEnd); }
		void touchUpdate	( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), EventsAble::kTouchUpdate); }

		void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseDoubleClick); }
		void mouseMoveEvent		( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseMove); }
		void mousePressEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos(), EventsAble::kMouseDown); }
		void mouseReleaseEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos(), EventsAble::kMouseUp); }
		void hoverEnterEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseEnter); }
		void hoverLeaveEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseLeave); }
};

} // end namespoace

#endif
