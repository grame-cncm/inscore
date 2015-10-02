#ifndef EXPRREADER_H
#define EXPRREADER_H

#include "ExprEvaluator.h"


namespace inscore {


/*!
 * \brief Special evaluator: read the instruction without process them, return the original expression
 */
class ExprReader: public ExprEvaluator{
public:
    std::string eval(std::string arg);
    std::string eval(IExpression* arg);
    std::string eval(filepath arg);
    std::string eval(identifier arg);
    std::string eval(oscaddress arg);

    static ExprReader* create(){return new ExprReader();}

protected:
    ExprReader();
};

}
#endif // EXPRREADER_H
