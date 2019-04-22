#ifndef __MainWindow__
#define __MainWindow__

#include <string>
#include <map>
#include <QMainWindow>

#include "ui_controllerWidget.h"

class OscThread;
//------------------------------------------------------------------------
class ControllerWidget : public QWidget, private Ui::ControllerWidget
{
     Q_OBJECT

	OscThread * fOscThread;

	const char*	fNotes[12];
	
	int fMin;
	int fMax;
	int fTempo;
	int fRange;
	int fTimeout;
	bool fRunning = false;
	
	double fLastTime = 0;
	float  fLastAccepted = 0;
	int	   fLastPitch = 0;

	public:
				 ControllerWidget(QWidget *parent = 0);
		virtual ~ControllerWidget () { save(); }

		int 	getPort() const;
		QString getScore() const;
		QString getAddress() const;
		const std::string getAddressPtr() const;
		int 	getMin() const;
		int		getMax() const;
		bool 	getAutoMin() const;
		bool	getAutoMax() const;
		int 	getTempo() const;
		int 	getRange() const;
		int 	getTimeout() const;

		void 	receive (float value);
		void 	accept (float value, float duration);

	protected slots:
		void restart();
		void chgeTimeout()	{ fTimeout = getTimeout(); }
		void chgeMin()		{ fMin = getMin();}
		void chgeMax()		{ fMax = getMax();}
		void chgeTempo()	{ fTempo = getTempo(); }
		void chgeRange()	{ fRange = getRange(); }
		void chgeState();

	protected:
		void init ();
		void restore ();
		void save ();
		int  val2midipitch (float value);
		std::string pitch2note (int pitch);
		std::string dur2symdur (float duration);
		void setScore();
		void send(const char* to, const char *msg, const char* value);
		void send(const char* to, const char *msg, const char* type, const char* value);
};

//------------------------------------------------------------------------
class MainWindow: public QMainWindow
{
	public:
		 MainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
		~MainWindow();

};

#endif
