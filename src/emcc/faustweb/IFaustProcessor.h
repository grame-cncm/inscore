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

#include "IMessageHandlers.h"
#include "IRectShape.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IFaustProcessor;
typedef class libmapping::SMARTP<IFaustProcessor>	SIFaustProcessor;

class oldFaustProcessorUIElement {
	public:
		std::string	fAddress;
		std::string fType;
		std::string fLabel;
		float	fValue, fMin, fMax, fStep;
	
				 oldFaustProcessorUIElement(std::string type, std::string label, std::string address, float init, float min, float max, float step) :
				  fType(type), fLabel(label), fAddress(address), fValue(init), fMin(min), fMax(max), fStep(step) {}
		virtual ~oldFaustProcessorUIElement() {}
};

class FaustProcessorUIElement {
	public:
		std::string fType, fLabel;
		float	fValue = 0, fMin = 0, fMax = 0, fStep = 0;
	
				 FaustProcessorUIElement(std::string type, std::string label, float init, float min, float max, float step) :
				  fType(type), fLabel(label), fValue(init), fMin(min), fMax(max), fStep(step) {}
				 FaustProcessorUIElement() {}
		virtual ~FaustProcessorUIElement() {}
};


class TFaustParamUpdate {
	public:
	enum { kButton, kOther };
	std::string	address;
	float value;
	int type = kOther;
	TFaustParamUpdate (const std::string& a, float v) : address(a), value(v) {}
	TFaustParamUpdate (const std::string& a, float v, int type) : address(a), value(v), type(type) {}
};
class TFaustKeysUpdate {
	public:
	enum { kKeyOn, kKeyOff, kAllNotesOff=-1 , kButton = -2 };
	int type, chan, pitch, velocity;
	TFaustKeysUpdate (int type, int chan, int pitch, int vel) : type(type), chan(chan), pitch(pitch), velocity(vel) {}
};

//--------------------------------------------------------------------------
/*!
	\brief a Faust processor (that is also a parallel signal)
*/
class IFaustProcessor : public IRectShape
{
	std::string	fDspCode;
	int fVoices = 0;
	int fNumInputs = 0;
	int fNumOutputs = 0;
	bool fPlaying = false;

	typedef std::map<std::string,float> TParamsValues;
	TParamsValues fParamValues;
		
	std::string address2msg 	(const char * address) const;
	void 		addMsgHandler 	(const std::string& address, const std::string& name, float min, float max);
	void 		addMsgHandler 	(const std::string& address, const std::string& name);
	std::string oscaddress2faustaddress (const std::string& oscaddress) const;
	float 		getParamValue 	(const std::string& address) const;
	SIMessage	getParamMsg		(const std::string& target, float value ) const;
	template<typename T> SIMessage	getParamMsg	(const std::string& target, const std::string& type, T value ) const {
		SIMessage msg = IMessage::create(target);
		msg->add (type);
		msg->add (value);
		return msg;
	}

    public:
		typedef std::vector<TFaustParamUpdate> TNewValues;
		typedef std::vector<TFaustKeysUpdate>  TKeyValues;
		
		static const std::string kFaustProcessorType;
		static SIFaustProcessor create(const std::string& name, IObject * parent)	{ return new IFaustProcessor(name, parent); }
		virtual void	accept (Updater* u);

		std::string getCode () const 		{ return fDspCode; }
		int			getVoices () const		{ return fVoices; }
		bool		playing() const			{ return fPlaying; }
		void		setIONums (int inputs, int outputs)  { fNumInputs = inputs; fNumOutputs = outputs; }
		void	 	setFaustUI (std::string type, std::string label, std::string address, float init, float min, float max, float step);
		void	 	setParamValue (const std::string& address, float val);
		void	 	setButtonValue (const std::string& address, float val);

		const TNewValues& 	getChangedValues() const	{ return fNewValues; }
		const TKeyValues& 	getKeyValues() const		{ return fKeyValues; }
		void 				clearChangedValues() 		{ fNewValues.clear(); fKeyValues.clear(); }

		// overrides message processing for handling faust address space
		virtual int processMsg (const std::string& address, const std::string& addressTail, const IMessage* msg);
		virtual SIMessageList getMsgs (const IMessage* msg) const;
		virtual SIMessageList getAll() const;
		
	protected:
		std::vector<TFaustParamUpdate> 			fNewValues;
		std::vector<TFaustKeysUpdate> 			fKeyValues;
		std::vector<oldFaustProcessorUIElement> 	fPaths;
		std::map<std::string, FaustProcessorUIElement> 	fAddressSpace;

				 IFaustProcessor( const std::string& name, IObject * parent);
		virtual ~IFaustProcessor();

		void setPlay (bool status) 		{ fPlaying = status; }
		SIMessageList getPaths() const;
		
		/// \brief print the set message
		virtual void	print (IMessage& out) const;

		/// \brief the set method handler
		virtual MsgHandler::msgStatus	set (const IMessage* msg);
		virtual MsgHandler::msgStatus	keyon (const IMessage* msg);
		virtual MsgHandler::msgStatus	keyoff (const IMessage* msg);
		virtual MsgHandler::msgStatus	allNotesOff (const IMessage* msg);

		// ------------------------
		// messages handling
		// ------------------------
		class SetFaustParamMsgHandler;
		typedef libmapping::SMARTP<SetFaustParamMsgHandler> SSetFaustParamMsgHandler;
		class SetFaustParamMsgHandler : public MsgHandler {
			public:
				typedef void (IFaustProcessor::*MsgHandlerMethod)(const std::string&, float);
				virtual float check(float val)	{ return std::min ( std::max(val,fMin), fMax ); }
				static SSetFaustParamMsgHandler create(IFaustProcessor* obj, MsgHandlerMethod method, const std::string& address, float min, float max)
						{ return new SetFaustParamMsgHandler(obj, method, address, min, max); }
				virtual msgStatus operator ()(const IMessage* msg) {
					float val;
					if ( msg->size() != 1 || !msg->cast_param(0, val)) return kBadParameters;
					(fObject->*fMethod)( fAddress, val );
					return kProcessed;
				}
			protected:
				IFaustProcessor*	fObject;
				MsgHandlerMethod	fMethod;
				std::string fAddress;
				float fMin, fMax;
				SetFaustParamMsgHandler(IFaustProcessor* obj, MsgHandlerMethod method, const std::string& address, float min, float max) :
					fObject(obj), fMethod(method), fAddress(address), fMin(min), fMax(max) {}
		};

		class GetFaustParamMethodHandler;
		typedef libmapping::SMARTP<GetFaustParamMethodHandler> SGetFaustParamMethodHandler;
		class GetFaustParamMethodHandler : public TGetParamMethodHandler<IFaustProcessor, float (IFaustProcessor::*)()> {
			std::string fAddress;
			typedef float (IFaustProcessor::* GetMethodHandler)(const std::string&) const;
			GetMethodHandler fFaustGetMethod;
			GetFaustParamMethodHandler(IFaustProcessor* o, GetMethodHandler m, std::string address) : TGetParamMethodHandler(o,0), fFaustGetMethod(m), fAddress(address) {}
		public:
			static SGetFaustParamMethodHandler create(IFaustProcessor* obj, GetMethodHandler method, std::string address) {
				return new GetFaustParamMethodHandler(obj, method, address); }
			virtual SIMessage&  print(SIMessage& out) const	{ *out << (fObject->*fFaustGetMethod)(fAddress); return out; }
	};
};

/*! @} */

} // end namespoace
