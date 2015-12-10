#ifndef GMNEVALUATOR_H
#define GMNEVALUATOR_H

#include "ExprEvaluator.h"

namespace inscore{

class GmnEvaluator : public ExprEvaluator
{
public:
	static GmnEvaluator* create(const IObject* contextObject){return new GmnEvaluator(contextObject);}

	const std::string eval(const IObject *arg);
	const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0);

	std::string emptyValue() const {return "[]";}

	virtual ~GmnEvaluator(){}

protected:
        GmnEvaluator(const IObject* contextObject);
		bool isXml(const std::string &score) const;

private:
		static const OperatorList gmnOperators();
		static const OperatorList gOperators;
};

}

#endif // GMNEVALUATOR_H
