#include "ExprEvaluator.h"
#include <fstream>
#include "ITLError.h"

#include "IObject.h"


using namespace std;

namespace inscore{

bool ExprEvaluator::evalExpression(const IExpression *expr, std::string& result){
    fEvalStatus.init();
    result = eval(expr);
    return fEvalStatus.hasEvalSucceed();
}

//_____________________________________________________________
std::string ExprEvaluator::eval(const IExpression* arg)
{
    std::string arg1 = arg->getArg1()->accept(this);
    std::string arg2 = arg->getArg2()->accept(this);

    OperatorCb cb = arg->getOperatorPrototype()->getCallback();
    return cb(arg1, arg2);
}

//_____________________________________________________________
std::string ExprEvaluator::eval(std::string arg)
{
    return arg;
}

//_____________________________________________________________
std::string ExprEvaluator::eval(filepath arg)
{
    std::string fileData="";
    std::ifstream ifs;

    ifs.open(arg, std::ifstream::in);

    if(!ifs.is_open()){
        ITLErr<<"ExprEvaluator: can't find \""<<(string)arg<<"\""<<ITLEndl;
        fEvalStatus.fail();
        return "";
    }

    char c = ifs.get();
    while (ifs.good()) {
        fileData += c;
        c = ifs.get();
      }

    ifs.close();

    return eval(fileData);
}

//_____________________________________________________________
std::string ExprEvaluator::eval(identifier arg)
{
    oscaddress address = fContextObject->getParent()->getOSCAddress() + "/" + (string)arg;

    std::string r = eval(address);

    if(fEvalStatus.hasEvalSucceed())
        return r;

     ITLErr<<"ExprEvaluator: "<<(string)arg<<" not known identifier"<<ITLEndl;
    return "";
}


//_____________________________________________________________
std::string ExprEvaluator::eval(oscaddress arg)
{
    const IObject* o = fContextObject->findnode(arg);

    if(o==NULL){
        ITLErr<<"ExprEvaluator: "<<(string)arg<<" not known at this address..."<<ITLEndl;
        fEvalStatus.fail();
        return "";
    }
    return eval(o);
}

//_____________________________________________________________
std::string ExprEvaluator::eval(const IObject *arg)
{
    return "IObject: "+arg->name();
}



//_____________________________________________________________
ExprEvaluator::ExprEvaluator(const IObject* contextObject):
    evaluator()
{
    fContextObject = contextObject;
}



//_____________________________________________________________
void EvaluationStatus::init()
{
    fEvalSucceed = true;
}

EvaluationStatus::EvaluationStatus():fEvalSucceed(true)
{

}

} //end namespace
