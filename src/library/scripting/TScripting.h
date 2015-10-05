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
#ifdef V8ENGINE
#include <TV8Js.h>
#elif defined QTJSENGINE
#include <TQtJs.h>
#endif
#include "IMessage.h"
#include "smartpointer.h"

#ifdef EXPRESSIONTEST
#include "IExpressionFactory.h"
#endif

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
typedef TV8Js		TJSEngine;
#elif defined QTJSENGINE
typedef TQtJs		TJSEngine;
#else
typedef void*		TJSEngine;
#endif

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

#ifdef EXPRESSIONTEST

private:
        ExprFactory* fExprFactory;
public:
		/*!
		 * \brief create a message param that encapsulate a smart pointer on an argument IExprArg with the corresponding type artT
		 * \param argument to encapsulate
		 * \return a simple message param
		 */
		template<typename argT> Sbaseparam* createArg(argT arg){
            SIExprArgbase argB = fExprFactory->createArg<argT>(arg);
		    IMsgParam<SIExprArgbase>* param = new IMsgParam<SIExprArgbase>(argB);
		    return new Sbaseparam(param);
		}

        /*!
        * \brief surcharge createArg to accept parser object
        * \param pointer on the arg string
        * \return a simple message param
        */
        template<typename argT> Sbaseparam* createArg(std::string* arg){
            argT param(*arg);
            return createArg<argT>(param);
        }


        /*!
         * \brief encapsulate an expression into a valid expression argument
         * \return a simple Sbaseparam
         */
        Sbaseparam* createArgFromExpr(Sbaseparam* param);

		/*!
		 * \brief create a message param that contains an Expression Operator
		 * \param operatorName: the name of the operator
		 * \param arg1: first argument passed to the operator
		 * \param arg2: second argument passed to the operator
		 * \return a simple message param
		 */
        Sbaseparam* createExpr(std::string operatorName, Sbaseparam* param1, Sbaseparam* param2);
        Sbaseparam* createExpr(std::string* operatorName, Sbaseparam* param1, Sbaseparam* param2){return createExpr(*operatorName, param1, param2);}


        /*!
         * \brief dig into a Sbaseparam to extract the smart pointer on IExprArgbase
         * \param the base param containing the argument
         * \return the arguments
		 */
        static SIExprArgbase argFromParam(Sbaseparam* param);

        /*!
         * \brief dig into a Sbaseparam to extract the smart pointer on IExpression (for testing purpose)
         * \param the base param containing the expression
         * \return the IExpression
         */
        static SIExpression exprFromParam(const Sbaseparam* param);

        /*!
         * \brief construct an empty arg, used when syntax  errors are found
         * \return an empty arg: <std::string> ""
         */
        inline Sbaseparam* emptyArg(){
            return createArg<std::string>("");
        }

#endif
};


} // namespace

#endif
