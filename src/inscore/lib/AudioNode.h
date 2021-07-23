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
#include <vector>

#include "IMessageHandlers.h"

namespace inscore
{

class IObject;
class IMessage;

/*!
\addtogroup ITLModel
@{
*/
//--------------------------------------------------------------------------
/*!
	\brief a generic audio node (used for connections)
*/
class AudioNode
{
    public:
		typedef struct AudioConnection {
			int from = 0;
			int to = 0;
			IObject* obj = nullptr;
			AudioConnection (IObject* o, int v1, int v2) : from(v1), to(v2), obj(o) {}
			bool operator == (const AudioConnection& v) const 	{ return (from == v.from) && (to == v.to) && (obj == v.obj); }
			bool operator != (const AudioConnection& v) const	{ return !(*this == v); }
//			bool operator < (const AudioConnection& v) const 	{ return (from < v.from) || (to < v.to) || (obj < v.obj); }
		} AudioConnection;
		typedef struct _AudioConnection {
			int from = 0;
			int to = 0;
			std::string name;
		} _AudioConnection;
		typedef std::vector<AudioConnection>	AudioNodeCnxList;
		
				 AudioNode() {}
		virtual ~AudioNode() {}

		void	setIONums (int inputs, int outputs) { fNumInputs = inputs; fNumOutputs = outputs; }
		int		getInputs () const  				{ return fNumInputs; }
		int		getOutputs () const  				{ return fNumOutputs; }
		const AudioNodeCnxList& newConnections() const { return fNotifyNew; }
		const AudioNodeCnxList& delConnections() const { return fNotifyDel; }
		void	resetNotifications() 				{ fNotifyDel.clear(); fNotifyNew.clear(); }
	
	protected:
		AudioNodeCnxList fOutputs;
		AudioNodeCnxList fNotifyNew;
		AudioNodeCnxList fNotifyDel;
	
		int fNumInputs = 0;
		int fNumOutputs = 0;

		virtual MsgHandler::msgStatus		connect (const IMessage* msg);
		virtual std::vector<std::string> 	getconnect () const;
		virtual MsgHandler::msgStatus		disconnect (const IMessage* msg);

		AudioNodeCnxList&	getOutputs () 				{ return fOutputs; }
		void 				cleanup(AudioNodeCnxList& list);

	private:
		MsgHandler::msgStatus 	getAudioNodes(const IMessage* msg, AudioNodeCnxList& list);
		_AudioConnection		getAudioConnection (std::string desc) const;
		bool 					remove(const AudioConnection& elt, AudioNodeCnxList& list);
};

/*! @} */

} // end namespoace
