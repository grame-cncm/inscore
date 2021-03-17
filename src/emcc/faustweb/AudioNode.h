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
		typedef std::vector<IObject*>	AudioNodeList;
		
				 AudioNode() {}
		virtual ~AudioNode() {}

		void	setIONums (int inputs, int outputs) { fNumInputs = inputs; fNumOutputs = outputs; }
		int		getInputs () const  				{ return fNumInputs; }
		int		getOutputs () const  				{ return fNumOutputs; }
		const AudioNodeList& newConnections() const { return fNotifyNew; }
		const AudioNodeList& delConnections() const { return fNotifyDel; }
	
	protected:
		AudioNodeList fOutputs;
		AudioNodeList fNotifyNew;
		AudioNodeList fNotifyDel;
	
		int fNumInputs = 0;
		int fNumOutputs = 0;

		virtual MsgHandler::msgStatus		connect (const IMessage* msg);
		virtual std::vector<std::string> 	getconnect () const;
		virtual MsgHandler::msgStatus		disconnect (const IMessage* msg);

//		void 			addOutput (AudioNode* node) { fOutputs.push_back(node); }
		AudioNodeList&	getOutputs () 				{ return fOutputs; }
		void 			cleanup(AudioNodeList& list);

	private:
		MsgHandler::msgStatus 	getAudioNodes(const IMessage* msg, AudioNodeList& list);
		bool 					remove(const IObject* node, AudioNodeList& list);
};

/*! @} */

} // end namespoace
