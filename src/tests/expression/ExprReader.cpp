#include "ExprReader.h"

using namespace inscore;

std::string ExprReader::eval(std::string arg)
{
    return "\""+arg+"\"";
}


std::string inscore::ExprReader::eval(IExpression *arg)
{
    return "expr( "
            + arg->getName() + " "
            + arg->getArg1()->accept(this) + " "
            + arg->getArg2()->accept(this)
            +" ) ";
}

//_________________________________
std::string ExprReader::eval(filepath arg)
{
    return arg;
}

//_________________________________
std::string ExprReader::eval(identifier arg)
{
    return arg;
}

//_________________________________
std::string ExprReader::eval(oscaddress arg)
{
    return arg;
}


//_________________________________
ExprReader::ExprReader():
    ExprEvaluator()
{

}
