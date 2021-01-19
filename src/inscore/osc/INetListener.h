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


#pragma once

#include "smartpointer.h"
#include "Modules.h"

#if HASOSCStream
// oscpack include files
#include "ip/UdpSocket.h"
#include "osc/OscPacketListener.h"
#endif

namespace inscore
{

class IMessageStack;
typedef class libmapping::SMARTP<IMessageStack>	SIMessageStack;

#if HASOSCStream

/*!
\addtogroup ITLCtrl Controller
@{
*/
//--------------------------------------------------------------------------
/*!
	\brief an OSC listener that converts OSC input to IMessage
*/
class INetListener : public osc::OscPacketListener, public libmapping::smartable
{
	UdpListeningReceiveSocket fSocket;	///< the udp socket listener
	SIMessageStack	fMsgStack;			///< the messages stack
//	unsigned long	fMyAddress;
	bool	fRunning;

	public:
		static libmapping::SMARTP<INetListener> create(SIMessageStack& stack, int port = 7000)
			{ return new INetListener(stack, port); }

		/*!
			\brief process OSC messages

			\param m the OSC message (pre-processed by the base class)
			\param remoteEndpoint the sender IP address
		*/
		virtual void ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint );
		virtual void run();
		virtual void stop(); //	{ fRunning=false; fSocket.AsynchronousBreak(); }

	protected:
				 INetListener(SIMessageStack& stack, int port = 7000);
		virtual ~INetListener();

				 bool isExpression(std::string arg) const;

};

#else

class INetListener : public libmapping::smartable
{
	public:
		static libmapping::SMARTP<INetListener> create(SIMessageStack& stack, int port = 7000)
			{ return new INetListener(stack, port); }

		virtual void run()	{}
		virtual void stop() {}

	protected:
				 INetListener(SIMessageStack& stack, int port = 7000) {}
		virtual ~INetListener() {}

				 bool isExpression(std::string arg) const;

};
#endif

typedef class libmapping::SMARTP<INetListener>	SINetListener;

/*!
@}
*/

}
