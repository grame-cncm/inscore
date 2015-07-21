#ifndef OSCLISTENER_H
#define OSCLISTENER_H

#include "ui_controllerWidget.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"

#include <QTimer>
#include <QThread>
#include <QObject>

class ControllerWidget;

class OSCListener : public QObject, public osc::OscPacketListener
{
		Q_OBJECT

	UdpListeningReceiveSocket fSocket;	///< the udp socket listener
	unsigned long	fMyAddress;
	bool	fRunning;
	unsigned long fCurrentMessageNumber;
	unsigned long fPreviousMessageNumber;
	unsigned long fErrorCounter;
	ControllerWidget * fController;

	QTimer refresh;

	public:
		OSCListener(int port, ControllerWidget * controller);
		virtual ~OSCListener();
		/*!
			\brief process OSC messages

			\param m the OSC message (pre-processed by the base class)
			\param remoteEndpoint the sender IP address
		*/
		virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName&);
		virtual void run();
		virtual void stop();

	public slots:
		void refreshController();
};

//------------------------------------------------------------------------
class OscThread : public QThread
{
	public:
		OSCListener fListener;

		OscThread(int port, ControllerWidget * controller) : fListener(port, controller) {}
		virtual ~OscThread() { stop(); }

		void stop() { fListener.stop(); quit() , wait(50);}

		/// \brief starts the osc listener
		void run()			 { fListener.run(); }
};


#endif // OSCLISTENER_H
