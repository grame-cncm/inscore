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

#include "TV8Js.h"
#include "TEnv.h"
#include "OSCStream.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

#ifdef V8ENGINE

class V8Disposer {
	public:
		virtual ~V8Disposer() {	v8::V8::Dispose(); }
};
static V8Disposer gV8Disposer;

//--------------------------------------------------------------------------------------------
/* tools for v8 */
static const char* ToCString(const v8::String::Utf8Value& value) { return *value ? *value : ""; }

// array values are separated by ',' which produces syntax errors
// ArrayString2IString replace the ',' by ' ' (space)
static void ArrayString2IString(const char* str, string& out) 
{
	bool indquote = false;
	bool inquote  = false;
	char prev = 0;
	while (*str) {
		char c = *str++;
		switch (c) {
			case ',':
				if (!inquote && !indquote) c = ' ';
				break;
			case '\'':	
				if (prev != '\\') inquote = !inquote;
				break;
			case '"':
				if (prev != '\\') indquote = !indquote;
				break;
		}
		out += c;
		prev = c;
	}
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
static v8::Handle<v8::Value> Print(const v8::Arguments& args) 
{
	bool first = true;
	cout << "javascript: ";
	oscout << OSCStart("javascript:");

	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		if (first)
			first = false;
		else cout << " ";
		v8::String::Utf8Value str(args[i]);
		const char* cstr = ToCString(str);
		cout << cstr;
		oscout << cstr;
	}
	cout << endl;
	oscout << OSCEnd();
	return v8::Undefined();
}

static v8::Handle<v8::Value> Version(const v8::Arguments& args) {
  return v8::String::New(v8::V8::GetVersion());
}

//int	TV8Js::fRefCount = 0;

//--------------------------------------------------------------------------------------------
/* The javascript error reporter callback. */
void TV8Js::ReportException(v8::TryCatch* try_catch) const
{
	v8::HandleScope handle_scope;
	v8::String::Utf8Value exception(try_catch->Exception());
	const char* exception_string = ToCString(exception);
	v8::Handle<v8::Message> message = try_catch->Message();
	if (message.IsEmpty()) {
		// V8 didn't provide any extra information about this error; just print the exception.
		ITLErr <<  "javascript error: " << exception_string << ITLEndl;
	} 
	else {
		ITLErr <<  "javascript error line " << message->GetLineNumber() + fLineOffset << ": " << exception_string << ITLEndl;
		// Print line of source code.
		v8::String::Utf8Value sourceline(message->GetSourceLine());
		const char* sourceline_string = ToCString(sourceline);
		ITLErr <<  "javascript error context: " << sourceline_string << ITLEndl;
	}
}

//--------------------------------------------------------------------------------------------
v8::Persistent<v8::Context> TV8Js::CreateV8Context() 
{
	v8::HandleScope handle_scope;
	// Create a template for the global object.
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	// Bind the global 'print' function to the C++ Print callback.
	global->Set(v8::String::New("print"), v8::FunctionTemplate::New(Print));
	// Bind the 'version' function
	global->Set(v8::String::New("version"), v8::FunctionTemplate::New(Version));
	return v8::Context::New(NULL, global);
}

//--------------------------------------------------------------------------------------------
TV8Js::TV8Js()
{
//	if (!fRefCount) {
		fContext = CreateV8Context();
		if (!fContext.IsEmpty()) {
			fContext->Enter();
//			fRefCount++;
		}
		else  ITLErr << "Error creating javascript context" << ITLEndl;
//	}
}

TV8Js::~TV8Js()
{ 
	if (!fContext.IsEmpty()) { // && !--fRefCount) {
		fContext->Exit();
		fContext.Dispose();
	}
}

//--------------------------------------------------------------------------------------------
void TV8Js::bindEnv  (const STEnv& env)
{
	stringstream s;
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
		string out;
		if (!eval (0, s.str().c_str(), out))
			ITLErr << "can't export export variables to javascript" << ITLEndl;
	}
}

//--------------------------------------------------------------------------------------------
void TV8Js::getResult (const v8::Handle<v8::Value>& result, std::string& outStr) const
{
	v8::HandleScope handle_scope;
	v8::String::Utf8Value str(result);
	const char* ptr = ToCString(str);
	if (result->IsArray()) {
		ArrayString2IString (ptr, outStr);
	}
	else outStr += ptr;
}

//--------------------------------------------------------------------------------------------
// Executes a string within the current v8 context.
bool TV8Js::eval(int line, const char* jscode, std::string& outStr)
{
	fLineOffset = 0; //line;
	v8::HandleScope handle_scope;
	v8::TryCatch try_catch;
	v8::Local<v8::String> name(v8::String::New("(INScore)"));
	v8::Handle<v8::String> source(v8::String::New(jscode));
	v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
	if (script.IsEmpty()) {
		ReportException(&try_catch);
		return false;
	} 
	else {
		v8::Handle<v8::Value> result = script->Run();
		if (result.IsEmpty()) {
			assert(try_catch.HasCaught());
			ReportException(&try_catch);
			return false;
		} 
		else {
			assert(!try_catch.HasCaught());
			if (!result->IsUndefined()) {
				getResult (result, outStr);
			}
			return true;
		}
	}
}

//--------------------------------------------------------------------------------------------
// Reset teh current javascript engine (actually allocate a new one
void TV8Js::Initialize  () 
{ 
	fContext->Exit();
	fContext.Dispose();
	fContext = CreateV8Context();
	if (!fContext.IsEmpty())
		fContext->Enter();
//	fContext->Exit();		// exit the current context
//	fContext->Enter();		// and reenter a new one
}

#else
//--------------------------------------------------------------------------------------------
TV8Js::TV8Js() {}
TV8Js::~TV8Js() {}
void TV8Js::bindEnv  (const STEnv& env) {}
void TV8Js::Initialize  () {}

bool TV8Js::eval (int line, const char* script, std::string& outStr)
{
	ITLErr << "javascript not available!" << ITLEndl;
	return true;
}
#endif

} // namespace
