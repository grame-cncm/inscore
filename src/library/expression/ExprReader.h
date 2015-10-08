#ifndef EXPRREADER_H
#define EXPRREADER_H

#include "evaluator.h"


namespace inscore {


/*!
 * \brief Special evaluator: read the instruction without process them, return the original expression
 */
class ExprReader: public evaluator{
public:
    ExprReader();

    virtual bool evalExpression(const IExpression* expr, std::string &result);

	const std::string eval(std::string arg);
	const std::string eval(const IExpression* arg);
	const std::string eval(filepath arg);
	const std::string eval(identifier arg);
	const std::string eval(oscaddress arg);

protected:

    bool evalSucceed;
};

}
#endif // EXPRREADER_H
