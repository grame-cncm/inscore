#ifndef __MainWindow__
#define __MainWindow__

#include <QMainWindow>

#include <QList>
#include <QVariant>
#include <QThread>

#include "ui_controllerWidget.h"

class ControllerWidget;

//------------------------------------------------------------------------
class OSCMessage
{
	QList<QVariant>	mValues;
	std::string		mAddress, mCommand;

	public:
	
		OSCMessage(const std::string& address) : mAddress(address) , mCommand("") {}
		
		OSCMessage setCommand( const std::string& command )	{ mCommand = command; return *this; }
		OSCMessage addFloat(double f)							{ mValues << f; return *this; }
		OSCMessage addString(const std::string& str)			{ mValues << QString(str.c_str()); return *this; }
		OSCMessage addInt(int i)								{ mValues << i; return *this; }
		
		void send( const std::string& str , int port ) const;
};

//------------------------------------------------------------------------
class ControllerWidget : public QWidget, private Ui::ControllerWidget
{
     Q_OBJECT

	QTimer*		mRotateAllTimer;
	unsigned long fMessageNumber;

	public:
		ControllerWidget(QWidget *parent = 0);
		void send( const OSCMessage& msg ) const;

	protected slots:
		
		void ITLQuit();
		void ITLReset();
		void scene1();
		void rotateAll();
	
		void rotateAllToggled(bool toggled);
};

//------------------------------------------------------------------------
class MainWindow: public QMainWindow
{
	public:
		MainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
		~MainWindow();

};

#endif
