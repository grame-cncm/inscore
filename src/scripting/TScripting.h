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
#include <TLua.h>
# include <TV8Js.h>
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
typedef TV8Js		TJSEngine;


//--------------------------------------------------------------------------------------------
class TScripting 
{
	TJSEngine*			fJavascript;
	TLua*				fLua;
	SIMessageList		fMessages;
	STEnv				fEnv;

	public:	
		yyscan_t fScanner;

				 TScripting(TJSEngine* js, TLua* lua = 0);
		virtual ~TScripting();

		void	add			(SIMessage& msg);
		void	add			(SIMessageList& msg);
		void	variable	(const char* ident, const IMessage::argslist* values);
		void	variable	(const char* ident, const SIMessageList* msgs);

		SIMessageList	luaEval		(const char* script);
		SIMessageList	jsEval		(const char* script, int lineno);
		bool			checkLua () const;
		bool			checkJavascript () const;

		IMessage::argslist		resolve	(const char* var, const char * defaultVal=0);
		IMessage::argslist		resolve	(const IMessage* var);
		const SIMessageList&	messages() const { return fMessages; }
};

} // namespace

#endif
