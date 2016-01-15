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

#include "Header.h"
#include <QtQuick>
#include <QtQml>
#include <QtCore>

namespace inscore {


Header::Header(QWidget *parent) : QQuickWidget(parent)
{
	setResizeMode(QQuickWidget::SizeViewToRootObject);
	setSource(QUrl("qrc:///qml/header.qml"));
	connect(rootObject(), SIGNAL(popupMenu()), this, SIGNAL(popupMenu()));
}

void Header::headerNameChanged(QString newTitle, bool isFirst, bool isLast)
{
	rootObject()->setProperty("title", newTitle);
}

void Header::panelNameListChanged(QStringList nameList)
{
	rootObject()->setProperty("titles", QVariant::fromValue(nameList));
}

//void Header::showEvent(QShowEvent *e)
//{
//	QQuickWidget::showEvent(e);
//
//	///Workaround a QQmlWidget bug where the qml item is resize with a wrong height
//	///when showing the header without triggering a resizeEvent() (for exemple when exiting fullscreen mode)
//	///This subclass of showEvent can be removed if the qt bug is fixed...
//	if(isVisible()){
//		QTimer::singleShot(10, [this](){
//			int h = height();
//			setFixedHeight(h+1);
//			setFixedHeight(h);
//		});
//	}
//}

}//end namespace

