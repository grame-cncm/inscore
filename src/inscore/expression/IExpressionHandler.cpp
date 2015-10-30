#include "IExpressionHandler.h"

#include <iostream>

#include "IObject.h"

#include "ExprReader.h"
#include "ExprEvaluator.h"

namespace inscore{


bool IExprHandlerbase::evalExpression(std::string &result) const{
    if(!checkExpression())
		return false;

	return evaluator()->evalExpression(fExprRoot, result);
}

bool IExprHandlerbase::forceEvalExpr(std::string &result){
    if(!checkExpression())
		return false;

	fExprRoot->recursiveClearEvaluated();
	return evaluator()->evalExpression(fExprRoot, result);
}

std::string IExprHandlerbase::printExpression(bool &succeed) const{
	std::string r;
	succeed = ExprReader::read(fExprRoot, r);
	return r;
}

std::string IExprHandlerbase::printExpression() const
{
	bool b=true;
	return printExpression(b);
}

IExprHandlerbase::~IExprHandlerbase()
{
}


//_________________________________________________________
bool IExprHandlerbase::composeExpr(inscore::SIExpression newExpr, std::string &result){
	WatchersList newWatchers;
	newExpr = newExpr->copy();
	if(!ExprCompositor::compose(newExpr, fContextObject, newWatchers))
		return false;

    fExprRoot = newExpr;
	if(fAutoWatch)
		updateWatchers(newWatchers);

    bool r = evalExpression(result);
    if(!r)
	clearExpr();
	return r;
}

void IExprHandlerbase::clearExpr(){
	fExprRoot = nullptr;
	WatchersList clearWatchers;

	if(fAutoWatch)
		updateWatchers(clearWatchers);
}


//________________________________________________________
SIExpression IExprHandlerbase::getExpression() const
{
	return fExprRoot;
}

bool IExprHandlerbase::hasExpression() const
{
	return fExprRoot;
}



//____________________________________________________________
IExprHandlerbase::IExprHandlerbase(IObject *object)
	:fContextObject(object), fAutoWatch(false)
{
}

bool IExprHandlerbase::checkExpression() const
{
	if(!fExprRoot){
		ITLErr<<"ExpressionHandler: no expression to evaluate"<<ITLEndl;
		return false;
	}
	return true;
}

void IExprHandlerbase::updateWatchers(WatchersList newWatchers)
{
	WatchersList addedWatch;

	for (auto itNew = newWatchers.begin(); itNew!=newWatchers.end(); ++itNew) {
		auto itPrev = fWatchers.find(*itNew);

		if(itPrev!=fWatchers.end())				//if a watchers is in both list
			fWatchers.erase(itPrev);
		else
			addedWatch.insert(*itNew);
	}
	//by the end of this process, all new watchers are in addedWatch,
	//all those who need to be deleted are listed by fWatchers
	//and newWatchers still contains the final list of watchers

	SIMessage computeMsg = IMessage::create(fContextObject->getOSCAddress(), kexpression_GetMethod);
	computeMsg->add("compute");

	SIMessageList computeMsgList = IMessageList::create();
	computeMsgList->list().push_back(computeMsg);

	SIMessage watchMsg = IMessage::create("", "watch+");
	watchMsg->add(EventsAble::type2string(EventsAble::kNewData));
	watchMsg->add(computeMsgList);

	//deleting watch not use a	anymore
	for (auto it = fWatchers.begin(); it != fWatchers.end(); ++it)
		std::cout<<fContextObject->name()<<" disconnect from "<<(*it)->name()<<std::endl;
		//it->signalsNode()->disconnectMsg(watchMsg)

	//adding new watch
	for (auto it = addedWatch.begin(); it != addedWatch.end(); ++it)
		std::cout<<fContextObject->name()<<" connect to "<<(*it)->name()<<std::endl;
		//it->addMsg(EventsAble::kNewData, computeMsg);

	fWatchers = newWatchers;
}





}	//End namespace
