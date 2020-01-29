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
#include <QDesktopServices>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileOpenEvent>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QNetworkInterface>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QUrl>

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

#include "INScore.h"
#include "INScoreAppl.h"
#include "INScoreAbout.h"
#include "QGuidoPainter.h"


using namespace inscore;
using namespace std;

//_______________________________________________________________________
extern INScoreAbout* gAbout;
extern const char* kPortOption;

//_______________________________________________________________________
void INScoreAppl::about()
{
	if (gAbout) gAbout->show();
}

//_______________________________________________________________________
void INScoreAppl::logwindow()
{
	INScore::MessagePtr msg = INScore::newMessage ("show");
	INScore::add (msg, 1);
	INScore::postMessage ("/ITL/log", msg);
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
void INScoreAppl::read(const string& buffer)
{
	INScore::MessagePtr msg = INScore::newMessage ("read");
	INScore::add (msg, buffer.c_str());
	INScore::postMessage ("/ITL", msg);
}

//_______________________________________________________________________
bool INScoreAppl::event(QEvent *ev)
{
    if (ev->type() == QEvent::FileOpen) {
		QString fileName = static_cast<QFileOpenEvent *>(ev)->file();
		if (fStarted)
			open (fileName.toStdString());
		else 
			fPendingOpen.push_back(fileName.toStdString());
		return true;
    }
	return QApplication::event(ev);
}

//_______________________________________________________________________
void INScoreAppl::setupMenu()
{
	fMenuBar = new QMenuBar(0);

    QAction* aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	
    QMenu* menu = fMenuBar->addMenu(tr("&About"));
    menu->addAction(aboutAct);


    QAction* logAct = new QAction(tr("&Show log window"), this);
    logAct->setStatusTip(tr("Show the application log window"));
    connect(logAct, SIGNAL(triggered()), this, SLOT(logwindow()));
	
    menu = fMenuBar->addMenu(tr("&Tools"));
    menu->addAction(logAct);
}

//_______________________________________________________________________
void INScoreAppl::showMobileMenu()
{
	QSettings settings("Grame", "INScore");

	settings.beginGroup("Mobile");
	bool show = settings.value("showMenu", true).toBool();
	if(show) {
		INScore::MessagePtr msg = INScore::newMessage ("show");
		INScore::add (msg, 1);
		INScore::postMessage ("/ITL/menu", msg);
	}
}

//_______________________________________________________________________
void INScoreAppl::started()
{
	fStarted = true;
	if (fPendingBuffer.size()) {
		read(fPendingBuffer);
	}
	for (unsigned int i=0; i<fPendingOpen.size(); i++) {
		open (fPendingOpen[i]);
	}
}

//_______________________________________________________________________
INScoreAppl::INScoreAppl (int & argc, char ** argv )
	: QApplication (argc, argv), fMenuBar(0), fStarted(false)
{
	for (int i = 1; i < argc; i++) {
		string stdinopt ("-");
		if (stdinopt == argv[i]) {
			// read stdin
			string str;
			stringstream sstr;
			while (!cin.eof()) {
				cin >> str;
				sstr << str << " ";
			}
			fPendingBuffer = sstr.str();
		}
		else {
			QFile file(argv[i]);
			if (file.exists())
				fPendingOpen.push_back(argv[i]);
		}
	}
	setQuitOnLastWindowClosed(false);
}

//_______________________________________________________________________
INScoreAppl::~INScoreAppl() { delete fMenuBar; }

//_______________________________________________________________________
void INScoreAppl::readArgs(int argc, char ** argv)
{
#ifdef WIN32
	for (int i = 1; i < arguments().size(); i++) {
		const QString& arg = arguments().at(i);
		open (arg.toUtf8().constData());
	}
#else
	for (int i = 1; i < argc; i++) {
		const string arg = argv[i];
		if (arg[0] == '-') {
			if (arg == kPortOption) i++;
		}	
		else open (arg);
	}
#endif
}

//_______________________________________________________________________
void INScoreTimer::start(inscore::INScoreGlue * glue)
{
	fGlue = glue;
	setTimerType(Qt::PreciseTimer);
	QTimer::start(1);
}
void INScoreTimer::timerEvent(QTimerEvent *)	{ fGlue->sorterTask(); }

//_______________________________________________________________________
void INScoreAppl::timerEvent(QTimerEvent *)
{
	fGlue->timeTask ();
	if (fGlue->getRate() != fRate) {
		fRate = fGlue->getRate();
		killTimer(fTimerId);
		fTimerId = startTimer(fRate);
	}
}

//_______________________________________________________________________
void INScoreAppl::stop()
{
	INScore::stop (fGlue);
}

//-----------------------------------------------------------------------
// INScoreApplicationGlue interface
//-----------------------------------------------------------------------
void INScoreAppl::showMouse (bool state)
{
	if (state)
		setOverrideCursor( QCursor( Qt::ArrowCursor ) );
	else
		setOverrideCursor( QCursor( Qt::BlankCursor ) );
}

//-----------------------------------------------------------------------
bool INScoreAppl::openUrl (const char* url)
{
	QUrl qurl(url);
	return QDesktopServices::openUrl(qurl);
}

//-----------------------------------------------------------------------
string INScoreAppl::viewVersion() const
{
	QString vers(qVersion());
	return vers.toStdString();
}

//-----------------------------------------------------------------------
string INScoreAppl::getIP () const
{
	QNetworkInterface ni;
	QList<QHostAddress>	hl = ni.allAddresses();
	for (int i=0; i < hl.size(); i++) {
		unsigned long ip = hl[i].toIPv4Address();
		if (ip) {
			unsigned long classe = ip >> 24;
			if ((classe >= 192) && (classe <= 223))		// look for a classe C network
				return hl[i].toString().toStdString();
		}
	}
	return "";
}

#define GUIDO_FONT_FILE ":/guido2.ttf"
//-----------------------------------------------------------------------
void INScoreAppl::startView ()
{
	QFontDatabase::addApplicationFont (GUIDO_FONT_FILE);
	QGuidoPainter::startGuidoEngine();
}

//-----------------------------------------------------------------------
void INScoreAppl::stopView  ()
{
	QGuidoPainter::stopGuidoEngine();
}


//-----------------------------------------------------------------------
const char* kDefaultFontName = "Carlito";

//_______________________________________________________________________
void INScoreAppl::start (int udpinport, int udpoutport)
{
	setApplicationName("INScoreViewer");
	setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, false);
	setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);
	setupMenu();

	const string applfont = ":/fonts/Carlito-Regular.ttf";
	int result = QFontDatabase::addApplicationFont (applfont.c_str());
	if (result < 0) {
		cerr << "Cannot load application font " << applfont << endl;
	}
	else {
		QFontDatabase dbf;
		QFont f = dbf.font(kDefaultFontName, "Regular", 12);
		setFont (f);
	}


	QDir dir(QApplication::applicationDirPath());
#ifndef WIN32
	dir.cdUp();
#endif
	dir.cd("PlugIns");
	addLibraryPath ( dir.absolutePath());
#ifndef WIN32
	dir.cdUp();
	dir.cdUp();
#endif

    fGlue = INScore::start (udpinport, udpoutport, udpoutport+1, this);
	fRate = fGlue->getRate();
	fTimerId = startTimer (fRate, Qt::PreciseTimer);
	fSorterTask.start(fGlue);
    started();
}
