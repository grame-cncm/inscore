#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "SwipePanel.h"
#include "Header.h"
#include "SlideMenu.h"

namespace inscore {


class MainWindow : public QWidget
{
	Q_OBJECT

	Header* fHeader;
	SwipePanel* fPanel;
	SlideMenu* fMenu;

public:
	explicit MainWindow(QWidget *parent = 0);

	SwipePanel* swipePanel()	{return fPanel ;}
	SlideMenu*	menu()			{return fMenu  ;}
	Header*		header()		{return fHeader;}

signals:

public slots:

protected:
	void resizeEvent(QResizeEvent *);
	void closeEvent(QCloseEvent*);
};

}//end namespace

#endif // MAINWINDOW_H
