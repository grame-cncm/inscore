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

#include "TMozillaJs.h"
#include "TEnv.h"
#include "OSCStream.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

#ifdef JAVASCRIPT

static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

//--------------------------------------------------------------------------------------------
/* The javascript error reporter callback. */
static void jsReportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    ITLErr <<  "javascript error line " << int(report->lineno) << ": " << message << ITLEndl;
}

//--------------------------------------------------------------------------------------------
TMozillaJs::TMozillaJs() : fRuntime(0), fContext(0), fGlobal(0)
{
    /* Create a JS runtime. */
    fRuntime = JS_NewRuntime(8L * 1024L * 1024L);
    if (fRuntime == NULL) {
		ITLErr << "cannot create javascript runtime" << ITLEndl;
        return;
	}

    /* Create a context. */
    fContext = JS_NewContext(fRuntime, 8192);
    if (fContext == NULL) {
		ITLErr << "cannot create javascript context" << ITLEndl;
        return;
	}

    JS_SetOptions(fContext, JSOPTION_VAROBJFIX | JSOPTION_JIT | JSOPTION_METHODJIT);
    JS_SetVersion(fContext, JSVERSION_LATEST);
    JS_SetErrorReporter(fContext, jsReportError);


    /* Create the global object in a new compartment. */
    fGlobal = JS_NewCompartmentAndGlobalObject(fContext, &global_class, NULL);
    if (fGlobal == NULL) {
		ITLErr << "cannot create javascript global" << ITLEndl;
        return;
	}

    /* Populate the global object with the standard globals, like Object and Array. */
    if (!JS_InitStandardClasses(fContext, fGlobal)) {
		ITLErr << "cannot initialize javascript" << ITLEndl;
	}
}

TMozillaJs::~TMozillaJs()
{ 
    JS_DestroyContext (fContext);
    JS_DestroyRuntime (fRuntime);
    JS_ShutDown ();
}

//--------------------------------------------------------------------------------------------
void TMozillaJs::bindEnv  (const STEnv& env)
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
		JSObject *script = JS_CompileScript(fContext, JS_GetGlobalObject(fContext), s.str().c_str(), s.str().size(), 0, 1);
		if (!script || !JS_ExecuteScript(fContext, JS_GetGlobalObject(fContext), script, &result))
			ITLErr << "can't export export variables to javascript" << ITLEndl;
	}
}

//--------------------------------------------------------------------------------------------
void TMozillaJs::getResult (const jsval& val, std::string& out) const
{
	if (JSVAL_IS_STRING (val))		out += JS_EncodeString (fContext, JSVAL_TO_STRING(val));
	else if (JSVAL_IS_OBJECT (val) && !JSVAL_IS_NULL(val)) {
		JSObject * obj = JSVAL_TO_OBJECT(val);
		if (JS_IsArrayObject (fContext, obj)) {
			jsuint length;
			if (JS_GetArrayLength(fContext, obj, &length)) {
				jsval aval;
				for (jsuint i = 0; i<length; i++) {
					if (JS_GetElement(fContext, obj, i, &aval)) {
						getResult (aval, out );
						out += "\n";
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
bool TMozillaJs::eval (const char* script, std::string& outStr)
{
	JSObject *object = JS_CompileScript(fContext, JS_GetGlobalObject(fContext), script, strlen(script), 0, 1);
	jsval result;
	if (!object || !JS_ExecuteScript(fContext, JS_GetGlobalObject(fContext), object, &result))
		return false;
	getResult (result, outStr);
	return true;
}
#else
//--------------------------------------------------------------------------------------------
TMozillaJs::TMozillaJs() {}
TMozillaJs::~TMozillaJs() {}

bool TMozillaJs::eval (const char* script)
{
	ITLErr << "javascript not available!" << ITLEndl;
	return true;
}
#endif

} // namespace
