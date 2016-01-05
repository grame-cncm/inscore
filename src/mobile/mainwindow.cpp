#include "mainwindow.h"

#include <QFrame>
#include <QVBoxLayout>

namespace inscore{

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	fHeader = new Header(this);
	fPanel = new SwipePanel(this);

	QVBoxLayout* l= new QVBoxLayout(this);
		l->addWidget(fHeader);
		l->addWidget(fPanel);
		l->setMargin(0);
		setLayout(l);

	fMenu = new SlideMenu(this);

	connect(fPanel, SIGNAL(currentPanelChanged(QString,bool,bool)), fHeader, SLOT(headerNameChanged(QString,bool,bool)));
	connect(fPanel, SIGNAL(panelListChanged(QStringList,int)), fMenu, SLOT(panelListChanged(QStringList,int)));
	connect(fMenu, SIGNAL(switchToPanel(QString)), fPanel, SLOT(switchToPanel(QString)));
	connect(fHeader, SIGNAL(previousPanel()), fPanel, SLOT(previousPanel()));
	connect(fHeader, SIGNAL(nextPanel()), fPanel, SLOT(nextPanel()));
	connect(fHeader, SIGNAL(switchToPanel(QString)), fPanel, SLOT(switchToPanel(QString)));
	connect(fHeader, SIGNAL(popupMenu()), fMenu, SLOT(popupMenu()));

}

SwipePanel* MainWindow::swipePanel(){
    return fPanel;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
	int h = e->size().height();
	int w = e->size().width();
	qDebug()<<w<<", "<<h;
	fHeader->setFixedHeight(qMin(h,w) * 0.1);
	fMenu->setGeometry(0,0, w, h);
	QWidget::resizeEvent(e);
	e->accept();
}

}//end namespace
