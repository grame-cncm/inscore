/*

  INScore Library
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

#pragma once

#include <iostream>

#include "INScore.h"
#include "INScoreGlue.h"

namespace inscore
{

class Message {};
typedef Message* MessagePtr;

//--------------------------------------------------------------------------
/*! \brief the main library interface for emcc
*/
class inscore_export INScoreAdapter
{
	inscore::INScoreJSGlue* fGlue = 0;
	inline INScore::MessagePtr message(MessagePtr msg) 	{ return INScore::MessagePtr(msg); }

	public:
		typedef const std::string	jsString;
	
				 INScoreAdapter() {}
		virtual ~INScoreAdapter() {}
		
		INScoreGlue* start (int udpport, int outport, int errport)
												{ fGlue = new INScoreJSGlue; return INScore::start (udpport, outport, errport, fGlue); }
		void 		 stop (INScoreGlue* glue)	{ INScore::stop(glue); delete fGlue; }

    	void restartNetwork()		{ INScore::restartNetwork(); }
    	void stopNetwork()			{ INScore::stopNetwork(); }

		bool loadInscore	(jsString& script, bool autoparse=false) { return INScore::loadInscore(script.c_str(), autoparse); }
		bool loadInscore2 	(jsString& script)						 { return INScore::loadInscore2(script.c_str()); }

		void postMessage	(jsString& address, MessagePtr msg)					{ INScore::postMessage(address.c_str(), message(msg)); }
		void postMessage	(jsString& address, jsString& msg)					{ INScore::postMessage(address.c_str(), msg.c_str()); }
		void postMessage	(jsString& address, jsString& msg, int val)			{ INScore::postMessage(address.c_str(), msg.c_str(), val); }
		void postMessage	(jsString& address, jsString& msg, float val)		{ INScore::postMessage(address.c_str(), msg.c_str(), val); }
		void postMessage	(jsString& address, jsString& msg, jsString& val)	{ INScore::postMessage(address.c_str(), msg.c_str(), val.c_str()); }
		void delayMessage	(jsString& address, MessagePtr msg)					{ INScore::delayMessage(address.c_str(), message(msg)); }

		MessagePtr newMessageM (jsString& msg)	{ return MessagePtr(INScore::newMessage(msg.c_str())); }
		MessagePtr newMessage ()				{ return MessagePtr(INScore::newMessage()); }
		void delMessage(MessagePtr msg)			{ INScore::delMessage(INScore::MessagePtr(msg)); }
		void add (MessagePtr msg, jsString& s)	{ INScore::add(message(msg), s.c_str()); }
		void add (MessagePtr msg, float f)		{ INScore::add(message(msg), f); }
		void add (MessagePtr msg, int n)		{ INScore::add(message(msg), n); }
	
	
		float 		version()				{ return INScore::version(); }
		std::string versionStr()			{ return INScore::versionStr(); }

		std::string guidoversion()			{ return INScore::guidoversion();}
		std::string musicxmlversion()		{ return INScore::musicxmlversion();}
};

}
