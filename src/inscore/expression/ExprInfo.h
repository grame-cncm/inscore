#ifndef EXPRINFO_H
#define EXPRINFO_H

#include <set>

#include "IExpression.h"

namespace inscore {

class ExprInfo
{
public:
    static std::set<std::string> fileDependency(const SIExpression& expr);

};

//____________________________________________________________________
// ------------------------------------------------------------------
/*!
 * \brief Special evaluator: read an expression, return the expression definition as a string
 */
class ExprFileDependency: public constEvaluator{

public:

	static std::set<std::__cxx11::string> fileDependency(const IExpression* expr);

	const std::string eval(const std::string& , const IExprArgBase* =0){return "";}
	const std::string eval(const IExprOperator* arg , const IExprArgBase* =0);
	const std::string eval(const filepath& arg, const IExprArgBase* =0);
	const std::string eval(const itladdress &, const IExprArgBase* =0){return "";}
	const std::string eval(const iexpression &, const IExprArgBase* =0){return "";}

protected:
	std::set<std::string> fDependency;
};

} // End namespace

#endif // EXPRINFO_H
