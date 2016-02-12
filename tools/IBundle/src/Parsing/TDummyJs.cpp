/*
  INScore Project

  Copyright (C) 2009,2016  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/
#include "TDummyJs.h"
#include "TEnv.h"

using namespace std;

namespace ibundle{

static const char* kReserved[] = {
	"_externals_",
	"_printCallback_",
	"_postCallback_",
	"print",
	"post",
	"version",
	"readfile"
};
enum { kExternals, kPrintCallback, kPostCallback, kPrint, kPost, kVersion, kReadfile, kEndExternals };

//--------------------------------------------------------------------------------------------
// check for  conflicts with reserved tokens
static bool checkConficts (const string& var)
{
	for (int i = 0; i < kEndExternals; i++)
		if (var == kReserved[i]) return true;
	return false;
}

TDummyJs::TDummyJs() {}
TDummyJs::~TDummyJs() {}

//--------------------------------------------------------------------------------------------
void TDummyJs::Initialize  () {fVars="";}

bool TDummyJs::eval (int /*line*/, const char* script, std::string& outStr)
{
	std::string s = fVars + "\n";
	s += script;

	size_t it = s.find('"');
	while(it < s.size()){
		s.insert(it, "\\");
		it += 2;
		if(it>=s.size() && it < 2)
			break;
		it = s.find('"', it);
	}

	outStr = "/ITL/bundle js \""+s+"\";";
	return true;
}

void TDummyJs::setRootPath(const char *path)
{
	fRootPath = std::string(path);
}

bool TDummyJs::bindEnv  (stringstream& s, const string& name, const inscore::IMessage::argPtr& val)
{
	if (val->isType<int>()) s << val->value<int>(0);
	else if (val->isType<float>()) s << val->value<float>(0.);
	else if (val->isType<string>()) s << '"' <<  val->value(string("")) << '"';
	else if (val->isType<inscore::SIMessageList>()) {
		inscore::SIMessageList l = val->value<inscore::SIMessageList>(0);
		s << "'(";
		l->list().printMsgs(s);
		s << ")'";
		return true;
	}
	else {
		cerr << name << ": unknown variable type" << endl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------
void TDummyJs::bindEnv  (stringstream& s, const string& name, const inscore::IMessage::argslist& values)
{
	if (values.size() == 0) return;
	if (!checkConficts(name)) {
		stringstream tmp;
		tmp << name << "=";
		size_t n = values.size();
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
	else {
		string msg = "javascript: variable '" + name + "' conflicts with reserved token";
		cerr << msg << endl;
	}
}

//--------------------------------------------------------------------------------------------
void TDummyJs::bindEnv  (const inscore::STEnv& env)
{
	stringstream s;
	for (inscore::TEnv::TEnvList::const_iterator i = env->begin(); i != env->end(); i++) {
		bindEnv (s, i->first, i->second);
	}
	if (s.str().size()) {
		fVars = s.str();
	}
}

} // End namespace
