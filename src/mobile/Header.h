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

#ifndef HEADER_H
#define HEADER_H

#include <QQuickWidget>

namespace inscore{

class Header : public QQuickWidget
{
	Q_OBJECT
public:
	explicit Header(QWidget *parent = 0);

signals:
	void nextPanel();
	void previousPanel();
	void switchToPanel(QString name);
	void popupMenu();

public slots:
	void headerNameChanged(QString newTitle, bool isFirst, bool isLast);
	void panelNameListChanged(QStringList nameList);

protected:

	///Workaround a QQmlWidget bug where the qml item is resize with a wrong height
	///when showing the header without triggering a resizeEvent() (for exemple when exiting fullscreen mode)
	///This subclass of showEvent can be removed if the qt bug is fixed...
//	void showEvent(QShowEvent *e);
};

}//end namespace

#endif // HEADER_H
