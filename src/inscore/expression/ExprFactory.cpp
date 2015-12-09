#include <string>
#include <deelx.h>

#include "ExprFactory.h"

#include "ITLError.h"
#include "TFile.h"



using namespace std;

namespace inscore{

SIExprArg ExprFactory::createArg(const std::string &arg)
{
	SIExprArg argResult;


	//  /?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+
	CRegexpT<char> fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");

	//  (../)*([_a-zA-Z0-9]+/)*[_a-zA-Z0-9]+
	CRegexpT<char> identifierRegex("(\\.\\./)*([_a-zA-Z0-9]+/)*[_a-zA-Z0-9]+");


	if(fileRegex.MatchExact(arg.c_str()).IsMatched() || Tools::isurl(arg)){
			//First check if is filepath or an url
		argResult = new IExprArg<filepath>(arg);

	}else if(identifierRegex.MatchExact(arg.c_str()).IsMatched()){
			//Then if is INScore objects
		argResult = new IExprArg<itladdress>(arg);
	}

			//If nothing was found encapsulate the string as it is...
	if(!argResult)
		argResult = new IExprArg<std::string>(arg);

	return argResult;
}

//_______________________________________________________
SIExprArg ExprFactory::createExpr(string operatorName, SIExprArg param1, SIExprArg param2)
{
	SIExprOperator expr;
	if(ExprFactory::createExpr(operatorName, param1, param2, expr))
		return new IExprArg<SIExprOperator>(expr);

	ITLErr<<"ExpressionFactory error: operator \""<< operatorName <<"\" unknown"<<ITLEndl;
	return createEmptyArg();
}


//_______________________________________________________
bool inscore::ExprFactory::createExpr(std::string operatorName, SIExprArg param1, SIExprArg param2, SIExprOperator &expr)
{

	expr = new IExprOperator(operatorName, param1, param2);

	return true;
}

} //end namespace
