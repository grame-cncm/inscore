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
#include <TLua.h>
#ifdef V8ENGINE
#include <TV8Js.h>
#elif defined QTJSENGINE
#include <TQtJs.h>
#elif defined ITLBUNDLE
#include "TDummyJs.h"
#endif
#include "ExprFactory.h"

#include "IMessage.h"
#include "smartpointer.h"


typedef void* yyscan_t;

namespace inscore 
{

class IMessageList;
class IMessage;
class baseparam;
typedef libmapping::SMARTP<baseparam> Sbaseparam;

class TEnv;
typedef libmapping::SMARTP<TEnv> STEnv;
#ifdef V8ENGINE
typedef TV8Js				TJSEngine;
#elif defined QTJSENGINE
typedef TQtJs				TJSEngine;
#elif defined ITLBUNDLE
typedef itlbundle::TDummyJs	TJSEngine;
#else
typedef void*		TJSEngine;
#endif

//--------------------------------------------------------------------------------------------
class TScripting 
{
	TJSEngine*			fJavascript;
	TLua*				fLua;
	SIMessageList		fMessages;

	protected:
		STEnv			fEnv;
		// add the 'env' environment to the object
		void	addEnv (const TScripting& env);

	public:
		yyscan_t fScanner;

				 TScripting(TJSEngine* js, TLua* lua = 0);
		virtual ~TScripting();

		void	add			(SIMessage& msg);
		void	add			(SIMessageList& msg);
		void	variable	(const char* ident, const IMessage::argslist* values);
		void	variable	(const char* ident, const SIMessageList* resolvemsgs);

		SIMessageList	luaEval		(const char* script);
		SIMessageList	jsEval		(const char* script, int lineno);
		bool			checkLua () const;
		bool			checkJavascript () const;

		IMessage::argslist		resolve	(const char* var, const char * defaultVal=0) const;
		IMessage::argslist		resolve	(const IMessage* var) const;
		const SIMessageList&	messages() const { return fMessages; }


		Sbaseparam* parseExpr(std::string definition, int lineOffset = 0, int columnOffset = 0) const;

};


} // namespace

#endif
