#include "ExprInfo.h"

namespace inscore{


std::set<std::string> ExprInfo::fileDependency(const SIExpression &expr){return ExprFileDependency::fileDependency(expr);}

/****************************************************
 *               ExprFileDependency                 *
 * *************************************************/

std::set<std::string> ExprFileDependency::fileDependency(const IExpression *expr)
{
    ExprFileDependency f;
	((const IExprArgBase*)expr->rootNode())->accept(&f);
    return f.fDependency;
}


const std::string ExprFileDependency::eval(const filepath& arg , const IExprArgBase*){
    fDependency.insert(arg);
    return "";
}
const std::string ExprFileDependency::eval(const IExprOperator *arg, const IExprArgBase *){
	((const IExprArgBase*)arg->constArg1())->accept(this);
	((const IExprArgBase*)arg->constArg2())->accept(this);
    return "";
}

} // End namespace
