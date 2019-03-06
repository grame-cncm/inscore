
#include "TreeTools.h"

using namespace std;


namespace inscore2
{

//------------------------------------------------------------
string lowercase (const string& str)
{
	string out = str;
	std::transform (out.begin(), out.end(), out.begin(), ::tolower);
	return out;
}

//------------------------------------------------------------
bool isNumber (const char* str)
{
	while (*str) {
		if (isdigit(*str++) == 0) return false;
	}
	return true;
}

} // end namespace
