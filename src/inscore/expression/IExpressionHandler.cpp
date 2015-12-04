#include "IExpressionHandler.h"

#include <iostream>

#include "IObject.h"

#include "ExprReader.h"
#include "ExprEvaluator.h"

namespace inscore{


bool IExprHandlerbase::evalExpression(std::string &result) const{
    if(!checkExpression())
		return false;

	return evaluator()->evalExpression(fExpression, result);
}

bool IExprHandlerbase::forceEvalExpr(std::string &result){
    if(!checkExpression())
		return false;

	fExpression->rootNode()->recursiveClearEvaluated();
	return evaluator()->evalExpression(fExpression, result);
}

std::string IExprHandlerbase::printExpression() const{
	return fExpression->definition();
}

std::string IExprHandlerbase::printTree(bool &succeed) const{
	std::string r;
	succeed = ExprReader::read(fExpression->rootNode(), r);
	return r;
}

std::string IExprHandlerbase::printTree() const
{
	bool b=true;
	return printTree(b);
}

IExprHandlerbase::~IExprHandlerbase()
{
}


//_________________________________________________________
bool IExprHandlerbase::composeExpr(SIExpression newExpr, std::string &result){
	SIExprArg rootNode = newExpr->rootNode()->copy();
	if(!ExprCompositor::compose( rootNode, fContextObject))
		return false;

	fExpression = IExpression::create(newExpr->definition(), rootNode);

    bool r = evalExpression(result);
    if(!r)
	clearExpr();
	return r;
}

void IExprHandlerbase::clearExpr(){
	fExpression = nullptr;
}


//________________________________________________________
SIExpression IExprHandlerbase::getExpression() const
{
	return fExpression;
}

bool IExprHandlerbase::hasExpression() const
{
	return fExpression;
}



//____________________________________________________________
IExprHandlerbase::IExprHandlerbase(IObject *object)
	:fContextObject(object)
{
}

bool IExprHandlerbase::checkExpression() const
{
	if(!fExpression){
		ITLErr<<"ExpressionHandler: no expression to evaluate"<<ITLEndl;
		return false;
	}
	return true;
}





}	//End namespace
