/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __IGlue__
#define __IGlue__

#include <QThread>
#include <QObject>

#include "IOSCListener.h"
#include "IController.h"
#include "PeriodicTask.h"
#include "udpinfo.h"
#include "Updater.h"
#include "smartpointer.h"

namespace interlude
{

class IMessage;
class IObject;
class IMessageStack;
typedef class SMARTP<IObject>		SIObject;
typedef class SMARTP<IMessageStack>	SIMessageStack;

//_______________________________________________________________________
/*!
	\brief a specific thread to listen incoming osc packets
*/
class OscThread : public QThread
{
	public:
		SIOSCListener fListener;	
	
				 OscThread(SIMessageStack& msgs, int udpport)  
							 { fListener = IOSCListener::create (msgs, udpport); }
		virtual ~OscThread() { fListener->stop(); quit(), wait(50); }
		/// \brief starts the osc listener
		void run()			 { fListener->run(); }
};

class OSCStream;
class IAppl;
typedef class SMARTP<IAppl>	SIAppl;
//--------------------------------------------------------------------------
/*!	\brief a glue between osc, a basic model and a controller

	IGlue inherits from QObject for timer capabilities.
*/
class export IGlue : public MsgListener, public QObject 
{

	OscThread *		fOscThread;
	SUpdater 		fViewUpdater;
	SUpdater 		fLocalMapUpdater;
	SUpdater 		fSlaveMapUpdater;
	SIController	fController;
	SIAppl			fModel;
	SIMessageStack	fMsgStack;
	SPeriodicTask	fTimeTask;

	int	fTimerID;
	udpinfo fUDP;
	
	public :
				 IGlue(int udpport, int outport, int errport);
		virtual ~IGlue();
			
				bool start(int timerInterval);
				void setViewUpdater(SUpdater updater);
				void setLocalMapUpdater(SUpdater updater);
				void setSlaveMapUpdater(SUpdater updater);
				void msgReceived (const IMessage* msg, int status);

				void setOSCOut (const std::string& a);
				void setOSCErr (const std::string& a);

		static void trace (const IMessage* msg, int status);

	protected:
		virtual void initialize ();
		virtual	void clean ();
		virtual void timerEvent ( QTimerEvent * event );
		void modelUpdate();
		void localMapUpdate();
		void slaveMapUpdate();
		void viewUpdate();

		void oscinit (SIAppl appl, udpinfo& udp);								// osc streams initialization
		void oscinit (int port);												// input stream initialization
		void oscinit (OSCStream& osc, const std::string& address, int port);	// outut osc stream initialization
		void checkUDPChange ();
		void setOSCOut (int port);
		void setOSCErr (int port);
};

} // end namespoace

#endif
