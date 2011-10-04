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
#include "TLoop.h"
#include "ITLParser.h"
#include "ITLError.h"

using namespace std;
extern inscore::TScripting* gScripter;

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
void TScripting::variable	(const char* ident, const char* val)		{ fEnv->bind( ident, val); }

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
void TScripting::add (IMessageList* msgs)	
{ 
	*fMessages += *msgs;
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
// lua support
//--------------------------------------------------------------------------------------------
void TScripting::luaBindEnv (lua_State* L, const STEnv& env)
{
	for (TEnv::TEnvList::const_iterator i = env->begin(); i != env->end(); i++) {
		if (i->second->isType<int>()) lua_pushnumber (L, i->second->value(0));
		else if (i->second->isType<float>()) lua_pushnumber (L, i->second->value(0.));
		else if (i->second->isType<string>()) lua_pushstring (L, i->second->value(string("")).c_str());
		else {
			ITLErr << i->first << " unknown variable type " << ITLEndl;
			break;
		}
		lua_setfield(L, LUA_GLOBALSINDEX, i->first.c_str());
	}
}


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
bool TScripting::luaEval (const char* script)
{
	lua_State * L = lua_open();
	lua_register(L, "print", luaPrint);
	luaBindEnv (L, fEnv);
	int ret = luaL_loadstring (L, script);
	switch (ret) {
		case LUA_ERRSYNTAX:
			ITLErr << "lua: syntax error: " << lua_tostring(L, 1) << ITLEndl;
			break;
		case LUA_ERRMEM:
			ITLErr << "lua: memory allocation error" << ITLEndl;
			break;
		default:
			lua_call(L, 0, LUA_MULTRET);
			int n = lua_gettop (L);
			string luaout;
			for (int i=1; i<=n; i++) {
				if (lua_istable (L, i)) luaout += luaGetTable(L, i);
				else if (lua_isstring (L, i)) luaout += lua_tostring(L, i);
			}

			istringstream stream(luaout);
			ITLparser p (&stream);
			IMessageList* msgs = p.parse();
			if (msgs) add (msgs);
	}
	lua_close (L);
	return ret == 0;
}

//--------------------------------------------------------------------------------------------
string TScripting::luaGetTable (lua_State* L, int i) const
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
// javascript support
//--------------------------------------------------------------------------------------------
static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

//--------------------------------------------------------------------------------------------
void TScripting::jsBindEnv  (JSContext *cx, const STEnv& env)
{
	stringstream s; jsval result;
	for (TEnv::TEnvList::const_iterator i = env->begin(); i != env->end(); i++) {
		s << i->first << "=";
		if (i->second->isType<int>())			s << i->second->value(0);
		else if (i->second->isType<float>())	s << i->second->value(0.);
		else if (i->second->isType<string>())	s << '"' <<  i->second->value(string("")) << '"';
		else {
			ITLErr << i->first << " unknown variable type " << ITLEndl;
			break;
		}
		s << ";\n";
	}
	if (s.str().size()) {
		JSObject *script = JS_CompileScript(cx, JS_GetGlobalObject(cx), s.str().c_str(), s.str().size(), 0, 1);
		if (!script || !JS_ExecuteScript(cx, JS_GetGlobalObject(cx), script, &result))
			cerr << "can't export export variables to javascript" << endl;
	}
}

//--------------------------------------------------------------------------------------------
/* The ja	vascript error reporter callback. */
static void jsReportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    ITLErr <<  "javascript error line " << int(report->lineno) << ": " << message << ITLEndl;
}

//--------------------------------------------------------------------------------------------
string TScripting::jsGetResult (JSContext *cx, const jsval& val) const
{
	string out;
	if (JSVAL_IS_STRING (val))		out = JS_EncodeString (cx, JSVAL_TO_STRING(val));
	else if (JSVAL_IS_OBJECT (val) && !JSVAL_IS_NULL(val)) {
		JSObject * obj = JSVAL_TO_OBJECT(val);
		if (JS_IsArrayObject (cx, obj)) {
			jsuint length;
			if (JS_GetArrayLength(cx, obj, &length)) {
				jsval aval;
				for (jsuint i = 0; i<length; i++) {
					if (JS_GetElement(cx, obj, i, &aval)) {
						out += jsGetResult (cx, aval) + "\n";
					}
				}
			}
		}
	}	
	return out;
}

//--------------------------------------------------------------------------------------------
bool TScripting::jsEval (const char* script)
{
   /* JS variables. */
    JSRuntime *rt;
    JSContext *cx;
    JSObject  *global;

    /* Create a JS runtime. */
    rt = JS_NewRuntime(8L * 1024L * 1024L);
    if (rt == NULL) {
		ITLErr << "cannot create javascript runtime" << ITLEndl;
        return true;
	}

    /* Create a context. */
    cx = JS_NewContext(rt, 8192);
    if (cx == NULL) {
		ITLErr << "cannot create javascript context" << ITLEndl;
        return true;
	}

    JS_SetOptions(cx, JSOPTION_VAROBJFIX | JSOPTION_JIT | JSOPTION_METHODJIT);
    JS_SetVersion(cx, JSVERSION_LATEST);
    JS_SetErrorReporter(cx, jsReportError);

    /* Create the global object in a new compartment. */
    global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
    if (global == NULL) {
		ITLErr << "cannot create javascript global" << ITLEndl;
        return true;
	}

    /* Populate the global object with the standard globals, like Object and Array. */
    if (!JS_InitStandardClasses(cx, global)) {
		ITLErr << "cannot initialize javascript" << ITLEndl;
        return true;
	}

	jsBindEnv (cx, fEnv);
	JSObject *object = JS_CompileScript(cx, JS_GetGlobalObject(cx), script, strlen(script), 0, 1);
	jsval result;
	if (!object || !JS_ExecuteScript(cx, JS_GetGlobalObject(cx), object, &result))
		return false;

	string out = jsGetResult (cx, result);
	if (out.size()) {
		istringstream stream(out);
		ITLparser p (&stream);
		IMessageList* msgs = p.parse();
		if (msgs) add (msgs);
	}

    /* Cleanup. */
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
	return true;
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
