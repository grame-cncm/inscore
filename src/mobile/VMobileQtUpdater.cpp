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

#include "VMobileQtUpdater.h"
#include "IApplVNodes.h"
#include "VLogWindow.h"
#include "VMobileQtInit.h"
#include "IMobileMenu.h"
#include "IScene.h"

#include <QWidget>

namespace inscore {

//--------------------------------------------------------------------------
void VMobileQtUpdater::updateTo(IScene * scene)
{
	// Force scene to fullscreen to use all space of tab widget
	scene->setFullScreen(true);
	((VSceneView*)scene->getView())->updateView(scene);
}

//--------------------------------------------------------------------------
void VMobileQtUpdater::updateTo(IApplLog * log)
{
    QWidget * w = log->window();
    // Add and remove log window in a tab
	QTabWidget * tw = VMobileQtInit::getTabWidget();
    int index = tw->indexOf(w);
    if(log->getVisible()) {
        if(index == -1) {
            tw->addTab(w, w->windowTitle());
            tw->setCurrentWidget(w);
        }
    } else {
        if(index != -1) {
            tw->removeTab(index);
        }
    }
}

//--------------------------------------------------------------------------
void VMobileQtUpdater::updateTo(IMenu* menu)
{
    QWidget * w = menu->window();
    // Add and remove log window in a tab
	QTabWidget * tw = VMobileQtInit::getTabWidget();
    int index = tw->indexOf(w);
    if(menu->getVisible()) {
        if(index == -1) {
            tw->addTab(w, w->windowTitle());
            tw->setCurrentWidget(w);
        }
    } else {
        if(index != -1) {
            tw->removeTab(index);
        }
    }
}

} // end namespoace
