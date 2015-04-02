

#include <iostream>

#include "segment.h"
#include "segmentation.h"
#include "relation.h"
#include "surjection.h"


using namespace std;
using namespace interlude;

const char * nodes[] = {
	"A", "B", "C", "D", "E", "F", 0
};

typedef surjection<string,string>	syncMap;

//--------------------------------------------------------------------------------
typedef struct compare {
	compare( const syncMap& s) : fSync(s) {}

	const syncMap& fSync;

	bool comp (const string& i, const string& j, map<string, string>& hist) const { 
		if (hist[j]==i)	{		// here we catch the loop case
			cerr << "WARNING! loop detected for node " << i << endl;
			return false;		
		}

		syncMap::const_iterator s = fSync.find(i);
		if (s == fSync.end())	// not synced
			return true;
		syncMap::const_iterator s2 = fSync.find(j);
		if (s2 == fSync.end())	// synced but second not synced
			return false;
		if (s2->second == i)	// master of the second
			return true;
		hist[j]=i;
		return comp(i, s2->second, hist);
	}

	bool operator() (const string& i, const string& j) const	{ 
		map<string, string> history;
		return comp(i, j, history); 
	}

}compare;

//--------------------------------------------------------------------------------
static void print(const syncMap& sync)
{
	for (syncMap::const_iterator i = sync.begin(); i != sync.end(); i++)
		cout << i->first << " -> " << i->second << endl;
}

//--------------------------------------------------------------------------------
static void print(const vector<string>& v)
{
	for (vector<string>::const_iterator i = v.begin(); i != v.end(); i++)
		cout << (*i) << " ";
	cout << endl;
}

//--------------------------------------------------------------------------------
static void addlink(const string& a, const string& b, syncMap& sync)
{
	cout << "sync " << a << " -> " << b << endl;
	sync[a] = b;
}

//--------------------------------------------------------------------------------
static void testsync()
{
	syncMap sync;
	vector<string> v;
	const char ** ptr = nodes;
	while (*ptr)  v.push_back(*ptr++);
	
	print (v);

	addlink ("A", "B", sync);
	addlink ("D", "C", sync);
	addlink ("C", "B", sync);
	addlink ("F", "C", sync);
//	addlink ("B", "A", sync);
	
	print(sync);

	compare c(sync);
	sort(v.begin(), v.end(), c);

	print (v);
	
}

//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	cout << "---------------------------" << endl;
	cout << "Synchronization tests" << endl;
	cout << "---------------------------" << endl;
	testsync();
	return 0;
}
