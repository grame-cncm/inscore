/*

  INScore Project
  Copyright (C) 2010  Grame

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

#ifdef ANDROID
#include <QMainWindow>
#endif

#include "VQtInit.h"
#include "GuidoFontLoader.h"
#include "QGuidoPainter.h"

namespace inscore
{

#ifdef ANDROID
QMainWindow* VQtInit::sMainWindow;
QTabWidget* VQtInit::sTabWidget;
#endif

void VQtInit::startQt ()
{
	installGuidoFont();
	QGuidoPainter::startGuidoEngine();
#ifdef ANDROID
	// Create main window. It contains tab for each scene.
	sMainWindow = new QMainWindow;
	sTabWidget = new QTabWidget(sMainWindow);
	sMainWindow->setCentralWidget(sTabWidget);
	sMainWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	// Man window is full screen.
	sMainWindow->showMaximized();
#endif
}

void VQtInit::stopQt ()
{
	QGuidoPainter::stopGuidoEngine();
#ifdef ANDROID
	delete sMainWindow;
#endif
}
#ifdef ANDROID
QTabWidget*	VQtInit::getTabWidget()
{
	return sTabWidget;
}
#endif
} // end namespoace
