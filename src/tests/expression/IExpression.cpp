#include "IExpression.h"
#include "evaluator.h"

using namespace inscore;



//_________________________________________________
IExpression::IExpression(OperatorPrototype *operatorPrototype, SIExprArgbase arg1, SIExprArgbase arg2):
    libmapping::smartable(),
    fArg1(&(*arg1)), fArg2(&(*arg2))
{
    fOperatorPrototype = operatorPrototype;
}

//_________________________________________________
std::string IExpression::getName()
{
    return fOperatorPrototype->getName();
}
