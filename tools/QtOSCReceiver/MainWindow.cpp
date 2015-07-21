#include "MainWindow.h"

#include "OSCListener.h"

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>

#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 7000

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
//	mReceived->setText("0");
//	mLost->setText("0");
//	mRatio->setText("0 %");
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
void ControllerWidget::report(int rcv, int errs, float ratio)
{
	QString str;
	str.setNum(rcv);
	mReceived->setText(str);
	str.setNum(errs);
	mLost->setText(str);
	str.setNum(ratio);
	str += " %";
	mRatio->setText(str);
}

//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtOSCReceiver");
	
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
