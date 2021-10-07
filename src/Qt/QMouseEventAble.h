/*

  INScore Project

  Copyright (C) 2020  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#pragma once

#include <QGraphicsSceneMouseEvent>
#include <QTouchEvent>

#include "Modules.h"
#include "EventsAble.h"
#include "Events.h"
#include "TIRect.h"


namespace inscore
{

class IObject;
class IMessage;
class IMessageList;
struct EventContext;

class _MouseEventAble
{
	public:
		
		static void handleEvent (const IObject * obj, float x, float y,  EventsAble::eventype type);
		// retrieves a touch event coordinates
		static TFloatPoint touchPos	( QTouchEvent* event );
};

//----------------------------------------------------------------------
template <typename T> class QMouseEventAble : public T
{
	int fTouchID;
	public:
					 QMouseEventAble(const IObject* h) :  fTouchID(-1), fEventsHandler(h) {}
			virtual ~QMouseEventAble()	{}

	protected:
		const IObject * fEventsHandler;
		
		void handleEvent (float x, float y,  EventsAble::eventype type) const	{_MouseEventAble::handleEvent(fEventsHandler, x, y, type); }
		void handleEvent (TFloatPoint p,  EventsAble::eventype type) 	const	{_MouseEventAble::handleEvent(fEventsHandler, p.x(), p.y(), type); }

		bool sceneEvent	(QEvent * event){
			if(event->type()==QEvent::TouchBegin || event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchEnd || event->type() == QEvent::TouchCancel) {
				QTouchEvent* e = static_cast<QTouchEvent*>(event);
#if Qt6
				auto points = e->points();
#else
				auto points = e->touchPoints();
#endif
				if (e->type() == QEvent::TouchBegin){
					if(!points.size() || points.size() > 1)
						return false;
					fTouchID = points.first().id();
#if Qt6
					QPointF pos = points.first().position();
#else
					QPointF pos = points.first().pos();
#endif
					handleEvent (pos.x(), pos.y(), kTouchBeginEvent);
				}else if(e->type() == QEvent::TouchEnd || e->type() == QEvent::TouchCancel){
					fTouchID = -1;
					touchEnd(e);
				}else{
					for(int i=0; i < points.size(); i++){
						const QTouchEvent::TouchPoint& p = points.at(i);
#if Qt6
						QPointF pos = p.position();
						auto state = e->touchPointStates();
#else
						QPointF pos = p.pos();
						auto state = p.state();
#endif
						if(p.id() == fTouchID){
							if(state == Qt::TouchPointMoved)
								handleEvent(pos.x(), pos.y(), kTouchUpdateEvent);
							else if(state == Qt::TouchPointReleased){
								handleEvent(pos.x(), pos.y(), kTouchEndEvent);
								fTouchID = -1;
							}
							break;
						}
					}
				}
				event->accept();
				return true;
			}
			return T::sceneEvent(event);
		}

		void touchBegin		( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), kTouchBeginEvent); }
		void touchEnd		( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), kTouchEndEvent); }
		void touchUpdate	( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), kTouchUpdateEvent); }

		void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos().x(), event->pos().y(), kMouseDoubleClickEvent); }
		void mouseMoveEvent		( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos().x(), event->pos().y(), kMouseMoveEvent); }
		void mousePressEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos().x(), event->pos().y(), kMouseDownEvent); }
		void mouseReleaseEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos().x(), event->pos().y(), kMouseUpEvent); }
		void hoverEnterEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos().x(), event->pos().y(), kMouseEnterEvent); }
		void hoverLeaveEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos().x(), event->pos().y(), kMouseLeaveEvent); }
};

} // end namespoace
