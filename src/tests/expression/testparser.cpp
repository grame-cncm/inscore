#include "IExprParser.h"
#include <fstream>


int main( int argc, const char* argv[] )
{
    std::ifstream ifs;
    ifs.open("test.inscore", std::ifstream::in);
    if(!ifs.is_open()){
	std::cerr<<"test.inscore not found..."<<std::endl;
	return -1;
    }

    std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    inscore::SIExpression e;
    if(!inscore::IExprParser::parseExpression(data, e)){
	std::cout<<"Parsing of: \""<<data<<"\" failed."<<std::endl;
	return -1;
    }
    std::cout<<e->rootNode()<<std::endl;
    return 0;
}
