#ifndef EXPREVALUATOR_H
#define EXPREVALUATOR_H

#include <string>

#include "smartpointer.h"
//#include "IObject.h"

#include "evaluator.h"
#include "IExpression.h"


namespace inscore{

class IObject;

/*!
 * \brief IEvaluableExpr evaluator mother class. Handle context for the evaluation, error...
 */
class ExprEvaluator: public evaluator{
public:

    virtual bool evalExpression(IExpression* expr, std::string &result);

    virtual std::string eval(IExpression* arg);
    virtual std::string eval(std::string arg);
    virtual std::string eval(filepath arg);
    virtual std::string eval(identifier arg);
    virtual std::string eval(oscaddress arg);

    virtual std::string eval(IObject *arg);


    static ExprEvaluator* create(){return new ExprEvaluator();}

protected:
    ExprEvaluator();

    bool evalSucceed;
   // IObject fContextObject;

};

}

#endif // EXPREVALUATOR_H
