#include "IExpressionFactory.h"

using namespace inscore;
using namespace std;

ExprFactory::ExprFactory(): fOperatorList()
{
    registerOperator("plus", [](std::string a, std::string b){return a+b;});
}


//_______________________________________________________
ExprFactory* ExprFactory::create(){
    return new ExprFactory();
}



//_______________________________________________________
bool inscore::ExprFactory::createExpr(std::string operatorName, SIExprArgbase param1, SIExprArgbase param2, SIExpression &expr)
{
    OperatorPrototype* op;
    try{
	op = fOperatorList.at(operatorName);
    }catch(std::out_of_range){
        expr = SIExpression();
        return false;
    }

    expr = new IExpression(op, param1, param2);

    return true;
}

//_______________________________________________________
void ExprFactory::registerOperator(OperatorPrototype *op)
{
    fOperatorList.insert({op->getName(), op});
}

