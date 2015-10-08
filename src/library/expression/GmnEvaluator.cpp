#include "GmnEvaluator.h"
#include "IGuidoCode.h"

#include <guidoar/libguidoar.h>
#include <sstream>

using namespace std;

namespace inscore{

#define GUIDOAR_OPERATOR(guidoOperator) [](std::string str1, std::string str2) -> std::string						\
											{																		\
											std::ostringstream oss;													\
											guido::garErr err = guidoOperator( str1.c_str(), str2.c_str(), oss );	\
											if ( err == guido::kNoErr )												\
												return oss.str();													\
											return "";																\
											}



GmnEvaluator::GmnEvaluator(const IObject *contextObject): ExprEvaluator("GmnEvaluator",contextObject)
{
	registerOperator(opGuidoSeq,	GUIDOAR_OPERATOR(guido::guidoGSeq));
	registerOperator(opGuidoPar,	GUIDOAR_OPERATOR(guido::guidoGPar));
	registerOperator(opGuidoParR,	GUIDOAR_OPERATOR(guido::guidoGRPar));
	registerOperator(opGuidoDur,	GUIDOAR_OPERATOR(guido::guidoGSetDuration));
	registerOperator(opGuidoTrans,	GUIDOAR_OPERATOR(guido::guidoGTranpose));
	registerOperator(opGuidoHead,	GUIDOAR_OPERATOR(guido::guidoGHead));
	registerOperator(opGuidoTail,	GUIDOAR_OPERATOR(guido::guidoGTail));
	registerOperator(opGuidoTop,	GUIDOAR_OPERATOR(guido::guidoGTop));
	registerOperator(opGuidoBottom,	GUIDOAR_OPERATOR(guido::guidoGBottom));

	registerOperator(opGuidoRythm, [](std::string str1, std::string str2) -> std::string
								{
									std::ostringstream oss;
									guido::garErr err = guido::guidoApplyRythm( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, oss );
									if ( err == guido::kNoErr )
										return oss.str();
									else
										return "GuidoAR Error!";
								});
	registerOperator(opGuidoPitch, [] (std::string str1, std::string str2) -> std::string
								{
									std::ostringstream oss;
									guido::garErr err = guido::guidoApplyPitch( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, guido::kUseLowest, oss );
									if ( err == guido::kNoErr )
										return oss.str();
									else
										return "GuidoAR Error!";
								});
}

//_____________________________________________________
std::string GmnEvaluator::eval(const IObject *arg)
{
    const IGuidoCode* guido = dynamic_cast<const IGuidoCode*>(arg);
    if(!guido){
        ITLErr << "GmnEvaluator: the object "<<arg->name()<<" is not a guido object"<<ITLEndl;
        fEvalStatus.fail();
        return "";
    }

    return guido->getGMN();
}

} //end namespace
