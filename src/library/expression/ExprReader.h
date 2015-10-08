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

    std::string eval(std::string arg);
    std::string eval(const IExpression* arg);
    std::string eval(filepath arg);
    std::string eval(identifier arg);
    std::string eval(oscaddress arg);

protected:

    bool evalSucceed;
};

}
#endif // EXPRREADER_H
