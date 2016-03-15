/*

  INScore Project

  Copyright (C) 2015  Grame

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

  Grame Research Laboratory, 11 cours Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include "VMobileSceneView.h"
#include "VMobileQtInit.h"

#include <QPinchGesture>
#include <QSwipeGesture>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

namespace inscore {

////------------------------------------------------------------------------------------------------------------------------
//MobileZoomingGraphicsView::MobileZoomingGraphicsView(QGraphicsScene *s)
//	: ZoomingGraphicsView(s)
//{
//	viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
//	setAttribute(Qt::WA_AcceptTouchEvents);
//}

//bool MobileZoomingGraphicsView::viewportEvent(QEvent *event)
//{

//	// Intercept gestures
//	if(event->type() == QEvent::Gesture ){
//		if(fFocus)
//			return gestureEvent(static_cast<QGestureEvent*>(event));
//		return true;
//	}

//	if(! (fFocus && (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd || event->type() == QEvent::TouchUpdate) )){
//		// Dispatch event to the graphics scene, if the event is consumed then a graphics item is owning the focus
//		if(QGraphicsView::viewportEvent(event) && event->isAccepted())
//			return true;
//	}
//	// If the event is not consumed by the graphics scene on a touch begin, the view own the focus
//	if(event->type() == QEvent::TouchBegin)
//		fFocus = true;
//	else if(event->type() == QEvent::TouchEnd)		//release the focus on touch end
//		fFocus = false;

//	// Detect if a swipe movement has been executed
//	if(VMobileQtInit::getMainPanel()->swipeEventFilter()->eventFilter(viewport(), event))
//		return true;

//	// TouchBegin events should always be accepted, otherwise no touch events will be sended to this object
//	if( event->type() == QEvent::TouchBegin)
//		return true;

//	return false;
//}

////------------------------------------------------------------------------------------------------------------------------
//bool MobileZoomingGraphicsView::gestureEvent(QGestureEvent *event)
//{
//	if (QGesture *pinch = event->gesture(Qt::PinchGesture))
//		pinchTriggered(static_cast<QPinchGesture *>(pinch));
//	else{
//		event->ignore();
//		return false;
//	}

//	event->accept();
//	return true;
//}

////------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::pinchTriggered(QPinchGesture *event)
//{

//	if(event->state() == Qt::GestureFinished || event->state() == Qt::GestureCanceled){
//		//Cleanup
//		fViewTranslate = QPointF( transform().dx(), transform().dy());
//		return;
//	}else if(event->state() == Qt::GestureStarted){
//		//Init
//		fIniViewScale = fViewScale;
//		fIniViewTranslate = fViewTranslate;
//		return;
//	}else if(event->state() == Qt::GestureCanceled){
//		//Undo
//		fViewScale = fIniViewScale;
//		fViewTranslate = fIniViewTranslate;
//	}else{
//		//Update

//		qreal newScale = qMax(event->totalScaleFactor() * fIniViewScale, 1.);
//		//QPointF deltaCenter = event->centerPoint() -  event->lastCenterPoint();

//		qDebug()<<fViewScale<<fViewTranslate;
//		QTransform t = transform();
//		t.translate(-event->lastCenterPoint().x()/fViewScale, -event->lastCenterPoint().y()/fViewScale);
//		t.scale(newScale/fViewScale, newScale/fViewScale);
//		t.translate(event->centerPoint().x()/newScale, event->centerPoint().y()/newScale);

//		setTransform(t);

//		fViewScale = newScale;
//		return;
//	}

//	// Zoom and translate
//	int l = 400/fViewScale;
//	QRect viewRect(-l+fViewTranslate.x(),-l+fViewTranslate.y(), 2*l, 2*l);

//	//fSceneRect = QRect(QPoint((-400 + fHorizontalOffset) / fScaleFactor, (-400 + fVerticalOffset) / fScaleFactor), QPoint((400 + fHorizontalOffset) / fScaleFactor, (400 + fVerticalOffset) / fScaleFactor));
//	fitInView( viewRect , Qt::KeepAspectRatio );

//}


////------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::resetViewZoomTranslate()
//{
//	fTotalScaleFactor = fViewScale;
//	doZoomTranslate();
//	fViewScale = 1;
//	fViewTranslate = QPointF(0,0);
//}

////------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::doZoomTranslate()
//{
//	QRect r = fSceneRect;
//	//Execute doZoomTranslate()
//	ZoomingGraphicsView::doZoomTranslate();

//	if(r!=fSceneRect){
//		// Reset view scale and translate
//		fViewScale = 1;
//		fViewTranslate = QPointF(0,0);
//	}
//}

//------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::animationDoneSlot(void) {
//	QTabWidget* tw = VMobileQtInit::getTabWidget();
//	// when ready, set next tab index as current index
//	tw->setCurrentIndex(fIndexNextTab);
//	// then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
//	tw->widget(fIndexCurrentTab)->hide();
//	//then set the position of the outshifted widget now back to its original
//	tw->widget(fIndexCurrentTab)->move(fInitialPos);

//	// No animation is running
//	sAnimationActive=false;
//	delete fAnimgroup;
//	emit animationFinished();
//}

//------------------------------------------------------------------------------------------------------------------------
VMobileSceneView::~VMobileSceneView()
{
	VMobileQtInit::getMainPanel()->removePanel(fGraphicsView->getSceneAddress());
}

//------------------------------------------------------------------------------------------------------------------------
void VMobileSceneView::foreground()
{
	// Select tab of the scene as current tab
	VMobileQtInit::getMainPanel()->switchToPanel(fGraphicsView->getSceneAddress());
	VMobileQtInit::hideMenu();
}

//------------------------------------------------------------------------------------------------------------------------
ZoomingGraphicsView * VMobileSceneView::createGraphicsView(QGraphicsScene * scene, const char * address)
{
//	MobileZoomingGraphicsView *view =  new MobileZoomingGraphicsView(scene);
	ZoomingGraphicsView *view =  VSceneView::createGraphicsView(scene, address);

	// Add scene to tabwidget
	VMobileQtInit::getMainPanel()->addScene(QString(address), view);

	// Add gesture event support.
	view->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
	view->viewport()->grabGesture(Qt::PinchGesture);
	view->viewport()->grabGesture(Qt::SwipeGesture);
	return view;
}

}
