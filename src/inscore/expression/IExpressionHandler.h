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
#ifndef IEXPRESSION_H
#define IEXPRESSION_H

#include <string>
#include <list>

#include "IExpression.h"
#include "evaluator.h"
#include "ExprManipulator.h"
#include "ITLError.h"

namespace inscore {

class IObject;
class ExprEvaluator;

/*!
 * \brief IExprHandler is the interface between objects definable by IExpression and their IExpressions, IExprHandlerbase hide the template of IExprHandler<evaluatorT>.
 */
class IExprHandlerbase{

	SIExpression fExpression;
	IObject* fContextObject;

public:
	bool evalExpression(std::string& result) const;
	bool forceEvalExpr(std::string& result) const;
	bool renewExpression(std::string &result);

	bool composeExpr(SIExpression newExpr, std::string &result);
	void clearExpr();

	SIExpression getExpression() const;
	bool hasExpression() const;
	std::string printExpression() const;
	std::string printTree(bool& succeed) const;
	std::string printTree() const;

	 virtual ~IExprHandlerbase();

protected:
	IExprHandlerbase(IObject* object);
	virtual ExprEvaluator* evaluator() const =0;
	inline const IObject* contextObject() const {return fContextObject;}

	bool checkExpression() const;
};



/*!
 * \brief IExprHandler<typename evaluatorT> define an IExpression handler specifying it with an ExprEvaluator that shall be used to evaluate a value from expressions.
 */
template <typename evaluatorT>
class IExprHandler: public IExprHandlerbase
{
public:
	explicit IExprHandler(IObject* object): IExprHandlerbase(object){}
	virtual ~IExprHandler(){}
protected:
	ExprEvaluator* evaluator() const {return evaluatorT::create(contextObject());}
};

} //end namespace

#endif // IEXPRESSION_H
