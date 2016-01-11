#include "ExprInfo.h"

namespace inscore{


std::set<std::string> ExprInfo::fileDependency(const SIExpression &expr){return ExprFileDependency::fileDependency(expr);}

void ExprInfo::fileReplace(SIExpression &expr, const filepath &search, const filepath &replace){
	ExprSearchReplace<filepath>::searchReplace(expr,search,replace);
}

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



/****************************************************
 *                  SearchReplace                   *
 * *************************************************/
template <typename T>
void ExprSearchReplace<T>::searchReplace(SIExpression &expression, T search, T replace)
{
	ExprSearchReplace e(search, replace);
	expression->rootNode()->accept(&e);
}

template <typename T>
const std::string ExprSearchReplace<T>::eval(const T &value, IExprArgBase *exprArg){
	if(value==fSearch){
		IExprArg<T>* arg = static_cast<IExprArg<T>*>(exprArg);
		arg->setArg(fReplace);
	}
	return "";
}




} // End namespace
