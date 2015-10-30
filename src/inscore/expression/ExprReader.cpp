#include "ExprReader.h"

#include "IExpression.h"

#define TAB "   "

namespace inscore{

bool ExprReader::evalExpression(const IExpression *expr, std::string &result)
{
	fTab = 0;
    evalSucceed = true;

	result = prefix();

	fPrefix = "    ";
	result += "expr"+expr->accept(this);

	if(fTab!=0)
		return false;
    return evalSucceed;
}

bool ExprReader::read(const IExpression *expr, std::string prefix, std::string &result)
{
	ExprReader r;
	r.fPrefix = prefix;
	return r.evalExpression(expr, result);
}

//_________________________________
const std::string ExprReader::eval(const std::string& arg, const IExpression *)
{
	return prefix(arg);
}

//_________________________________
const std::string ExprReader::eval(const IExprOperator *arg, const IExpression *)
{
	fTab++;
	std::string arg1 = ((const IExpression*)arg->constArg1())->accept(this);
	std::string arg2 = ((const IExpression*)arg->constArg2())->accept(this);
	fTab--;

	std::string r= "( "+arg->getName();

	if(	arg1.length() > 20 || arg1.find('\n') != std::string::npos
	 ||	arg2.length() > 20 || arg2.find('\n') != std::string::npos ){
		//multiline structure
		r	+=							+ "\n"
			+ prefix()	+ TAB	+ arg1	+ "\n"
			+ prefix()	+ TAB	+ arg2	+ "\n"
			+ prefix()	+ ")";
	}else
		r+= " "+ arg1 + " " + arg2 + " " + ")";

	return r;
}

//_________________________________
const std::string ExprReader::eval(const filepath& arg, const IExpression *exprArg)
{
	return argPrefix(exprArg) + prefix(arg);
}

//_________________________________
const std::string ExprReader::eval(const itladdress &arg, const IExpression *exprArg)
{
	return argPrefix(exprArg) + prefix(arg);
}

std::string ExprReader::argPrefix(const IExpression *exprArg)
{
	if(!exprArg)
		return "";

	std::string r = "";


	std::string evaluated = exprArg->getEvaluated();
	if(!evaluated.empty()){
		if(evaluated.find('\n') == std::string::npos)
			r+="[\""+evaluated+"\"]";	//Single line
		else{
			r+= "[\"";				//Multi line
			fTab++;
			r+= prefix("\n"+evaluated) + "\n";
			fTab--;
			r+= prefix() + "\"]";
		}
	}


	if(exprArg->dynamicEval())
		r+="&";
	if(exprArg->copyEval())
		r+="~";

	return r;
}

std::string ExprReader::prefix(std::string applyPrefixTo)
{
	std::string prefix = fPrefix;
	for (int i = 0; i < fTab; ++i)
		prefix+=TAB;

	if(applyPrefixTo=="")
		return prefix;

	auto it = applyPrefixTo.find('\n');
	while(it != std::string::npos){
		it++;
		applyPrefixTo.insert(it, prefix);
		it = applyPrefixTo.find('\n', it);
	}

	return applyPrefixTo;
}


//_________________________________
ExprReader::ExprReader()
	:constEvaluator()
{
    evalSucceed = true;
}



} //end namespace
