#ifndef __MainWindow__
#define __MainWindow__

#include <QMainWindow>

#include <QList>
#include <QVariant>
#include <QThread>

#include "ui_controllerWidget.h"

class ControllerWidget;
class SendThread;

//------------------------------------------------------------------------
class ControllerWidget : public QWidget, private Ui::ControllerWidget
{
     Q_OBJECT

	SendThread * mSender;
	unsigned long fMessageNumber;

	public:
				 ControllerWidget(QWidget *parent = 0);
		virtual ~ControllerWidget();

		int nextMessage();
		int getMessageSize();
		int getWait();
		int port () const;
		QString destination () const;

	protected slots:
		
		void start();
		void stop();
		void initNumber();
};

//------------------------------------------------------------------------
class SendThread : public QThread
{
		bool fRun;
		ControllerWidget * fController;
	public:

		SendThread(ControllerWidget * controller) : fController(controller) {}
		virtual ~SendThread() { stop(); }

		void stop() { fRun = false; wait(50); }

		/// \brief starts the osc listener
		void run();
};

//------------------------------------------------------------------------
class MainWindow: public QMainWindow
{
	public:
		MainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
		~MainWindow();

};

#endif
