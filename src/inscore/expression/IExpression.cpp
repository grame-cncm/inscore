#include "IExpression.h"

#include "evaluator.h"
#include "ExprReader.h"

namespace inscore
{

IExprOperator::IExprOperator(const OperatorPrototype *operatorPrototype, SIExpression arg1, SIExpression arg2):
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
std::string IExprOperator::getName() const
{
	return fOperatorPrototype->getName();
}


//_________________________________________________
// -----------------------------------------------
IExpression::IExpression(bool dynamicEval, bool copyEval)
	: libmapping::smartable(),
	  fCopyEval(copyEval), fDynamicEval(dynamicEval),
	  fEvaluated(new std::string())
{

}


//_________________________________________________
// -----------------------------------------------
template<>
SIExpression IExprArg<SIExprOperator>::copy()
{
	IExprOperator* op = new IExprOperator(fArg->operatorPrototype(), fArg->arg1()->copy(), fArg->arg2()->copy());
	IExpression* r = new IExprArg<SIExprOperator>(op, fDynamicEval, fCopyEval);
	r->setEvaluated(getEvaluated());
	return r;
}

//_________________________________________________
template<>
void IExprArg<SIExprOperator>::recursiveClearEvaluated()
{
	fArg->arg1()->recursiveClearEvaluated();
	fArg->arg2()->recursiveClearEvaluated();
	fEvaluated->clear();
}

//_________________________________________________
std::ostream& operator <<(std::ostream &out, const SIExpression &exprArg)
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
