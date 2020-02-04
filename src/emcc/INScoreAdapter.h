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

#include "INScore.h"

namespace inscore
{

//--------------------------------------------------------------------------
/*! \brief the main library interface for emcc
*/
class inscore_export INScoreAdapter
{
	public:
				 INScoreAdapter() {}
		virtual ~INScoreAdapter() {}
		
		INScoreGlue* start (int udpport, int outport, int errport, INScoreApplicationGlue* ag, bool offscreen=false)
												{ return INScore::start (udpport, outport, errport, ag, offscreen); }
		void 		 stop (INScoreGlue* glue)	{ INScore::stop(glue); }

    	void restartNetwork()		{ INScore::restartNetwork(); }
    	void stopNetwork()			{ INScore::stopNetwork(); }

		void postMessage	(const char* address, INScore::MessagePtr msg)	{ INScore::postMessage(address, msg); }
		void postMessage	(const char* address, const char* msg)	{ INScore::postMessage(address, msg); }
		void postMessage	(const char* address, const char* msg, int val)			{ INScore::postMessage(address, msg, val); }
		void postMessage	(const char* address, const char* msg, float val)		{ INScore::postMessage(address, msg, val); }
		void postMessage	(const char* address, const char* msg, const char* val)	{ INScore::postMessage(address, msg, val); }
		void delayMessage	(const char* address, INScore::MessagePtr msg)	{ INScore::delayMessage(address, msg); }

		INScore::MessagePtr newMessage (const char* msg)	{ return INScore::newMessage(msg); }
		INScore::MessagePtr newMessage ()					{ return INScore::newMessage(); }
		void delMessage(INScore::MessagePtr msg)			{ INScore::delMessage(msg); }
		void add (INScore::MessagePtr msg, const char* s)	{ INScore::add(msg, s); }
		void add (INScore::MessagePtr msg, float f)			{ INScore::add(msg, f); }
		void add (INScore::MessagePtr msg, int n)			{ INScore::add(msg, n); }
	
	
		float 		version()				{ return INScore::version(); }
		std::string versionStr()			{ return INScore::versionStr(); }

		std::string guidoversion()			{ return INScore::guidoversion();}
		std::string musicxmlversion()		{ return INScore::musicxmlversion();}
};

}
