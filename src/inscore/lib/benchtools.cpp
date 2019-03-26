/*
  Copyright (c) Grame 2010

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/

#include <fstream>

#include "benchtools.h"
#include "TSignal.h"

using namespace std;

namespace inscore
{

typedef pair<string,STSignal> BenchUnit;
static vector<BenchUnit>	gBenchs;
static bool					gRunning = false;


//_________________________________________________________________________________
void  bench::init(const char* sigs[], unsigned short size)
{
	gBenchs.clear();
	unsigned int i = 0;
	while (sigs[i] ) {
		gBenchs.push_back( BenchUnit(sigs[i], TSignal::create(sigs[i], size, 0.f)));
		i++;
	}
}

//_________________________________________________________________________________
static STSignal get (const string& name, const vector<BenchUnit>& from)
{
	for (unsigned int i = 0; i < from.size(); i++)
		if (from[i].first == name) return from[i].second;
	return 0;
}

//_________________________________________________________________________________
void bench::put(const string& sig, float val)
{
	if (gRunning) {
		STSignal s = get(sig, gBenchs);
		if (s) *s << val;
		else cerr << "bench::put - no bench named \"" << sig << "\"" << endl;
	}
}

//_________________________________________________________________________________
void  bench::start()		{ gRunning = true; }
void  bench::stop()			{ gRunning = false; }
bool  bench::running()		{ return gRunning; }

#define kFieldSep	"	"
//_________________________________________________________________________________
void  bench::write(const std::string& name)
{
	ofstream file (name.c_str());
	int avail = 0;
	for (unsigned int i = 0; i < gBenchs.size(); i++) {
		if (gBenchs[i].second->available() > avail) avail = gBenchs[i].second->available();
		file << gBenchs[i].first << kFieldSep;
	}
	file << endl;
	for (int n = 0; n < avail; n++) {
		for (unsigned int i = 0; i < gBenchs.size(); i++)
			file << (int)(*(gBenchs[i].second))[n] << kFieldSep;
		file << endl;
	}
	file.close();
}

} // end namespace
