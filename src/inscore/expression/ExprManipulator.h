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
typedef std::map<std::string, SIExprArg> ReplaceMap;


//____________________________________________________________________
// ------------------------------------------------------------------

class ExprCompositor: public evaluator{
	const IObject* fContextObject;
	ReplaceMap fReplacedNodes;

	bool succeed;

public:

	static bool compose(SIExprArg& expr, const IObject* contextObject);


	bool apply(SIExprArg& exprTree);

	virtual const std::string eval(IExprOperator *arg, IExprArgBase *exprArg);
	virtual const std::string eval(const std::string&, IExprArgBase*){return "";}
	virtual const std::string eval(const filepath&, IExprArgBase*){return "";}
	virtual const std::string eval(const itladdress &arg, IExprArgBase *exprArg);
	virtual const std::string eval(const IObject*, IExprArgBase*);
	virtual const std::string eval(const iexpression &arg, IExprArgBase *exprArg){return "";}

protected:
	ExprCompositor(const IObject* contextObject, const char* manipulatorName="ExprManipulator");
	std::string replaceBy(SIExprArg newNode, std::string key="");
	void continueExploration(IExprOperator* arg, IExprArgBase *exprArg);

	inline void manipulationFailed(){succeed = false;}

	const char* fManipulatorName;
private:
	void replaceNode(SIExprArg& node, SIExprArg newExpr);
	inline void replaceNode(SIExprArg &node, std::string key){replaceNode(node, fReplacedNodes.at(key));}

};


//____________________________________________________________________
// ------------------------------------------------------------------
class ExprSmartCopy: public constEvaluator{

	std::map<const IExprArgBase*, SIExprArg> fCopyMap;
	SIExprArg fCurrentNode;

public:
	static SIExpression copy(const SIExpression expression);
	static SIExprArg copy(const SIExprArg rootNode);

	virtual const std::string eval(const IExprOperator *arg,	const IExprArgBase *exprArg);
	virtual const std::string eval(const std::string &arg,		const IExprArgBase *exprArg);
	virtual const std::string eval(const filepath &arg,			const IExprArgBase *exprArg);
	virtual const std::string eval(const itladdress &arg,		const IExprArgBase *exprArg);
	virtual const std::string eval(const iexpression &argarg,	const IExprArgBase *exprArg);

protected:
	ExprSmartCopy(): constEvaluator() {}
	SIExprArg fCopyTree;

	SIExprArg smartCopy(const SIExprArg node);

};


}//End namespace


#endif // EXPRMANIPULATOR_H
