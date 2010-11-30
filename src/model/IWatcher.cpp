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

#include "IWatcher.h"
#include "OSCAddress.h"
#include "INScore.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
class EmptyGetParamMsgHandler : public GetParamMsgHandler {
	protected:
		EmptyGetParamMsgHandler() {}
	public: 
		static SMARTP<EmptyGetParamMsgHandler> create() { return new EmptyGetParamMsgHandler(); }
		virtual ~EmptyGetParamMsgHandler() {}
		virtual IMessage&  print(IMessage& m) const {return m;}
};


//--------------------------------------------------------------------------
const string IWatcher::kWatcherType("watcher");

//--------------------------------------------------------------------------
IWatcher::IWatcher(const std::string& name, IObject* parent) : IObject(name, parent)
{
	fTypeString = kWatcherType;
	
	fMsgHandlerMap["add"]		= TMethodMsgHandler<IWatcher>::create(this, &IWatcher::addMsg);
	fMsgHandlerMap["remove"]	= TMethodMsgHandler<IWatcher>::create(this, &IWatcher::removeMsg);
	fMsgHandlerMap["clear"]		= TMethodMsgHandler<IWatcher>::create(this, &IWatcher::clearMsg);
	
	fGetMsgHandlerMap[""]		= EmptyGetParamMsgHandler::create();
}

//--------------------------------------------------------------------------
IWatcher::~IWatcher() {}

//--------------------------------------------------------------------------
void IWatcher::print (ostream& out) const
{
	IObject::print (out);
	out << " watcher" << endl;
}

//--------------------------------------------------------------------------
// messages processing
//--------------------------------------------------------------------------
int IWatcher::execute (const IMessage* msg)
{
	int result = IObject::execute(msg);
	
	// Check if any watched condition has become true
	for ( int i = 0 ; i < int(fWatchedProperties.size()) ; i++ )
	{
		bool allConditions = true;
		for ( int conditionIndex = 0 ; conditionIndex < int(fWatchedProperties[i].fConditions.size()) ; conditionIndex++ )
		{
			if ( !fWatchedProperties[i].fConditions[conditionIndex]->check(this) )
			{
				allConditions = false;
				break;
			}
		}
		
		// The condition has become true: emit the related message
		if ( allConditions && ( fWatchedProperties[i].fAlwaysEmit || !fWatchedProperties[i].fConditionsState ) )
		{
			IMessage * builtMsg = buildEmitedMsg( fWatchedProperties[i].fTemplateMsg , this );
			INScore::postMessage( builtMsg->address().c_str() , builtMsg );
		}
		fWatchedProperties[i].fConditionsState = allConditions;
	}
	return result;
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IWatcher::set (const IMessage* msg)
{
	IObject::set(msg); 
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IWatcher::addMsg (const IMessage* msg )	
{
	// the 'add' message is of the form: add conditionsList osc-message
	//	- conditionsList is of the form: condition condition ... condition
	//		- condition is of the form: paramName operator referenceValue
	//			- paramName is a string
	//			- operator is one of the strings '==', '!=', '>', '<', '<=', '>='
	//			- referenceValue is an INScore base type (string, float, int, rational)
	//	- osc-message is a standard OSC message with: address msg [optional-parameters]
	
	// Parse the message arguments to build a WatchStruct
	WatchStruct watchStruct;
	
	// 1. Parse the optional '!' to determine if the watcher must always emit.
	int paramIndex = 0;
	if ( msg->params().size() && msg->params()[0]->value<std::string>("") == ALWAYS_EMIT )
	{
		watchStruct.fAlwaysEmit = true;
		paramIndex++;
	}
	
	// 2. Build the ParamChecker list and get the number of parsed params.
	paramIndex = buildParamCheckerList( *msg , paramIndex , watchStruct.fConditions );
	
	if ( !paramIndex )
		return MsgHandler::kBadParameters;

	// 3. Build the message to be emitted. 
	if ( !IWatcher::buildTemplateMsg( *msg , paramIndex , watchStruct.fTemplateMsg ) )
		return MsgHandler::kBadParameters;
		
	// 4. Add the newly built WatchStruct
	fWatchedProperties.push_back( watchStruct );
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
int	IWatcher::buildParamCheckerList(const IMessage& source , int startIndex , std::vector< SParamChecker >& outList)
{
	int parseIndex = startIndex;
	
	// At least 4 params for 1 ParamChecker, + at least 2 params for the template message
	//	=> we must have at least 6 params to build a new ParamChecker
	while (		( parseIndex + 6 <= int(source.params().size()) ) 
			||	( ( ( parseIndex + 4 <= int(source.params().size()) ) ) && (source.params()[parseIndex]->value<std::string>("") == ALWAYS_TRUE ) )
			)
	{
		if (source.params()[parseIndex]->value<std::string>("") == ALWAYS_TRUE )
		{
			// Special condition: always true, no test.
			
			if ( source.params()[parseIndex+1]->value<std::string>("") != CONDITION_SEPARATOR  )
				return 0;

			parseIndex += 2;
			outList.push_back( ParamCheckerAlwaysTrue::create() );
			continue;
		}

		std::string err = "";
		std::string paramName = source.params()[parseIndex]->value<std::string>(err);
		if ( paramName == err )
		{
			const char* msg = "IWatcher 'add': expected condition param string not found at index = ";
			std::cerr << msg << parseIndex << std::endl;
			oscerr << OSCErr() << msg << parseIndex << OSCEnd();
			return 0;
		}
		std::string operatorString = source.params()[parseIndex+1]->value<std::string>(err);
		IMessage::argPtr referenceValue = source.params()[parseIndex+2];

		
		// Handle rational case: reference value is an int, and following param is an int too
		IMessage::argPtr optionalReferenceValue = 0;
		if ( referenceValue->isType<int>() && source.params()[parseIndex+3]->isType<int>() )
		{
			optionalReferenceValue = source.params()[parseIndex+3];
			parseIndex++;
		}
		
		SParamChecker paramChecker = buildParamChecker( paramName , operatorString , referenceValue , optionalReferenceValue );
		if ( paramChecker )
			outList.push_back( paramChecker );

		if ( source.params()[parseIndex+3]->value<std::string>("") != CONDITION_SEPARATOR  )
		{
			return 0;
			// TODO handle rational
			//argPtr referenceValue2 = source.params()[parseIndex+2];
		}
		parseIndex += 4;
	}
	
	return parseIndex;
}

//--------------------------------------------------------------------------
IWatcher::SParamChecker IWatcher::buildParamChecker( const std::string& paramName , const std::string& operatorString , IMessage::argPtr referenceValue , IMessage::argPtr optionalReferenceValue ) 
{
	if ( referenceValue->isType<int>() )
		if ( optionalReferenceValue && optionalReferenceValue->isType<int>() ) 
			return buildParamCheckerTemplate<rational>( paramName , operatorString , rational(referenceValue->value<int>(0) , optionalReferenceValue->value<int>(0)) );
		else
			return buildParamCheckerTemplate<int>( paramName , operatorString , referenceValue->value<int>(0) );
	else if ( referenceValue->isType<float>() )
		return buildParamCheckerTemplate<float>( paramName , operatorString , referenceValue->value<float>(0.0) );
	else if ( referenceValue->isType<std::string>() )
		return buildParamCheckerTemplate<std::string>( paramName , operatorString , referenceValue->value<std::string>("") );
		
	return 0;
}

//--------------------------------------------------------------------------
bool IWatcher::buildTemplateMsg(const IMessage& source, int startIndex , IMessage& outMsg)
{
	if ( int(source.params().size()) <= startIndex + 1 ) 
	{
		const char* msg = "IWatcher 'add': Template message is missing.";
		std::cerr << msg << std::endl;
		oscerr << OSCErr() << msg << OSCEnd();

		return false;
	}

	outMsg = source;

	const std::string err = "";
	const std::string oscAddress	= source.params()[startIndex]->value<std::string>(err);
	if ( oscAddress == err )
		return false;
	outMsg.setAddress( oscAddress );	// moves the address from params to address field
	int parsedElements = 1;

	// If there is a message string, move it from params to message field
	const std::string message		= source.params()[startIndex+1]->value<std::string>(err);
	if ( message != err )
	{
		parsedElements++;
		outMsg.setMessage( message );
	}
	else
		outMsg.setMessage( "" );

	// and removes the conditions, address and message from the parameters list
	IMessage::argslist::iterator first = outMsg.params().begin();
	outMsg.params().erase(first, first + startIndex + parsedElements);
	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IWatcher::removeMsg (const IMessage* msg )	
{
	if ( msg->params().size() != 1 )
		return MsgHandler::kBadParameters;
		
	std::string removedAddress = msg->params()[0]->value<std::string>("");
	if ( !removedAddress.size() )
		return MsgHandler::kBadParameters;

	for ( int i = 0 ; i < int(fWatchedProperties.size()) ; i++ )
	{
		if ( removedAddress == fWatchedProperties[i].fTemplateMsg.address() )
			fWatchedProperties.erase( fWatchedProperties.begin() + i );
	}
	return MsgHandler::kProcessedNoChange;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IWatcher::clearMsg (const IMessage* msg)
{
	fWatchedProperties.clear();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
IMessage* IWatcher::buildEmitedMsg( const IMessage& templateMsg  , SIObject o )
{
	IMessage * builtMsg = new IMessage( templateMsg.address() , templateMsg.message() );
	for ( int i = 0 ; i < int(templateMsg.params().size()) ; i++ )
	{
		string param = templateMsg.params()[i]->value<std::string>("");
		// String '$param' is a variable parameter: get the corresponding value in
		// the source object and add it to the built message.
		if ( ( param.size() >= 2 ) && ( param[0] == VARIABLE_PREFIX ) && ( param[1] != VARIABLE_PREFIX ) )
		{
			param.erase(0,1);
			assert( o );

			SGetParamMsgHandler getHandler = o->getMessageHandler( param );
			if ( !getHandler )
			{
				const char* msg = "Variable parameter '";
				const char* msg2 = "' does not have a 'get' handler."; 
				std::cerr << msg << param << msg2 << std::endl;
				oscerr << OSCWarn() << msg << param << msg2 << OSCEnd();
				continue;
			}
			IMessage getMsg;
			getHandler->print(getMsg);

			for ( int j = 0 ; j < int(getMsg.params().size()) ; j++ )
				builtMsg->add( getMsg.params()[j] );
		}
		// Standard msg parameter: just copy it from the template to the built message.
		else
			builtMsg->add( templateMsg.params()[i] );
	}
	return builtMsg;
}

//--------------------------------------------------------------------------
template <>
bool IWatcher::ParamCheckerTemplate<rational>::check( SIObject o ) const
{
	assert ( o );

	SGetParamMsgHandler getHandler = o->getMessageHandler( fParamName );
	if ( !getHandler )
		return false;
	IMessage msg;
	getHandler->print(msg);
	if ( msg.params().size() != 2 )
		return false;
	return fComparator->result( rational( msg.params()[0]->value<int>( 0 ) , msg.params()[1]->value<int>( 0 ) ) );
}

//--------------------------------------------------------------------------
IMessageList IWatcher::getSetMsg () const
{	
	IMessageList outMsgs = IObject::getSetMsg();
	
	for ( unsigned int i = 0 ; i < fWatchedProperties.size() ; i++ )
	{
		IMessage* msg = new IMessage(getOSCAddress(), "add");
		if ( fWatchedProperties[i].fAlwaysEmit )
			*msg << std::string(ALWAYS_EMIT);
		for ( unsigned int j = 0 ; j < fWatchedProperties[i].fConditions.size() ; j++ )
		{
			fWatchedProperties[i].fConditions[j]->print(*msg);
			*msg << std::string(CONDITION_SEPARATOR);
		}
		*msg << &(fWatchedProperties[i].fTemplateMsg);
		outMsgs += msg;
	}
	return outMsgs;
}

}
