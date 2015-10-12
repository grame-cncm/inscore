#ifndef EXPREVALUATOR_H
#define EXPREVALUATOR_H

#include <string>
#include <unordered_map>

#include "smartpointer.h"

#include "evaluator.h"
#include "IExpression.h"
#include "Operators.h"

namespace inscore{

class IObject;

/*!
 * \brief Handle the status of the evaluator during the processing of the evaluation (failing...)
 */
class EvaluationStatus{
    bool fEvalSucceed;

public:
    EvaluationStatus();
    void init();

    void fail(){fEvalSucceed = false;}
    bool hasEvalSucceed(){return fEvalSucceed;}
};

typedef const std::string (*OperatorCb)(const std::string&,const std::string&);

/*!
 * \brief IEvaluableExpr evaluator mother class. Handle context for the evaluation, error...
 */
class ExprEvaluator: public evaluator{
public:

    virtual bool evalExpression(const IExpression* expr, std::string &result);

	virtual const std::string eval(const IExpression* arg);
	virtual const std::string eval(std::string arg);
	virtual const std::string eval(filepath arg);
	virtual const std::string eval(identifier arg);
	virtual const std::string eval(oscaddress arg);

	virtual const std::string eval(const IObject *arg);


	static ExprEvaluator* create(const IObject* contextObject){return new ExprEvaluator("ExprEvaluator", contextObject);}

protected:
	ExprEvaluator(const char* name, const IObject* contextObject);

	const char* fEvalName;
    EvaluationStatus fEvalStatus;
    const IObject* fContextObject;

	std::unordered_map<const OperatorPrototype*, OperatorCb> fCallbackList;
	void registerOperator(const OperatorPrototype &op, OperatorCb cb);
	bool callbackByOperator(const OperatorPrototype* op, OperatorCb &cb) const ;

};

}

#endif // EXPREVALUATOR_H
