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

#include <QFrame>
#include <QVBoxLayout>

#include "mainwindow.h"

namespace inscore{

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	fHeader = new Header(this);
	fHeader->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
	fPanel = new SwipePanel(this);

	QVBoxLayout* l= new QVBoxLayout(this);
	l->setSizeConstraint(QLayout::SetFixedSize);
	l->addWidget(fHeader);
	l->addWidget(fPanel);
	l->setMargin(0);
	setLayout(l);

	fMenu = new SlideMenu(this);

	connect(fPanel, SIGNAL(currentPanelChanged(QString,bool,bool)), fHeader, SLOT(headerNameChanged(QString,bool,bool)));
	connect(fPanel, SIGNAL(panelListChanged(QStringList,int)), fMenu, SLOT(panelListChanged(QStringList,int)));
	connect(fMenu, SIGNAL(switchToPanel(QString)), fPanel, SLOT(switchToPanel(QString)));
	connect(fHeader, SIGNAL(popupMenu()), fMenu, SLOT(popupMenu()));
}

SwipePanel* MainWindow::swipePanel(){
    return fPanel;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
	int h = height();
	int w = width();
	fMenu->setGeometry(0,0, w, h);
	QWidget::resizeEvent(e);
}

}//end namespace
