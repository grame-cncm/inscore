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

#ifndef __IApplVNodes__
#define __IApplVNodes__

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
	
	public:	
		enum { kNolog, kLogError, kLogMsg };

		/// \brief creates a new IApplLog
		static SIApplLog create(IObject * parent)		{ return new IApplLog(parent); }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& ) const	{}

		/// \brief accept an Update visitor
		virtual void	accept (Updater*);

		/// \brief return accept 'get' messages status
		virtual bool	acceptMsgs () const		{ return fLogLevel >= kLogMsg; };
		virtual bool	acceptErrors () const	{ return fLogLevel > kNolog; };
	
		VLogWindow* window()				{ return fWindow; }
		void		print(const char*);

		void	setX		(float x)	{ fXPos = x; }
		void	setY		(float y)	{ fYPos = y; }
		void	setW		(float x)	{ fWidth = x; }
		void	setH		(float y)	{ fHeight = y; }
		void	setWrap		(bool state);

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
	\brief a virtual node for plugins managemen
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


/*! @} */

} // end namespoace

#endif
