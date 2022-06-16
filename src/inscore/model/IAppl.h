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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#ifndef __IAppl__
#define __IAppl__

#include <mutex>

#include "benchtools.h"
#include "Connect.h"
#include "Forwarder.h"
#include "IMessageHandlers.h"
#include "IObject.h"
#include "PeriodicTask.h"
#include "TILoader.h"
#include "TScripting.h"
#include "TWallClock.h"
#include "udpinfo.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class INScoreApplicationGlue;
class IAppl;
typedef class libmapping::SMARTP<IAppl>	SIAppl;
class IApplDebug;
typedef class libmapping::SMARTP<IApplDebug> 	SIApplDebug;
class IApplStat;
typedef class libmapping::SMARTP<IApplStat>		SIApplStat;
class IApplLog;
typedef class libmapping::SMARTP<IApplLog>		SIApplLog;
class IFilterForward;
typedef class libmapping::SMARTP<IFilterForward> SIFilterForward;

#if HASSSLSUPPORT
class IApplSsl;
typedef class libmapping::SMARTP<IApplSsl>		SIApplSsl;
#endif

//--------------------------------------------------------------------------
/*!
	\brief the application object of the model
*/
class IAppl : public IObject, public TILoader
{
	public:
	struct TAliasParam {
		std::string	fName;
		float		fMin;
		float 		fMax;
		TAliasParam (std::string name)							: fName(name), fMin(-1.f), fMax(1.f) {}
		TAliasParam (std::string name, float min, float max)	: fName(name), fMin(min), fMax(max) {}
		bool 		scaled() const		{ return (fMin!=-1.0) || (fMax!=1.0); }
		std::string toString() const;
		float 		scale(float val) const;
	};
	typedef std::pair<std::string, std::vector<TAliasParam> >	TAlias;
	typedef std::map<std::string, TAlias>						TAliasesMap;

	private:
	static TAliasesMap fAliases;
	static TAliasParam string2param (const std::string& str);

	static std::string	fDefaultFontName;
	static std::string	fRootPath;
	static bool			fRunning;
	static std::string	fVersion;					// the application version number
	static float		fVersionNum;				// the application version number as floating point value
	static float		fCompatibilityVersionNum;	// the supported version number as floating point value
	static udpinfo		fUDP;						// udp port settings
	static int			fRate;						// the time task rate
	static double		fRealRate;					// the time task real rate in mls (maintained for every tick)
	static std::string	fParseVersion;				// used to switch the parser to different versions of the language

		int			fStartTime;					// the application start time
		double		fCurrentTime;				// the application current time
		int			fCurrentTicks;				// the current count of clocks
		SIApplDebug	fApplDebug;					// debug flags
		SIApplStat	fApplStat;					// statistics
		SIApplLog	fApplLog;					// log window
#if HASSSLSUPPORT
		SIApplSsl	fSsl;						// ssl certificates
#endif
#if HASMIDISupport
		SIApplMIDI	fMidi;						// MIDI support
#endif
		SIFilterForward fFilterForward;			// A virtual node to manage filter for message forwarding
		Forwarder	fForwarder;					// A forwarder class to manage message forwarding
		Connect		fConnecter;					// A connect class to manage host connections
		bool		fOffscreen;
		INScoreApplicationGlue* fAppl;				// the Qt application
		std::mutex	fTimeMutex;
		TJSEngine*	fJavascript = 0;

	public:
		static unsigned long kUPDPort;	// Default listening port
		static bool fDefaultShow;
		static const std::string kApplType;
		static const std::string kName;
		static SIAppl			create(int udpport, int outport, int errport,  INScoreApplicationGlue* ag, bool offscreen=false)
			{
				IAppl::setUDPInPort(udpport);
				IAppl::setUDPOutPort(outport);
				IAppl::setUDPErrPort(errport);
				return new IAppl(ag, offscreen);
			}
		static std::string		getRootPath()				{ return fRootPath; }	//< returns the application root path
		static std::string		absolutePath( const std::string& path );			//< returns the absolute path corresponding to 'path',
		static const std::string&	parseVersion()			{ return fParseVersion; }

		static void				addAlias( const std::string& alias, const std::string& address, const std::string& msg);
		static void				addAlias( const std::string& alias, const std::string& address, const std::vector<std::string>& msg);
		static void				delAliases( const std::string& address);
		static void				getAliases( const std::string& address, std::vector<TAlias>& aliases);
		static void				setRootPath();
		static std::string		getHome();
		static int				getParseVersion	();

		static bool	running() 		{ return fRunning; }

		bool	oscDebug() const;
		void	clock();
		double	time() const				{ return fCurrentTime; }
		int		mstime() const				{ return int(fCurrentTime); }		// the current time in milliseconds
		int		ticks() const				{ return fCurrentTicks; }
		void	quit();
		static int			getUDPInPort() 		{ return fUDP.fInPort; }
		static int			getUDPOutPort() 	{ return fUDP.fOutPort; }
		static int			getUDPErrPort() 	{ return fUDP.fErrPort; }
		std::string	getIP() const;
		bool	defaultShow() const				{ return fDefaultShow; }
		static const std::string&	getUDPOutAddress()		{ return fUDP.fOutDstAddress; }
		static const std::string&	getUDPErrAddress()		{ return fUDP.fErrDstAddress; }
	
		void				logMsgs(const SIMessageList& msgs);
		IApplLog*			getLogWindow()				{ return fApplLog; }
#if HASSSLSUPPORT
		const IApplSsl*		getSsl() const				{ return fSsl; }
#endif
#if HASMIDISupport
		const IApplMIDI*	getMIDI() const 			{ return fMidi; }
#endif
		INScoreApplicationGlue* getApplicatonGlue() 	{ return fAppl; }
	
		/*!
		 * \brief getForwardList Get the list of host to which forward message.
		 * \return
		 */
		const std::vector<IMessage::TUrl> getForwardList() const { return fForwarder.getForwardList(); }
		const std::vector<IMessage::TUrl> getCnxList() const 	 { return fConnecter.getCnxList(); }
		SIMessageList getClients() const						 { return fForwarder.getClients(); }
		std::vector<std::string> getScenes() const;
		IScene* 			getScene( std::string name ) const;
		virtual void		forwardMsg (const IMessage* msg)	 { fForwarder.forward(msg); }
		virtual void		accept (Updater*);
		virtual void		print(std::ostream& out) const;
		virtual void		cleanup ();
		virtual void 		add (const nodePtr& node);

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
			\brief processing of an alias
		 
			Processing an alias consist in building a message with a resolved adress from the input message.
			The resolved address is contained in the alias. In addition, an arbitrary number of implicit message
			strings can be associated to the alias and may include scaling specification. A new message is build for
			each implicit message string and the input message parameters are passed in sequence to each message,
			with scaling when it applies.
			\param msg the input message
			\param alias an alias for the input message address
			\return true when the message has been successfully processed i.e. when the model is modified
		*/
		virtual int processAlias (const TAlias& alias, const IMessage* msg);

		/*!
			\brief processing of a message
			
			Process a single message.
			\param msg the message to be processed
			\return true when the message has been successfully processed
		*/
		virtual bool processMsg (const IMessage* msg);
	
		static int		getRate()					{ return fRate; }
		static double	getRealRate()				{ return fRealRate; }
		static void		setUDPInPort(int p)			{ fUDP.fInPort = p; }
		static void		setUDPOutPort(int p)		{ fUDP.fOutPort = p; }
		static void		setUDPErrPort(int p)		{ fUDP.fErrPort = p; }
		void		setUDPInPortHandler(int p)		{ IAppl::setUDPInPort(p); }
		void		setUDPOutPortHandler(int p)		{ IAppl::setUDPOutPort(p); }
		void		setUDPErrPortHandler(int p)		{ IAppl::setUDPErrPort(p); }
		void 		setErrOSCAddress (const std::string& address);
		void		setRate(int rate)				{ fRate = rate; }
		void		setRealRate(double rate)		{ fRealRate = rate; }
		void		setReceivedOSC(int n);

		void 		timeTask ();
		void 		startTime ();

		void		resetBench();
		bool		offscreen()	const				{ return fOffscreen; }
		void		ptask ();
		void		error () const;					//< trigger the error event, error must be checked before

		TJSEngine*	getJSEngine()					{ return fJavascript; }

		/// \brief gives the application node
		virtual SIAppl			getAppl()			{ return this; }
		virtual const IAppl*	getAppl() const		{ return this; }

		static std::string checkRootPath (const std::string& path);
		static std::string defaultFontName ()  			{ return fDefaultFontName; }
		static float version ()							{ return fVersionNum; }
		static float compatibilityVersion ()			{ return fCompatibilityVersionNum; }
				void setCompatibilityVersion (float v)	{ fCompatibilityVersionNum = v; }

	protected:
				 IAppl(INScoreApplicationGlue* ag, bool offscreen);
		virtual ~IAppl();
		
		void		setRootPath		(const std::string& s);
		void		setParseVersion	(const std::string& s);
		static void		setUDPOutAddress(const std::string& a)	{ fUDP.fOutDstAddress = a; }
		static void		setUDPErrAddress(const std::string& a)	{ fUDP.fErrDstAddress = a; }
		void		setDefaultShow(bool state)				{ fDefaultShow = state; }

		virtual		SIMessageList getAll () const;

		SIMessage	hello() const;
		void		helloMsg();
		int			scenesCount() const;
//		void		activate() const;
		std::string	guidoversion() const;
		std::string	musicxmlversion() const;

		/// \brief override IObject method
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;

		/// \brief application \c 'require' message handler. Provided to check for version number.
		virtual MsgHandler::msgStatus requireMsg(const IMessage* msg);

		/// \brief application \c 'preprocess' message handler.
		virtual MsgHandler::msgStatus preProcessMsg (const IMessage* msg);

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

		/// \brief application \c 'connect' message handler.
		virtual MsgHandler::msgStatus connect (const IMessage* msg);

		/// \brief application \c 'time' message handler.
		virtual MsgHandler::msgStatus setTime (const IMessage* msg);

		/// \brief application \c 'ticks' message handler.
		virtual MsgHandler::msgStatus setTicks (const IMessage* msg);

		/// \brief application \c 'scenes' message handler.
		virtual MsgHandler::msgStatus scenesMsg (const IMessage* msg);

//		/// \brief application \c 'clear' message handler.
//		virtual MsgHandler::msgStatus urlCache (const IMessage* msg);

#if defined(RUNBENCH) || defined(TIMEBENCH)
		void	startBench()			{ bench::start(); }
		void	stopBench()				{ bench::stop(); }
		MsgHandler::msgStatus	writeBench(const IMessage* msg);
#endif
};

/*! @} */

} // end namespoace

#endif
