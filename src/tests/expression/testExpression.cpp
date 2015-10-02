#include <iostream>
#include <fstream>
#include "TScripting.h"
#include "ITLparser.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "ExprEvaluator.h"
#include "ExprReader.h"

using namespace inscore;
using namespace std;

int main(int argc, char * argv[])
{

    //*
    TScripting reader(0);
    Sbaseparam* e = reader.createExpr("plus", reader.createArg<std::string>("Hello "), reader.createArg<std::string>("World!"));

    if(e == NULL)
        return -1;
    SIExpression expr = TScripting::exprFromParam(e);

    if(expr == NULL)
        return -1;

    std::string r;

    ExprEvaluator* evalutator = ExprEvaluator::create();
    evalutator->evalExpression(expr, r);
    std::cout<<r<<std::endl;

    evalutator = ExprReader::create();
    evalutator->evalExpression(expr, r);
    std::cout<<r<<std::endl;

    /*/

    Sbaseparam* e;

    if (argc > 1) {
        ifstream in (argv[1]);
        ITLparser p(&in, 0, 0, 0);

        SIMessageList outMsgs;
        outMsgs = p.parse ();
        if (outMsgs) {
            outMsgs->list().set("", "\n");
            cout << outMsgs->list() << endl;
        }
        else
            cout << "error reading " << argv[1] << endl;
    }

    //*/


    return 0;
}

