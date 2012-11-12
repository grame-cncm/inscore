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
#include <sstream>

#include "TScripting.h"

#include "IMessage.h"
#include "TEnv.h"
#include "ITLparser.h"
#include "ITLError.h"

using namespace std;
extern inscore::TScripting* gScripter;


namespace inscore
{

class IMessageList;
class IMessage;
class TEnv;

//--------------------------------------------------------------------------------------------
TScripting::TScripting(TJSEngine* js, TLua* lua)
	: 	fJavascript(js), fLua(lua)
{
	fMessages = new IMessageList;
	fEnv = TEnv::create();
}

TScripting::~TScripting()	{ delete fMessages; }

//--------------------------------------------------------------------------------------------
void TScripting::variable	(const char* ident, int val)				{ fEnv->bind( ident, val); }
void TScripting::variable	(const char* ident, float val)				{ fEnv->bind( ident, val); }
void TScripting::variable	(const char* ident, const char* val)		{ fEnv->bind( ident, val); }

//--------------------------------------------------------------------------------------------
void TScripting::add (IMessage* msg)
{
	*fMessages += msg;
}

//--------------------------------------------------------------------------------------------
void TScripting::add (IMessageList* msgs)
{
	*fMessages += *msgs;
}

//--------------------------------------------------------------------------------------------
// lua support
//--------------------------------------------------------------------------------------------
#ifdef LUA
bool TScripting::luaEval (const char* script)
{
	if (fLua) {
		fLua->bindEnv (fEnv);
		string luaout;
		if (fLua->eval(script, luaout)) {
			if (luaout.size()) {
				istringstream stream(luaout);
				ITLparser p (&stream, 0, fJavascript, fLua);
				IMessageList* msgs = p.parse();
				if (msgs) add (msgs);
			}
			return true;
		}
	}
	else ITLErr << "lua is not available!" << ITLEndl;
	return false;
}
#else
bool TScripting::luaEval (const char* script)
{
	ITLErr << "lua is not available!" << ITLEndl;
	return false;
}
#endif


//--------------------------------------------------------------------------------------------
// javascript support
//--------------------------------------------------------------------------------------------
#ifdef V8ENGINE
bool TScripting::jsEval (const char* script, int lineno)
{
	if (fJavascript) {
		fJavascript->bindEnv (fEnv);
		string jsout;
		if (fJavascript->eval(lineno, script, jsout)) {
			if (jsout.size()) {
				istringstream stream(jsout);
				ITLparser p (&stream, 0, fJavascript, fLua);
				IMessageList* msgs = p.parse();
				if (msgs) add (msgs);
			}
			return true;
		}
	}
	else ITLErr << "javascript is not available!" << ITLEndl;
	return false;
}
#else
bool TScripting::jsEval (const char* script, int lineno)
{
	ITLErr << "javascript is not available!" << ITLEndl;
	return false;
}
#endif

//--------------------------------------------------------------------------------------------
Sbaseparam*	TScripting::resolve (const char* var)
{
	Sbaseparam value = fEnv->value (var);
	return value ? new Sbaseparam(value) : 0;
}

} // namespace
