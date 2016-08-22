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

#include "VSceneView.h"

#include <QImage>
#include <QDebug>
#include <QScreen>
#include <QBuffer>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QGestureEvent>
#include <QPinchGesture>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#ifdef __MOBILE__
#include "VMobileQtInit.h"
#endif

#include "IScene.h"
#include "IColor.h"
#include "TMessageEvaluator.h"
#include "VExport.h"
#include "INScore.h"
#include "ISignalProfiler.h"
#include "WindowEventFilter.h"


namespace inscore
{
	QRect defaultRect(-400,-400,800,800);

//------------------------------------------------------------------------------------------------------------------------
ZoomingGraphicsView::ZoomingGraphicsView(QGraphicsScene * s) : QGraphicsView(s), fScene(0), fScaleFactor(1),
		fTotalScaleFactor(1), fHorizontalOffset(0), fVerticalOffset(0), fSceneRect(defaultRect), fFocus(false)
{
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::doZoomTranslate()
{
	if(fScene) {
        qreal h = fScene->getXOrigin() * -400;
        qreal v = fScene->getYOrigin() * -400;
		// Due to unknown tiny error while processing offset and scale through INScore message, the offset sould be updated only if the difference is bigger than 10e-2 (2.5e-5 in INScore mesure)
		if (round(10e5*fTotalScaleFactor) != round(10e5*fScene->getScale()) || round(h*10e2) != round(10e2*fHorizontalOffset) || round(10e2*v) != round(10e2*fVerticalOffset)) {

//			if(round(10e5*fTotalScaleFactor) != round(10e5*fScene->getScale()))
//				qDebug()<<"Scale: "<<(int)round(10e5*fTotalScaleFactor)<<" != "<<(int)round(10e5*fScene->getScale());
//			if(round(10e2*fHorizontalOffset) != round(10e2*h))
//				qDebug()<<"x: "<<(int)round(10e2*fHorizontalOffset)<<" != "<<(int)round(10e2*h);
//			if(round(10e2*fVerticalOffset) != round(10e2*v))
//				qDebug()<<"y: "<<(int)round(10e2*fVerticalOffset)<<" != "<<(int)round(10e2*v);

			fHorizontalOffset = h;
			fVerticalOffset = v;
            fTotalScaleFactor = fScene->getScale();
            fScaleFactor = fTotalScaleFactor;
			fSceneRect = QRect(QPoint((-400 + fHorizontalOffset) / fTotalScaleFactor, (-400 + fVerticalOffset) / fTotalScaleFactor), QPoint((400+ fHorizontalOffset) / fTotalScaleFactor, (400 + fVerticalOffset) / fTotalScaleFactor));
			fitInView( fSceneRect , Qt::KeepAspectRatio );
        }
	}
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::resetViewZoomTranslate()
{
	fHorizontalOffset = 0;
	fVerticalOffset   = 0;
	fTotalScaleFactor = 1;
	fScaleFactor      = fTotalScaleFactor;
	fSceneRect = QRect(QPoint((-400 + fHorizontalOffset) / fTotalScaleFactor, (-400 + fVerticalOffset) / fTotalScaleFactor), QPoint((400+ fHorizontalOffset) / fTotalScaleFactor, (400 + fVerticalOffset) / fTotalScaleFactor));
	fitInView( fSceneRect , Qt::KeepAspectRatio );
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::stateChange ( bool fullscreen )
{
	if (fullscreen != fScene->getFullScreen()) {
		fScene->setFullScreen(fullscreen);
	}
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::resizeEvent ( QResizeEvent * )
{
	// scene adaptation to avoid scroll bars
	fitInView( fSceneRect , Qt::KeepAspectRatio );
	if(fScene) {
		fScene->setUpdateVersion(true);
	}
}

#ifndef __MOBILE__
//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::changeEvent(QEvent *e)
{
	if(e->type() == QEvent::ActivationChange){
		if(isActiveWindow() && e->spontaneous() && fScene){
			INScore::postMessage(fScene->getOSCAddress().c_str(), "foreground");
			e->accept();
			return;
		}
	}
	QGraphicsView::changeEvent(e);
}

#endif

//------------------------------------------------------------------------------------------------------------------------
qreal ZoomingGraphicsView::getXOrigin()
{
	return fHorizontalOffset / -400;
}

//------------------------------------------------------------------------------------------------------------------------
qreal ZoomingGraphicsView::getYOrigin()
{
	return fVerticalOffset / -400;
}

std::string ZoomingGraphicsView::getSceneAddress() const
{
	return fSceneAddress;
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::paintEvent (QPaintEvent * event) 
{
    QGraphicsView::paintEvent (event);
	if (fScene)  {
		fScene->endPaint();

		VSceneView * sceneView = dynamic_cast<VSceneView*>(fScene->getView());
		sceneView->updateSreenShot(fScene->isUpdateVersion());
		// Initialisation of updated flag after redrawing the scene
		fScene->setUpdateVersion(false);
	}
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::closeEvent (QCloseEvent * event) 
{
	INScore::postMessage (fSceneAddress.c_str(), kdel_SetMethod);
	event->accept();
}

//------------------------------------------------------------------------------------------------------------------------
bool ZoomingGraphicsView::viewportEvent(QEvent *event)
{
	// Intercept gestures
	if(event->type() == QEvent::Gesture ){
		if(fFocus)
			return gestureEvent(static_cast<QGestureEvent*>(event));
		return true;
	}

	if(! (fFocus && (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd || event->type() == QEvent::TouchUpdate) )){
		// Dispatch event to the graphics scene, if the event is consumed then a graphics item is owning the focus
		if(QGraphicsView::viewportEvent(event) && event->isAccepted())
			return true;
	}
	// If the event is not consumed by the graphics scene on a touch begin, the view own the focus
	if(event->type() == QEvent::TouchBegin)
		fFocus = true;
	else if(event->type() == QEvent::TouchEnd)		//release the focus on touch end
		fFocus = false;

#ifdef __MOBILE__
	// Detect if a swipe movement has been executed
	if(VMobileQtInit::getMainPanel()->swipeEventFilter()->eventFilter(viewport(), event))
		return true;
#endif

	// TouchBegin events should always be accepted, otherwise no touch events will be sended to this object
	if( event->type() == QEvent::TouchBegin)
		return true;


	return false;
}

//------------------------------------------------------------------------------------------------------------------------
bool ZoomingGraphicsView::gestureEvent(QGestureEvent *event)
{
	if (QGesture *pinch = event->gesture(Qt::PinchGesture))
		pinchTriggered(static_cast<QPinchGesture *>(pinch));
	else{
		event->ignore();
		return false;
	}
	event->accept();
	return true;
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::pinchTriggered(QPinchGesture *event)
{
	if(event->state() == Qt::GestureFinished || event->state() == Qt::GestureCanceled){
		//Clean up
		fTotalScaleFactor = fScaleFactor;
		fSceneRect = QRect(QPoint((-400 + fHorizontalOffset) / fTotalScaleFactor, (-400 + fVerticalOffset) / fTotalScaleFactor), QPoint((400+ fHorizontalOffset) / fTotalScaleFactor, (400 + fVerticalOffset) / fTotalScaleFactor));
		return;
	}else if(event->state() == Qt::GestureStarted){
		//Init
		return;
	}

	//Update
	qreal newScale = event->totalScaleFactor() * fTotalScaleFactor;
	if(newScale<1)
		newScale = 1;
	else if(event->totalScaleFactor()>.9 && event->totalScaleFactor()<1.1)
		newScale = fScaleFactor;


	QTransform t = transform();
	t.translate(-event->lastCenterPoint().x()/fScaleFactor, -event->lastCenterPoint().y()/fScaleFactor);
	t.scale(newScale/fScaleFactor, newScale/fScaleFactor);

	fHorizontalOffset = event->centerPoint().x()/newScale;
	fVerticalOffset   = event->centerPoint().y()/newScale;
	t.translate(fHorizontalOffset, fVerticalOffset);

	setTransform(t);

	fScaleFactor = newScale;
	return;
}




//------------------------------------------------------------------------------------------------------------------------
VSceneView::VSceneView()
{
	fImage = 0;
	fGraphicsView = 0;
	fResizeMoveEventFilter = 0;
	fDataScreenShotSize = 0;
	fUpdateScreenShot = false;
	fNewVersion = 0;
}

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::initializeView(const std::string& address, QGraphicsScene * scene)
{
	if (scene) {
		fScene = scene;
		fGraphicsView = createGraphicsView(scene, address.c_str());
		fGraphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
		fGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Default to Qt::ScrollBarAsNeeded
		fGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Default to Qt::ScrollBarAsNeeded
		fGraphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
		fGraphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

		fGraphicsView->scene()->setSceneRect( defaultRect );
		fGraphicsView->setWindowTitle( address.c_str() );
		fGraphicsView->setSceneAddress( address.c_str() );
		fDefaultFlags = fGraphicsView->windowFlags();
		fResizeMoveEventFilter = new ResizeMoveEventFilter( address, fGraphicsView );
		fTouchEventFilter = new TouchEventFilter( address, fGraphicsView );
		fGraphicsView->viewport()->installEventFilter(fTouchEventFilter);

		QColor white(255, 255, 255, 255);
		fGraphicsView->setBackgroundBrush( QBrush(white));
		fScene->setBackgroundBrush (white);
	}
	else {		// no scene is for offscreen rendering
		fScene = new QGraphicsScene;
		fImage = new QImage;
	}
}

//------------------------------------------------------------------------------------------------------------------------
VSceneView::~VSceneView()
{
	delete fImage;
	delete fScene;
	delete fGraphicsView;
}

//------------------------------------------------------------------------------------------------------------------------
QGraphicsScene * VSceneView::scene() const		{ return fScene; }

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::foreground()
{
	fGraphicsView->raise();
	fGraphicsView->activateWindow();
}

//------------------------------------------------------------------------------------------------------------------------
QPoint VSceneView::scenePos(const IScene * scene) const
{
	QRect r = QApplication::desktop()->screenGeometry();
	QPoint pos;
	if (scene->getAbsoluteCoordinates()) {
		pos= QPoint (scene->getXPos(), scene->getYPos());
	}
	else {
		QPointF screenCenter = r.center();
		float lowestDimension = qMin( r.width(), r.height() );
		pos= QPoint (screenCenter.x() + (scene->getXPos() ) * lowestDimension / 2.0f - fGraphicsView->width()/2.0f,
							screenCenter.y() + (scene->getYPos() ) * lowestDimension / 2.0f - fGraphicsView->height()/2.0f);
	}
	return pos;
}

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::updateOnScreen( IScene * scene )
{
	// Color
	int r,g,b,a;
	fGraphicsView->backgroundBrush().color().getRgb(&r,&g,&b,&a);
	IColor cc(r,g,b,a);
	IColor sc = *scene;
	if (cc != sc) {
		fGraphicsView->setBackgroundBrush( QBrush(QColor(sc.getR(), sc.getG(), sc.getB() , sc.getA())));
		fScene->setBackgroundBrush (QColor(sc.getR(), sc.getG(), sc.getB() , sc.getA()));
	}

	// Transparency
	if (!scene->getWindowOpacity())
		fGraphicsView->setWindowOpacity(sc.getA()/255.0f);


#ifdef __MOBILE__
	//On Mobile only fullscreen command works

	VMobileQtInit::getMainPanel()->setFullScreen(QString::fromStdString(fGraphicsView->getSceneAddress()), scene->getFullScreen());

#else
	// Fullscreen/Normalscreen
	// switch screen mode before resizing in order to get the correct size and position
	bool fullscreen = fGraphicsView->windowState() & Qt::WindowFullScreen;
	if (fullscreen != scene->getFullScreen())
		fGraphicsView->setWindowState(fGraphicsView->windowState() ^ Qt::WindowFullScreen);

	// Visibility
	if (scene->getVisible()) {
		bool minimized = fGraphicsView->windowState() & Qt::WindowMinimized;
		if (minimized) fGraphicsView->setWindowState(fGraphicsView->windowState() ^ Qt::WindowMinimized);
		fGraphicsView->show();
	}
	else fGraphicsView->hide();

	bool frameless = fGraphicsView->windowFlags () & Qt::FramelessWindowHint;
	if (scene->getFrameless() != frameless) {
			fGraphicsView->setWindowFlags (frameless ? fDefaultFlags : Qt::FramelessWindowHint);
			fGraphicsView->showNormal ();
	}

	// Size
	if ( !fResizeMoveEventFilter->running() )	{		// do not update the size/position while the fEventFilter is running.
		if (!scene->getFullScreen()) {		// don't resize or move in fullscreen mode
			QRect r = QApplication::desktop()->screenGeometry();
			float lowestDimension = qMin( r.width(), r.height() );


			// size
			int w = scene->getWidth() * lowestDimension / 2;
			int h = scene->getHeight() * lowestDimension / 2;
			bool needResize = (w != fGraphicsView->width()) || (h != fGraphicsView->height());
			if (needResize) {
				// deactivates the events notification to avoid events loop between 'updateModel' and 'updateTo'
				fGraphicsView->removeEventFilter( fResizeMoveEventFilter );
				fGraphicsView->resize( w, h );
				fGraphicsView->installEventFilter( fResizeMoveEventFilter );
			}

			// Position
			fResizeMoveEventFilter->setAbsoluteXY (scene->getAbsoluteCoordinates());
			QPoint newPos = scenePos(scene);
			bool needMove = (newPos != fGraphicsView->pos());
			if (needMove ) {
				// deactivates the events notification to avoid events loop between 'updateModel' and 'updateTo'
				fGraphicsView->removeEventFilter( fResizeMoveEventFilter );
				fGraphicsView->move( newPos );
				fGraphicsView->installEventFilter( fResizeMoveEventFilter );
			}
		}
    }
#endif
    // If user is doing a gesture, don't update zoom and translation.
    if (!fTouchEventFilter->running()) {
        // Zoom and position of the scene
        fGraphicsView->doZoomTranslate();
    }
}


//------------------------------------------------------------------------------------------------------------------------
void VSceneView::updateOffScreen( IScene * scene )
{
	// Size
	QRect r = QApplication::desktop()->screenGeometry();
	float lowestDimension = qMin( r.width(), r.height() );
	int w = scene->getWidth() * lowestDimension / 2;
	int h = scene->getHeight() * lowestDimension / 2;

	fScene->setSceneRect (0,0,w,h);
	IColor sc = *scene;
	fScene->setBackgroundBrush (QColor(sc.getR(), sc.getG(), sc.getB() , sc.getA()));
}

//------------------------------------------------------------------------------------------------------------------------
bool VSceneView::copy(unsigned int* dest, int w, int h, bool /*smooth*/ )
{
	QImage image (w, h, QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&image);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	painter.fillRect (0,0,w,h, QColor(0,0,0,0));
	fScene->render(&painter);
	painter.end();

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			QRgb pix = image.pixel(x, y);
			*dest++ = pix;
		}
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::updateView( IScene * scene )
{
    if (scene->getDeleted()) return;

	if (fGraphicsView) updateOnScreen (scene);
	else updateOffScreen (scene);
	fGraphicsView->setScene (scene);

    // Export
	std::pair<std::string, bool> myExport = scene->getNextExportFlag();
    while ( myExport.first.length() ) {
        VExport::exportScene( fGraphicsView , myExport.first.c_str() );
		const IMessageList*	msgs = scene->getMessages(EventsAble::kExport);
        if (msgs) {
			MouseLocation mouse (0, 0, 0, 0, 0, 0);
			EventContext env(mouse, scene->getDate(), scene);
			TMessageEvaluator me;
			SIMessageList outmsgs = me.eval (msgs, env);
			if (outmsgs && outmsgs->list().size()) outmsgs->send();
		}
		myExport = scene->getNextExportFlag();
	}
}

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::updateSreenShot(bool newVersion)
{
	if(newVersion) fNewVersion++;

	if(fUpdateScreenShot) {
		this->fDataScreenShotSize = 0;
		fUpdateScreenShot = false;
		// Update the screenshot
		QSize size (this->fGraphicsView->width() , this->fGraphicsView->height() );
		QImage image(size, QImage::Format_ARGB32_Premultiplied);
		QPainter painter(&image);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
		this->fGraphicsView->render( &painter );
		painter.end();

		QBuffer buffer(&fDataScreenShot);
		buffer.open(QIODevice::WriteOnly);
		image.save(&buffer, fScreenshotFormat.c_str());
		// Set the image is available
		this->fDataScreenShotSize = fDataScreenShot.size();
	} else {
		// Invalidate previous screenshot
		this->fDataScreenShotSize = 0;
	}
}

#ifdef WIN32
# define wait(n)	Sleep(n)
#else
# define wait(n)	usleep(n * 1000);
#endif // win32

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::setUpdateScreenShot(const char *format)
{
	// Ask for an update of the image in a format
	fUpdateScreenShot = true;
	fScreenshotFormat = format;
}

//------------------------------------------------------------------------------------------------------------------------
const AbstractData VSceneView::getImage(const char *format)
{
	// If screenshot is ready we do nothing
	if(!isScreenShotReady()) {

		// Request a screen shot
		setUpdateScreenShot(format);

		// Wait for a new screenshot provided by an automatic refresh.
		int i = 0;
		do {
			wait(5);
			i++;
		} while(!isScreenShotReady() && i != 100);
		// The score have not been automatically refresh, we force refresh it
		if(!isScreenShotReady()) {
			// Force update of the widget
			fGraphicsView->viewport()->update();

			// Wait for the force refresh
			i = 0;
			do {
				wait(5);
				i++;
			} while(!isScreenShotReady() && i != 100);
		}

		// We can't have a image of the score
		if(!isScreenShotReady()) {
			AbstractData data;
			data.data = 0;
			data.size = 0;
			data.version = 0;
			return data;
		}
	}
	AbstractData data;
	data.data = fDataScreenShot.data();
	data.size = fDataScreenShot.size();
	data.version = fNewVersion;
	return data;
}

//------------------------------------------------------------------------------------------------------------------------
ZoomingGraphicsView *VSceneView::createGraphicsView(QGraphicsScene * scene, const char *)
{
	return new ZoomingGraphicsView(scene);
}

} // end namespoace
