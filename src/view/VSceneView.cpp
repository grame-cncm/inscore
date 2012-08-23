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

#include <iostream>

#include "VSceneView.h"

#include <QImage>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QDebug>

#include "IScene.h"
#include "IColor.h"
#include "VExport.h"
#include "INScore.h"
#include "ISignalProfiler.h"

#define SCENE_RECT QRect(-400,-400,800,800)

//#define OSC_SCENE_ADDRESS	"/ITL/scene"
#define OSC_HEIGHT_MSG		"height"
#define OSC_WIDTH_MSG		"width"
#define OSC_X_MSG			"x"
#define OSC_Y_MSG			"y"

namespace inscore
{

class ZoomingGraphicsView : public QGraphicsView
{
	std::string fSceneAddress;
	VSceneView * fSceneView;

	public :
		ZoomingGraphicsView(QGraphicsScene * s) : QGraphicsView(s) {}
		virtual ~ZoomingGraphicsView() {}

		void setSceneAddress(const std::string& name)	{ fSceneAddress = name; }

	protected:
		virtual void closeEvent(QCloseEvent *);
		void resizeEvent ( QResizeEvent * event ) {
			// scene adaptation to avoid scroll bars
			fitInView( SCENE_RECT , Qt::KeepAspectRatio );
		}
};

//------------------------------------------------------------------------------------------------------------------------
void ZoomingGraphicsView::closeEvent (QCloseEvent * event) 
{
	INScore::MessagePtr msg = INScore::newMessage ("del");
	INScore::postMessage (fSceneAddress.c_str(), msg);
	event->accept();
}


#define PRECISION 100.0f

//------------------------------------------------------------------------------------------------------------------------
VSceneView::VSceneView(const std::string& address, QGraphicsScene * scene)
{
	fImage = 0;
	fGraphicsView = 0;
	fEventFilter = 0;
	if (scene) {
		fScene = scene;
		fGraphicsView = new ZoomingGraphicsView(scene);
		fGraphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
		fGraphicsView->scene()->setSceneRect( SCENE_RECT );
		fGraphicsView->setWindowTitle( address.c_str() );
		fGraphicsView->setSceneAddress( address.c_str() );
		fDefaultFlags = fGraphicsView->windowFlags();
		fEventFilter = new WindowEventFilter( address, fGraphicsView );
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
//void VSceneView::foreground()	{ fGraphicsView->activateWindow(); }

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
	fGraphicsView->setWindowOpacity(sc.getA()/255.0f);

	// Fullscreen/Normalscreen
	// switch screen mode before resizing in order to get the correct size and position
	bool fullscreen = fGraphicsView->windowState() & Qt::WindowFullScreen;
	if ( (fullscreen && !scene->getFullScreen()) || ( !fullscreen && scene->getFullScreen()))
	{
		fGraphicsView->setWindowState(fGraphicsView->windowState() ^ Qt::WindowFullScreen);
	}
	// Size
	if ( !fEventFilter->running() )			// do not update the size/position while the fEventFilter is running.
	{

		if (!scene->getFullScreen()) {		// don't resize or move in fullscreen mode
			QRect r = QApplication::desktop()->screenGeometry();
			float lowestDimension = qMin( r.width(), r.height() );


			// size
			int w = scene->getWidth() * lowestDimension / 2;
			int h = scene->getHeight() * lowestDimension / 2;
			bool needResize = (w != fGraphicsView->width()) || (h != fGraphicsView->height());
			if (needResize) {
				// deactivates the events notification to avoid events loop between 'updateModel' and 'updateTo'
				fGraphicsView->removeEventFilter( fEventFilter );
				fGraphicsView->resize( w, h );
				fGraphicsView->installEventFilter( fEventFilter );
			}

			// Position
			QPointF screenCenter = r.center();
			QPoint newPos(screenCenter.x() + (scene->getXPos() ) * lowestDimension / 2.0f - fGraphicsView->width()/2.0f,
									screenCenter.y() + (scene->getYPos() ) * lowestDimension / 2.0f - fGraphicsView->height()/2.0f);
			bool needMove = (newPos != fGraphicsView->pos());

			if (needMove) {
				// deactivates the events notification to avoid events loop between 'updateModel' and 'updateTo'
				fGraphicsView->removeEventFilter( fEventFilter );
				fGraphicsView->move( newPos );
				fGraphicsView->installEventFilter( fEventFilter );
			}
		}
	}

	// Visibility
	scene->getVisible() ? fGraphicsView->show() : fGraphicsView->hide();
	Qt::WindowFlags flags = fGraphicsView->windowFlags();
	if (scene->getFrameless()) {
		if (flags != Qt::FramelessWindowHint) {
			fGraphicsView->setWindowFlags (Qt::FramelessWindowHint);
			fGraphicsView->showNormal ();
		}
	}
	else if (flags != fDefaultFlags) {
		fGraphicsView->setWindowFlags (fDefaultFlags);
		fGraphicsView->showNormal ();
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
bool VSceneView::copy(unsigned int* dest, int w, int h, bool smooth )
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

	// Export
	if ( scene->getExportFlag().length() )
		VExport::exportScene( fGraphicsView , scene->getExportFlag().c_str() );
}

//--------------------------------------------------------------------------
WindowEventFilter::WindowEventFilter(const std::string& address, QGraphicsView* parent) 
	: QObject(parent), fOSCAddress(address)
{
	fTimer = new QTimer(this);
	fTimer->setSingleShot(true);
	connect(fTimer, SIGNAL(timeout()), this, SLOT(updateModel()));
}

//--------------------------------------------------------------------------
void WindowEventFilter::sendMessage( const char * addr , const char * cmd , float f )
{
	INScore::MessagePtr msg = INScore::newMessage( cmd );
	INScore::add(msg, f);
	INScore::postMessage( addr , msg );
}

//--------------------------------------------------------------------------
bool WindowEventFilter::eventFilter(QObject *obj, QEvent *event)
{
 	if ( (event->type() == QEvent::Move) || (event->type() == QEvent::Resize) )
	{
		fTimer->stop();
		fTimer->start(100);
		return false;
	}
	else
		// standard event processing
        return QObject::eventFilter(obj, event);
}

//--------------------------------------------------------------------------
void WindowEventFilter::updateModel()
{
	QWidget * view = dynamic_cast<QWidget *>(parent());
	if ( !view ) {
		qFatal("WindowEventFilter::update(): WindowEventFilter parent must be a QWidget");
		return;
	}

	QRect r = QApplication::desktop()->screenGeometry();
	float lowestDimension = qMin( r.width(), r.height() );
	QPointF screenCenter = r.center();

	float x = (view->pos().x() + view->width()/2.0f - screenCenter.x()) / (lowestDimension/2.0f);
	float y = (view->pos().y() + view->height()/2.0f - screenCenter.y()) / (lowestDimension/2.0f);
	sendMessage( fOSCAddress.c_str() , OSC_X_MSG , x );
	sendMessage( fOSCAddress.c_str() , OSC_Y_MSG , y );

	float width = view->width() / (lowestDimension/2.0f);
	float height = view->height() / (lowestDimension/2.0f);
	sendMessage( fOSCAddress.c_str() , OSC_WIDTH_MSG , width );
	sendMessage( fOSCAddress.c_str() , OSC_HEIGHT_MSG , height );
}

} // end namespoace
