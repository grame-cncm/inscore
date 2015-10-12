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

//bool MobileZoomingGraphicsView::sAnimationActive = false;
//
////------------------------------------------------------------------------------------------------------------------------
//bool MobileZoomingGraphicsView::viewportEvent(QEvent *event)
//{
//	if (event->type() == QEvent::Gesture) {
//		return gestureEvent(static_cast<QGestureEvent*>(event));
//	}
//	return QGraphicsView::viewportEvent(event);
//}
//
////------------------------------------------------------------------------------------------------------------------------
//bool MobileZoomingGraphicsView::gestureEvent(QGestureEvent *event)
//{
//	if (QGesture *pinch = event->gesture(Qt::SwipeGesture))
//		swipeTriggered(static_cast<QSwipeGesture *>(pinch));
//	else if (QGesture *pinch = event->gesture(Qt::PinchGesture))
//		pinchTriggered(static_cast<QPinchGesture *>(pinch));
//	return true;
//}
//
////------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::pinchTriggered(QPinchGesture *event)
//{
//	// New Zoom factor
//	fScaleFactor = event->totalScaleFactor() * fTotalScaleFactor;
//
//	QPointF p0 = event->lastCenterPoint();
//	QPointF p1 = event->centerPoint();
//	// Verify horizontal limits to avoid scrolling when no scale factor.
//	qreal h = fHorizontalOffset - (p1.x() - p0.x());
//
//	// limit translation gesture if the zoom is too small
//	qreal max = fScaleFactor * 400 - 400;
//	if(max > abs(h))
//		fHorizontalOffset = h;
//	else {
//		if(h > 0)
//			fHorizontalOffset = max;
//		else fHorizontalOffset = -max;
//	}
//
//	// Verify vertical limits to avoid scrolling when no scale factor.
//	qreal v = fVerticalOffset - (p1.y() - p0.y());
//	if(max > abs(v))
//		fVerticalOffset = v;
//	else {
//		if(v > 0)
//			fVerticalOffset = max;
//		else fVerticalOffset = -max;
//	}
//
//	// Zoom and translate
//	fSceneRect = QRect(QPoint((-400 + fHorizontalOffset) / fScaleFactor, (-400 + fVerticalOffset) / fScaleFactor), QPoint((400 + fHorizontalOffset) / fScaleFactor, (400 + fVerticalOffset) / fScaleFactor));
//	fitInView( fSceneRect , Qt::KeepAspectRatio );
//}
//
////------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::swipeTriggered(QSwipeGesture *event) {
//	// Only one animation at same time.
//    if(sAnimationActive)
//		return;
//    sAnimationActive=true;
//	// Get gesture direction to change for next or previous tab.
//	QSwipeGesture::SwipeDirection direction = event->horizontalDirection();
//
//	QTabWidget* tw = VMobileQtInit::getTabWidget();
//	int currentIndex = tw->currentIndex();
//	int offsetx = tw->width();
//	int nextIndex;
//	if(direction == QSwipeGesture::Right) {
//		//offsetx=offsetx;
//		nextIndex = currentIndex - 1;
//	} else if(direction == QSwipeGesture::Left) {
//		offsetx=-offsetx;
//		nextIndex = currentIndex + 1;
//	} else return;
//
//	int nbTab = tw->count();
//	if(nextIndex >= nbTab || nextIndex < 0)
//		return;
//	QWidget *nextWidget = tw->widget(nextIndex);
//	QWidget *currentWidget = tw->widget(currentIndex);
//	nextWidget->setGeometry ( 0,  0, currentWidget->width(), currentWidget->height() );
//
//	//re-position the next widget outside/aside of the display area
//	QPoint pnext = nextWidget->pos();
//	QPoint pnow = currentWidget->pos();
//	fInitialPos = pnow;
//
//	// Move the next window at the border of the current window.
//	nextWidget->move(pnext.x() - offsetx, pnext.y());
//	//make it visible/show
//	nextWidget->show();
//	nextWidget->raise();
//
//	// Animate both, the now and next widget to the side, using animation framework
//	QPropertyAnimation *animnow = new QPropertyAnimation(currentWidget, "pos");
//    animnow->setDuration(1000);
//	animnow->setEasingCurve(QEasingCurve::OutBack); // Change this to change animation mouvement
//	animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
//	animnow->setEndValue(QPoint(offsetx + pnow.x(), pnow.y()));
//	QPropertyAnimation *animnext = new QPropertyAnimation(nextWidget, "pos");
//    animnext->setDuration(1000);
//	animnext->setEasingCurve(QEasingCurve::OutBack);
//	animnext->setStartValue(QPoint(-offsetx + pnext.x(), pnext.y()));
//	animnext->setEndValue(QPoint(pnext.x(), pnext.y()));
//
//	// Execute the two animations at same time
//	fAnimgroup = new QParallelAnimationGroup;
//	fAnimgroup->addAnimation(animnow);
//	fAnimgroup->addAnimation(animnext);
//	QObject::connect(fAnimgroup, SIGNAL(finished()),this,SLOT(animationDoneSlot()));
//	fIndexNextTab=nextIndex;
//	fIndexCurrentTab=currentIndex;
//	fAnimgroup->start();
//}
//
////------------------------------------------------------------------------------------------------------------------------
//void MobileZoomingGraphicsView::animationDoneSlot(void) {
//	QTabWidget* tw = VMobileQtInit::getTabWidget();
//	// when ready, set next tab index as current index
//	tw->setCurrentIndex(fIndexNextTab);
//	// then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
//	tw->widget(fIndexCurrentTab)->hide();
//	//then set the position of the outshifted widget now back to its original
//	tw->widget(fIndexCurrentTab)->move(fInitialPos);
//
//	// No animation is running
//    sAnimationActive=false;
//	delete fAnimgroup;
//	emit animationFinished();
//}

//------------------------------------------------------------------------------------------------------------------------
VMobileSceneView::~VMobileSceneView()
{
	QTabWidget * tw = VMobileQtInit::getTabWidget();
	int index = tw->indexOf(fGraphicsView);
	tw->removeTab(index);
}

//------------------------------------------------------------------------------------------------------------------------
void VMobileSceneView::foreground()
{
	// Select tab of the scene as current tab
	VMobileQtInit::getTabWidget()->setCurrentWidget(fGraphicsView);
}

//------------------------------------------------------------------------------------------------------------------------
ZoomingGraphicsView * VMobileSceneView::createGraphicsView(QGraphicsScene * scene, const char * address)
{
//	MobileZoomingGraphicsView *view =  new MobileZoomingGraphicsView(scene);
	ZoomingGraphicsView *view =  VSceneView::createGraphicsView(scene, address);

	// Add scene to tabwidget
	VMobileQtInit::getTabWidget()->addTab(view, address);

	// Add gesture event support.
	view->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
	view->viewport()->grabGesture(Qt::PinchGesture);
	view->viewport()->grabGesture(Qt::SwipeGesture);
	return view;
}

}
