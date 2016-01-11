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
