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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __IAppl__
#define __IAppl__

#ifndef PARSERTEST
#include <QMutex>
#endif

#include "IMessageHandlers.h"
#include "PeriodicTask.h"
#include "IObject.h"
#include "TILoader.h"
#include "TScripting.h"
#include "udpinfo.h"
#include "benchtools.h"
#include "Forwarder.h"

class QApplication;
namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IAppl;
typedef class libmapping::SMARTP<IAppl>	SIAppl;

class IApplDebug;
typedef class libmapping::SMARTP<IApplDebug> SIApplDebug;
class IApplStat;
typedef class libmapping::SMARTP<IApplStat>		SIApplStat;
class IApplLog;
typedef class libmapping::SMARTP<IApplLog>		SIApplLog;
class IFilterForward;
typedef class libmapping::SMARTP<IFilterForward> SIFilterForward;

//--------------------------------------------------------------------------
/*!
	\brief the application object of the model
*/
class IAppl : public IObject, public TILoader
{
	typedef std::map<std::string, std::pair<std::string, std::string> >		TAliasesMap;
	static TAliasesMap fAliases;

	static std::string	fDefaultFontName;
	static std::string	fRootPath;
	static bool			fRunning;
	static std::string	fVersion;					// the application version number
	static float		fVersionNum;				// the application version number as floating point value
	static float		fCompatibilityVersionNum;	// the supported version number as floating point value
	static udpinfo		fUDP;						// udp port settings
	static int			fRate;						// the time task rate
	static float		fRealRate;				// the time task real rate in mls (maintained for every tick)

		int			fStartTime;					// the application start time
		int			fCurrentTime;				// the application current time
		int			fCurrentTicks;				// the current count of clocks
		SIApplDebug	fApplDebug;					// debug flags
		SIApplStat	fApplStat;					// statistics
		SIApplLog	fApplLog;					// log window
		SIFilterForward fFilterForward;			// A virtual node to manage filter for message forwarding
		Forwarder	fForwarder;					// A forwarder class to manage message forwarding
		bool		fOffscreen;
		QApplication*	fAppl;					// the Qt application
#ifndef PARSERTEST
		QMutex		fTimeMutex;
#endif
		TJSEngine		fJavascript;

	public:
		static unsigned long kUPDPort;	// Default listening port
		static bool fDefaultShow;
		static const std::string kApplType;
		static const std::string kName;
		static SIAppl			create(int udpport, int outport, int errport,  QApplication* appl, bool offscreen=false)		
			{
				IAppl::setUDPInPort(udpport);
				IAppl::setUDPOutPort(outport);
				IAppl::setUDPErrPort(errport);
				return new IAppl(appl, offscreen);
			}
		static std::string		getRootPath()				{ return fRootPath; }	//< returns the application root path
		static std::string		absolutePath( const std::string& path );			//< returns the absolute path corresponding to 'path',

		static void				addAlias( const std::string& alias, const std::string& address, const std::string& msg);
		static void				delAliases( const std::string& address);
		static void				getAliases( const std::string& address, std::vector<std::pair<std::string, std::string> >& aliases);

		static bool	running() 		{ return fRunning; }

		bool	oscDebug() const;
		void	clock();
		int		time() const				{ return fCurrentTime; }
		int		ticks() const				{ return fCurrentTicks; }
		void	quit();
		static int			getUDPInPort() 		{ return fUDP.fInPort; }
		static int			getUDPOutPort() 	{ return fUDP.fOutPort; }
		static int			getUDPErrPort() 	{ return fUDP.fErrPort; }
		static std::string	getIP();
		bool	defaultShow() const			{ return fDefaultShow; }
		static const std::string&	getUDPOutAddress()		{ return fUDP.fOutDstAddress; }
		static const std::string&	getUDPErrAddress()		{ return fUDP.fErrDstAddress; }
		IApplLog*			getLogWindow()	{ return fApplLog; }
		
		/*!
		 * \brief getForwardList Get the list of host to which forward message.
		 * \return
		 */
		const std::vector<IMessage::TUrl> getForwardList() const { return fForwarder.getForwardList(); }
		virtual void		accept (Updater*);
		virtual void		print(std::ostream& out) const;

		virtual void		cleanup ();

		/*!
			\brief creates the object virtual nodes
		*/
		virtual void	createVirtualNodes ();

		/*!
			\brief application processing of a message
			
			Processing a message at application level differs from general scheme since the IAppl object
			call its self \c execute method while this method is called by the parent object when not at the root
			of the model tree.
			\param address the current osc address location
			\param addressTail the remainging part of the osc address
			\param msg the message to be processed
			\return true when the message has been successfully processed i.e. when the model is modified
		*/
		virtual int processMsg (const std::string& address, const std::string& addressTail, const IMessage* msg);

		/*!
			\brief processing of a message
			
			Process a single message.
			\param msg the message to be processed
			\return true when the message has been successfully processed
		*/
		virtual bool processMsg (const IMessage* msg);
	
		static int		getRate()					{ return fRate; }
		static float	getRealRate()				{ return fRealRate; }
		static void		setUDPInPort(int p)			{ fUDP.fInPort = p; }
		static void		setUDPOutPort(int p)		{ fUDP.fOutPort = p; }
		static void		setUDPErrPort(int p)		{ fUDP.fErrPort = p; }
		void		setUDPInPortHandler(int p)		{ IAppl::setUDPInPort(p); }
		void		setUDPOutPortHandler(int p)		{ IAppl::setUDPOutPort(p); }
		void		setUDPErrPortHandler(int p)		{ IAppl::setUDPErrPort(p); }
		void		setRate(int rate)				{ fRate = rate; }
		void		setRealRate(unsigned long rate)	{ fRealRate = rate / 1000.f; }
		void		setReceivedOSC(int n);

		void		resetBench();
		bool		offscreen()	const				{ return fOffscreen; }
		void		ptask ();
		void		error () const;					//< trigger the error event, error must be checked before

		TJSEngine*	getJSEngine()					{ return &fJavascript; }

		/// \brief gives the application node
		virtual SIAppl			getAppl()			{ return this; }
		virtual const IAppl*	getAppl() const		{ return this; }

		static std::string checkRootPath (const std::string& path);
		static std::string defaultFontName ();
		static float version ()							{ return fVersionNum; }
		static float compatibilityVersion ()			{ return fCompatibilityVersionNum; }
				void setCompatibilityVersion (float v)	{ fCompatibilityVersionNum = v; }

	protected:
				 IAppl(QApplication* appl, bool offscreen);
		virtual ~IAppl();
		
		void		setRootPath(const std::string& s);
		static void		setUDPOutAddress(const std::string& a)	{ fUDP.fOutDstAddress = a; }
		static void		setUDPErrAddress(const std::string& a)	{ fUDP.fErrDstAddress = a; }
		void		setDefaultShow(bool state)				{ fDefaultShow = state; }

		virtual		SIMessageList getAll () const;

		SIMessage	hello() const;
		void		helloMsg() const;
//		void		activate() const;
		std::string	guidoversion() const;
		std::string	musicxmlversion() const;

		/// \brief override IObject method
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;

		/// \brief application \c 'require' message handler. Provided to check for version number.
		virtual MsgHandler::msgStatus requireMsg(const IMessage* msg);

		/// \brief application \c 'load' message handler.
		virtual MsgHandler::msgStatus loadMsg (const IMessage* msg);

		/// \brief application \c 'browse' message handler.
		virtual MsgHandler::msgStatus browseMsg (const IMessage* msg);
	
		/// \brief load a buffer containing an inscore script
		virtual MsgHandler::msgStatus loadBuffer (const IMessage* msg);

		/// \brief application \c 'mouse' message handler.
		virtual MsgHandler::msgStatus cursor (const IMessage* msg);

		/// \brief application \c 'forward' message handler.
		virtual MsgHandler::msgStatus forward (const IMessage* msg);

		/// \brief application \c 'time' message handler.
		virtual MsgHandler::msgStatus setTime (const IMessage* msg);

		/// \brief application \c 'ticks' message handler.
		virtual MsgHandler::msgStatus setTicks (const IMessage* msg);

		/// \brief application \c 'clear' message handler.
		virtual MsgHandler::msgStatus urlCache (const IMessage* msg);

#if defined(RUNBENCH) || defined(TIMEBENCH)
		void	startBench()			{ bench::start(); }
		void	stopBench()				{ bench::stop(); }
		MsgHandler::msgStatus	writeBench(const IMessage* msg);
#endif
};

/*! @} */

} // end namespoace

#endif
