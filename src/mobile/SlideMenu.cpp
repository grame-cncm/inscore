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

#include "SlideMenu.h"

#include <QStandardPaths>

#include "INScore.h"
#include "IAppl.h"

namespace inscore {

//--------------------------------------------------------------------------
// Q_INVOKABLE methods
//--------------------------------------------------------------------------
void MsgSender::postMessage	 (const QString& address, const QString& msg)
	{ INScore::postMessage(address.toStdString().c_str(), msg.toStdString().c_str()); }

void MsgSender::postMessage (const QString& address, const QString& msg, int val)
	{ INScore::postMessage(address.toStdString().c_str(), msg.toStdString().c_str(), val); }

void MsgSender::postMessage (const QString& address, const QString& msg, bool val)
	{ INScore::postMessage(address.toStdString().c_str(), msg.toStdString().c_str(), int(val)); }

void MsgSender::postMessage (const QString& address, const QString& msg, float val)
	{ INScore::postMessage(address.toStdString().c_str(), msg.toStdString().c_str(), val); }

void MsgSender::postMessage (const QString& address, const QString& msg, const QString& val)
{ INScore::postMessage(address.toStdString().c_str(), msg.toStdString().c_str(), val.toStdString().c_str()); }

QString MsgSender::rootPath()
{
	return QString::fromStdString(IAppl::getRootPath());
}


//--------------------------------------------------------------------------
SlideMenu::SlideMenu(QWidget *parent) : QFrame(parent)
{
	fMenu = new QQuickWidget(this);
	fMenu->rootContext()->setContextProperty("contextObject", this);
	fMenu->rootContext()->setContextProperty("inscore", &fSender);
	fMenu->rootContext()->setContextProperty("downloadPath", QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).last()+"/bundles");
	fMenu->setSource(QUrl("qrc:///qml/slideMenu.qml"));
	fMenu->rootObject()->setProperty("version", QVariant::fromValue( QString::fromStdString(INScore::versionStr()) ));

	fMenu->setResizeMode(QQuickWidget::SizeRootObjectToView);
	connect(fMenu->rootObject(), SIGNAL(switchToPanel(QString)), this, SIGNAL(switchToPanel(QString)));
	connect(fMenu->rootObject(), SIGNAL(switchToPanel(QString)), this, SLOT(hideMenu()));

	fOpacity = 1;
	setOpacity(0);

	QPropertyAnimation *opacityIn  = new QPropertyAnimation(this, "opacity", this);
	QPropertyAnimation *opacityOut = new QPropertyAnimation(this, "opacity", this);
	opacityIn ->setEndValue(0.4);
	opacityOut->setEndValue(0);
	opacityIn ->setDuration(250);
	opacityOut->setDuration(250);

	QPropertyAnimation *posIn  = new QPropertyAnimation(fMenu, "pos", this);
	fPosOut = new QPropertyAnimation(fMenu, "pos", this);
	posIn ->setEndValue(QPoint(0,0));
	fPosOut->setEndValue(QPoint(-fMenu->width(),0));
	posIn ->setDuration(500);
	fPosOut->setDuration(500);
	posIn ->setEasingCurve(QEasingCurve::OutQuad);
	fPosOut->setEasingCurve(QEasingCurve::InQuad);

	fAnimIn.addAnimation(opacityIn);
	fAnimIn.addAnimation(posIn);
	fAnimOut.addAnimation(opacityOut);
	fAnimOut.addAnimation(fPosOut);

	connect(&fAnimOut, &QAbstractAnimation::finished, [this]{hide(); fMenu->rootObject()->setProperty("state","mainMenu");});
	setAutoFillBackground(true);
	hide();
}

//_________________________________________________
QStringList SlideMenu::sceneList() const
{
	return fSceneList;
}

QStringList SlideMenu::panelList() const
{
	return fPanelList;
}

//_________________________________________________
void SlideMenu::resizeEvent(QResizeEvent *)
{
	int menuWidth = width()*WIDTH;

	fMenu->resize(menuWidth, height());

	if(!isVisible())
		fMenu->move(-menuWidth, 0);

	fPosOut->setEndValue(QPoint(-menuWidth,0));
}

//_________________________________________________
void SlideMenu::popupMenu()
{
	show();
	fMenu->rootObject()->setProperty("state","mainMenu");
	fAnimIn.start();
}

void SlideMenu::hideMenu()
{
	fAnimOut.start();
}

void SlideMenu::setOpacity(float alpha)
{
	if(qAbs(alpha-fOpacity) < 0.05)
		return;

	if(alpha<0 && alpha>1)
		return;

	fOpacity = alpha;

	setPalette(QColor(0,0,0,255*fOpacity));
}

void SlideMenu::panelListChanged(QStringList panelList, int sceneCount)
{
	fSceneList = panelList.mid(0, sceneCount);
	fPanelList = panelList.mid(sceneCount);
	emit sceneListChanged();
	emit panelListChanged();
}

//_________________________________________________
void SlideMenu::deleteDownloadedFile(QString fileName)
{
	QString path = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).last();
	QDir d(path+"/bundles");
	d.remove(fileName);
}


//_________________________________________________
void SlideMenu::keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Back) {
		hideMenu();
		e->accept();
		return;
	}

	QWidget::keyPressEvent(e);
}

void SlideMenu::keyReleaseEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Back){
		e->accept();
		return;
	}

	QWidget::keyReleaseEvent(e);
}

void SlideMenu::mousePressEvent(QMouseEvent *e)
{
	if(e->pos().x() > width()*WIDTH){
		e->accept();
		hideMenu();
	}
}

}//end namespace

