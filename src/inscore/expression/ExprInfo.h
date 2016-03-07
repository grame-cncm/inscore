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
#ifndef EXPRINFO_H
#define EXPRINFO_H

//#include <selinux/context.h>
#include <set>

#include "IExpression.h"

namespace inscore {

/*!
 * \brief Evaluate an IExpression and return a list of the ressources used in it
 */
class ExprFileDependency: public constEvaluator{

public:

	static std::set<std::string> fileDependency(const IExpression* expr);

	const std::string eval(const std::string& , const IExprArgBase* =0){return "";}
	const std::string eval(const IExprOperator* arg , const IExprArgBase* =0);
	const std::string eval(const filepath& arg, const IExprArgBase* =0);
	const std::string eval(const itladdress &, const IExprArgBase* =0){return "";}
	const std::string eval(const iexpression &, const IExprArgBase* =0){return "";}

protected:
	std::set<std::string> fDependency;
};

//____________________________________________________________________
// ------------------------------------------------------------------
/*!
 * \brief Search for parameters and replace them with a new value
 */
class ExprSearchReplacebase: public evaluator{

public:
	virtual const std::string eval(IExprOperator *arg,	IExprArgBase *){
		arg->arg1()->accept(this);
		arg->arg2()->accept(this);
		return "";
	}
	virtual const std::string eval(const filepath &,	IExprArgBase *){return "";}
	virtual const std::string eval(const std::string &,	IExprArgBase *){return "";}
	virtual const std::string eval(const itladdress &,	IExprArgBase *){return "";}
	virtual const std::string eval(const iexpression &,	IExprArgBase *){return "";}

protected:
	ExprSearchReplacebase(): evaluator() {}

};

template <typename T>
class ExprSearchReplace: public ExprSearchReplacebase{
	const T fSearch, fReplace;

public:
	static void searchReplace(SIExpression &expression, T search, T replace);
	virtual const std::string eval(const T& value, IExprArgBase *exprArg);

protected:
	ExprSearchReplace(T search, T replace): ExprSearchReplacebase(), fSearch(search), fReplace(replace){}

};

//____________________________________________________________________
// ------------------------------------------------------------------

/*!
 * \brief The ExprInfo class defines static method to retreive information from an expression tree
 */
class ExprInfo
{
public:
	static std::set<std::string> fileDependency(const SIExpression& expr);
	static void fileReplace(SIExpression &expr, const filepath& search, const filepath& replace);

	template <typename T>
	static void searchAndReplace(SIExpression &expr, const T& search, const T& replace)	{ExprSearchReplace<T>::searchReplace(expr, search, replace);}

};


} // End namespace

#endif // EXPRINFO_H
