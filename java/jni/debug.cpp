
#include <iostream>

#include <QtGui/QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPainter>
#include <QMutexLocker>
#include <QObject>

#include "debug.h"


static DebugListener*	gListener;
static QMutex			gMutex;

//--------------------------------------------------------------------------
class myTimeTask : public QObject 
{
	int fID;
	QGraphicsScene* fScene;

	public:
				 myTimeTask(QGraphicsScene* scene, int size) : fID(0), fScene(scene) {}
		virtual ~myTimeTask()			{ if (fID) killTimer(fID); }
			void start(int interval)	{ fID = startTimer(interval); }

	protected:
		virtual void timerEvent ( QTimerEvent *  ) {
			QMutexLocker lock(&gMutex);
			QList<QGraphicsItem *> items = fScene->items ();
			QList<QGraphicsItem *>::iterator i = items.begin();
			while (i != items.end()) {
				(*i)->rotate (1.);
				i++; 
			}
//std::cout << "(";
			if (gListener) gListener->update();
//std::cout << ")\n";
		}
};

//------------------------------------------------------------------------
static void init(QGraphicsScene* scene, int w, int h, int size)
{
	const int gap = 4;
	float wf = (float)w / (size - gap) - gap;
	float hf = (float)h / (size - gap) - gap;
	int n = size * size;
	float x = 2.0, y = 2.0;
	for ( int i = 0 ; i < n ; ) {
		QGraphicsRectItem * rect = new QGraphicsRectItem (QRect(0, 0, wf, hf));
		QRectF brect = rect->boundingRect();
		rect->setPos(x, y);
		rect->translate( -brect.center().x(), -brect.center().y());
		rect->setTransformOriginPoint (brect.center().x(), brect.center().y());
		i++;
		if (!(i % size)) {
			x = 2.0;
			y += brect.height() + 6;
		}
		else x += brect.width() + 6;	
		scene->addItem (rect);
	}
}

//------------------------------------------------------------------------
// below are the JNI public functions
//------------------------------------------------------------------------
/*
	this is intended to notify the Java client that the scene has changed and 
	needs to be redrawn
*/
void setListener (DebugListener* listener)		{ gListener = listener; }


//------------------------------------------------------------------------
/*
	this is intended to notify the Java client that the scene has changed and 
	needs to be redrawn
*/
void getBitmap(QGraphicsScene* scene, unsigned int* dest, int w, int h)
{
	QMutexLocker lock(&gMutex);
//std::cout << "->";
	QImage image (w, h, QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&image);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	painter.fillRect (0,0,w,h, QColor(255,255,255,255));
	scene->render(&painter);
	painter.end();

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			QRgb pix = image.pixel(x, y);
			*dest++ = pix;
		}
	}
//std::cout << "<-\n";
}

//--------------------------------------------------------------------------
/*
	the Qt part initialization, 
	note that when called from Java, a QApplication is created
	but QApplication::exec() is not called.

*/
QGraphicsScene* start( QApplication* appl )
{
	const int size = 20;
	int argc; char** argv = 0;
	if (!appl) appl = new QApplication(argc, argv);

	QGraphicsScene* scene = new QGraphicsScene;
	init (scene, 600, 600, size);
	
	myTimeTask *t = new myTimeTask(scene, size);
	t->start (10);
	return scene;
}



//--------------------------------------------------------------------------
//	and that's the initialization when compiled as stand-alone application
//--------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a (argc, argv);
	QGraphicsScene* scene = start (&a);

	QGraphicsView *view = new QGraphicsView(scene);
	view->resize(600, 600);
	view->show();

	a.exec();
	return 0;
}

