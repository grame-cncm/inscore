/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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


#ifndef __EventMessage__
#define __EventMessage__

#include <string>
#include "smartpointer.h"
 
namespace interlude
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
			
	protected:
				 EventMessage(const IMessage* msg, int startindex);
		virtual ~EventMessage();

	public:
		enum { kDefaultUPDPort = 7001 };
		
		static SEventMessage	create (const IMessage* msg, int startindex)	{ return new EventMessage(msg, startindex); }
		void	send() const;
};

} // end namespoace

#endif
