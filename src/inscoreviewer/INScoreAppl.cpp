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
#include <QDesktopServices>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileOpenEvent>
#include <QFontDatabase>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QProcess>
#include <QSettings>
#include <QSplashScreen>
#include <QString>
#include <QTimer>
#include <QUrl>

#ifdef WIN32
#include <windows.h>
#define sleep(n)	Sleep(n*1000)
#else
#include <unistd.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

#include "INScore.h"
#include "INScoreAppl.h"
#include "QGuidoPainter.h"


using namespace inscore;
using namespace std;

#define kUPDPort		7000

static const char* kPortOption = "--port";


//_______________________________________________________________________
static void disableAppNap ()
{
	#if __APPLE__ && !defined(IOS)
	QProcess process;
	process.start("defaults write fr.grame.INScore NSAppSleepDisabled -bool YES");
	#endif
}

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

static const char* kFontName = "Helvetica";
static int kFontSize  = 9;


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

#ifdef linux
	kFontName = "FreeSans";
#endif
#ifdef WIN32
	kFontSize = 7;
#endif
#ifdef ANDROID
	kFontSize = 7;
#endif
	QFont font (kFontName, kFontSize);
	font.setPixelSize(kFontSize);

//#ifdef linux
//	QFont font ("FreeSans", 9);
//#elif defined(WIN32)
//	QFont font ("Helvetica", 7);
//	font.setPixelSize(7);
//#elif defined(ANDROID)
//	blurp
//	QFont font ("Helvetica", 7);
//	font.setPixelSize(7);
//#else
//	QFont font ("Helvetica", 9);
//	font.setPixelSize(9);
//#endif
	int h = height();

	QString version("INScore v.");
	version += INScore::versionStr();
	QLabel* text = new QLabel(version, this);
	text->setFont(font);
	text->move(27, h - 45);

	QString qt("Using Qt v.");
	qt += qVersion();
	text = new QLabel(qt, this);
	text->setFont(font);
	text->move(22, h - 33);

	QString guido("Using Guido Engine v.");
	guido += INScore::guidoversion();
	text = new QLabel(guido, this);
	text->setFont(font);
	text->move(17, h - 21);
}

INScoreAbout* gAbout = 0;
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

#if defined(WIN32) && !defined(_DEBUG)
# define USEWINMAIN
#endif

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#include "QtAppDelegate-C-Interface.h"
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

	int udpPort = intopt (kPortOption, kUPDPort, argc, argv);

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    // Initialize application delegate to manage external application event (close tablet, open new application...)
    QtAppDelegateInitialize();
    // Q_INIT_RESOURCE() and Q_CLEANUP_RESOURCE() is not necessary when the resource is built as part
    // of the application. (see QT documentation)
#else
    // We have to test on all plateform but it seems it's not necessary to call Q_INIT_RESOURCE.
    Q_INIT_RESOURCE( inscore );
#endif

	INScoreAppl appl(argc, argv);	// must be called before building a QPixmap

    QPixmap pixmap(":/INScoreViewer.png");
    gAbout = new INScoreAbout(pixmap);
    gAbout->show();
	
	appl.start (udpPort, kUPDPort+1);
    appl.readArgs(argc, argv);

    sleep (1);
    gAbout->hide();
    disableAppNap();

    appl.showMobileMenu();
    int ret = appl.exec();
//	appl.stop ();
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    delete gAbout;
#endif
    return ret;
}
