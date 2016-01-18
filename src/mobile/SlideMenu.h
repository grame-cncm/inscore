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

#ifndef SLIDEMENU_H
#define SLIDEMENU_H

#include <QtQuickWidgets>
#include <QtWidgets>

#define WIDTH 0.7
namespace inscore {

//--------------------------------------------------------------------------
// an object wrapper around inscore postMessage interface
class MsgSender : public QObject {
	Q_OBJECT
	public:
				 MsgSender() {}
		virtual ~MsgSender() {}

		Q_INVOKABLE void postMessage	(const QString& address, const QString& msg);
		Q_INVOKABLE void postMessage	(const QString& address, const QString& msg, int val);
		Q_INVOKABLE void postMessage	(const QString& address, const QString& msg, bool val);
		Q_INVOKABLE void postMessage	(const QString& address, const QString& msg, float val);
		Q_INVOKABLE void postMessage	(const QString& address, const QString& msg, const QString& val);
};

//--------------------------------------------------------------------------
class SlideMenu : public QFrame
{
	Q_OBJECT

	Q_PROPERTY(float opacity READ opacity WRITE setOpacity)
	Q_PROPERTY(QVariant sceneList READ sceneList NOTIFY sceneListChanged)
	Q_PROPERTY(QVariant panelList READ panelList NOTIFY panelListChanged)

	QParallelAnimationGroup fAnimIn, fAnimOut;
	QPropertyAnimation* fPosOut;
	float fOpacity;

	QQuickWidget* fMenu;
	QStringList fSceneList, fPanelList;
	MsgSender	fSender;

public:
	explicit SlideMenu(QWidget *parent = 0);

	QStringList sceneList() const;
	QStringList panelList() const;

signals:
	void sceneListChanged();
	void panelListChanged();
	void switchToPanel(QString panelName);

public slots:
	void popupMenu();
	void hideMenu();

	float opacity(){return fOpacity;}
	void setOpacity(float alpha);

	void panelListChanged(QStringList panelList, int sceneCount);

protected:
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *);

	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *){}
	void mouseMoveEvent(QMouseEvent *){}

	void resizeEvent(QResizeEvent *);
};

}//end namespace
#endif // SLIDEMENU_H
