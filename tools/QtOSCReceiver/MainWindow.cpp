#include "MainWindow.h"

#include "OSCListener.h"

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTimer>

#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#define DEFAULT_ADDRESS "127.0.0.1"
//#define DEFAULT_ADDRESS "marcopolo.grame.fr"
#define DEFAULT_PORT 7000

#define OUTPUT_BUFFER_SIZE 2048

#define DEBUG

using namespace std;

//------------------------------------------------------------------------
ControllerWidget::ControllerWidget(QWidget *parent)
	 : QWidget(parent)
{
	setupUi(this);
	fOscThread = new OscThread(getPort(), this);
	fOscThread->start();
	connect( mRestart , SIGNAL(clicked()) , this , SLOT(restart()) );
}

//------------------------------------------------------------------------
void ControllerWidget::restart()
{
	mLostMessages->setValue(0);
	mLastMessage->setValue(0);
	fOscThread->stop();
	delete fOscThread;
	fOscThread = new OscThread(getPort(), this);
	fOscThread->start();
}

//------------------------------------------------------------------------
int ControllerWidget::getPort()
{
	return mPort->value();
}

//------------------------------------------------------------------------
void ControllerWidget::setError(unsigned long number)
{
	mLostMessages->setValue(number);
}

//------------------------------------------------------------------------
void ControllerWidget::setLastMessage(unsigned long number)
{
	mLastMessage->setValue(number);
}
//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtController");
	
	QSettings settings;
	resize(settings.value("size", QSize(100, 100)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	 
	ControllerWidget * centralW = new ControllerWidget(this);
	setCentralWidget(centralW);
}

//------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	QSettings settings;

    settings.setValue("size", size());
    settings.setValue("pos", pos());
}
