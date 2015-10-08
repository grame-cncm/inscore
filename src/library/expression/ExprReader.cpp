#include "ExprReader.h"
#include "IExpression.h"

namespace inscore{

bool ExprReader::evalExpression(const IExpression *expr, std::string &result)
{
    evalSucceed = true;
    result = eval(expr);
    return evalSucceed;
}

//_________________________________
const std::string ExprReader::eval(std::string arg)
{
    return "\""+arg+"\"";
}

//_________________________________
const std::string ExprReader::eval(const IExpression *arg)
{
    return "expr( "
            + arg->getName() + " "
            + arg->getArg1()->accept(this) + " "
            + arg->getArg2()->accept(this)
            +" ) ";
}

//_________________________________
const std::string ExprReader::eval(filepath arg)
{
	return arg;
}

//_________________________________
const std::string ExprReader::eval(identifier arg)
{
    return arg;
}

//_________________________________
const std::string ExprReader::eval(oscaddress arg)
{
    return arg;
}


//_________________________________
ExprReader::ExprReader():
    evaluator()
{
    evalSucceed = true;
}

} //end namespace
