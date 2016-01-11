#ifndef EXPRINFO_H
#define EXPRINFO_H

#include <set>

#include "IExpression.h"

namespace inscore {

class ExprInfo
{
public:
    static std::set<std::string> fileDependency(const SIExpression& expr);
	static void fileReplace(SIExpression &expr, const filepath& search, const filepath& replace);

};

//____________________________________________________________________
// ------------------------------------------------------------------
/*!
 * \brief Evaluate an IExpression and return a list of the ressources used in it
 */
class ExprFileDependency: public constEvaluator{

public:

	static std::set<std::string> fileDependency(const IExpression* expr);

	const std::string eval(const std::string& , const IExprArgBase* =0){return "";}
	const std::string eval(const IExprOperator* arg , const IExprArgBase* =0);
	const std::string eval(const filepath& arg, const IExprArgBase* =0);
	const std::string eval(const itladdress &, const IExprArgBase* =0){return "";}
	const std::string eval(const iexpression &, const IExprArgBase* =0){return "";}

protected:
	std::set<std::string> fDependency;
};

//____________________________________________________________________
// ------------------------------------------------------------------
/*!
 * \brief Search for parameters and replace them with a new value
 */
class ExprSearchReplacebase: public evaluator{

public:
	virtual const std::string eval(IExprOperator *arg,	IExprArgBase *){
		arg->arg1()->accept(this);
		arg->arg2()->accept(this);
		return "";
	}
	virtual const std::string eval(const filepath &,	IExprArgBase *){return "";}
	virtual const std::string eval(const std::string &,	IExprArgBase *){return "";}
	virtual const std::string eval(const itladdress &,	IExprArgBase *){return "";}
	virtual const std::string eval(const iexpression &,	IExprArgBase *){return "";}

protected:
	ExprSearchReplacebase(): evaluator() {}

};

template <typename T>
class ExprSearchReplace: public ExprSearchReplacebase{
	const T fSearch, fReplace;

public:
	static void searchReplace(SIExpression &expression, T search, T replace);
	virtual const std::string eval(const T& value, IExprArgBase *exprArg);

protected:
	ExprSearchReplace(T search, T replace): ExprSearchReplacebase(), fSearch(search), fReplace(replace){}

};

} // End namespace

#endif // EXPRINFO_H
