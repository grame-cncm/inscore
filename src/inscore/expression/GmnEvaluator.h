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

	const char* emptyValue() const {return "[]";}


protected:
        GmnEvaluator(const IObject* contextObject);
		bool isXml(const std::string &score) const;
};

}

#endif // GMNEVALUATOR_H
