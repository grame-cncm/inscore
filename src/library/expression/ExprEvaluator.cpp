#include "ExprEvaluator.h"
#include <fstream>
#include "ITLError.h"

#include "IObject.h"
#include "IScene.h"


using namespace std;

namespace inscore{

bool ExprEvaluator::evalExpression(const IExpression *expr, std::string& result){
    fEvalStatus.init();
    result = eval(expr);
    return fEvalStatus.hasEvalSucceed();
}

//_____________________________________________________________
const string ExprEvaluator::eval(const IExpression* arg)
{
	OperatorCb cb;

	if( !callbackByOperator(arg->getOperatorPrototype(), cb) ){
		ITLErr<<fEvalName	<<": operator \""
							<<arg->getOperatorPrototype()->getName()
							<<"\" has no definition in this evaluator";
		fEvalStatus.fail();
		return "";
	}

    std::string arg1 = arg->getArg1()->accept(this);

    if(!fEvalStatus.hasEvalSucceed())
        return "";

    std::string arg2 = arg->getArg2()->accept(this);

    return cb(arg1, arg2);
}

//_____________________________________________________________
const string ExprEvaluator::eval(std::string arg)
{
    return arg;
}

//_____________________________________________________________
const string ExprEvaluator::eval(filepath arg)
{

	arg = fContextObject->getScene()->absolutePath(arg);

    std::string fileData="";
    std::ifstream ifs;

    ifs.open(arg, std::ifstream::in);

    if(!ifs.is_open()){
		ITLErr<<fEvalName<<": can't find \""<<(string)arg<<"\""<<ITLEndl;
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
const string ExprEvaluator::eval(identifier arg)
{
    oscaddress address = fContextObject->getParent()->getOSCAddress() + "/" + (string)arg;

    std::string r = eval(address);

    if(fEvalStatus.hasEvalSucceed())
        return r;

    return "";
}


//_____________________________________________________________
const string ExprEvaluator::eval(oscaddress arg)
{
    const IObject* o = fContextObject->findnode(arg);

    if(!o){
		ITLErr<<fEvalName<<": "<<(string)arg<<" not known at this address..."<<ITLEndl;
        fEvalStatus.fail();
        return "";
    }
    return eval(o);
}

//_____________________________________________________________
const string ExprEvaluator::eval(const IObject *arg)
{
    return "IObject: "+arg->name();
}



//_____________________________________________________________
ExprEvaluator::ExprEvaluator(const char *name, const IObject* contextObject):
	evaluator(), fEvalName(name)
{
	fContextObject = contextObject;
}

//_____________________________________________________________
void ExprEvaluator::registerOperator(const OperatorPrototype& op, OperatorCb cb)
{
	fCallbackList.insert({&op, cb});
}

//_____________________________________________________________
bool ExprEvaluator::callbackByOperator(const OperatorPrototype* op, OperatorCb &cb) const
{
	try{
		cb = fCallbackList.at(op);
	}catch(std::out_of_range){
		return false;
	}

	return true;
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
