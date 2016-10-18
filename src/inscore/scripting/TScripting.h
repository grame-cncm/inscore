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

#ifndef __TScripting__
#define __TScripting__

#include <stack>
#include <functional>

#ifdef QTJSENGINE
#include <TQtJs.h>
#elif defined IBUNDLE
#include "TDummyJs.h"
#endif
#include "ExprFactory.h"

#include "IMessage.h"
#include "smartpointer.h"


typedef void* yyscan_t;

namespace inscore 
{

class IAppl;
class IMessageList;
class IMessage;
class baseparam;
typedef libmapping::SMARTP<baseparam> Sbaseparam;

class TEnv;
typedef libmapping::SMARTP<TEnv> STEnv;
#ifdef QTJSENGINE
typedef TQtJs				TJSEngine;
#elif defined IBUNDLE
typedef ibundle::TDummyJs	TJSEngine;
#else
typedef void*		TJSEngine;
#endif

//--------------------------------------------------------------------------------------------
class TScripting 
{
#ifdef IBUNDLE
	inscore::TJSEngine fJavascriptEngine;		// a javscript engine for the bundle tool
#endif
	IAppl*				fRoot;
	TJSEngine*			fJavascript;
	SIMessageList		fMessages;
	bool				fExecute;

	bool checkVar	(IMessage::argslist& val, const char* var, int line) const;

	protected:
		STEnv			fEnv;
		// add the 'env' environment to the object
		void	addEnv (const TScripting& env);

	public:
		yyscan_t fScanner;

				 TScripting(IAppl* root, bool execute=true);
		virtual ~TScripting();

		void	process		(SIMessage& msg);
		void	process		(SIMessageList& msg);
		void	variable	(const char* ident, const IMessage::argslist* values);
		void	variable	(const char* ident, const SIMessageList* resolvemsgs);

		SIMessageList	jsEval		(const char* script, int lineno);
		bool		checkJavascript () const;
		void		error(int line, int col, const char* s) const;

		IMessage::argslist		resolve	(const char* var, int line) const;
		IMessage::argslist		resolveinc	(const char* var, bool post, int line);
		IMessage::argslist		resolvedec	(const char* var, bool post, int line);
		IMessage::argslist		resolve	(const IMessage* var) const;
		const SIMessageList&	messages() const { return fMessages; }


		Sbaseparam* parseExpr(std::string definition, int lineOffset = 0, int columnOffset = 0) const;
};


} // namespace

#endif
