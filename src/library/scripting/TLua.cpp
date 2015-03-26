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
#ifdef NO_OSCSTREAM
# define ITLErr		cerr
# define ITLEndl	endl
#else
#include "ITLError.h"
#endif

using namespace std;

namespace inscore
{

#ifdef LUA
//--------------------------------------------------------------------------------------------
static int luaPrint(lua_State *L)
{
	int n = lua_gettop(L);
#ifndef NO_OSCSTREAM
	oscout << OSCStart("lua:");
#endif
	for (int i=1; i<=n; i++)
	{
		const char* sep = (i<n) ? " " : "";
		if (lua_isstring(L,i)) {
			cout << lua_tostring(L,i) << sep;
#ifndef NO_OSCSTREAM
			oscout << lua_tostring(L,i);
#endif
		}
		else if (lua_isnil(L,i)) {
			cout << "nil" << sep;
#ifndef NO_OSCSTREAM
			oscout << "nil";
#endif
		}
		else if (lua_isboolean(L,i)) {
			cout << (lua_toboolean(L,i) ? "true" : "false") << sep;
#ifndef NO_OSCSTREAM
			oscout << (lua_toboolean(L,i) ? "true" : "false");
#endif
		}
		else {
			char buff[64];
			sprintf (buff, "%p", lua_topointer(L,i));
			cout << luaL_typename(L,i) << ":" << buff;
#ifndef NO_OSCSTREAM
			oscout << luaL_typename(L,i) << ":" << buff;
#endif
		}
	}
#ifndef NO_OSCSTREAM
	oscout << OSCEnd();
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
static int luaVersion(lua_State *L)
{
#ifndef NO_OSCSTREAM
	oscout << OSCStart("lua:") << LUA_RELEASE << OSCEnd();
#endif
	lua_pushstring (L, LUA_RELEASE);
	return 1;
}

//--------------------------------------------------------------------------------------------
TLua::TLua()
{
	fLua = lua_open();
	lua_register(fLua, "print", luaPrint);
	lua_register(fLua, "version", luaVersion);
}
TLua::~TLua() { lua_close (fLua); }


//--------------------------------------------------------------------------------------------
// lua support
//--------------------------------------------------------------------------------------------
bool TLua::bindEnv  (stringstream& s, const string& name, const IMessage::argPtr& val)
{
	if (val->isType<int>())			s << val->value(0);
	else if (val->isType<float>())	s << val->value(0.);
	else if (val->isType<string>())	s << '"' <<  val->value(string("")) << '"';
	else {
		ITLErr << name << "unknown variable type" << ITLEndl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------
void TLua::bindEnv  (stringstream& s, const string& name, const IMessage::argslist& values)
{
	unsigned int n = values.size();
	if (n == 0) return;

	stringstream tmp;
	tmp << name << "=";
	if (n == 1) {
		if (!bindEnv (tmp, name, values[0])) return;
	}
	else {
		tmp << "{";
		for (unsigned int i=0; i<n;) {
			if (!bindEnv (tmp, name, values[i])) return;
			i++;
			if (i<n) tmp << ", ";
		}
		tmp << "}";
	}
	s << tmp.str() << "\n";
}

//--------------------------------------------------------------------------------------------
void TLua::bindEnv (const STEnv& env)
{
	stringstream s;
	for (TEnv::TEnvList::const_iterator i = env->begin(); i != env->end(); i++) {
		bindEnv (s, i->first, i->second);
	}
	if (s.str().size()) {
		string out;
		if (!eval (s.str().c_str(), out))
			ITLErr << "can't export export variables to lua" << ITLEndl;
	}
}

//--------------------------------------------------------------------------------------------
bool TLua::check( int code ) const
{
	switch (code) {
	case LUA_ERRSYNTAX:
		ITLErr << "lua: syntax error:" << lua_tostring(fLua, 1) << ITLEndl;
		break;
	case LUA_ERRMEM:
		ITLErr << "lua: memory allocation error" << ITLEndl;
		break;
	case LUA_ERRRUN:
		ITLErr << "lua: runtime error:" << lua_tostring(fLua, 1) << ITLEndl;
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
	if (check (luaL_dostring (fLua, script))) {
		int n = lua_gettop (fLua);
		for (int i=1; i<=n; i++) {
			if (lua_istable (fLua, i)) outStr += getTable(fLua, i);
			else if (lua_isstring (fLua, i)) outStr += lua_tostring(fLua, i);
		}
		lua_pop (fLua, n);
		return true;
	}
	else cout << "  >>>>> luaL_dostring failed" << endl;
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

//--------------------------------------------------------------------------------------------
void TLua::Initialize ()
{
	lua_close (fLua);
	fLua = lua_open();
	lua_register(fLua, "print", luaPrint);
}

#else

//--------------------------------------------------------------------------------------------
TLua::TLua()	{}
TLua::~TLua()	{}

void TLua::Initialize () {}
void TLua::bindEnv (const STEnv& ) {}

bool TLua::eval (const char* /*script*/, string& /*outStr*/)
{
	ITLErr << "lua not available!" << ITLEndl;
	return false;
}

#endif


} // namespace
