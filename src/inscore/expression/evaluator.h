#ifndef EVALUATOR
#define EVALUATOR

#include <string>

namespace inscore{

//Custom acceptable type as arguments


struct specializedString{
        std::string string;
        specializedString(std::string s=""){string = s;}
        operator std::string() const {return string;}
};
#define STRING_TYPE(typeName) struct typeName: specializedString{ typeName(std::string s=""):specializedString(s){} };

STRING_TYPE(filepath)
STRING_TYPE(itladdress)


class IExpression;
class IExprOperator;

/*!
 * \brief Interface defining an evaluator: it can evaluate specific arguments or an entire expression
 */
class evaluator{
public:

	virtual const std::string eval(IExprOperator* arg, IExpression* exprArg=0)=0;
	virtual const std::string eval(const std::string& arg, IExpression* exprArg=0)=0;
	virtual const std::string eval(const filepath& arg, IExpression* exprArg=0)=0;
	virtual const std::string eval(const itladdress& arg, IExpression* exprArg=0)=0;

};

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

