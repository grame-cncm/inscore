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
#include <fstream>
#include <sstream>

#include <QDebug>

#include "TQtJs.h"
#include "TEnv.h"
#include "IAppl.h"
#include "OSCStream.h"
#include "INScore.h"

#ifdef NO_OSCSTREAM
# define ITLErr		cerr
# define ITLEndl	endl
#else
#include "ITLError.h"
#endif

using namespace std;

namespace inscore
{

#ifdef QTJSENGINE


//--------------------------------------------------------------------------------------------
static std::string makeAbsolutePath( const char* file )
{
	return IAppl::absolutePath (file);
}

//--------------------------------------------------------------------------------------------
/* tools for v8 */
/*
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

// The callback that is invoked by v8 whenever the JavaScript 'readfile'
// function is called. Read the file and returns its content as a string.
static v8::Handle<v8::Value> ReadFile(const v8::Arguments& args)
{
	if (args.Length() != 1) {
		ITLErr << "javascript : readfile invoked with incorrect arguments" << ITLEndl;
		return v8::Undefined();
	}
	v8::String::Utf8Value str(args[0]);
	std::string path = makeAbsolutePath (ToCString(str));
	ifstream file (path.c_str());
	if (!file.is_open()) {
		ITLErr << "javascript : readfile can't open file " << path << ITLEndl;
		return v8::Undefined();
	}
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
    char * buffer = new char [length];
    // read data as a block:
	file.read (buffer,length);
	v8::Local<v8::String> content = v8::String::New(buffer);
	delete[] buffer;
	return content;
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
static v8::Handle<v8::Value> Print(const v8::Arguments& args) 
{
	bool first = true;
	cout << "javascript: ";
#ifndef NO_OSCSTREAM
	oscout << OSCStart("javascript:");
#endif
	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		if (first)
			first = false;
		else cout << " ";
		v8::String::Utf8Value str(args[i]);
		const char* cstr = ToCString(str);
		cout << cstr;
#ifndef NO_OSCSTREAM
		oscout << cstr;
#endif
	}
	cout << endl;
#ifndef NO_OSCSTREAM
	oscout << OSCEnd();
#endif
	return v8::Undefined();
}

// The callback that is invoked by v8 whenever the JavaScript 'send'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
static v8::Handle<v8::Value> PostMsg(const v8::Arguments& args)
{
	if (! args.Length()) return v8::Undefined();

	INScore::MessagePtr msg = INScore::newMessage ();
	std::string address;
	const char* argErr = "v8::PostMsg: unknown arg type";
	const char* adrErr = "v8::PostMsg: incorrect OSC address";
	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		if (i==0) {
			if (args[i]->IsString()) {
				v8::String::Utf8Value str(args[i]);
				address = ToCString(str);
			}
			else {
				cerr << adrErr << endl;
#ifndef NO_OSCSTREAM
				oscerr << adrErr;
#endif
				return v8::Undefined();
			}

		}
		else {
			if (args[i]->IsString()) {
				v8::String::Utf8Value str(args[i]->ToString());
				INScore::add(msg, ToCString(str));
			}
			else if (args[i]->IsInt32()) {
				INScore::add(msg, args[i]->Int32Value());
			}
			else if (args[i]->IsUint32()) {
				INScore::add(msg, int(args[i]->Uint32Value()));
			}
			else if (args[i]->IsNumber()) {
				INScore::add(msg, float(args[i]->NumberValue()));
			}
			else {
				cerr << argErr << endl;
#ifndef NO_OSCSTREAM
				oscerr << argErr;
#endif
			}
		}
	}
	INScore::delayMessage(address.c_str(), msg);	// post the message for delayed processing
	return v8::Undefined();
}

static v8::Handle<v8::Value> Version(const v8::Arguments& args) {
  return v8::String::New(v8::V8::GetVersion());
}
*/

//--------------------------------------------------------------------------------------------
// extern functions support
//--------------------------------------------------------------------------------------------
class jsversion : public QObject {
	public:
				 jsversion() {}
		virtual ~jsversion() {}
	
	const char* operator ()(void)	{
		return "1.00";
	}
};


//--------------------------------------------------------------------------------------------
void TQtJs::setRootPath	(const char* path)
{
	fRootPath = path;
}

//--------------------------------------------------------------------------------------------
TQtJs::TQtJs()	: fEngine(0) { Initialize(); }
TQtJs::~TQtJs()	{ delete fEngine; }

//--------------------------------------------------------------------------------------------
// Reset the current javascript engine (actually allocate a new one)
void TQtJs::Initialize  ()
{ 
	delete fEngine;
	fEngine = new QJSEngine;
//	fEngine->globalObject().setProperty("function version() { return \"1.00\"}" );

//	jsversion* vers = new jsversion();
//	QJSValue vObject = fEngine->newQObject(vers);
//	fEngine->globalObject().setProperty("version", vObject);
//	string out;
//	eval(1, "version()", out);
}

//--------------------------------------------------------------------------------------------
bool TQtJs::bindEnv  (stringstream& s, const string& name, const IMessage::argPtr& val)
{
	if (val->isType<int>())			s << val->value(0);
	else if (val->isType<float>())	s << val->value(0.);
	else if (val->isType<string>())	s << '"' <<  val->value(string("")) << '"';
	else {
		ITLErr << name << ": unknown variable type" << ITLEndl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------
void TQtJs::bindEnv  (stringstream& s, const string& name, const IMessage::argslist& values)
{
	if (values.size() == 0) return;

	stringstream tmp;
	tmp << name << "=";
	unsigned int n = values.size();
	if (n == 1) {
		if (!bindEnv (tmp, name, values[0])) return;
	}
	else {
		tmp << "[";
		for (unsigned int i=0; i<n;) {
			if (!bindEnv (tmp, name, values[i])) return;
			i++;
			if (i<n) tmp << ", ";
		}
		tmp << "]";
	}
	s << tmp.str() << "\n";
}

//--------------------------------------------------------------------------------------------
void TQtJs::bindEnv  (const STEnv& env)
{
	stringstream s;
	for (TEnv::TEnvList::const_iterator i = env->begin(); i != env->end(); i++) {
		bindEnv (s, i->first, i->second);
	}
	if (s.str().size()) {
		string out;
		if (!eval (0, s.str().c_str(), out))
			ITLErr << "can't export export variables to javascript" << ITLEndl;
	}
}

//--------------------------------------------------------------------------------------------
void TQtJs::getResult (const QString& result, std::string& outStr) const
{
	outStr += result.toUtf8().constData();
}

//--------------------------------------------------------------------------------------------
// Executes a string within the current v8 context.
bool TQtJs::eval(int line, const char* jscode, std::string& outStr)
{
	fLineOffset = line;
	outStr = "";

	QString program (jscode);
	QJSValue result = fEngine->evaluate(program, "", line);

	if (result.isString()) {
		getResult (result.toString(), outStr);
	}
	else if (result.isArray()) {
		QVariant v = result.toVariant();
		if (v.canConvert<QList<QVariant> >()) {
			QList<QVariant> list = v.toList();
			QList<QVariant>::const_iterator it;
			for(it = list.begin(); it != list.end(); it++) {
				if (it->canConvert<QString> ()) {
					getResult (it->toString(), outStr);
				}
			}
		}
	}
	else if (result.isError()) {
//		ITLErr <<  "javascript error " << result.toString().toUtf8().constData() << ITLEndl;
		cerr <<  "javascript error " << result.toString().toUtf8().constData() << endl;
		return false;
	}
	return true;
}

#else
//--------------------------------------------------------------------------------------------
TQtJs::TQtJs() {}
TQtJs::~TQtJs() {}
void TQtJs::bindEnv  (const STEnv& env) {}
void TQtJs::Initialize  () {}

bool TQtJs::eval (int line, const char* script, std::string& outStr)
{
	ITLErr << "javascript not available!" << ITLEndl;
	return true;
}
#endif

} // namespace
