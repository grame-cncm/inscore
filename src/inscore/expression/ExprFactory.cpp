#include "ExprFactory.h"


//#include <sstream>
#include <string>
#include <regex>



using namespace std;

namespace inscore{

std::unordered_map<std::string, OperatorPrototype*> ExprFactory::operatorList = std::unordered_map<std::string, OperatorPrototype*>();

//_______________________________________________________
//ExprFactory* ExprFactory::create(){
//	return new ExprFactory();
//}

//_______________________________________________________
SIExpression ExprFactory::createArg(std::string string)
{
	std::regex fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");
	if(std::regex_match(string, fileRegex))
		return createArg<filepath>(string);

	return createArg<std::string>(string);
}

//_______________________________________________________
SIExpression ExprFactory::createArg(SIExprOperator expression)
{
	return createArg<SIExprOperator>(expression, expression->dynamicEval());
}



//_______________________________________________________
bool inscore::ExprFactory::createExpr(std::string operatorName, SIExpression param1, SIExpression param2, SIExprOperator &expr)
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
