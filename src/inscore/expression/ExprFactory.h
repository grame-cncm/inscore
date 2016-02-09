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
#ifndef EXPRESSIONFACTORY_H
#define EXPRESSIONFACTORY_H

#include <string>
#include <unordered_map>

#include "IExpression.h"

namespace inscore{

/*!
 * @brief An EvaluableExpr factory: it can generate ExprArg and EvaluableExpr for the parser
 */
class ExprFactory{
public:
    /*!
	 * \brief create an expression argument with the corresponding type inferred by analysing arg
     * \param argument to encapsulate
	 * \return the constructed expression argument
     */
	static SIExprArg createArg(const std::string &arg);

	/*!
	 * \brief generate a default, empty expression argument containing an empty string: ""
	 * \return a smart pointer to an empty but still valid expression argument.
	 */
	inline static SIExprArg createEmptyArg(){return new IExprArg<std::string>("");}

	/*!
	 * \brief create an expression arguments that contains an Expression Operator
	 * \param operatorName: the name of the operator
	 * \param arg1: first argument passed to the operator
	 * \param arg2: second argument passed to the operator
	 * \return a smart pointer to the constructed IExprArg if succeed, if not the smart pointer is empty
	 */
	static SIExprArg createExpr(std::string operatorName, SIExprArg param1, SIExprArg param2);

	/*!
     * \brief create a message param that contains an Expression Operator
     * \param operatorName: the name of the operator
     * \param arg1: first argument passed to the operator
     * \param arg2: second argument passed to the operator
     * \param expr: if the operator exists, store the constructed expression
     * \return true if the operator exists, false otherwise
     */
	static bool createExpr(std::string operatorName, SIExprArg param1, SIExprArg param2, SIExprOperator& expr);

	static bool isurl(const std::string& path);
};



}

#endif // EXPRESSIONFACTORY_H
