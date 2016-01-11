#ifndef EXPRREADER_H
#define EXPRREADER_H

#include "evaluator.h"


namespace inscore {


class IExprEvaluatedMap;

/*!
 * \brief Special evaluator: read an expression, return the expression definition as a string
 */
class ExprReader: public constEvaluator{
	std::string fPrefix;
	unsigned short fTab;
public:
	/*!
	 * \brief read an expression
	 * \param expr The expression to read.
	 * \param prefix A prefix added at the start of any line (allows to handle tabulations)
	 * \param result The computed string is stored in result.
	 * \param printInternalData Allows to show the evaluated value stored together with every nodes for debuf purpose (false by default).
	 * \return True if the expression was correctly read.
	 */
	static bool read(const IExprArgBase *expr, std::string prefix, std::string &result, bool printInternalData = false);

	/*!
	 * \brief Overload of read with an empty prefix.
	 */
	static bool read(const IExprArgBase *expr, std::string &result, bool printData = false){return read(expr, "", result, printData);}

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
