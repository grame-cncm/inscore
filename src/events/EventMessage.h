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


#ifndef __EventMessage__
#define __EventMessage__

#include <string>
#include "rational.h"
#include "smartpointer.h"
 
namespace inscore
{

class IMessage;
class EventMessage;
typedef SMARTP<EventMessage>	SEventMessage;

//----------------------------------------------------------------------
class EventMessage : public smartable
{
	IMessage *	fMessage;
	std::string	fDest;
	int			fPort;
	
	bool decodeAddress	(const std::string& address, std::string& oscAddress, std::string& host, int& port) const;
	void sockSend		(const IMessage* msg, const std::string& dst, int port) const;
	void localSend		(const IMessage* msg) const;

	void decodeMessage	(const IMessage* msg, int startindex);
	void checkvariable	(IMessage& msg, const std::string& param, float x, float y, float relx, float rely, 
						 const rational& date, bool setmsg=false) const;
			
	protected:
				 EventMessage(const IMessage* msg, int startindex);
		virtual ~EventMessage();

	public:
		enum { kDefaultUPDPort = 7001 };
		
		static SEventMessage	create (const IMessage* msg, int startindex)	{ return new EventMessage(msg, startindex); }
		void	send() const;
		void	send(float x, float y, float relx, float rely, const rational& date) const;
};

} // end namespoace

#endif
