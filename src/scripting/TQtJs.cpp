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

#include "CustomScripts.h"

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

	// Javascript wrapper for variable argument number functions.
	QJSValue print = fEngine->evaluate("function() { printCallback(Array.prototype.slice.apply(arguments));}");
	fEngine->globalObject().setProperty("print", print);
	QJSValue post = fEngine->evaluate("function() { postCallback(Array.prototype.slice.apply(arguments));}");
	fEngine->globalObject().setProperty("post", post);

	// create object with method callback
	CustomScripts * scriptObject = new CustomScripts;
	QJSValue scriptTest = fEngine->newQObject(scriptObject);
	QJSValue versionFunc =  scriptTest.property("version");
	QJSValue readFileFunc =  scriptTest.property("readfile");
	QJSValue printFunc =  scriptTest.property("print");
	QJSValue postFunc =  scriptTest.property("post");

	// Expose C++ functions
	fEngine->globalObject().setProperty("version", versionFunc);
	fEngine->globalObject().setProperty("readfile", readFileFunc);
	fEngine->globalObject().setProperty("printCallback", printFunc);
	fEngine->globalObject().setProperty("postCallback", postFunc);
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
