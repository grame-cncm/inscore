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

#include "AudioNode.h"
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
class IFaustwProcessor;
typedef class libmapping::SMARTP<IFaustProcessor>	SIFaustProcessor;


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
class IFaustProcessor : public IRectShape, public AudioNode
{
	bool fWasmExport = false;

	typedef std::map<std::string,float> TParamsValues;
	TParamsValues fParamValues;
		
	std::vector<std::string> oscaddress2faustaddress (const std::string& oscaddress) const;
	SIMessage						getParamMsg	(const std::string& target, float value ) const;
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
		void	 	setFaustUI (std::string type, std::string label, std::string address, float init, float min, float max, float step);
		void	 	setParamValue (const std::string& address, float val, int type);

		const TNewValues& 	getChangedValues() const	{ return fNewValues; }
		const TKeyValues& 	getKeyValues() const		{ return fKeyValues; }
		void 				clearChangedValues() 		{ fNewValues.clear(); fKeyValues.clear(); }

		// overrides message processing for handling faust address space
		virtual int processMsg (const std::string& address, const std::string& addressTail, const IMessage* msg);
		virtual SIMessageList 	getMsgs (const IMessage* msg) const;
		virtual SIMessageList 	getAll() const;
		// export the dsp as a faust module
		virtual std::string 	getWasm();
		virtual bool 						wasmFlag() const 	{ return fWasmExport; }
		virtual const IFaustwProcessor* 	wasmBased() const 	{ return nullptr; }
		
	protected:
		std::string	fDspCode;	// contains the dspCode
								// used by the wasm based dsp to store the wasm file name
		int fVoices = 0;

		std::vector<TFaustParamUpdate> 			fNewValues;
		std::vector<TFaustKeysUpdate> 			fKeyValues;
		std::map<std::string, FaustProcessorUIElement> 	fAddressSpace;

				 IFaustProcessor( const std::string& name, IObject * parent);
		virtual ~IFaustProcessor();

		SIMessageList getPaths() const;
		SIMessageList getUI() const;
		/// \brief print the set message
		virtual void	print (IMessage& out) const;
		virtual void 	cleanup();
		/// \brief object \c 'get' without parameter form: gives the corresponding 'set' message list
		virtual SIMessageList getSetMsg () const;

		/// \brief method handlers
		virtual MsgHandler::msgStatus	set (const IMessage* msg);
		virtual MsgHandler::msgStatus	keyon (const IMessage* msg);
		virtual MsgHandler::msgStatus	keyoff (const IMessage* msg);
		virtual MsgHandler::msgStatus	allNotesOff (const IMessage* msg);
};

/*! @} */

} // end namespoace
