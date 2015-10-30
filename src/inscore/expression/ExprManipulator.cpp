#include "ExprManipulator.h"

#include "ITLError.h"
#include "ExprFactory.h"
#include "ExprEvaluator.h"

#include "IGuidoCode.h"
//#include "IObject.h"

#include <string>

using namespace std;

namespace inscore {

/****************************************************
 *				ExprManipulator						*
 * *************************************************/

ExprManipulator::ExprManipulator(const IObject *contextObject, const char *manipulatorName)
	: evaluator(),
	  fContextObject(contextObject), fManipulatorName(manipulatorName)
{

}


bool ExprManipulator::apply(SIExpression &expr, WatchersList &watchers)
{
	succeed = true;

	std::string newNode = expr->accept(this);
	if(!newNode.empty())
		replaceNode(expr, newNode);


	watchers = fWatchers;

	return succeed;
}

const string ExprManipulator::eval(IExprOperator *arg, IExpression *exprArg)
{
	return continueExploration(arg, exprArg);
}

const std::string ExprManipulator::eval(const itladdress& arg, IExpression *exprArg)
{
	const IObject* o = ExprEvaluator::objectFromAddress(arg, fContextObject);

	if(!o){
		ITLErr<<fManipulatorName<<": "<<(string)arg<<" not known at this address..."<<ITLEndl;
		manipulationFailed();
	}else{
		if(!exprArg->pureStaticEval()){
			//If static eval, manipulator doesn't change anything
			if(exprArg->copyEval())
				return eval(o, exprArg);

			//If dynamic eval, add object to watchers
			const IGuidoCode* guido = dynamic_cast<const IGuidoCode*>(o);
			if(!guido)
				return "";

			fWatchers.insert(o);
		}
	}

	return "";
}

string ExprManipulator::replaceBy(SIExpression newNode, std::string key)
{
	if(key.empty()){			//generate a key if none
		stringstream ss;
		ss<<"!"<<fReplacedNodes.size();
		key = ss.str();
	}else{
		if(fReplacedNodes.find(key) != fReplacedNodes.end())
			return key;			//Don't change the node in the list if already added
	}

	fReplacedNodes.insert(pair<string,SIExpression>(key, newNode->copy()));
	newNode->accept(this);	//explore new branch, searching for watchers

	return key;
}

string ExprManipulator::continueExploration(IExprOperator *arg, IExpression* exprArg)
{
	std::string newNode;

	newNode = arg->constArg1()->accept(this);
	if(!newNode.empty())
		replaceNode(arg->arg1(), newNode);


	newNode = arg->constArg2()->accept(this);
	if(!newNode.empty())
		replaceNode(arg->arg2(), newNode);

	if(arg->arg1()->dynamicEval() || arg->arg2()->dynamicEval())
		exprArg->switchToDynamic();

	return "";
}

void ExprManipulator::replaceNode(SIExpression &node, SIExpression newExpr)
{
	node = newExpr;
}

/****************************************************
 *				ExprCompositor						*
 * *************************************************/

const string ExprCompositor::eval(const IObject *arg, IExpression *exprArg)
{
	const IGuidoCode* guido = dynamic_cast<const IGuidoCode*>(arg);
	if(!guido){
		ITLErr << "ExprCompositor: the object "<<arg->name()<<" is not a guido object"<<ITLEndl;
		manipulationFailed();
		return "";
	}

	if(exprArg->copyEval()){
		SIExpression newNode = guido->getExprHandler()->getExpression();
		if(newNode)
			return  replaceBy(newNode, guido->name());

		exprArg->setEvaluated(guido->getCleanGMN());
	}

	return "";
}



ExprCompositor::ExprCompositor(const IObject *contextObject)
	:ExprManipulator(contextObject, "ExprCompositor")
{

}

bool ExprCompositor::compose(SIExpression &expr, const IObject *contextObject, WatchersList &watchers)
{
	ExprCompositor compositor(contextObject);
	return compositor.apply(expr, watchers);
}






} //End namespace

