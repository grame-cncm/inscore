/*

  INScore Project

  Copyright (C) 2015  Grame

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

  Grame Research Laboratory, 11 cours Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/
#include "VMobileQtInit.h"

#include "mainwindow.h"

#ifdef ANDROID
#include <QtAndroidExtras>
#include <QNetworkInterface>
#endif

namespace inscore
{

MainWindow* VMobileQtInit::gMainWindow;

//--------------------------------------------------------------------------
void VMobileQtInit::startQt ()
{
    VQtInit::startQt();
    // Create main window. It contains tab for each scene.
	gMainWindow = new MainWindow();
    // Man window is full screen.
#ifdef MOBILE_TEST
	gMainWindow->show();
#else
	gMainWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	gMainWindow->showMaximized();
#endif
// makes INScore crash on android 5
//    VMobileQtInit::keepScreenOn();
}

//--------------------------------------------------------------------------
void VMobileQtInit::stopQt ()
{
    VQtInit::stopQt();
	delete gMainWindow;
}

//--------------------------------------------------------------------------
SwipePanel *VMobileQtInit::getMainPanel()
{
	return gMainWindow->swipePanel();
}


//--------------------------------------------------------------------------
unsigned long VMobileQtInit::getIP()
{
	QNetworkInterface ni;
	QList<QHostAddress>	hl = ni.allAddresses();
	for (int i=0; i < hl.size(); i++) {
		unsigned long ip = hl[i].toIPv4Address();
		if (ip) {
			unsigned long classe = ip >> 24;
			if ((classe >= 192) && (classe <= 223))		// look for a classe C network
				return ip;
		}
	}
	return 0x7F000001;
}

//--------------------------------------------------------------------------
QString VMobileQtInit::getIPString()
{
	QNetworkInterface ni;
	QList<QHostAddress>	hl = ni.allAddresses();
	for (int i=0; i < hl.size(); i++) {
		unsigned long ip = hl[i].toIPv4Address();
		if (ip) {
			unsigned long classe = ip >> 24;
			if ((classe >= 192) && (classe <= 223))		// look for a classe C network
				return hl[i].toString();
		}
	}
	return "";
}


//--------------------------------------------------------------------------
void VMobileQtInit::keepScreenOn()
{
#ifdef ANDROID
//    QAndroidJniObject activity = QtAndroid::androidActivity();
//    if (activity.isValid()) {
//        QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");

//        if (window.isValid()) {
//            const int FLAG_KEEP_SCREEN_ON = 128;
//            window.callObjectMethod("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
//        }
//    }
#else
#endif
}

} // end namespoace


