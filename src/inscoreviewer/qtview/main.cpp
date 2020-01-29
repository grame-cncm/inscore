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

#include <QProcess>

#ifdef WIN32
#include <windows.h>
#define sleep(n)	Sleep(n*1000)
#else
#include <unistd.h>
#endif

#include "INScore.h"
#include "INScoreAppl.h"
#include "INScoreAbout.h"

using namespace inscore;
using namespace std;

#define kUPDPort		7000

const char* kPortOption = "--port";
INScoreAbout* gAbout;

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
