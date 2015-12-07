#include "ExprManipulator.h"

#include "ITLError.h"
#include "ExprFactory.h"
#include "ExprEvaluator.h"
#include "ExprReader.h"

#include "IGuidoCode.h"
//#include "IObject.h"

#include <string>

using namespace std;

namespace inscore {

/****************************************************
 *				ExprManipulator						*
 * *************************************************/

ExprCompositor::ExprCompositor(const IObject *contextObject, const char *manipulatorName)
	: evaluator(),
	  fContextObject(contextObject), fManipulatorName(manipulatorName)
{

}

bool ExprCompositor::compose(SIExprArg &expr, const IObject *contextObject)
{
	ExprCompositor compositor(contextObject);
	return compositor.apply(expr);
}

bool ExprCompositor::apply(SIExprArg &exprTree)
{
	succeed = true;


	std::string newNode = exprTree->accept(this);
	if(!newNode.empty())
		replaceNode(exprTree, newNode);

	return succeed;
}

//___________________________________________________________________
const string ExprCompositor::eval(IExprOperator *arg, IExprArgBase *exprArg)
{
	continueExploration(arg, exprArg);
	return "";
}

const std::string ExprCompositor::eval(const itladdress& arg, IExprArgBase *exprArg)
{
	const IObject* o = ExprEvaluator::objectFromAddress(arg, fContextObject);

	if(!o){
		ITLErr<<fManipulatorName<<": "<<(string)arg<<" not known at this address..."<<ITLEndl;
		manipulationFailed();
	}else{
		if(exprArg->copyEval())
			return eval(o, exprArg);
	}

	return "";
}

const string ExprCompositor::eval(const IObject *arg, IExprArgBase *exprArg)
{
	const IGuidoCode* guido = dynamic_cast<const IGuidoCode*>(arg);
	if(!guido){
		ITLErr << "ExprCompositor: the object "<<arg->name()<<" is not a guido object"<<ITLEndl;
		manipulationFailed();
		return "";
	}

	if(exprArg->copyEval()){
		SIExprArg newNode = guido->getExprHandler()->getExpression()->rootNode();
		if(newNode)
			return  replaceBy(newNode, guido->name());

		exprArg->setEvaluated(guido->getCleanGMN());
	}

	return "";
}


//___________________________________________________________________
string ExprCompositor::replaceBy(SIExprArg newNode, std::string key)
{
	if(key.empty()){			//generate a key if none
		stringstream ss;
		ss<<"!"<<fReplacedNodes.size();
		key = ss.str();
	}else{
		if(fReplacedNodes.find(key) != fReplacedNodes.end())
			return key;			//Don't change the node in the list if already added
	}

	fReplacedNodes.insert(pair<string,SIExprArg>(key, ExprSmartCopy::copy(newNode)));

	return key;
}

void ExprCompositor::continueExploration(IExprOperator *arg, IExprArgBase* exprArg)
{

	std::string arg1 = arg->arg1()->accept(this);
	std::string arg2 = arg->arg2()->accept(this);

	if(!arg1.empty())
		replaceNode(arg->arg1(), arg1);

	if(!arg2.empty())
		replaceNode(arg->arg2(), arg2);

	if(arg->arg1()->dynamicEval() || arg->arg2()->dynamicEval())
		exprArg->switchToDynamic();

}

void ExprCompositor::replaceNode(SIExprArg &node, SIExprArg newExpr)
{
	node = newExpr;
}

/****************************************************
 *				ExprSimplificator						*
 * *************************************************/
void ExprSimplificator::simplify(SIExpression &expression)
{
	SIExprArg rootNode = expression->rootNode();
	simplify(rootNode);
	expression->setRootNode(rootNode);
}

void ExprSimplificator::simplify(SIExprArg &rootNode)
{
	ExprSimplificator s;
	s.simplifyNode(rootNode);
}

//__________________________________________________________________
const string ExprSimplificator::eval(IExprOperator *arg, IExprArgBase *exprArg)
{
	if(exprArg->pureStaticEval()){
		//simplifying the node
		std::string nodeDef;
		if(ExprReader::read(exprArg, "", nodeDef)){
			nodeDef = nodeDef.substr(4);		//Removing the "expr" token at the start of the definition
			fSimplifiedNode = new IExprArg<iexpression>(nodeDef);
			*fSimplifiedNode->evaluated() = exprArg->getEvaluated();
		}

	}else{
		//if not statically evaluated try to simplify the params
		simplifyNode(arg->arg1());
		simplifyNode(arg->arg2());
	}

	return "";
}



//___________________________________________________________________
bool ExprSimplificator::simplifyNode(SIExprArg &node)
{
	fSimplifiedNode = SIExprArg(0);
	node->accept(this);

	if(!fSimplifiedNode)
		return false;

	node = SIExprArg(fSimplifiedNode);
	return true;
}



//___________________________________________________________________


/****************************************************
 *				ExprSmartCopy						*
 * *************************************************/


SIExpression ExprSmartCopy::copy(const SIExpression expression)
{
	return IExpression::create(expression->definition(), copy(expression->rootNode()));
}

SIExprArg ExprSmartCopy::copy(const SIExprArg rootNode)
{
	ExprSmartCopy d;
	return SIExprArg(d.smartCopy(rootNode));
}

//___________________________________________________________________
const string ExprSmartCopy::eval(const IExprOperator *arg, const IExprArgBase *exprArg)
{
	SIExprArg arg1 = smartCopy(arg->constArg1());
	SIExprArg arg2 = smartCopy(arg->constArg2());

	IExprOperator* argCopy = new IExprOperator(arg->operatorPrototype(), arg1, arg2);

	fCurrentNode = SIExprArg(new IExprArg<SIExprOperator>(argCopy));

	if(arg1->dynamicEval() || arg2->dynamicEval())
		fCurrentNode->switchToDynamic();

	return "";
}


const string ExprSmartCopy::eval(const string &, const IExprArgBase *exprArg)
{
	fCurrentNode = exprArg->copy();
	return "";
}

const string ExprSmartCopy::eval(const filepath &, const IExprArgBase *exprArg)
{
	fCurrentNode = exprArg->copy();
	return "";
}

const string ExprSmartCopy::eval(const urlpath &, const IExprArgBase *exprArg)
{
	fCurrentNode = exprArg->copy();
	return "";
}

const string ExprSmartCopy::eval(const itladdress &, const IExprArgBase *exprArg)
{
	fCurrentNode = exprArg->copy();
	return "";
}


const string ExprSmartCopy::eval(const iexpression &, const IExprArgBase *exprArg)
{
	fCurrentNode = exprArg->copy();
	return "";
}

//___________________________________________________________________
SIExprArg ExprSmartCopy::smartCopy(const SIExprArg node)
{

	auto iter = fCopyMap.find(node);
	if(iter!=fCopyMap.end())
		return SIExprArg(iter->second);

	((const IExprArgBase*)node)->accept(this);
	fCopyMap.insert({node, SIExprArg(fCurrentNode)});
	return fCurrentNode;
}










} //End namespace

