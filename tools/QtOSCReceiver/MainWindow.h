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
		void setError(unsigned long number);
		void setLastMessage(unsigned long number);

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
