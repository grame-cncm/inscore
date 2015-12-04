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

	static bool read(const IExprArgBase *expr, std::string &result, bool printData = false){return read(expr, "", result, printData);}
	static bool read(const IExprArgBase *expr, std::string prefix, std::string &result, bool printData = false);

	const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0);
	const std::string eval(const IExprOperator* arg, const IExprArgBase* exprArg=0);
	const std::string eval(const filepath& arg, const IExprArgBase* exprArg=0);
	const std::string eval(const itladdress &arg, const IExprArgBase* exprArg=0);
	const std::string eval(const iexpression &arg, const IExprArgBase* exprArg=0);

protected:
	ExprReader();
	virtual bool evalExpression(const IExprArgBase* expr, std::string &result, bool printData = false);
	bool fPrintData;

	std::string argPrefix(const IExprArgBase* exprArg);
	std::string prefix(std::string applyPrefixTo="");

    bool evalSucceed;
};

}
#endif // EXPRREADER_H
