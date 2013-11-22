

#include <iostream>
#include <string>

/*
 * This define is for Windows only, it is a work-around for bug 661663.
 */
#ifdef _MSC_VER
# define XP_WIN
#endif

#include "jsapi.h"

using namespace std;

/* The class of the global object. */
static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    cerr <<  "line " << report->lineno << ": " << message << endl;
//	fprintf(stderr, "%s:%u:%s\n",
//            report->filename ? report->filename : "<no filename>",
//            (unsigned int) report->lineno,
//            message);
}

//========================================================================
static string jsprint (JSContext *cx, const jsval& val) {
	string out;
	if (JSVAL_IS_STRING (val))		out = JS_EncodeString (cx, JSVAL_TO_STRING(val));
	else if (JSVAL_IS_NULL (val))	out = "NULL";
	else if (JSVAL_IS_VOID (val))	out = "VOID";
	else if (JSVAL_IS_OBJECT (val) && !JSVAL_IS_NULL(val)) {
		JSObject * obj = JSVAL_TO_OBJECT(val);
		if (JS_IsArrayObject (cx, obj)) {
			jsuint length;
			if (JS_GetArrayLength(cx, obj, &length)) {
				jsval aval;
				for (jsuint i = 0; i<length; i++) {
					if (JS_GetElement(cx, obj, i, &aval)) {
						out += jsprint (cx, aval) + "\n";
					}
				}
			}
		}
//		else {
//			JSClass * c = JS_GetClass (obj);
//			cout << "object: " << c->name << endl;
//		}
	}
//	else cout << "unknown val" << endl;
	return out;
}

//========================================================================
int main(int argc, const char *argv[])
{
    /* JS variables. */
    JSRuntime *rt;
    JSContext *cx;
    JSObject  *global;

    /* Create a JS runtime. */
    rt = JS_NewRuntime(8L * 1024L * 1024L);
    if (rt == NULL)
        return 1;

    /* Create a context. */
    cx = JS_NewContext(rt, 8192);
    if (cx == NULL)
        return 1;
    JS_SetOptions(cx, JSOPTION_VAROBJFIX | JSOPTION_JIT | JSOPTION_METHODJIT);
    JS_SetVersion(cx, JSVERSION_LATEST);
    JS_SetErrorReporter(cx, reportError);

    /* Create the global object in a new compartment. */
    global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
    if (global == NULL)
        return 1;

    /* Populate the global object with the standard globals,
       like Object and Array. */
    if (!JS_InitStandardClasses(cx, global))
        return 1;

	cout << "myjs running " << endl;

    /* Your application code here. This may include JSAPI calls
       to create your own custom JS objects and run scripts. */
	jsval result;
	string js = "var a = new Array; \n \
	var b = new Array; \n \
	b[0] = 'bibi';\n\
	b[1] = 'bobo';\n\
	a[0] = 'tititi';\n\
	a[1] = 'toto';\n\
	a[2] = b;\n\
	a;";
	
	cout << "myjs execute : \n" << js << endl;
	JSObject *script = JS_CompileScript(cx, JS_GetGlobalObject(cx), js.c_str(), js.size(), 0, 1);
	if (!script || !JS_ExecuteScript(cx, JS_GetGlobalObject(cx), script, &result))
		cerr << " JS_ExecuteScript error" << endl;
	else 
		cout << jsprint (cx, result);

    /* Cleanup. */
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
    return 0;
}