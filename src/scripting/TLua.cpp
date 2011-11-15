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

#include "TLua.h"
#include "TEnv.h"
#include "OSCStream.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

#ifdef LUA
//--------------------------------------------------------------------------------------------
static int luaPrint(lua_State *L)
{
	int n = lua_gettop(L);
	cout << "lua: ";
	oscout << OSCStart("lua:");
	for (int i=1; i<=n; i++)
	{
		if (lua_isstring(L,i)) {
			cout << lua_tostring(L,i) << " ";
			oscout << lua_tostring(L,i);
		}
		else if (lua_isnil(L,i)) {
			cout << "nil ";
			oscout << "nil";
		}
		else if (lua_isboolean(L,i)) {
			cout << (lua_toboolean(L,i) ? "true " : "false ");
			oscout << (lua_toboolean(L,i) ? "true" : "false");
		}
		else {
			char buff[64];
			sprintf (buff, "%p", lua_topointer(L,i));
			cout << luaL_typename(L,i) << ":" << buff;
			oscout << luaL_typename(L,i) << ":" << buff;
		}
	}
	oscout << OSCEnd();
	return 0;
}

//--------------------------------------------------------------------------------------------
TLua::TLua()
{
	fLua = lua_open();
	lua_register(fLua, "print", luaPrint);
}

TLua::~TLua()
{
	lua_close (fLua);
}


//--------------------------------------------------------------------------------------------
// lua support
//--------------------------------------------------------------------------------------------
void TLua::bindEnv (const STEnv& env)
{
	for (TEnv::TEnvList::const_iterator i = env->begin(); i != env->end(); i++) {
		if (i->second->isType<int>()) lua_pushnumber (fLua, i->second->value(0));
		else if (i->second->isType<float>()) lua_pushnumber (fLua, i->second->value(0.));
		else if (i->second->isType<string>()) lua_pushstring (fLua, i->second->value(string("")).c_str());
		else {
			ITLErr << i->first << " unknown variable type " << ITLEndl;
			break;
		}
		lua_setfield(fLua, LUA_GLOBALSINDEX, i->first.c_str());
	}
}

//--------------------------------------------------------------------------------------------
bool TLua::check( int code ) const
{
	switch (code) {
	case LUA_ERRSYNTAX:
		ITLErr << "lua: syntax error: " << lua_tostring(fLua, 1) << ITLEndl;
		break;
	case LUA_ERRMEM:
		ITLErr << "lua: memory allocation error" << ITLEndl;
		break;
	case LUA_ERRRUN:
		ITLErr << "lua: runtime error: " << lua_tostring(fLua, 1) << ITLEndl;
		break;
	case LUA_ERRERR:
		ITLErr << "lua: error while running the error handler function" << ITLEndl;
		break;
	default:
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------------
bool TLua::eval (const char* script, string& outStr)
{
	if (check (luaL_loadstring (fLua, script))) {
		if (check (lua_pcall(fLua, 0, LUA_MULTRET, 0))) {
			int n = lua_gettop (fLua);
			string luaout;
			for (int i=1; i<=n; i++) {
				if (lua_istable (fLua, i)) outStr += getTable(fLua, i);
				else if (lua_isstring (fLua, i)) outStr += lua_tostring(fLua, i);
			}
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------------
string TLua::getTable (lua_State* L, int i) const
{
	string out;
	lua_pushnil(L);  /* first key */
	while (lua_next(L, i) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		if (lua_type(L, -1) == LUA_TSTRING) out += lua_tostring(L, -1);
		out += "\n";
		lua_pop(L, 1);
	}
	return out;
}

#else

//--------------------------------------------------------------------------------------------
TLua::TLua()	{}
TLua::~TLua()	{}
void TLua::bindEnv (const STEnv& env) {}

bool TLua::eval (const char* script, string& outStr)
{
	ITLErr << "lua not available!" << ITLEndl;
	return false;
}

#endif


} // namespace
