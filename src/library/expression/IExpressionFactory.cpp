#include "IExpressionFactory.h"

#include <guidoar/libguidoar.h>
#include <sstream>



using namespace std;

namespace inscore{

/*#define GUIDOAR_OPERATOR(guidoOperator) [](std::string a, std::string b)                            \
                                            {                                                       \
                                            std::ostringstream oss;                                 \
                                            guido::garErr err = guidoOperator( a, b, oss );         \
                                            if ( err == guido::kNoErr )                             \
                                                return oss.str();                                   \
                                            else                                                    \
                                                return "GuidoAR Error!";                            \
                                            }
/*/
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

ExprFactory::ExprFactory(): fOperatorList()
{
    registerOperator("seq", GUIDOAR_OPERATOR(guido::guidoGSeq));
    registerOperator("par", GUIDOAR_OPERATOR(guido::guidoGPar));
    registerOperator("parRight", GUIDOAR_OPERATOR(guido::guidoGRPar));
    registerOperator("duration", GUIDOAR_OPERATOR(guido::guidoGSetDuration));
    registerOperator("transpose", GUIDOAR_OPERATOR(guido::guidoGTranpose));
    registerOperator("head", GUIDOAR_OPERATOR(guido::guidoGHead));
    registerOperator("tail", GUIDOAR_OPERATOR(guido::guidoGTail));
    registerOperator("top", GUIDOAR_OPERATOR(guido::guidoGTop));
    registerOperator("bottom", GUIDOAR_OPERATOR(guido::guidoGBottom));

    registerOperator("rythm", [](std::string str1, std::string str2) -> std::string
                                {
                                    std::ostringstream oss;
                                    guido::garErr err = guido::guidoApplyRythm( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, oss );
                                    if ( err == guido::kNoErr )
                                        return oss.str();
                                    else
                                        return "GuidoAR Error!";
                                });
    registerOperator("pitch", [] (std::string str1, std::string str2) -> std::string
                                {
                                    std::ostringstream oss;
                                    guido::garErr err = guido::guidoApplyPitch( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, guido::kUseLowest, oss );
                                    if ( err == guido::kNoErr )
                                        return oss.str();
                                    else
                                        return "GuidoAR Error!";
                                });
}


//_______________________________________________________
ExprFactory* ExprFactory::create(){
    return new ExprFactory();
}



//_______________________________________________________
bool inscore::ExprFactory::createExpr(std::string operatorName, SIExprArgbase param1, SIExprArgbase param2, SIExpression &expr)
{
    OperatorPrototype* op;
    try{
	op = fOperatorList.at(operatorName);
    }catch(std::out_of_range){
        expr = SIExpression();
        return false;
    }

    expr = new IExpression(op, param1, param2);

    return true;
}

//_______________________________________________________
void ExprFactory::registerOperator(OperatorPrototype *op)
{
    fOperatorList.insert({op->getName(), op});
}


} //end namespace
