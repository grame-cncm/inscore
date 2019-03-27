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
#include "TMessageEvaluator.h"
#include "IExprParser.h"
#include "IAppl.h"

#include "TSorter.h"
#include "TEnv.h"
#include "ITLparser.h"
#include "ITLError.h"

#include "TMaths.h"
#include "TWallClock.h"

using namespace std;
extern inscore::TScripting* gScripter;


namespace inscore
{

class IMessageList;
class IMessage;
class TEnv;

//--------------------------------------------------------------------------------------------
TScripting::TScripting(IAppl* root, bool execute)
	: fRoot(root), fExecute(execute)
{
#ifdef IBUNDLE
	fJavascriptEngine.Initialize();
	fJavascript = &fJavascriptEngine;
	fExecute = false;				// never execute a message in bundle environment
#else
	fJavascript = root->getJSEngine();
#endif
	fMessages = IMessageList::create();
	fEnv = TEnv::create();
}

TScripting::~TScripting()	{}

//--------------------------------------------------------------------------------------------
void TScripting::variable (const char* ident, const IMessage::argslist* values)		
{ 
	fEnv->clear( ident ); 
	for (IMessage::argslist::const_iterator i = values->begin(); i != values->end(); i++)
		fEnv->bind( ident, *i); 
}

//--------------------------------------------------------------------------------------------
void TScripting::variable (const char* ident, const SIMessageList* msgs)
{
	fEnv->clear( ident );
	fEnv->bind( ident, new IMsgParam<SIMessageList>(*msgs));
}

//--------------------------------------------------------------------------------------------
void TScripting::process (SIMessage& msg)
{
	if (msg->delay())
		inscore2::TSorter::schedule(msg, TWallClock::time());
	else if (fExecute)
		fRoot->processMsg(msg);
	else
		fMessages->list().push_back (msg);
}

//--------------------------------------------------------------------------------------------
void TScripting::process (SIMessageList& msgs)
{
	if (fExecute) {
		double time = TWallClock::time();
		for (size_t i=0; i<msgs->list().size(); i++) {
			if (msgs->list()[i]->delay())
				inscore2::TSorter::schedule(msgs->list()[i], time);
			else
				fRoot->processMsg(msgs->list()[i]);
		}
	}
	else
		fMessages->list().push_back (msgs->list());
}

//--------------------------------------------------------------------------------------------
// add the 'env' environment to the object
void TScripting::addEnv (const TScripting& sc)
{
	for (TEnv::TEnvList::const_iterator i = sc.fEnv->begin(); i != sc.fEnv->end(); i++) {
		variable ( i->first.c_str(), &(i->second));
	}
}

//--------------------------------------------------------------------------------------------
// called in case of parsing error
void TScripting::error(int line, int col, const char* s) const
{
	ITLErr << "line" << line << "col" << col << ":" << s << ITLEndl;
#if !defined(IBUNDLE) && !defined(PARSERTEST)	// no appl instance for the bundle tool nor in parser test
	if (fRoot) fRoot->error();
#endif
}


//--------------------------------------------------------------------------------------------
// javascript support
//--------------------------------------------------------------------------------------------
#if defined QTJSENGINE || IBUNDLE
bool TScripting::checkJavascript () const						{ return fJavascript != 0; }

static int countlines (const char* script)
{
	int n = 1;
	while (*script) {
		int c = *script++;
		if (c == 0x0D) {
			n++;
			if (*script == 0x0A) script++;
		}
		else if (c == 0x0A) n++;
	}
	return n;
}

SIMessageList TScripting::jsEval (const char* script, int lineno)
{
	if (fJavascript) {
		fJavascript->bindEnv (fEnv);
		string jsout;
		if (fJavascript->eval(lineno - countlines(script), script, jsout)) {
			if (jsout.size()) {
				istringstream stream(jsout);
				ITLparser p (&stream, 0, fRoot, false);
				p.parse();
				addEnv( p.fReader );
				return p.messages();
			}
		}
	}
	else ITLErr << "javascript is not available!" << ITLEndl;
	return 0;
}
#else
bool TScripting::checkJavascript () const						{ return false; }
SIMessageList TScripting::jsEval (const char* script, int lineno)
{
	ITLErr << "javascript is not available!" << ITLEndl;
	return 0;
}
#endif

//--------------------------------------------------------------------------------------------
#ifdef PARSERTEST
IMessage::argslist TScripting::resolve (const IMessage* ) const
#else
IMessage::argslist TScripting::resolve (const IMessage* msg) const
#endif
{
#ifdef PARSERTEST
	IMessage::argslist out;
	out.push_back (new inscore::IMsgParam<std::string>("unresolved"));
	return out;
#else
	EventContext env (0);
	TMessageEvaluator me;
	return me.evalMessage(msg, env);
#endif
}


//--------------------------------------------------------------------------------------------
bool TScripting::checkVar (IMessage::argslist& val, const char* var, int line) const
{
	if (val.empty()) {
		string pvar("$");
		pvar += var;
		ITLErr << "line " << line <<": warning! variable " <<  pvar << " is not defined." << ITLEndl;
		val.push_back(new IMsgParam<string>(pvar));
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------
IMessage::argslist TScripting::resolve (const char* var, int line) const
{
	IMessage::argslist val = fEnv->value (var);
	checkVar (val, var, line);
	return val;
}
//--------------------------------------------------------------------------------------------
IMessage::argslist TScripting::resolveinc (const char* var, bool post, int line)
{
	string svar (var);
	svar = post ? svar.substr(0, svar.size()-2) : svar.substr(2, string::npos);
	IMessage::argslist val = fEnv->value (svar);
	if (checkVar (val, svar.c_str(), line)) {
		TMaths m;
		IMessage::argslist* val1 = m.inc(val);
		variable (svar.c_str(), val1);
		if (!post) val = *val1;
		delete val1;
	}
	return val;
}

//--------------------------------------------------------------------------------------------
IMessage::argslist TScripting::resolvedec (const char* var, bool post, int line)
{
	string svar (var);
	svar = post ? svar.substr(0, svar.size()-2) : svar.substr(2, string::npos);
	IMessage::argslist val = fEnv->value (svar);
	if (checkVar (val, svar.c_str(), line)) {
		TMaths m;
		IMessage::argslist* val1 = m.dec(val);
		variable (svar.c_str(), val1);
		if (!post) val = *val1;
		delete val1;
	}
	return val;
}



//--------------------------------------------------------------------------------------------
//          Expression support
//--------------------------------------------------------------------------------------------

Sbaseparam* TScripting::parseExpr(std::string definition, int lineOffset, int columnOffset) const {

	SIExpression expr;

	if(!IExprParser::parseExpression(definition, expr, this, lineOffset-1, columnOffset-1)){
		expr = IExpression::create(definition, 0);		//define an invalid expression containing its definition
	}

	IMsgParam<SIExpression>* param = new IMsgParam<SIExpression>(expr);
	return new Sbaseparam(param);
}

} // namespace
