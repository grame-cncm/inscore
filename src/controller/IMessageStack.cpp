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


#include "IMessageStack.h"
#include "IMessage.h"

namespace inscore
{

//--------------------------------------------------------------------------
IMessageStack::IMessageStack()	{ fifoinit(&fMsgFifo); }
IMessageStack::~IMessageStack()	{ flush(); }
	
//--------------------------------------------------------------------------
int IMessageStack::size()					{ return fifosize(&fMsgFifo); } 
void IMessageStack::push(IMessage* msg)		{ fifoput (&fMsgFifo, new fifocell(msg)); } 

//--------------------------------------------------------------------------
IMessage* IMessageStack::pop()
{ 
	fifocell * c = fifoget (&fMsgFifo);
	IMessage* msg = 0;
	if (c) {
		msg = (IMessage*)c->msg;
		delete c;
	}
	return msg;
}

//--------------------------------------------------------------------------
void IMessageStack::flush()
{
	IMessage* msg = pop();
	while (msg) {
		delete msg;
		msg = pop();
	}
}

} // end namespoace
