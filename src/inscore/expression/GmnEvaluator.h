#ifndef GMNEVALUATOR_H
#define GMNEVALUATOR_H

#include "ExprEvaluator.h"

namespace inscore{

class GmnEvaluator : public ExprEvaluator
{
public:
    static GmnEvaluator* create(IObject* contextObject){return new GmnEvaluator(contextObject);}

	const std::string eval(const IObject *arg);

protected:
        GmnEvaluator(const IObject* contextObject);

};

}

#endif // GMNEVALUATOR_H
