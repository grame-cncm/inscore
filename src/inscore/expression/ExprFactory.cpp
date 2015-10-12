#include "ExprFactory.h"


//#include <sstream>
#include <string>
#include <regex>



using namespace std;

namespace inscore{


/*
#define GUIDOAR_OPERATOR(guidoOperator) [](std::string str1, std::string str2) -> std::string{return operate(str1, str2, guidoOperator);}


typedef guido::garErr (*GuidoAROperation)( const char * , const char * , std::ostream& );

std::string operate(const std::string str1, const std::string str2, GuidoAROperation operation){
    std::ostringstream oss;
    guido::garErr err = operation( str1.c_str(), str2.c_str(), oss );
    if ( err == guido::kNoErr )
        return oss.str();
    else
        return "GuidoAR Error!";
}
//*/

ExprFactory::ExprFactory()
{
//    registerOperator("seq", GUIDOAR_OPERATOR(guido::guidoGSeq));
//    registerOperator("par", GUIDOAR_OPERATOR(guido::guidoGPar));
//    registerOperator("parRight", GUIDOAR_OPERATOR(guido::guidoGRPar));
//    registerOperator("duration", GUIDOAR_OPERATOR(guido::guidoGSetDuration));
//    registerOperator("transpose", GUIDOAR_OPERATOR(guido::guidoGTranpose));
//    registerOperator("head", GUIDOAR_OPERATOR(guido::guidoGHead));
//    registerOperator("tail", GUIDOAR_OPERATOR(guido::guidoGTail));
//    registerOperator("top", GUIDOAR_OPERATOR(guido::guidoGTop));
//    registerOperator("bottom", GUIDOAR_OPERATOR(guido::guidoGBottom));

//    registerOperator("rythm", [](std::string str1, std::string str2) -> std::string
//                                {
//                                    std::ostringstream oss;
//                                    guido::garErr err = guido::guidoApplyRythm( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, oss );
//                                    if ( err == guido::kNoErr )
//                                        return oss.str();
//                                    else
//                                        return "GuidoAR Error!";
//                                });
//    registerOperator("pitch", [] (std::string str1, std::string str2) -> std::string
//                                {
//                                    std::ostringstream oss;
//                                    guido::garErr err = guido::guidoApplyPitch( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, guido::kUseLowest, oss );
//                                    if ( err == guido::kNoErr )
//                                        return oss.str();
//                                    else
//                                        return "GuidoAR Error!";
//                                });
}

std::unordered_map<std::string, OperatorPrototype*> ExprFactory::operatorList = std::unordered_map<std::string, OperatorPrototype*>();

//_______________________________________________________
ExprFactory* ExprFactory::create(){
	return new ExprFactory();
}

//_______________________________________________________
SIExprArgbase ExprFactory::createArg(std::string string)
{
	std::regex fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");
	if(std::regex_match(string, fileRegex))
		return createArg<filepath>(string);

	return createArg<std::string>(string);
}



//_______________________________________________________
bool inscore::ExprFactory::createExpr(std::string operatorName, SIExprArgbase param1, SIExprArgbase param2, SIExpression &expr)
{

    OperatorPrototype* op;

	if(!operatorByName(operatorName, op)){
		return false;
		expr = SIExpression();
	}

	expr = new IExpression(op, param1, param2);

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
