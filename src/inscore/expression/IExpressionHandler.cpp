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
#include "IExpressionHandler.h"

#include <iostream>

#include "IObject.h"

#include "ExprReader.h"
#include "IExprParser.h"
#include "ExprEvaluator.h"

namespace inscore{


bool IExprHandlerbase::evalExpression(std::string &result) const{
    if(!checkExpression())
		return false;

	ExprEvaluator* e = evaluator();
	bool r = e->evalExpression(fExpression, result);
	delete e;

	return r;
}

bool IExprHandlerbase::forceEvalExpr(std::string &result) const{
    if(!checkExpression())
		return false;

	fExpression->rootNode()->recursiveClearEvaluated();

	ExprEvaluator* e = evaluator();
	bool r = e->evalExpression(fExpression, result);
	delete e;

	return r;
}

bool IExprHandlerbase::renewExpression(std::string &result)
{
	if(!checkExpression())
		return false;

	SIExpression expr;
	if(!IExprParser::parseExpression(fExpression->definition(), expr))
		return false;

	return composeExpr(expr, result);
}

std::string IExprHandlerbase::printExpression() const{
	return fExpression->definition();
}

std::string IExprHandlerbase::printTree(bool &succeed) const{
	std::string r;
	succeed = ExprReader::read(fExpression->rootNode(), r);
	return r;
}

std::string IExprHandlerbase::printTree() const
{
	bool b=true;
	return printTree(b);
}

IExprHandlerbase::~IExprHandlerbase()
{
}


//_________________________________________________________
bool IExprHandlerbase::composeExpr(SIExpression newExpr, std::string &result){

	if(!newExpr->isValid())
		return false;

	SIExprArg rootNode = newExpr->rootNode()->copy();
	if(!ExprCompositor::compose( rootNode, fContextObject))
		return false;

	fExpression = IExpression::create(newExpr->definition(), rootNode);

    bool r = evalExpression(result);
    if(!r)
		clearExpr();
	else
		ExprSimplificator::simplify(fExpression);

	return r;
}

void IExprHandlerbase::clearExpr(){
	fExpression = nullptr;
}


//________________________________________________________
SIExpression IExprHandlerbase::getExpression() const
{
	return fExpression;
}

bool IExprHandlerbase::hasExpression() const
{
	return fExpression!=0;
}



//____________________________________________________________
IExprHandlerbase::IExprHandlerbase(IObject *object)
	:fContextObject(object)
{
}

bool IExprHandlerbase::checkExpression() const
{
	if(!fExpression){
		ITLErr<<"ExpressionHandler: no expression to evaluate"<<ITLEndl;
		return false;
	}
	return true;
}





}	//End namespace
