
#include <iostream>
#include <fstream>
#include <sstream>

#include "mathparser.h"

using namespace std;

void init(std::stringstream * stream, void * scanner);
void yyparse();


int main (int argc, char * argv[])
{
	setlocale(LC_NUMERIC, "C");
	
	stringstream s;
	mathparser p (&s);

	cout << "Test math operations parser" << endl;
	string input;
	do {
		getline(cin, input);
		if (input == "quit") break;
		s.clear();
		s << input;
		p.parse ();
	} while (1);
	
/*
	if (argc > 1) {
		ifstream in (argv[1]);

		TestEnv env;
		ITLparser p(&in, 0, &env);
		SIMessageList outMsgs;
		outMsgs = p.parse ();
		if (outMsgs) {
			outMsgs->list().set("", "\n");
			cout << outMsgs->list() << endl;
		}
		else
			cout << "error reading " << argv[1] << endl;
	}
*/
 	return 0;
}

