#ifndef EXPREVALUATOR_H
#define EXPREVALUATOR_H

#include <string>

#include "smartpointer.h"

#include "evaluator.h"
#include "IExpression.h"


namespace inscore{

class IObject;

class EvaluationStatus{
    bool fEvalSucceed;

public:
    EvaluationStatus();
    void init();

    void fail(){fEvalSucceed = false;}
    bool hasEvalSucceed(){return fEvalSucceed;}
};

/*!
 * \brief IEvaluableExpr evaluator mother class. Handle context for the evaluation, error...
 */
class ExprEvaluator: public evaluator{
public:

    virtual bool evalExpression(const IExpression* expr, std::string &result);

    virtual std::string eval(const IExpression* arg);
    virtual std::string eval(std::string arg);
    virtual std::string eval(filepath arg);
    virtual std::string eval(identifier arg);
    virtual std::string eval(oscaddress arg);

    virtual std::string eval(const IObject *arg);


    static ExprEvaluator* create(const IObject* contextObject){return new ExprEvaluator(contextObject);}

protected:
    ExprEvaluator(const IObject* contextObject);

    EvaluationStatus fEvalStatus;
    const IObject* fContextObject;

};

}

#endif // EXPREVALUATOR_H
