#ifndef GMNEVALUATOR_H
#define GMNEVALUATOR_H

#include "ExprEvaluator.h"

namespace inscore{

class GmnEvaluator : public ExprEvaluator
{
public:
	static GmnEvaluator* create(const IObject* contextObject){return new GmnEvaluator(contextObject);}

	const std::string eval(const IObject *arg);

	const char* emptyValue() const {return "[]";}


protected:
        GmnEvaluator(const IObject* contextObject);

};

}

#endif // GMNEVALUATOR_H
