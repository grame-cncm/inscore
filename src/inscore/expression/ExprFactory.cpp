#include <string>
#include <regex>
#include <QUrl>

#include "ExprFactory.h"

#include "ITLError.h"



using namespace std;

namespace inscore{

std::unordered_map<std::string, OperatorPrototype*> ExprFactory::operatorList = std::unordered_map<std::string, OperatorPrototype*>();

SIExprArg ExprFactory::createArg(const std::string &arg)
{
	SIExprArg argResult;


	//  /?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+
	std::regex fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");

	//  (../)*([_a-zA-Z0-9]+/)*[_a-zA-Z0-9]+
	std::regex identifierRegex("(\\.\\./)*([_a-zA-Z0-9]+/)*[_a-zA-Z0-9]+");


	if(std::regex_match(arg, fileRegex)){
			//First check if is filepath
		argResult = new IExprArg<filepath>(arg);

	}else if(std::regex_match(arg, identifierRegex)){
			//Then if is INScore objects
		argResult = new IExprArg<itladdress>(arg);
	}
//	else if(QUrl(QString::fromStdString(arg)).isValid()){
//			//Check for url
//		argResult = new IExprArg<urlpath>(arg);
//	}

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

    OperatorPrototype* op;

	if(!operatorByName(operatorName, op)){
		return false;
		expr = SIExprOperator();
	}

	expr = new IExprOperator(op, param1, param2);

	return true;
}



//_______________________________________________________
void ExprFactory::registerOperator(OperatorPrototype* op)
{
	ExprFactory::operatorList.insert({op->getName(), op});
}

bool ExprFactory::operatorByName(string name, OperatorPrototype*& op)
{
	auto iter = operatorList.find(name);

	if(iter == operatorList.end())
		return false;

	op = iter->second;

	return true;
}

} //end namespace
