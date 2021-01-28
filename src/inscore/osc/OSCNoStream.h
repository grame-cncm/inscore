/*
  Copyright (c) Grame 2020

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#pragma once

#define oscout std::cout
#define oscerr std::cerr

#include "TIRect.h"

namespace inscore
{

//--------------------------------------------------------------------------
typedef struct OSCStart {
	const char* fAddress;
	OSCStart() {}
	OSCStart(const char* a) : fAddress(a) {}
} OSCStart;

typedef struct OSCErr : public OSCStart {
	OSCErr() : OSCStart("error:") {}
} OSCErr;

typedef struct OSCWarn : public OSCStart {
	OSCWarn() : OSCStart("warning:") {}
} OSCWarn;

typedef struct OSCEnd {} OSCEnd;

#define kLocalhost	0x7f000001

class IMessage;
class IMessageList;
class IExpression;
class IExprArgBase;
class IExprOperator;
class IColor;
class UdpSocket;

//--------------------------------------------------------------------------
/*!
\brief	OSC output streams
*/
class OSCStream
{
	public:
	enum state	{ kIdle, kInProgress };

	static bool start() { return true; }
	static void stop()	{}
	static void sendEvent(const IMessage* msg, const std::string& dst, int port) {}

				 OSCStream(UdpSocket* socket) {}
		virtual ~OSCStream() {}
		
//		osc::OutboundPacketStream& stream()				{ return fOutStream; }
		int					getPort () const			{ return 0; }
		unsigned long		getAddress () const			{ return 0; }
		UdpSocket*			socket()					{ return 0; }
		int					state()	const				{ return kIdle; }
		
		virtual OSCStream&			start(const char * address) { return *this; }
		virtual OSCStream&			end()	{ return *this; }

		void setPort (int port)							{}
		void setAddress (unsigned long address)			{}
		void setAddress (const std::string& address)	{}
};

template <typename T> 	OSCStream& operator <<(OSCStream& s, T arg)		{ return s; }

class IApplLog;
//--------------------------------------------------------------------------
/*!
\brief	OSC error stream
*/
class OSCErrorStream : public OSCStream
{
	std::stringstream	fSStream;

	public:
				 OSCErrorStream(UdpSocket* socket) : OSCStream(socket) {}
		virtual ~OSCErrorStream() {}
		
		void	setLogWindow (IApplLog* w)						{}
		std::stringstream& stream()								{ return fSStream; }
		virtual OSCErrorStream&		start(const char * address) { return *this; }
		virtual OSCErrorStream&		end() { return *this; }
		/*!
		 * \brief activeConcatError concat all error in a streamstring while it is reactivated.
		 * \param activate if true reset the error streamstring and active concat error.
		 * If false new errors are not added.
		 */
		void activeConcatError(bool activate) {}

		/*!
		 * \brief streamConcat get the concat streamstring
		 * \return
		 */
		std::stringstream& streamConcat() { return fSStream; }
};

template <typename T> 	OSCErrorStream& operator <<(OSCErrorStream& s, T arg)	{ return s; }
template <typename T> 	OSCErrorStream& operator <<(OSCErrorStream& s, T& arg)	{ return s; }

} // end namespace
