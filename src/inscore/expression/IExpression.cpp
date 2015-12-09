#include <sstream>

#include "IExpression.h"

#include "evaluator.h"
#include "ExprReader.h"
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

//_________________________________________________
std::ostream& operator <<(std::ostream &out, const SIExprArg &exprArg)
{
	std::string r;
	ExprReader::read(exprArg, r);
	out << r;
	return out;
}

//_________________________________________________
std::ostream& operator <<(std::ostream &out, const SIExprOperator& exprArg)
{
    std::string arg1, arg2;
    if(ExprReader::read(exprArg->constArg1(), arg1) && ExprReader::read(exprArg->constArg2(), arg2))
        out << "expr( " << arg1.c_str() << " " << arg2.c_str() << ") (how did you get here by the way?)";
	return out;
}


} //end namespace
