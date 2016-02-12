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
#ifndef EVALUATOR
#define EVALUATOR

#include <string>

namespace inscore{

///Macro defining new string-like types usable in templates (they are not assimilate to template on the contrary to typedef std::string type; ).
struct specializedString{
        std::string string;
        specializedString(std::string s=""){string = s;}
        operator std::string() const {return string;}
		bool operator== ( const specializedString& other) const {return string == other.string;}
};
#define STRING_TYPE(typeName) struct typeName: specializedString{ typeName(std::string s=""):specializedString(s){} };


// Custom String-like type definition
STRING_TYPE(filepath)
STRING_TYPE(itladdress)
STRING_TYPE(iexpression)


class IExprArgBase;
class IExprOperator;

/*!
 * \brief Interface defining an evaluator: it can evaluate specific arguments or an entire expression.
 */
class evaluator{
public:

	/*!
	 * \brief eval evaluate an evaluable object
	 * \param arg the argument to evaluate
	 * \param exprArg the evaluated node, use as a context for the evaluator
	 * \return the evaluated value
	 */
	virtual const std::string eval(IExprOperator* arg, IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const std::string& arg, IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const filepath& arg, IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const itladdress& arg, IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const iexpression& arg, IExprArgBase* exprArg=0)=0;

};

/*!
 * \brief Unlike evaluator, constEvaluator can't modify expressions trees (apart from the evaluated values).
 */
class constEvaluator: public evaluator{
public:

	/*!
	 * \brief eval evaluate an evaluable object
	 * \param arg the argument to evaluate
	 * \param exprArg the evaluated node, use as a context for the evaluator
	 * \return the evaluated value
	 */
	virtual const std::string eval(const IExprOperator* arg, const IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const filepath& arg, const IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const itladdress& arg, const IExprArgBase* exprArg=0)=0;
	virtual const std::string eval(const iexpression& arg, const IExprArgBase* exprArg=0)=0;

	/*!
	 * \brief eval evaluate an evaluable object, the default implementation use the equivalent const eval method.
	 * \param arg the value to evaluate
	 * \param exprArg the evaluated node, use as a context for the evaluator
	 * \return the evaluated value
	 */
	const std::string eval(IExprOperator* arg, IExprArgBase* exprArg=0)		{return eval(arg, (const IExprArgBase*)exprArg);}
	const std::string eval(const std::string& arg, IExprArgBase* exprArg=0)	{return eval(arg, (const IExprArgBase*)exprArg);}
	const std::string eval(const filepath& arg, IExprArgBase* exprArg=0)	{return eval(arg, (const IExprArgBase*)exprArg);}
	const std::string eval(const itladdress& arg, IExprArgBase* exprArg=0)	{return eval(arg, (const IExprArgBase*)exprArg);}
	const std::string eval(const iexpression& arg, IExprArgBase* exprArg=0)	{return eval(arg, (const IExprArgBase*)exprArg);}

};

/*!
 * \brief Interface for evaluable class (visitable by an evaluator and a constEvaluator in the visitor design pattern logic)
 */
class evaluable{
public:
	virtual std::string accept(evaluator* e)=0;
	virtual std::string accept(constEvaluator* e) const =0;
};

}
#endif // EVALUATOR

