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

#include <QMainWindow>

#ifdef ANDROID
#include <QtAndroidExtras>
#endif

namespace inscore
{

QMainWindow* VMobileQtInit::sMainWindow;
QTabWidget* VMobileQtInit::sTabWidget;

//--------------------------------------------------------------------------
void VMobileQtInit::startQt ()
{
    VQtInit::startQt();
    // Create main window. It contains tab for each scene.
    sMainWindow = new QMainWindow;
    sTabWidget = new QTabWidget(sMainWindow);
    sMainWindow->setCentralWidget(sTabWidget);
    sMainWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    // Man window is full screen.
    sMainWindow->showMaximized();
// makes INScore crash on android 5
//    VMobileQtInit::keepScreenOn();
}

//--------------------------------------------------------------------------
void VMobileQtInit::stopQt ()
{
    VQtInit::stopQt();
    delete sMainWindow;
}

//--------------------------------------------------------------------------
QTabWidget* VMobileQtInit::getTabWidget()
{
    return sTabWidget;
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


