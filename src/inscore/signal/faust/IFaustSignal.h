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


#ifndef __IFaustSignal__
#define __IFaustSignal__

#include "ISignal.h"
#include "IMessageHandlers.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
//--------------------------------------------------------------------------
/*!
	\brief a Faust processor (that is also a parallel signal)
*/
class IFaustSignal : public ISignal
{    
        const char*	translate (const char* name) const;
    
	public:
		virtual void	accept (Updater* u) = 0;
	
		void addMsgHandler (const char* name, float* zone);
		void addMsgHandler (const char* name, float* zone, float min, float max);
	
		/// \brief in faust context, provides access to output signals using an index
		virtual bool	findSubNode (std::string node, subnodes& outlist);

	protected:

    
        //      Faust DSP characteristics 
        int		fNumIntputs, fNumOutputs;
        //      Input/Output buffers
        float ** fInBuffers, **fOutBuffers;

        
        virtual void		init() = 0;
        virtual void		call_compute (int nframes, int index, int step) = 0;

    
				 IFaustSignal( const std::string& name, IObject * parent);
		virtual ~IFaustSignal();

		enum { kMaxBuffer=4096 };

		/// \brief print the set message
		virtual void	print (IMessage& out) const = 0;

		/// \brief put the message values into a projection of the signal
		virtual bool	putAt (const IMessage* msg, int index, int step);

		/// \brief set signals to the message signals
		virtual MsgHandler::msgStatus	set (const IMessage* msg) = 0;

		// ------------------------
		// messages handling
		// ------------------------	
		class SetFaustParamMsgHandler;
		typedef libmapping::SMARTP<SetFaustParamMsgHandler> SSetFaustParamMsgHandler;
		class SetFaustParamMsgHandler : public MsgHandler {
			protected:
				float* fValue;
				SetFaustParamMsgHandler(float* value) : fValue(value) {}
			public:
				virtual MsgHandler::msgStatus operator ()(const IMessage* msg);
				virtual float check(float val)	{ return val; }
				static SSetFaustParamMsgHandler create(float* value) { return new SetFaustParamMsgHandler(value); }
		};
		
		// ------------------------	
		class SetCheckedFaustParamMsgHandler;
		typedef libmapping::SMARTP<SetCheckedFaustParamMsgHandler> SSetCheckedFaustParamMsgHandler;
		class SetCheckedFaustParamMsgHandler : public SetFaustParamMsgHandler {
			protected:
				float fMin, fMax;
				SetCheckedFaustParamMsgHandler(float* value, float min, float max) : SetFaustParamMsgHandler(value), fMin(min), fMax(max) {}
			public:
				virtual float check(float val);
				static SSetFaustParamMsgHandler create(float* value, float min, float max) { return new SetCheckedFaustParamMsgHandler(value, min, max); }
		};

		// ------------------------	
		class GetFaustParamMsgHandler;
		typedef libmapping::SMARTP<GetFaustParamMsgHandler> SGetFaustParamMsgHandler;
		class GetFaustParamMsgHandler : public GetParamMsgHandler {
			protected:
				float* fValue;
				GetFaustParamMsgHandler(float* value) : fValue(value) {}
			public:
				virtual SIMessage&  print(SIMessage&) const;
				static SGetFaustParamMsgHandler create(float* value) { return new GetFaustParamMsgHandler(value); }
		};
};

/*! @} */

} // end namespoace

#endif
