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

#include <iostream>

#include "INetListener.h"
#include "IMessageStack.h"
#include "IMessage.h"
#include "IExprParser.h"
#include "Tools.h"

#if HASOSCStream

#include "osc/OscReceivedElements.h"
#include "ip/IpEndpointName.h"

using namespace std;
using namespace osc;

namespace inscore
{

//--------------------------------------------------------------------------
INetListener::INetListener(SIMessageStack& stack, int port)
		: fSocket(IpEndpointName( IpEndpointName::ANY_ADDRESS, port ), this), fMsgStack(stack), fRunning(false)
{
//	fMyAddress = Tools::getIP("");
}

INetListener::~INetListener()	{ stop(); }

//--------------------------------------------------------------------------
void INetListener::run()
{ 
	fRunning = true;
//	while (fRunning) {
		try {
			fSocket.Run(); 
		}
		catch (osc::Exception e) {
			cerr << "osc error: " << e.what() << endl;
		}
//	}
	fRunning = false;
}

//--------------------------------------------------------------------------
void INetListener::stop()
{ 
	fSocket.AsynchronousBreak();
}

//--------------------------------------------------------------------------
void INetListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& src )
{
	SIMessage msg = IMessage::create(m.AddressPattern());
	msg->setSrcIP (src.address);
	ReceivedMessageArgumentIterator i = m.ArgumentsBegin();
	bool first = true;		// used to handle the message string
	while (i != m.ArgumentsEnd()) {
		if (i->IsString()) {
			// the message string is expected to be the first parameter
			if (first) msg->setMessage(i->AsStringUnchecked());
			else{
				string t = i->AsStringUnchecked();
				//If the string describes and IExpression, it should be parsed here
				bool expressionParsed = false;
				if(isExpression(t)){
					SIExpression expr;
					if(IExprParser::parseExpression(t, expr)){
						IMsgParam<SIExpression>* param = new IMsgParam<SIExpression>(expr);
						msg->add(IMessage::argPtr(param));
						expressionParsed = true;
					}
				}
				//If the string doesn't describe expresison, it should be added as it is
				if(!expressionParsed)
					msg->add(t);
			}
		}
		else if (i->IsInt32()) {
			msg->add( int(i->AsInt32Unchecked()) );
		}
		else if (i->IsFloat()) {
			msg->add(i->AsFloatUnchecked());
		}
		if (first) first = false;
		i++;
	}
	fMsgStack->push (new SIMessage(msg));
	fMsgStack->inc();
}

#endif


//--------------------------------------------------------------------------
bool INetListener::isExpression(std::string arg) const
{
	if(arg.empty())
		return false;

	auto it = arg.begin();
	int i = 0;
	do{
		if(i){
			switch(i){
			case 1: if(*it!='x') return false; i++; break;
			case 2: if(*it!='p') return false; i++; break;
			case 3: if(*it!='r') return false; i++; break;
			case 4: if(*it!='(') return false; i++; break;
			default: return true;
			}
		}else if(*it == 'e')
			i++;
		else if(*it != ' ' && *it != '\t' && *it != '\n')
			return false;
	}while(it++ != arg.end());

	return false;
}

} // end namespoace

