/*

  Interlude Library
  Copyright (C) 2009,2010  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation.

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

#include "interlude.h"
#include "IMessage.h"
#include "IMessageStack.h"

using namespace std;
namespace interlude 
{


SIMessageStack gMsgStask;

//--------------------------------------------------------------------------
static IMessage* Message2IMessage (Interlude::MessagePtr p)
{
	return (IMessage*)p;
}

//--------------------------------------------------------------------------
int Interlude::version	()				{ 
#ifdef __x86_64__
	return 62; 
#else
	return 61; 
#endif
}
const char* Interlude::versionStr ()	{ 
#ifdef __x86_64__
	return "0.62";
#else
	return "0.61"; 
#endif
}

//--------------------------------------------------------------------------
void Interlude::postMessage	(const char* address, MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) {
		m->setAddress(address);
		if (gMsgStask) gMsgStask->push(m);
	}
}

//--------------------------------------------------------------------------
Interlude::MessagePtr Interlude::newMessage (const char* msg)
{
	IMessage* m = new IMessage;
	m->setMessage(msg);
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
Interlude::MessagePtr Interlude::newMessage ()
{
	IMessage* m = new IMessage;
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
void Interlude::delMessage(MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) delete m;
}

//--------------------------------------------------------------------------
void Interlude::add (MessagePtr p, const char* s)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add<string>(s);
}

//--------------------------------------------------------------------------
void Interlude::add (MessagePtr p, float f)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add<float>(f);
}

//--------------------------------------------------------------------------
void Interlude::add (MessagePtr p, int n)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add<int>(n);
}

}
