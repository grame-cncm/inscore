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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#include <QSettings>
#include <QtQuick>

#include "IAppl.h"
#include "INScore.h"
#include "IMessage.h"
#include "Methods.h"
#include "VMobileMenu.h"

namespace inscore
{
//--------------------------------------------------------------------------
VMobileMenu::VMobileMenu(const char * name, const char* qtversion, const char* ipnum, QWidget* parent) : QQuickWidget(parent)
{
	setResizeMode(QQuickWidget::SizeViewToRootObject);
	setSource(QUrl("qrc:///qml/about.qml"));


	setWindowTitle( tr(name) );
	QQuickItem *root = rootObject();
	root->setProperty("version", QVariant(INScore::versionStr()));
	root->setProperty("qtversion", QVariant(qtversion));
	root->setProperty("guidoversion", QVariant(INScore::guidoversion()));
	root->setProperty("ip", QString(ipnum));

	QSettings settings("Grame", "INScore");
	settings.beginGroup("Mobile");

	if(settings.value("loadWelcome", QVariant::fromValue(true)).toBool()){
		INScore::postMessage("/ITL", "load", "qrc:/scripts/Welcome.inscore");
		settings.setValue("loadWelcome", QVariant::fromValue(false));
	}

}

} // end namespoace
