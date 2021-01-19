/*

  INScore project

  Copyright (C) 2009,2020  Grame

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

#ifdef WIN32
#include <windows.h>
#define usleep(n)	Sleep(n)
#else
#include <unistd.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <string>

#include <QApplication>
#include <QTimer>

#include "IAppl.h"
#include "INScore.h"
#include "INScoreAppl.h"

using namespace inscore;
using namespace std;

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
		INScore::MessagePtr msg = INScore::newMessage (krootPath_GetSetMethod);
		INScore::add (msg, path.c_str());
		INScore::postMessage ("/ITL", msg);
	}
	INScore::MessagePtr msg = INScore::newMessage (kload_SetMethod);
	INScore::add (msg, file.c_str());
	INScore::postMessage ("/ITL", msg);
}

//_______________________________________________________________________
void INScoreAppl::timerEvent(QTimerEvent *)
{
cerr << "INScoreAppl::timerEvent" << endl; 
	fGlue->timeTask ();
	if (fGlue->getRate() != fRate) {
		fRate = fGlue->getRate();
		killTimer(fTimerId);
		fTimerId = startTimer(fRate);
	}
}

//_______________________________________________________________________
void INScoreAppl::start (int udpinport, int udpoutport)
{
	setApplicationName("INScoreViewer");

	fGlue = INScore::start (udpinport, udpoutport, udpoutport+1, this);
	fRate = fGlue->getRate();
	fTimerId = startTimer (fRate, Qt::PreciseTimer);
}

//_______________________________________________________________________
void INScoreAppl::run()
{
	do {
		usleep (100);
		fGlue->timeTask();
	} while (IAppl::running());
}
