#include "GmnEvaluator.h"
#include "IGuidoCode.h"

namespace inscore{

std::string GmnEvaluator::eval(const IObject *arg)
{
    const IGuidoCode* guido = dynamic_cast<const IGuidoCode*>(arg);
    if(guido == NULL){
        ITLErr << "GmnEvaluator: the object "<<arg->name()<<" is not a guido object"<<ITLEndl;
        fEvalStatus.fail();
        return "";
    }

    return guido->getGMN();
}

GmnEvaluator::GmnEvaluator(const IObject *contextObject): ExprEvaluator(contextObject)
{

}

} //end namespace
