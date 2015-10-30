#ifndef EXPRMANIPULATOR_H
#define EXPRMANIPULATOR_H

#include <string>
#include <unordered_set>
#include <stack>
#include <map>
#include <utility>

#include "IExpression.h"


namespace inscore {

class IObject;
typedef std::unordered_set<const IObject*> WatchersList;
typedef std::map<std::string, SIExpression> ReplaceMap;


//____________________________________________________________________
// ------------------------------------------------------------------

class ExprManipulator: public evaluator{
	const IObject* fContextObject;
	ReplaceMap fReplacedNodes;
	WatchersList fWatchers;
	const char* fManipulatorName;

	bool succeed;

public:

	bool apply(SIExpression& expr, WatchersList& watchers);
	bool apply(SIExpression& expr){ WatchersList w; return apply(expr, w); }

	virtual const std::string eval(IExprOperator *arg, IExpression *exprArg);
	virtual const std::string eval(const std::string& arg, IExpression *exprArg){return "";}
	virtual const std::string eval(const filepath& arg, IExpression *exprArg){return "";}
	virtual const std::string eval(const itladdress &arg, IExpression *exprArg);
	virtual const std::string eval(const IObject* arg, IExpression *exprArg){return "";}

protected:
	ExprManipulator(const IObject* contextObject, const char* manipulatorName="ExprManipulator");
	std::string replaceBy(SIExpression newNode, std::string key="");
	std::string continueExploration(IExprOperator* arg, IExpression *exprArg);

	inline void manipulationFailed(){succeed = false;}
private:
	void replaceNode(SIExpression& node, SIExpression newExpr);
	inline void replaceNode(SIExpression &node, std::string key){replaceNode(node, fReplacedNodes.at(key));}

};


//____________________________________________________________________
// ------------------------------------------------------------------
class ExprCompositor: public ExprManipulator{

public:
	static bool compose(SIExpression& expr, const IObject* contextObject, WatchersList &watchers);

	const std::string eval(const IObject* arg, IExpression *exprArg);
protected:
	ExprCompositor(const IObject* contextObject);
};


}//End namespace


#endif // EXPRMANIPULATOR_H
