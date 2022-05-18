/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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

#pragma once

#include <string>
#include <ostream>

#include "Modules.h"

#if HASSSLSUPPORT
#include <QByteArray>
class QSslCertificate;
class QSslCertificate;
class QSslKey;
#endif

#include "IVNode.h"
#include "IObjectVNodes.h"


namespace inscore
{

class IMessage;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IApplDebug;
typedef class libmapping::SMARTP<IApplDebug>		SIApplDebug;

//--------------------------------------------------------------------------
/*!
	\brief an object debug virtual node
*/
class IApplDebug : public IObjectDebug
{
	protected:
		bool fOSCDebug;					///< flag to debug OSC messages
	
	public:	
		/// \brief creates a new IApplDebug
		static SIApplDebug create(IObject * parent)		{ return new IApplDebug(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& out) const;

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);

		virtual bool	getOSCDebug () const		{ return fOSCDebug; }

	protected:	
				 IApplDebug(IObject * parent);
		virtual ~IApplDebug() {}

		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual SIMessageList getSetMsg () const;
		void		setOSCDebug(bool state)			{ fOSCDebug = state; }
};
std::ostream&	operator << (std::ostream& out, const SIApplDebug& o);


class IApplStat;
typedef class libmapping::SMARTP<IApplStat>		SIApplStat;

//--------------------------------------------------------------------------
/*!
	\brief an object debug virtual node
*/
class IApplStat : public IVNode
{
	protected:
		int fMsgCount;					///< count of received OSC messages
	
	public:	
		/// \brief creates a new IApplStat
		static SIApplStat create(IObject * parent)		{ return new IApplStat(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& ) const	{}

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);
				void	count(int n)			{ fMsgCount += n; }

	protected:	
				 IApplStat(IObject * parent);
		virtual ~IApplStat() {}

		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual SIMessageList getSetMsg () const;
		void		reset();
};


class IApplLog;
class VLogWindow;
typedef class libmapping::SMARTP<IApplLog>		SIApplLog;

//--------------------------------------------------------------------------
/*!
	\brief an object debug virtual node
*/
class IApplLog : public IVNode
{
	VLogWindow*	fWindow;
	int			fLogLevel;		// log level: 0: no log, 1: log errors, 2: + log get messages
	float		fZoom = 1;
	
	public:	
		enum { kNolog, kLogError, kLogMsg };

		/// \brief creates a new IApplLog
		static SIApplLog create(IObject * parent)		{ return new IApplLog(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& ) const	{}

		/// \brief displays a message list
		virtual void	write(const SIMessageList& msgs);

		/// \brief displays a message list
		virtual void	write(const std::string& msg);

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);

		/// \brief return accept 'get' messages status
		virtual bool	acceptMsgs () const		{ return fLogLevel >= kLogMsg; };
		virtual bool	acceptErrors () const	{ return fLogLevel > kNolog; };
	
		VLogWindow* window()				{ return fWindow; }
		void		print(const char*);

		void	setX		(float x)	{ _setXPos (x); }
		void	setY		(float y)	{ _setYPos (y); }
		void	setW		(float w)	{ _setWidth(w); }
		void	setH		(float h)	{ _setHeight(h); }
		void	setWrap		(bool state);
		void	setZoom		(float zoom);
		float	getZoom		() const 	{ return fZoom; }

	protected:	
				 IApplLog(IObject * parent);
		virtual ~IApplLog();

		void	clear();

		virtual void	setXPos		(float x);
		virtual void	setYPos		(float y);
		virtual void	setWidth	(float w);
		virtual void	setHeight	(float h);
		virtual void	setVisible	(bool vis);
		virtual void	setLevel	(int level)		{ fLogLevel = level; };
		virtual void	foreground ();

		/// \brief object \c 'write' message handler.
		virtual MsgHandler::msgStatus writeMsg (const IMessage* msg) const;

		/// \brief object \c 'save' message handler.
		virtual MsgHandler::msgStatus saveMsg (const IMessage* msg) const;
};

class IApplPlugin;
typedef class libmapping::SMARTP<IApplPlugin>		SIApplPlugin;
//--------------------------------------------------------------------------
/*!
	\brief a virtual node for plugins management
*/
class IApplPlugin : public IVNode
{
	public:
		/// \brief creates a new IApplPlugin
		static SIApplPlugin create(IObject * parent)		{ return new IApplPlugin(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& ) const	{}

	protected:
				 IApplPlugin(IObject * parent);
		virtual ~IApplPlugin()	{}

		/// \brief object \c 'addPath' message handler.
		virtual MsgHandler::msgStatus addPath (const IMessage* msg) const;

		/// \brief object \c 'reset' message handler.
		virtual MsgHandler::msgStatus reset (const IMessage* msg) const;
};

#if HASSSLSUPPORT
class IApplSsl;
typedef class libmapping::SMARTP<IApplSsl>		SIApplSsl;
//--------------------------------------------------------------------------
/*!
	\brief a virtual node for ssl certificates management
*/
class IApplSsl : public IVNode
{
	public:
		typedef struct ssl {
			QSslCertificate* cert = nullptr;
			QSslCertificate* cacert = nullptr;
			QSslKey* 		 key = nullptr;
		} Ssl;
		
		/// \brief creates a new IApplSsl
		static SIApplSsl create(IObject * parent)		{ return new IApplSsl(parent); }
		
		Ssl getSslInfos () const;

	protected:
				 IApplSsl(IObject * parent);
		virtual ~IApplSsl();

		virtual MsgHandler::msgStatus setCert (const IMessage* msg);
		virtual MsgHandler::msgStatus setCA (const IMessage* msg);
		virtual MsgHandler::msgStatus setKey (const IMessage* msg);

	private:
		QSslCertificate* fCert = nullptr;
		QSslCertificate* fCA = nullptr;
		QSslKey* 		 fKey = nullptr;
	
		bool readFile (const std::string& name, QByteArray& data) const;

		bool getFileName  (const IMessage* msg, std::string& name) const;
		bool setCert (const std::string& filename);
		bool setCA (const std::string& filename);
		bool setKey (const std::string& filename);
		void delCert ();
		void delCA ();
		void delKey ();
	
		std::string fCertFile;
		std::string fCAFile;
		std::string fKeyFile;
};
#endif

#if HASMIDISupport
class IApplMIDI;
typedef class libmapping::SMARTP<IApplMIDI>		SIApplMIDI;
//--------------------------------------------------------------------------
/*!
	\brief a virtual node for ssl certificates management
*/
class IApplMIDI : public IVNode
{
	int	fVerbose = 0;
	
	public:
		/// \brief creates a new IApplMIDI
		static SIApplMIDI create(IObject * parent)		{ return new IApplMIDI(parent); }
		
	protected:
				 IApplMIDI(IObject * parent);
		virtual ~IApplMIDI() {}

		virtual MsgHandler::msgStatus init (const IMessage* msg);
		virtual MsgHandler::msgStatus verbose (const IMessage* msg);

		virtual void init ();
		virtual void verbose (int mode);
};
#endif

/*! @} */

} // end namespoace
