#include "IExprParser.h"
#include <fstream>

using namespace std;

int main( int argc, const char* argv[] )
{
	for (int i=1; i<argc; i++) {
		const char* arg = argv[i];
		std::ifstream ifs;
		cout << "check " << arg << ":" << endl;
		ifs.open(arg, ifstream::in);
		if(!ifs.is_open()){
			cerr << arg << ": not found..." << endl;
			return -1;
		}

		string data((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
		inscore::SIExpression e;
		if(!inscore::IExprParser::parseExpression(data, e)){
			cerr << "Parsing of: \"" << data << "\" failed." << endl;
			return -1;
		}
		cout << " => " << e << endl;
	}
    return 0;
}
