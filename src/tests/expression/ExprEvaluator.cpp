#include "ExprEvaluator.h"

using namespace inscore;

bool ExprEvaluator::evalExpression(IExpression *expr, std::string& result){
    result = eval(expr);
    return true;
}

//_____________________________________________________________
std::string ExprEvaluator::eval(IExpression* arg)
{
    std::string arg1 = arg->getArg1()->accept(this);
    std::string arg2 = arg->getArg2()->accept(this);

    OperatorCb cb = arg->getOperatorPrototype()->getCallback();
    return cb(arg1, arg2);
}

//_____________________________________________________________
std::string ExprEvaluator::eval(std::string arg)
{
    return arg;
}

//_____________________________________________________________
std::string ExprEvaluator::eval(filepath arg)
{
    std::string fileData="";

    ///TODO: acquire file

    return eval(fileData);
}

//_____________________________________________________________
std::string ExprEvaluator::eval(identifier arg)
{
    oscaddress address;
    //= fContextObject.getOSCAddress() + "/" + arg;

    return eval(address);
}


//_____________________________________________________________
std::string ExprEvaluator::eval(oscaddress arg)
{
    IObject* o;
    //fContextObject.findnode(arg);

    return eval(o);
}

//_____________________________________________________________
std::string ExprEvaluator::eval(IObject *arg)
{
    return "IObject";
}






//_____________________________________________________________
ExprEvaluator::ExprEvaluator():
    evaluator()
{

}
