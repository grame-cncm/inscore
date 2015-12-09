#ifndef EXPREVALUATOR_H
#define EXPREVALUATOR_H

#include <string>
#include <unordered_map>

#include "smartpointer.h"

#include "evaluator.h"
#include "IExpression.h"

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

	inline std::string fail(const IExprArgBase* arg){return fail(arg->getEvaluated());}
	inline std::string fail(const std::string defaultValue){if(defaultValue.empty()){return fail();} return defaultValue;}
	inline std::string fail(){fEvalSucceed = false; return "";}
    bool hasEvalSucceed(){return fEvalSucceed;}
};

typedef const std::string (*OperatorCb)(const std::string&,const std::string&, bool &success);
typedef std::unordered_map<std::string, OperatorCb> OperatorList;

/*!
 * \brief IEvaluableExpr evaluator mother class. Handle context for the evaluation, error...
 */
class ExprEvaluator: public constEvaluator{
	const char* fEvalName;
	const IObject* fContextObject;
	const OperatorList fCallbackList;

public:
	/*!
	 * \brief evaluate an expression according to previously evaluated values
	 * \param expr expression to evaluate
	 * \param result result of the evaluation
	 * \param newEvaluatedMap previously evaluated values
	 * \return true if the evaluation succeed, false otherwise
	 *
	 * \warning evalExpression is not reentrant
	 */
	bool evalExpression(const IExpression *expr, std::string &result);

	virtual const std::string eval(const IExprOperator* arg, const IExprArgBase* exprArg=0);
	virtual const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0);
	virtual const std::string eval(const filepath& arg, const IExprArgBase* exprArg=0);
	virtual const std::string eval(const itladdress& arg, const IExprArgBase* exprArg=0);
	virtual const std::string eval(const iexpression& arg, const IExprArgBase* exprArg=0);
	virtual const std::string eval(const IObject *arg);


//	static ExprEvaluator* create(const IObject* contextObject){return new ExprEvaluator("ExprEvaluator", contextObject);}

	const char* evaluatorName() const {return fEvalName;}
	virtual const char* emptyValue() const {return "";}


	static const IObject* objectFromAddress(itladdress address, const IObject *contextObject);

protected:
	ExprEvaluator(const char* name, const IObject* contextObject, const OperatorList operatorList);

	EvaluationStatus fEvalStatus;

	inline const IObject* contextObject(){return fContextObject;}
	bool smartEval(const IExprArgBase *expr, std::string &result);

	bool callbackByOperator(const std::string op, OperatorCb &cb) const ;
};

}

#endif // EXPREVALUATOR_H
