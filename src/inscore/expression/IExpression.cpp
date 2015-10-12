#include "IExpression.h"

#include "evaluator.h"
#include "ExprReader.h"

namespace inscore
{

//_________________________________________________
IExpression::IExpression(OperatorPrototype *operatorPrototype, SIExprArgbase arg1, SIExprArgbase arg2):
    libmapping::smartable(),
	fOperatorPrototype(operatorPrototype), fArg1(&(*arg1)), fArg2(&(*arg2))
{
}

//_________________________________________________
std::string IExpression::getName() const
{
	return fOperatorPrototype->getName();
}


//_________________________________________________
std::ostream& operator <<(std::ostream &out, const SIExpression &expr)
{
    std::string r;
    ExprReader reader;
    if(reader.evalExpression(expr, r))
        out<<r;

    return out;
}

//_________________________________________________
std::ostream& operator <<(std::ostream &out, const SIExprArgbase &exprArg)
{
    ExprReader reader;
    out << exprArg->accept(&reader);
    return out;
}

} //end namespace
