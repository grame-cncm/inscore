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
#include <sstream>

#include "IExpression.h"

#include "evaluator.h"
#include "IExprParser.h"
#include "ExprFactory.h"

namespace inscore
{

//_________________________________________________
SIExpression IExpression::create(const std::string &definition, const SIExprArg &fRootNode)
{
	return new IExpression(definition, fRootNode);
}


SIExpression IExpression::createEmpty()
{
	return create("expr(\"\")", ExprFactory::createEmptyArg());
}

void IExpression::setRootNode(SIExprArg rootNode)
{
	fRootNode = SIExprArg(rootNode);
}

//_________________________________________________
IExpression::IExpression(const std::string &definition, const SIExprArg &rootNode):
	libmapping::smartable(),
	fRootNode(rootNode), fDefinition(definition)
{
}



//_________________________________________________
// -----------------------------------------------
IExprOperator::IExprOperator(const std::string operatorPrototype, SIExprArg arg1, SIExprArg arg2):
    libmapping::smartable(),
	fOperatorPrototype(operatorPrototype), fArg1(&(*arg1)), fArg2(&(*arg2))
{
}

//_________________________________________________
bool IExprOperator::dynamicEval() const
{
	return (fArg1->dynamicEval()) || fArg2->dynamicEval();
}


//_________________________________________________
// -----------------------------------------------
IExprArgBase::IExprArgBase()
	: libmapping::smartable(),
	  fCopyEval(false), fDynamicEval(false),
	  fEvaluated(new std::string())
{

}

//_________________________________________________
std::ostream& operator <<(std::ostream &out, const SIExpression &exprArg)
{
	out << exprArg->definition();
	return out;
}



} //end namespace
