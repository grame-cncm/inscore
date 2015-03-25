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
#include <QPixmap>
#include <QScreen>
#include <QBuffer>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QDebug>

#ifdef ANDROID
#include <QTabWidget>
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

#define SCENE_RECT QRect(-400,-400,800,800)


namespace inscore
{

class ZoomingGraphicsView : public QGraphicsView
{
	std::string		fSceneAddress;
//	VSceneView* fSceneView;
	IScene*	fScene;

	public :
		ZoomingGraphicsView(QGraphicsScene * s) : QGraphicsView(s), fScene(0) {}
		virtual ~ZoomingGraphicsView() {}

		void setSceneAddress(const std::string& name)	{ fSceneAddress = name; }
		void setScene		(IScene* scene)		{ fScene = scene; }

	protected:
		virtual void	closeEvent	(QCloseEvent *);
		virtual void	paintEvent  (QPaintEvent * );

		void resizeEvent ( QResizeEvent * event ) {
			// scene adaptation to avoid scroll bars
			fitInView( SCENE_RECT , Qt::KeepAspectRatio );
			if(fScene) {
				fScene->setUpdateVersion(true);
			}
		}
};

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
	fEventFilter = 0;
	fDataScreenShotSize = 0;
	fUpdateScreenShot = false;
	fNewVersion = 0;
	if (scene) {
		fScene = scene;
		fGraphicsView = new ZoomingGraphicsView(scene);
#ifdef ANDROID
		VQtInit::getTabWidget()->addTab(fGraphicsView, address.c_str());
#endif
		fGraphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
		fGraphicsView->scene()->setSceneRect( SCENE_RECT );
		fGraphicsView->setWindowTitle( address.c_str() );
		fGraphicsView->setSceneAddress( address.c_str() );
		fDefaultFlags = fGraphicsView->windowFlags();
		fEventFilter = new WindowEventFilter( address, fGraphicsView );
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

#ifdef ANDROID
	VQtInit::getTabWidget()->setCurrentWidget(fGraphicsView);
#else
	fGraphicsView->activateWindow();
#endif
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
			QPoint newPos;
			if (scene->getAbsoluteCoordinates()) {
				newPos= QPoint (scene->getXPos(), scene->getYPos());
			}
			else {
				QPointF screenCenter = r.center();
				newPos= QPoint (screenCenter.x() + (scene->getXPos() ) * lowestDimension / 2.0f - fGraphicsView->width()/2.0f,
									screenCenter.y() + (scene->getYPos() ) * lowestDimension / 2.0f - fGraphicsView->height()/2.0f);
			}
			fEventFilter->setAbsoluteXY (scene->getAbsoluteCoordinates());
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
		fEventFilter->setFrameless(true);
	}
	else {
		fEventFilter->setFrameless(false);
		if ((flags != fDefaultFlags) && !scene->getFullScreen()) {
			fGraphicsView->setWindowFlags (fDefaultFlags);
			fGraphicsView->showNormal ();
		}
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
	fGraphicsView->setScene (scene);

	// Export
	std::string filename = scene->getNextExportFlag();
	while ( filename.length() ) {
		VExport::exportScene( fGraphicsView , filename.c_str() );
		const IMessageList*	msgs = scene->getMessages(EventsAble::kExport);
		if (msgs) {
			MouseLocation mouse (0, 0, 0, 0, 0, 0);
			EventContext env(mouse, scene->getDate(), scene);
			TMessageEvaluator me;
			SIMessageList outmsgs = me.eval (msgs, env);
			if (outmsgs && outmsgs->list().size()) outmsgs->send();
		}
		filename = scene->getNextExportFlag();
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

//--------------------------------------------------------------------------
WindowEventFilter::WindowEventFilter(const std::string& address, QGraphicsView* parent) 
	: QObject(parent), fAbsoluteXY(false), fFrameless(false), fOSCAddress(address)
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
	if (fFrameless) return;

	QWidget * view = dynamic_cast<QWidget *>(parent());
	if ( !view ) {
		qFatal("WindowEventFilter::update(): WindowEventFilter parent must be a QWidget");
		return;
	}

	float x, y;
	QRect r = QApplication::desktop()->screenGeometry();
	float lowestDimension = qMin( r.width(), r.height() );
	if (fAbsoluteXY) {
		x = view->pos().x();
		y = view->pos().y();
	}
	else {
		QPointF screenCenter = r.center();

		x = (view->pos().x() + view->width()/2.0f - screenCenter.x()) / (lowestDimension/2.0f);
		y = (view->pos().y() + view->height()/2.0f - screenCenter.y()) / (lowestDimension/2.0f);
	}
	sendMessage( fOSCAddress.c_str() , kx_GetSetMethod , x );
	sendMessage( fOSCAddress.c_str() , ky_GetSetMethod , y );

	float width = view->width() / (lowestDimension/2.0f);
	float height = view->height() / (lowestDimension/2.0f);
	sendMessage( fOSCAddress.c_str() , kwidth_GetSetMethod , width );
	sendMessage( fOSCAddress.c_str() , kheight_GetSetMethod , height );
}

} // end namespoace
