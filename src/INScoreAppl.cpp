/*

  Interlude Prototype
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

#include <QApplication>
#include <QBitmap>
#include <QDebug>
#include <QDir>
#include <QEvent>
#include <QFileDialog>
#include <QFileOpenEvent>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplashScreen>
#include <QString>
#include <QUrl>

#ifdef WIN32
#include <windows.h>
#define sleep(n)	Sleep(n*1000)
#endif

#include <stdlib.h>
#include <iostream>
#include <string>

#include "INScore.h"
#include "INScoreAppl.h"

using namespace inscore;
using namespace std;

#define kUPDPort		7000
#define kTimeInterval	10			// time task interval in milliseconds

static const char* kPortOption = "--port";


//_______________________________________________________________________
static int intopt (const string& opt, int defaultValue, int n, char **argv)
{
	for (int i = 0; i < n; i++) {
		if (opt == argv[i]) {
			int port = ( i+1 == n) ? 0 : atoi(argv[i+1]);
			return port ? port : defaultValue;
		}
	}
	return defaultValue;
}


//_______________________________________________________________________
class INScoreAbout : public QSplashScreen
{
	public:
				 INScoreAbout (const QPixmap & pixmap);
		virtual ~INScoreAbout() {}
};

INScoreAbout::INScoreAbout (const QPixmap & pixmap) : QSplashScreen (pixmap)
{
    setMask (pixmap.mask());

	QFont font ("Helvetica", 9);
	int h = height();

	QString version("INScore v.");
	version += INScore::versionStr();
	QLabel* text = new QLabel(version, this);
	text->setFont(font);
	text->move(25, h - 42);

	QString qt("Using Qt v.");
	qt += qVersion();
	text = new QLabel(qt, this);
	text->setFont(font);
	text->move(20, h - 30);

	QString guido("Using Guido Engine v.");
	guido += INScore::guidoversion();
	text = new QLabel(guido, this);
	text->setFont(font);
	text->move(15, h - 18);
}

INScoreAbout* gAbout = 0;
//_______________________________________________________________________
void INScoreAppl::about()
{
	if (gAbout) gAbout->show();
}


#if WIN32
#define sep '\\'
#else
#define sep '/'
#endif

//_______________________________________________________________________
void INScoreAppl::open(const string& file)
{
	size_t pos = file.find_last_of (sep);
	if (pos != string::npos) {
		string path = file.substr(0, pos);
		INScore::MessagePtr msg = INScore::newMessage ("rootPath");
		INScore::add (msg, path.c_str());
		INScore::postMessage ("/ITL", msg);
	}
	INScore::MessagePtr msg = INScore::newMessage ("load");
	INScore::add (msg, file.c_str());
	INScore::postMessage ("/ITL", msg);
}

//_______________________________________________________________________
bool INScoreAppl::event(QEvent *ev)
{
    if (ev->type() == QEvent::FileOpen) {
		QString fileName = static_cast<QFileOpenEvent *>(ev)->file();
		open (fileName.toStdString());
		return true;
    }
	return QApplication::event(ev);
}

//_______________________________________________________________________
void INScoreAppl::setupMenu()
{
	QMenuBar *fMenuBar = new QMenuBar(0);

    QAction* aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	
    QMenu* menu = fMenuBar->addMenu(tr("&Help"));
    menu->addAction(aboutAct);
}

//_______________________________________________________________________
INScoreAppl::~INScoreAppl() { delete fMenuBar; }


#if defined(WIN32) && !defined(_DEBUG)
# define USEWINMAIN
#endif
//_______________________________________________________________________
#ifdef USEWINMAIN
#include <windows.h>
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int iCmdShow)
#else
int main( int argc, char **argv )
#endif
{
#ifdef USEWINMAIN
	int argc = __argc;
	char **argv = __argv;
#endif

	int ret = 1;
	int udpPort = intopt (kPortOption, kUPDPort, argc, argv);
	INScoreAppl appl(argc, argv);
	appl.setApplicationName("INScoreViewer");
	QDir dir(QApplication::applicationDirPath());

	Q_INIT_RESOURCE( inscore );
    QPixmap pixmap(":/INScoreViewer.png");
    gAbout = new INScoreAbout(pixmap);
	gAbout->show();
	
	appl.setupMenu();
#ifndef WIN32
	dir.cdUp();
#endif
	dir.cd("PlugIns");
	appl.addLibraryPath		( dir.absolutePath());

	IGlue * glue = INScore::start (kTimeInterval, udpPort, kUPDPort+1, kUPDPort+2, &appl);

#ifdef WIN32
	for (int i = 1; i < appl.arguments().size(); i++) {
		const QString& arg = appl.arguments().at(i);
		appl.open (arg.toUtf8().constData());
	}
#else
	for (int i = 1; i < argc; i++) {
		const string arg = argv[i];
		if (arg[0] == '-') {
			if (arg == kPortOption) i++;
		}	
		else appl.open (arg);
	}
#endif
	sleep (2);
    gAbout->hide();
	ret = appl.exec();
	INScore::stop (glue);
	delete gAbout;
	return ret;
}
