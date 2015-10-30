#ifndef IEXPRESSION_H
#define IEXPRESSION_H

#include <string>
#include <list>

#include "IExpression.h"
#include "evaluator.h"
#include "ExprManipulator.h"
#include "ITLError.h"

namespace inscore {

class IObject;
class ExprEvaluator;


class IExprHandlerbase{

	SIExpression fExprRoot;
	IObject* fContextObject;
	WatchersList fWatchers;
	bool fAutoWatch;

public:
	bool evalExpression(std::string& result) const;
	bool forceEvalExpr(std::string& result);

	bool composeExpr(SIExpression newExpr, std::string &result);
	void clearExpr();

	SIExpression getExpression() const;
	bool hasExpression() const;
	std::string printExpression(bool& succeed) const;
	std::string printExpression() const;

	void setAutoWatch(bool autoWatch=true){fAutoWatch = autoWatch;}
	bool autoWatch() const {return fAutoWatch;}

	 virtual ~IExprHandlerbase();

protected:
	IExprHandlerbase(IObject* object);
	virtual ExprEvaluator* evaluator() const =0;
	inline const IObject* contextObject() const {return fContextObject;}

	bool checkExpression() const;
	void updateWatchers(WatchersList newWatchers);
};




template <typename evaluatorT>
class IExprHandler: public IExprHandlerbase
{
public:
	explicit IExprHandler(IObject* object): IExprHandlerbase(object){}
	virtual ~IExprHandler(){}
protected:
	ExprEvaluator* evaluator() const {return evaluatorT::create(contextObject());}
};

} //end namespace

#endif // IEXPRESSION_H
