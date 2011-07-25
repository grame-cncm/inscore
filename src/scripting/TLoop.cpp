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

#include "TLoop.h"

#include "TEnv.h"
#include "TLoopEval.h"

namespace inscore 
{

//--------------------------------------------------------------------------------------------
void LoopedMessage::accept (TLoopEval* visitor)	{ visitor->eval(fMessage); }
LoopedMessage::~LoopedMessage()					{ delete fMessage; }

void LoopedLoop::accept (TLoopEval* visitor)		{ visitor->eval(fLoop); }

//--------------------------------------------------------------------------------------------
void TLoop::eval(TEnv* env, IMessageList* outlist) 
{
	unsigned int n = fLooped.size();
	
	for (unsigned int i=0; i<fCount; i++) {	
		STEnv newEnv = TEnv::create(env);
		newEnv->bind (fIdent, int(i));
		TLoopEval eval (newEnv, outlist);

		for (unsigned int j=0; j<n; j++) {
			fLooped[i]->accept(&eval);
		}
	}
}

} // namespace
