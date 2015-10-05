#include <iostream>
#include <fstream>
#include "TScripting.h"
#include "ITLparser.h"
#include "IMessage.h"
#include "IMessageStream.h"

using namespace inscore;
using namespace std;

int main(int argc, char * argv[])
{

    /*
    TScripting reader(0);
    Sbaseparam* e = reader.createExpr("pitch", reader.createArg<filepath>(new std::string("score.gmn")), reader.createArg<std::string>("[e f g]"));

    if(e == NULL)
        return -1;
    SIExpression expr = TScripting::exprFromParam(e);

    if(expr == NULL)
        return -1;

    std::string r;

    std::cout<<"ExprEvaluator::eval():"<<endl;
    ExprEvaluator* evalutator = ExprEvaluator::create();
    if(evalutator->evalExpression(expr, r))
        std::cout<<r<<std::endl;


    std::cout<<"__________________________________"<<endl;

    std::cout<<"ExprReader::eval():"<<endl;
    evalutator = ExprReader::create();
    if(evalutator->evalExpression(expr, r))
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

