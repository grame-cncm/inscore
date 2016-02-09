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
#ifndef EXPRREADER_H
#define EXPRREADER_H

#include "evaluator.h"


namespace inscore {


class IExprEvaluatedMap;

/*!
 * \brief Special evaluator: read an expression, return the expression definition as a string
 */
class ExprReader: public constEvaluator{
	std::string fPrefix;
	unsigned short fTab;
public:
	/*!
	 * \brief read an expression
	 * \param expr The expression to read.
	 * \param prefix A prefix added at the start of any line (allows to handle tabulations)
	 * \param result The computed string is stored in result.
	 * \param printInternalData Allows to show the evaluated value stored together with every nodes for debuf purpose (false by default).
	 * \return True if the expression was correctly read.
	 */
	static bool read(const IExprArgBase *expr, std::string prefix, std::string &result, bool printInternalData = false);

	/*!
	 * \brief Overload of read with an empty prefix.
	 */
	static bool read(const IExprArgBase *expr, std::string &result, bool printData = false){return read(expr, "", result, printData);}

	const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0);
	const std::string eval(const IExprOperator* arg, const IExprArgBase* exprArg=0);
	const std::string eval(const filepath& arg, const IExprArgBase* exprArg=0);
	const std::string eval(const itladdress &arg, const IExprArgBase* exprArg=0);
	const std::string eval(const iexpression &arg, const IExprArgBase* exprArg=0);

protected:
	ExprReader();
	virtual bool evalExpression(const IExprArgBase* expr, std::string &result, bool printData = false);
	bool fPrintData;

	std::string argPrefix(const IExprArgBase* exprArg);
	std::string prefix(std::string applyPrefixTo="");

    bool evalSucceed;
};

}
#endif // EXPRREADER_H
