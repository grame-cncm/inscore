
#include <iostream>
#include <fstream>
#include "../mapparser.h"
#include "../basicmapreader.h"
#include "../long2D_to_rational_reader.h"
#include "../float2D_to_rational_reader.h"
#include "../long_to_rational_reader.h"
#include "../float_to_rational_reader.h"
#include "testreader.h"

using namespace std;
using namespace libmapping;

int main (int argc, char* argv[])
{
	cout << "Mapping parser test" << endl;
	for (int i=1; i<argc; i++) {
#if 0
		testreader r;
#else
//		basicmapreader r;
//		long2D_to_rational_reader r;
//		float2D_to_rational_reader r;
//		long_to_rational_reader r;
		float_to_rational_reader r;
#endif
		fstream f ( argv[i]);
		if (f.is_open()) {
			cout << "reading " << argv[i] << endl;
			mapparser p (&r, &f);
			if  (p.parse())
				cout << *(r.mapping()) << endl;
		}
		else cerr << "can't open " << argv[i] << endl;
	}
	return 0;
}
