/*

  INScore Project

  Copyright (C) 2011  Grame

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

#include <iostream>

#include "TScripting.h"

#include "IMessage.h"
#include "TEnv.h"
#include "TLoop.h"

using namespace std;

namespace inscore 
{

class IMessageList;
class IMessage;
class TLoop;
class TEnv;

//--------------------------------------------------------------------------------------------
TScripting::TScripting() 
{
	fMessages = new IMessageList;
	fEnv = TEnv::create();
}

TScripting::~TScripting()	{ delete fMessages; }

//--------------------------------------------------------------------------------------------
void TScripting::variable	(const char* ident, int val)				{ fEnv->bind( ident, val); }
void TScripting::variable	(const char* ident, float val)				{ fEnv->bind( ident, val); }
void TScripting::variable	(const char* ident, const char* val)	{ fEnv->bind( ident, val); }

//--------------------------------------------------------------------------------------------
void TScripting::add (IMessage* msg)	
{ 
	if (fLoops.size()) {
		STLoop loop = fLoops.top();
		loop->add (msg);
	}
	else *fMessages += msg; 
}

//--------------------------------------------------------------------------------------------
void TScripting::startLoop	(const char* ident, unsigned int count, int lineno)
{
	STLoop loop = TLoop::create (ident, count, lineno);
	if (fLoops.size()) {
		STLoop current = fLoops.top();
		current->add (loop);
	}
	fLoops.push(loop);
}

//--------------------------------------------------------------------------------------------
Sbaseparam*	TScripting::resolve (const char* var)
{
	Sbaseparam value = fEnv->value (var);
	return value ? new Sbaseparam(value) : 0;
}

//--------------------------------------------------------------------------------------------
int TScripting::endLoop ()
{
	if (fLoops.size()) {
		STLoop loop = fLoops.top();
		fLoops.pop ();
		if (fLoops.empty()) {		// evaluates the loop with a new environment
			return loop->eval(TEnv::create(), fMessages) ? 0 : loop->lineno();
		}
	}
	return 0;
}

} // namespace
