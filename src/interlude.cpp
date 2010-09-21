/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <QApplication>
#include <QDir>
#include <QtDebug>

#include <iostream>
#include <fstream>
#include <string>

#include "IGlue.h"

#ifdef TEXTVIEW
# include "VTextUpdater.h"

#else
# include "VQtLocalMappingUpdater.h"
# include "VQtUpdater.h"
# include "VQtInit.h"
#endif

using namespace interlude;
using namespace std;

#define kUPDPort		7000
#define kTimeInterval	10			// time task interval in milliseconds

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

#if defined(WIN32) && !defined(_DEBUG) && !defined(TEXTVIEW)
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

	int ret;
	int udpPort = intopt ("--port", kUPDPort, argc, argv);
	QApplication appl(argc, argv);

	IGlue glue (udpPort, kUPDPort+1, kUPDPort+2);
	if (glue.start (kTimeInterval)) {
#ifdef TEXTVIEW
		ofstream outfile  ("ITLTextView.txt");
		glue.setViewUpdater (VTextUpdater::create(outfile));
		ret = appl.exec();
#else

		appl.setApplicationName("InterludeSceneViewer");	
		QDir dir(QApplication::applicationDirPath());
#ifndef WIN32
		dir.cdUp();
#endif
		dir.cd("PlugIns");
		appl.addLibraryPath( dir.absolutePath());
		VQtInit::startQt();
		glue.setLocalMapUpdater		(VQtLocalMappingUpdater::create() );
		glue.setViewUpdater			(VQtUpdater::create() );
		ret = appl.exec();
		VQtInit::stopQt();
#endif
	}
	return ret;
}
