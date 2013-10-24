

#include <iostream>
#include <string>

#include "INScore.h"

using namespace std;
using namespace inscore;


static const string verbopt1 = "-v";
static const string verbopt2 = "--v";

int main (int argc, char * argv[])
{
	bool verbose = (argc == 2) && (verbopt1 == argv[1] || verbopt2 == argv[1] );
	if (verbose) cout << "INScore version ";
	cout << INScore::versionStr() << endl;
	return 0;
}
