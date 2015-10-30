#ifndef EXPRREADER_H
#define EXPRREADER_H

#include "evaluator.h"


namespace inscore {


class IExprEvaluatedMap;

/*!
 * \brief Special evaluator: read the instruction without process them, return the original expression
 */
class ExprReader: public constEvaluator{
	IExprEvaluatedMap* fEvaluatedMap;
	std::string fPrefix;
	unsigned short fTab;
public:

	static bool read(const IExpression *expr, std::string &result){return read(expr, "", result);}
	static bool read(const IExpression *expr, std::string prefix, std::string &result);

	const std::string eval(const std::string& arg, const IExpression* exprArg=0);
	const std::string eval(const IExprOperator* arg, const IExpression* exprArg=0);
	const std::string eval(const filepath& arg, const IExpression* exprArg=0);
	const std::string eval(const itladdress &arg, const IExpression* exprArg=0);

protected:
	ExprReader();
	virtual bool evalExpression(const IExpression* expr, std::string &result);
	std::string argPrefix(const IExpression* exprArg);
	std::string prefix(std::string applyPrefixTo="");
    bool evalSucceed;
};

}
#endif // EXPRREADER_H
