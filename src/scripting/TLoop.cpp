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

#include "TLoop.h"
#include "TEnv.h"
#include "TLoopEval.h"

using namespace std;

namespace inscore 
{

//--------------------------------------------------------------------------------------------
LoopedMessage::~LoopedMessage()					{ delete fMessage; }
bool LoopedMessage::accept (TLoopEval* visitor)	{ return visitor->eval(fMessage); }
bool LoopedLoop::accept (TLoopEval* visitor)	{ return visitor->eval(fLoop); }

//--------------------------------------------------------------------------------------------
// evaluate a message in a given environment
bool TLoop::eval(TEnv* env, IMessageList* outlist) 
{
	bool result = true;
	unsigned int n = fLooped.size();	
	for (unsigned int i=0; i<fCount; i++) {	
		STEnv newEnv = TEnv::create(env);
		newEnv->bind (fIdent.c_str(), int(i));
		TLoopEval eval (newEnv, outlist);

		for (unsigned int j=0; j<n; j++) {
			result &= fLooped[j]->accept(&eval);
		}
	}
	return result;
}

} // namespace
