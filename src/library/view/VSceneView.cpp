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
#include <QScreen>
#include <QBuffer>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QPinchGesture>

#if defined(ANDROID) || defined(IOS)
#include "VQtInit.h"
#endif

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#include "IScene.h"
#include "IColor.h"
#include "TMessageEvaluator.h"
#include "VExport.h"
#include "INScore.h"
#include "ISignalProfiler.h"
#include "WindowEventFilter.h"

QRect SCENE_RECT(-400,-400,800,800);


namespace inscore
{

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::doZoomTranslate()
{
	if(fScene) {
        qreal h = fScene->getXOrigin() * -400;
        qreal v = fScene->getYOrigin() * -400;
        if (fTotalScaleFactor != fScene->getScale() || h != horizontalOffset || v != verticalOffset) {
            horizontalOffset = h;
            verticalOffset = v;
            fTotalScaleFactor = fScene->getScale();
            fScaleFactor = fTotalScaleFactor;
            SCENE_RECT = QRect(QPoint((-400 + horizontalOffset) / fTotalScaleFactor, (-400 + verticalOffset) / fTotalScaleFactor), QPoint((400+ horizontalOffset) / fTotalScaleFactor, (400 + verticalOffset) / fTotalScaleFactor));
            fitInView( SCENE_RECT , Qt::KeepAspectRatio );
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::resizeEvent ( QResizeEvent * ) {
	// scene adaptation to avoid scroll bars
    fitInView( SCENE_RECT , Qt::KeepAspectRatio );
	if(fScene) {
		fScene->setUpdateVersion(true);
	}
	QSize	s = size();
	QRect r = QApplication::desktop()->screenGeometry();
	if (!fScene) return;

	// full screen detection and transmission to the model
	bool fullscreen = (r.width() == s.width()) && (r.height() == s.height());
	if (fullscreen) {
		if (!fScene->getFullScreen()) fScene->setFullScreen(true);
	}
	else if (fScene->getFullScreen()) fScene->setFullScreen(false);
}

//------------------------------------------------------------------------------------------------------------------------
bool ZoomingGraphicsView::viewportEvent(QEvent *event)
{
	if (event->type() == QEvent::Gesture)
		return gestureEvent(static_cast<QGestureEvent*>(event));
	return QGraphicsView::viewportEvent(event);
}

//------------------------------------------------------------------------------------------------------------------------
bool ZoomingGraphicsView::gestureEvent(QGestureEvent *event)
{
	if (QGesture *pinch = event->gesture(Qt::PinchGesture))
		pinchTriggered(static_cast<QPinchGesture *>(pinch));
	return true;
}

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::pinchTriggered(QPinchGesture *event)
{
	// New Zoom factor
	fScaleFactor = event->totalScaleFactor() * fTotalScaleFactor;

	QPointF p0 = event->lastCenterPoint();
	QPointF p1 = event->centerPoint();
	// Verify horizontal limits to avoid scrolling when no scale factor.
    qreal h = horizontalOffset - (p1.x() - p0.x());

    // limit translation gesture if the zoom is too small
    qreal max = fScaleFactor * 400 - 400;
    if(max > abs(h))
		horizontalOffset = h;
    else {
        if(h > 0)
            horizontalOffset = max;
        else horizontalOffset = -max;
    }

    // Verify vertical limits to avoid scrolling when no scale factor.
    qreal v = verticalOffset - (p1.y() - p0.y());
    if(max > abs(v))
		verticalOffset = v;
    else {
        if(v > 0)
            verticalOffset = max;
        else verticalOffset = -max;
    }

    // Zoom and translate
    SCENE_RECT = QRect(QPoint((-400 + horizontalOffset) / fScaleFactor, (-400 + verticalOffset) / fScaleFactor), QPoint((400+ horizontalOffset) / fScaleFactor, (400 + verticalOffset) / fScaleFactor));
    fitInView( SCENE_RECT , Qt::KeepAspectRatio );
}

//------------------------------------------------------------------------------------------------------------------------
qreal ZoomingGraphicsView::getXOrigin()
{
    return horizontalOffset / -400;
}

//------------------------------------------------------------------------------------------------------------------------
qreal ZoomingGraphicsView::getYOrigin()
{
    return verticalOffset / -400;
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
	INScore::MessagePtr msg = INScore::newMessage (kdel_SetMethod);
	INScore::postMessage (fSceneAddress.c_str(), msg);
	event->accept();
}


#define PRECISION 100.0f

//------------------------------------------------------------------------------------------------------------------------
VSceneView::VSceneView(const std::string& address, QGraphicsScene * scene)
{
	fImage = 0;
	fGraphicsView = 0;
	fResizeMoveEventFilter = 0;
	fDataScreenShotSize = 0;
	fUpdateScreenShot = false;
	fNewVersion = 0;
	if (scene) {
		fScene = scene;
		fGraphicsView = new ZoomingGraphicsView(scene);
#if defined(ANDROID) || defined(IOS)
		// Add scene to tabwidget
		VQtInit::getTabWidget()->addTab(fGraphicsView, address.c_str());
#endif
		fGraphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
		fGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Default to Qt::ScrollBarAsNeeded
		fGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Default to Qt::ScrollBarAsNeeded
		fGraphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
		fGraphicsView->viewport()->grabGesture(Qt::PinchGesture);
		fGraphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
		fGraphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

		fGraphicsView->scene()->setSceneRect( SCENE_RECT );
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
#if defined(ANDROID) || defined(IOS)
	QTabWidget * tw = VQtInit::getTabWidget();
	int index = tw->indexOf(fGraphicsView);
	tw->removeTab(index);
#endif
	delete fGraphicsView;
}

//------------------------------------------------------------------------------------------------------------------------
QGraphicsScene * VSceneView::scene() const		{ return fScene; }

//------------------------------------------------------------------------------------------------------------------------
void VSceneView::foreground()
{
#if defined(ANDROID) || defined(IOS)
	// Select tab of the scene as current tab
	VQtInit::getTabWidget()->setCurrentWidget(fGraphicsView);
#else
	fGraphicsView->raise();
	fGraphicsView->activateWindow();
#endif
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

	// Fullscreen/Normalscreen
	// switch screen mode before resizing in order to get the correct size and position
	bool fullscreen = fGraphicsView->windowState() & Qt::WindowFullScreen;
	if ( (fullscreen && !scene->getFullScreen()) || ( !fullscreen && scene->getFullScreen()))
	{
		if (!fullscreen)	fResizeMoveEventFilter->setFullScreen (true);
		fGraphicsView->setWindowState(fGraphicsView->windowState() ^ Qt::WindowFullScreen);
		if (fullscreen)		fResizeMoveEventFilter->setFullScreen (false);
	}

	// Visibility
	if (scene->getVisible()) {
		bool minimized = fGraphicsView->windowState() & Qt::WindowMinimized;
		if (minimized) fGraphicsView->setWindowState(fGraphicsView->windowState() ^ Qt::WindowMinimized);
		fGraphicsView->show();
	}
	else fGraphicsView->hide();

	if (scene->getFrameless()) {
		if ( !fResizeMoveEventFilter->getFrameless() ){
			fGraphicsView->setWindowFlags (Qt::FramelessWindowHint);
			fGraphicsView->showNormal ();
			fResizeMoveEventFilter->setFrameless(true);
			fGraphicsView->move( scenePos(scene) );
		}
	}
	else if ( fResizeMoveEventFilter->getFrameless() ) {
		fGraphicsView->setWindowFlags (fDefaultFlags);
		fGraphicsView->showNormal ();
		fResizeMoveEventFilter->setFrameless(false);
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

//--------------------------------------------------------------------------
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

//--------------------------------------------------------------------------
void VSceneView::setUpdateScreenShot(const char *format)
{
	// Ask for an update of the image in a format
	fUpdateScreenShot = true;
	fScreenshotFormat = format;
}

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
			return data;
		}
	}
	AbstractData data;
	data.data = fDataScreenShot.constData();
	data.size = fDataScreenShot.size();
	return data;
}

} // end namespoace
