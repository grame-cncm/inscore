#ifndef __MainWindow__
#define __MainWindow__

#include "ui_controllerWidget.h"
#include <QMainWindow>

class OscThread;

//------------------------------------------------------------------------
class ControllerWidget : public QWidget, private Ui::ControllerWidget
{
     Q_OBJECT

	OscThread * fOscThread;

	public:
		ControllerWidget(QWidget *parent = 0);
		int getPort();
		void report(int rcv, int errs, float ratio, int msgspersec);
		
	protected slots:
		void restart();
	protected:

};

//------------------------------------------------------------------------
class MainWindow: public QMainWindow
{
	public:
		MainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
		~MainWindow();

};

#endif
