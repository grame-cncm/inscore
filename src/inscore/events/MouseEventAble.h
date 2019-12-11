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
#include "Events.h"
#include "TRect.h"


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
		
		static void handleEvent (const IObject * obj, float x, float y,  EventsAble::eventype type);
		// converts a point to a date in the context of an object and a given map
		static libmapping::rational point2date (const IObject * obj, float x, float y, const std::string& mapname, int n);
		// retrieves a touch event coordinates
		static TFloatPoint touchPos	( QTouchEvent* event );
};

//----------------------------------------------------------------------
template <typename T> class MouseEventAble : public T
{
	int fTouchID;
	public:
					 MouseEventAble(const IObject* h) :  fTouchID(-1), fEventsHandler(h)
										{}
			virtual ~MouseEventAble()	{}

	protected:
		const IObject * fEventsHandler;
		
		void handleEvent (float x, float y,  EventsAble::eventype type) const	{_MouseEventAble::handleEvent(fEventsHandler, x, y, type); }
		void handleEvent (TFloatPoint p,  EventsAble::eventype type) 	const	{_MouseEventAble::handleEvent(fEventsHandler, p.x(), p.y(), type); }

		bool sceneEvent			(QEvent * event){
			if(event->type()==QEvent::TouchBegin || event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchEnd || event->type() == QEvent::TouchCancel){
				QTouchEvent* e = static_cast<QTouchEvent*>(event);
				if(e->type() == QEvent::TouchBegin){
					if(!e->touchPoints().size() || e->touchPoints().size()>1)
						return false;
					fTouchID = e->touchPoints().first().id();
//					handleEvent (e->touchPoints().first().pos(), EventsAble::kTouchBegin);
					handleEvent (e->touchPoints().first().pos().x(), e->touchPoints().first().pos().y(), kTouchBeginEvent);
				}else if(e->type() == QEvent::TouchEnd || e->type() == QEvent::TouchCancel){
					fTouchID = -1;
					touchEnd(e);
				}else{
					for(int i=0; i<e->touchPoints().size(); i++){
						const QTouchEvent::TouchPoint& p = e->touchPoints().at(i);
						if(p.id() == fTouchID){
							if(p.state() == Qt::TouchPointMoved)
//								handleEvent(p.pos(), EventsAble::kTouchUpdate);
								handleEvent(p.pos().x(), p.pos().y(), kTouchUpdateEvent);
							else if(p.state() == Qt::TouchPointReleased){
//								handleEvent(p.pos(), EventsAble::kTouchEnd);
								handleEvent(p.pos().x(), p.pos().y(), kTouchEndEvent);
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

//		void touchBegin		( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), EventsAble::kTouchBegin); }
//		void touchEnd		( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), EventsAble::kTouchEnd); }
//		void touchUpdate	( QTouchEvent * event )		{ handleEvent (_MouseEventAble::touchPos(event), EventsAble::kTouchUpdate); }
//
//		void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseDoubleClick); }
//		void mouseMoveEvent		( QGraphicsSceneMouseEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseMove); }
//		void mousePressEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos(), EventsAble::kMouseDown); }
//		void mouseReleaseEvent	( QGraphicsSceneMouseEvent * event)			{ handleEvent (event->pos(), EventsAble::kMouseUp); }
//		void hoverEnterEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseEnter); }
//		void hoverLeaveEvent	( QGraphicsSceneHoverEvent * event )		{ handleEvent (event->pos(), EventsAble::kMouseLeave); }

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

#endif
