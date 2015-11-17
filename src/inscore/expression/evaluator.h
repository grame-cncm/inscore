#ifndef EVALUATOR
#define EVALUATOR

#include <string>

namespace inscore{

///Macro defining new string-like types usable in templates (they are not assimilate to template on the contrary to typedef std::string type; ).
struct specializedString{
        std::string string;
        specializedString(std::string s=""){string = s;}
        operator std::string() const {return string;}
};
#define STRING_TYPE(typeName) struct typeName: specializedString{ typeName(std::string s=""):specializedString(s){} };


// Custom String-like type definition
STRING_TYPE(filepath)
STRING_TYPE(itladdress)


class IExpression;
class IExprOperator;

/*!
 * \brief Interface defining an evaluator: it can evaluate specific arguments or an entire expression
 */
class evaluator{
public:

	/*!
	 * \brief eval
	 * \param arg the value to evaluate
	 * \param exprArg the evaluated node, use as a context for the evaluator
	 * \return the evaluated value
	 */
	virtual const std::string eval(IExprOperator* arg, IExpression* exprArg=0)=0;
	virtual const std::string eval(const std::string& arg, IExpression* exprArg=0)=0;
	virtual const std::string eval(const filepath& arg, IExpression* exprArg=0)=0;
	virtual const std::string eval(const itladdress& arg, IExpression* exprArg=0)=0;

};

/*!
 * \brief Unlike evaluator, constEvaluator can't modify expressions trees (apart from the evaluated values)
 */
class constEvaluator: public evaluator{
public:

	virtual const std::string eval(const IExprOperator* arg, const IExpression* exprArg=0)=0;
	virtual const std::string eval(const std::string& arg, const IExpression* exprArg=0)=0;
	virtual const std::string eval(const filepath& arg, const IExpression* exprArg=0)=0;
	virtual const std::string eval(const itladdress& arg, const IExpression* exprArg=0)=0;

	const std::string eval(IExprOperator* arg, IExpression* exprArg=0)		{return eval(arg, (const IExpression*)exprArg);}
	const std::string eval(const std::string& arg, IExpression* exprArg=0)	{return eval(arg, (const IExpression*)exprArg);}
	const std::string eval(const filepath& arg, IExpression* exprArg=0)		{return eval(arg, (const IExpression*)exprArg);}
	const std::string eval(const itladdress& arg, IExpression* exprArg=0)	{return eval(arg, (const IExpression*)exprArg);}

};

/*!
 * \brief Interface for evaluable class (visitable by an evaluator in the visitor design pattern logic)
 */
class evaluable{
public:
	//std::string accept(evaluator& e){return accept(&e);}
	virtual std::string accept(evaluator* e)=0;
	virtual std::string accept(constEvaluator*) const {return "";}
};

}
#endif // EVALUATOR

