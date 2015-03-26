
#define RationalRelation

#include <iostream>
#include <set>
#include <vector>
#include <stdlib.h>
#include <string.h>

#include "MapTools.h"
#include "TComposition.h"
#include "TMapping.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "TRelation.h"
#include "TVirtualRelation.h"
#include "rational.h"


using namespace std;
using namespace interlude;

typedef struct RedMap {
	TSegment<int,1>		tseg;
	TSegment<float,2> 	gseg;
} RedMap;

typedef TSegment<int,1>		TI;
typedef TSegment<float,2>	TF;
typedef TInterval<float>	FI;

#define gMapSize	6
RedMap gMap[] = {
	{ TI(0,1), TF( FI(0,1), FI(0,2)) },
	{ TI(1,2), TF( FI(1,2), FI(0,2)) },
	{ TI(2,3), TF( FI(1,2), FI(0,2)) },
	{ TI(3,4), TF( FI(3,4), FI(2,4)) },
	{ TI(4,5), TF( FI(4,5), FI(2,4)) },
	{ TI(5,6), TF( FI(5,6), FI(2,4)) }
};

//RedMap gMap[] = {
//	{ TI(0,1), TF( FI(0,1), FI(0,2)) },
//	{ TI(1,2), TF( FI(1,2), FI(0,2)) },
//	{ TI(2,3), TF( FI(1,2), FI(0,2)) },
//	{ TI(3,4), TF( FI(3,4), FI(2,4)) },
//	{ TI(4,5), TF( FI(4,5), FI(2,4)) },
//	{ TI(5,6), TF( FI(5,6), FI(2,4)) }
//};

static const char* bstr(bool v)		{ return (v ? "yes" : "no"); }

#ifdef RationalRelation
std::ostream& operator << (std::ostream& out, const MapTools::Relation& r)
#else
template <typename T> std::ostream& operator << (std::ostream& out, const MapTools::Relation<T>& r) 
#endif
{
	out << "(" << r.r << "," << r.p << ")";
	return out;
}

template <typename T> 
std::ostream& operator << (std::ostream& out, const vector<T>& v) { 
	for (unsigned int i=0; i < v.size(); i++)
		out << v[i] << " ";
	return out;
}

template <typename T> 
std::ostream& operator << (std::ostream& out, const set<T>& s) { 
	typedef typename set<T>::const_iterator const_iterator;
	for (const_iterator i=s.begin(); i != s.end(); i++)
		out << *i << " ";
	return out;
}

template <typename T> 
std::ostream& operator << (std::ostream& out, const pair<T,T>& p) { 
	out << "(" << p.first << "," << p.second << ")";
	return out;
}

//--------------------------------------------------------------------------------
static void testrational(float f)
{
	cout << "testrational float " << f << " => ";
	rational r(f);
	cout << r << " -> " << float(r) << " err: " << (f - float(r)) << endl;
}

//--------------------------------------------------------------------------------
static void testrational(float f, float g)
{
	cout << "testrational float float (" << f << "," << g << ") => ";
	rational r(f,g);
	cout << r << " -> " << float(r) << " err: " << (f/g - float(r)) << endl;
}

//--------------------------------------------------------------------------------
void testrational()
{
	testrational(1.23456789123456789);
	testrational(0.123456789);
	testrational(123456789.123456789);
	testrational(-1.23456789);
	testrational(-0.123456789);
	testrational(-123456789.123456789);

	testrational(0.5);
	testrational(0.333333333);
	testrational(0.25);	
	testrational(2., 0.5);
	testrational(0.5, 2.);
	testrational(1., 2.);
}

//--------------------------------------------------------------------------------
template<typename T> T random (T range)			{ return T((rand() / float(RAND_MAX)) * float(range)); }
template<> rational random (rational range)		{ 
	long n = (rand() / float(RAND_MAX)) * float(range);
	long d = (rand() / float(RAND_MAX)) * float(range);
	rational r(n, d); 
	r.rationalize();
	return r;
}

//--------------------------------------------------------------------------------
template<typename T> TInterval<T> randomInterval (T range)
{
	T a = random (range);
	T b = random (range);
	return TInterval<T> (min(a,b), max(a,b));
}

//--------------------------------------------------------------------------------
template<typename T, int D> struct randomSegment {};

template<typename T> struct randomSegment<T,1>
{
	TSegment<T,1> operator() (int range=200) {
		T v1 = (rand() / float(RAND_MAX)) * range;
		T v2 = (rand() / float(RAND_MAX)) * range;
//		T v2 = v1 + T((rand() / float(RAND_MAX)) * range / 2);
		return TSegment<T,1>(min(v1,v2), max(v1,v2));
	}
};

template <> struct randomSegment<rational,1>
{
	TSegment<rational,1> operator() (int range=200) {
		rational v1 (int((rand() / float(RAND_MAX)) * range));
		rational v2 (int((rand() / float(RAND_MAX)) * range));
		return TSegment<rational,1>(min(v1,v2), max(v1,v2));
	}
};

template<typename T> struct randomSegment<T,2>
{
	TSegment<T,2> operator() (int range=200) {
		T v1 = (rand() / float(RAND_MAX)) * range;
		T v2 = v1 + (rand() / float(RAND_MAX)) * range / 2;
		T v3 = (rand() / float(RAND_MAX)) * range;
		T v4 = v3 + (rand() / float(RAND_MAX)) * range / 2;
		return TSegment<T,2>(v1, v3, v2, v4);
	}
};

//--------------------------------------------------------------------------------
template<typename T> void print(const T& s)
{
	cout << s << " \t size: " << s.size() << " empty? " << bstr(s.empty()) << endl;
}

//--------------------------------------------------------------------------------
template<typename T, unsigned int D, typename R> void testSegments(int n)
{
	cout << "\ntestSegments " << D << "D (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	for (int i=0; i< n; ) {
		TSegment<T,D> s1 = randomSegment<T, D>()(10);
		TSegment<T,D> s2 = randomSegment<T, D>()(10);
		R  r = MapTools::relation(s1, s2);
		TSegment<T,D> sr = MapTools::related(s1, r);
		if (s1.intersect(s2)) {
			cout << string(s1) << " - " << string(s2) << " => intersection: " << string(s1 & s2) 
				 <<  " relation: " << r << " related: " << sr << endl;
			i++;
			if (sr != s2)
				cout << " Warning! related: " << string(sr) << " - expecting: " << string(s2) << endl; 
		}
	}
}

//--------------------------------------------------------------------------------
template<typename T, int D> SMARTP<TSegmentation<TSegment<T,D> > > buildSegmentation(int n, const TSegment<T,D>& r)
{
	SMARTP<TSegmentation<TSegment<T,D> > > s = TSegmentation<TSegment<T,D> >::create(r);
	for (int i=0; i < n; ) {
		TSegment<T,D> seg = randomSegment<T, D>()();
//		if (seg.size() && s->add( seg )) i++;
		if (s->add( seg )) i++;
	}
	return s;
}

//--------------------------------------------------------------------------------
template<typename T, unsigned D> void testSegmentation(int n)
{
	cout << "\ntestSegmentation "<< D << "D (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	TInterval<T> bounds(T(0), T(200));
	TSegment<T,D> r (bounds);
	
	SMARTP<TSegmentation<TSegment<T,D> > > s1 = buildSegmentation<T,D>(n, r);
	cout << (*s1) << endl;
	SMARTP<TSegmentation<TSegment<T,D> > > s2 = buildSegmentation<T,D>(n, r);
	cout << (*s2) << endl;

	for (int i=0; i < n; i++) {
		TSegment<T,D> r = randomSegment<T, D>()();
		TSegment<T,D> foundbeg = s1->find(r.start());
		TSegment<T,D> foundend = s1->find(r.end());
		cout << "looking for segment " << r << " locations: ";
		if (foundbeg.size()) cout << r.start() << " -> " << foundbeg << " ";
		if (foundend.size()) cout << r.end() << " -> " << foundend;
		cout << endl;
	}
	cout << "intersection : " << endl;
	SMARTP<TSegmentation<TSegment<T,D> > > si = MapTools::intersect (s1, s2);
	cout << (*si) << endl;
	cout << "intersection v2 : " << endl;
//	si = MapTools::intersect<set<TSegment<T,D> > > (s1->begin(), s1->end(), s2->begin(), s2->end());
	set<TSegment<T,D> > inter;
	MapTools::intersect (s1->begin(), s1->end(), s2->begin(), s2->end(), inter);
	cout << inter << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void buildRelation(int n, T1 range1, T2 range2, TRelation<T1, T2>& relation)
{
	for (int i = 0; i < n; i++) {
		T1 o = random(range1);
		int rr = max(1, random(3));
		for (int j = 0; j < rr; j++) {
			T2 ro = random(range2);
			relation.add (o, ro);
		}
	}
}

//--------------------------------------------------------------------------------
template<typename T1, int D1, typename T2, int D2> 
void buildSegRelation(int n, TRelation<TSegment<T1,D1>, TSegment<T2,D2> >& relation)
{
	for (int i = 0; i < n; i++) {
		TSegment<T1,D1> s = randomSegment<T1,D1>()(20);
		int rr = max(1, random(2));
		for (int j = 0; j < rr; j++) {
			TSegment<T2,D2> rs = randomSegment<T2,D2>()(20);
			relation.add (s, rs);
		}
	}
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void testRelation(int n, T1 range1, T2 range2)
{
	cout << "\ntestRelation (" << n << ")" << endl;
	TRelation<T1, T2> relation;
	buildRelation (n, range1, range2, relation);
	cout << relation;
}

//--------------------------------------------------------------------------------
template<typename T1, int D1, typename T2, int D2> void testRelation(int n)
{
	cout << "\ntestSegmentsRelation (" << n << ")" << endl;
	TRelation<TSegment<T1,D1>, TSegment<T2,D2> > relation;
	buildSegRelation<T1,D1,T2,D2> (n, relation);
	cout << relation;
}

//--------------------------------------------------------------------------------
template<typename T1, int D1, typename T2, int D2> void testVirtualRelation(int n)
{
	cout << "\ntestVirtualRelation (" << n << "x" << ")" << endl;
	TRelation<TSegment<T1,D1>, TSegment<T2,D2> > relation;
//	TVirtualRelation<T1,D1,T2,D2> relation;
	buildSegRelation<T1,D1,T2,D2> (n, relation);
	TVirtualRelation<TSegment<T1,D1>, TSegment<T2,D2> > vrelation(relation);
	cout << "Relation: " << endl;
	cout << relation;
	cout << "Virtual Relation: " << endl;
	cout << vrelation;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> SMARTP<TMapping<T1, T2> > buildMapping(int n, int r, T1 range1, T2 range2)
{
	SMARTP<TMapping<T1, T2> > mapping = TMapping<T1, T2>::create();
	for (int i = 0; i < n; i++) {
		T1 o = random(range1);
		int revc = random(r);
		int rr = max(1, revc);
		for (int j = 0; j < rr; j++) {
			T2 ro = random(range2);
			mapping->add (o, ro);
		}
	}
	return mapping;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> SMARTP<TMapping<TSegment<T1,1>, TSegment<T2,1> > > buildSegMapping(int n)
{
	SMARTP<TMapping<TSegment<T1,1>, TSegment<T2,1> > > mapping = TMapping<TSegment<T1,1>, TSegment<T2,1> >::create();
	for (int i = 0; i < n; i++) {
		TSegment<T1,1> o = randomSegment<T1,1>()(100);
		TSegment<T2,1> ro = randomSegment<T2,1>()(100);
		mapping->add (o, ro);
	}
	return mapping;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void testMapping(int n, int r, T1 range1, T2 range2)
{
	cout << "\ntestMapping (" << n << "x" << r << ")" << endl;
	SMARTP<TMapping<T1, T2> > mapping = buildMapping ( n, r, range1, range2 );
	cout << *mapping;

	rational date (1,1);
	cout << "\ntestMapping translation " << date << endl;
	SMARTP<TMapping<TSegment<rational, 1>, TSegment<T2,1> > > rmap = buildSegMapping<rational, T2> ( n );
	cout << *rmap << "------------ translated ------------" << endl;
	SMARTP<TMapping<TSegment<rational, 1>, TSegment<T2,1> > > trmap = MapTools::translate (rmap, date);
	cout << *trmap;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2,  typename T3> void testComposition(int n, int r, T1 range1, T2 range2, T3 range3)
{
	cout << "\ntestComposition (" << n << "x" << r << ")" << endl;
	SMARTP<TMapping<T1, T2> > m1 = buildMapping ( n, r, range1, range2 );
	SMARTP<TMapping<T2, T3> > m2 = buildMapping ( n, r, range2, range3 );
	cout << "== first map:" << endl;
	cout << m1->direct();
	cout << "== second map:" << endl;
	cout << m2->direct();
	SMARTP<TMapping<T1, T3> > compo = TComposition<T1, T2, T3>::create(m1->direct(), m2->direct());
	cout << "== composition:" << endl;
	cout << *compo;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void testIDComposition(int n)
{
	cout << "\ntestIDComposition (" << n << ")" << endl;
	SMARTP<TMapping<T1, T2> > m = buildMapping ( n, 1, T1(10), T2(5) );
	cout << "== first map:" << endl;
	cout << m->direct();
	SMARTP<TMapping<T1, T1> > compo = TComposition<T1, T2, T1>::create(m->direct(), m->reverse());
	cout << "== composition:" << endl;
	cout << *compo;
}

//--------------------------------------------------------------------------------
template<typename T, typename R> void testIntervals(int n)
{
	cout << "\ntestIntervals (" << n << ")" << endl;
	for (int i = 0; i < n; i++) {
		TInterval<T> i1;
		do { i1 = randomInterval (T(50)); } while (i1.empty());
		TInterval<T> i2 = randomInterval (T(50));
#ifdef RationalRelation
		MapTools::Relation r = MapTools::relation(i1, i2);
#else
		MapTools::Relation<R> r = MapTools::relation(i1, i2);
#endif
		TInterval<T> relate = MapTools::related(i1, r);
		cout << i1 << " - " << i2 << " union: " << i1.union_op(i2) << " intersect: " << (i1 & i2) << " rel: " << r << " related: " << relate << endl;
		if (relate != i2) cout << "warning ! related " << relate << " - " << i2 << " expected diff: " << (relate.size() - i2.size()) << endl;
	}
}

//--------------------------------------------------------------------------------
void testMapTools()
{
	TInterval<int> i1;
	do { i1 = randomInterval (5); } while (i1.empty());
	TInterval<int> i2;
	do { i2 = randomInterval (5); } while (i2.empty());

	TInterval<rational> ri1 = randomInterval (rational(5));
	TInterval<rational> ri2 = randomInterval (rational(5));
	
#ifdef RationalRelation
	MapTools::Relation rf = MapTools::relation (i1, i2);
	MapTools::Relation rr = MapTools::relation (ri1, ri2);
#else
	MapTools::Relation<double> rf = MapTools::relation (i1, i2);
	MapTools::Relation<rational> rr = MapTools::relation (ri1, ri2);
#endif
	cout << i1 << " - " << i2 <<  " relation: " << rf << " related " << MapTools::related(i1, rf) << endl;
	cout << ri1 << " - " << ri2 <<  " relation: " << rr << " related " << MapTools::related(ri1, rr) << endl;
	cout << "relation: " << rr << " : " << i1 << " related " << MapTools::related(i1, rr) << endl;
}

//--------------------------------------------------------------------------------
template <typename T> set<T> union_op (const set<T>& s1, const set<T>& s2)
{
	set<T> outset;
	if (s1.size() != s2.size()) return outset;
//	if (s1.size() != 1) return outset;
	typedef typename set<T>::const_iterator const_iterator;
	const_iterator i1 = s1.begin();
	const_iterator i2 = s2.begin();
	while (i1 != s1.end()) {
		T  inter = *i1 & *i2;
		T  u = i1->union_op(*i2);
		if (u.empty() || inter.size()) {
			outset.clear();
			break;
		}
		outset.insert (u);
		i1++; i2++;
	}
	return outset;
}

//--------------------------------------------------------------------------------
template <typename T1, typename T2> SMARTP<TMapping<T1, T2> > reduce( const SMARTP<TMapping<T1, T2> >& map)
{
	SMARTP<TMapping<T1, T2> > outmap = TMapping<T1, T2>::create();
	T1 tmp1; set<T2> tmp2;
	const TRelation<T1,T2>& rel = map->direct();
	typedef typename TRelation<T1,T2>::const_iterator const_iterator;
	for (const_iterator i = rel.begin(); i != rel.end(); i++) {
		if (!tmp2.size()) {
			tmp1 = i->first;
			tmp2 = i->second;
		}
		else {
			T1 u1 = tmp1.union_op(i->first);
			set<T2> u2 = union_op (tmp2, i->second);
			if (u1.empty() || !u2.size()) {
				outmap->add (tmp1, tmp2);
				tmp1 = i->first;
				tmp2 = i->second;
			}
			else {
				tmp1 = u1;
				tmp2 = u2;
			}
		}
	}
	if (tmp2.size())
		outmap->add (tmp1, tmp2);
	return outmap;
}

//--------------------------------------------------------------------------------
static void testMapReduction()
{
	cout << "\ntestMapReduction" << endl;
	SMARTP<TMapping<TI, TF> > mapping = TMapping<TI, TF>::create();
	for (int i=0; i < gMapSize; i++)
		mapping->add(gMap[i].tseg, gMap[i].gseg);
	cout << *mapping;
	mapping = reduce (mapping);
	cout << "----------- reduced -----------" << endl;
	cout << *mapping;
}

//--------------------------------------------------------------------------------
static bool lopt (const char* opt, int argc, char** argv)
{
	for (int i=1; i< argc; i++) {
		if (!strcmp(argv[i], opt)) return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	cout << "----------------------------" << endl;
	cout << "Segments and relations tests" << endl;
	cout << "----------------------------" << endl;
		
	if (lopt("-help", argc, argv) || lopt("--help", argc, argv) || lopt("-h", argc, argv)) {
		cout << "usage : test options" << endl;
		cout << "        -int test Intervals" << endl;
		cout << "        -seg test Segments" << endl;
		cout << "        -sgt test Segmentation" << endl;
		cout << "        -map test Mapping" << endl;
		cout << "        -red test Mapping reduction" << endl;
		cout << "        -rel test Relations" << endl;
		cout << "        -tools test MapTools" << endl;
		cout << "        -rat test rationals" << endl;
		exit (0);
	}

	if (lopt("-int", argc, argv)) {
		testIntervals<long, double> (10);
		testIntervals<double, double> (10);
//		testIntervals<rational, double> (10);
		testIntervals<rational, rational> (10);
	}

	if (lopt("-seg", argc, argv)) {
#ifdef RationalRelation
		testSegments<int, 1, MapTools::SegmRelation>(10);
		testSegments<rational,1, MapTools::SegmRelation>(10);
		testSegments<int,2, MapTools::SegmRelation>(10);
#else
		testSegments<int, 1, MapTools::SegmRelation<double> >(10);
		testSegments<rational,1, MapTools::SegmRelation<rational> >(10);
		testSegments<int,2, MapTools::SegmRelation<double> >(10);
#endif
	}

	if (lopt("-sgt", argc, argv)) {
		testSegmentation<int,1>(10);
		testSegmentation<rational,1>(10);
		testSegmentation<int,2>(10);
	}

	if (lopt("-map", argc, argv)) {
		testMapping<long, float> (10,3,30, 3.f);
		testComposition<float, long, float> (10, 3, 1.f, 8, 3.f);
		testIDComposition<long, float> (10);
	}

	if (lopt("-rel", argc, argv)) {
//		testRelation<long, float>(10, 200, 5.);
//		testRelation<float, rational>(10, 1., rational(40,1));
//		testRelation<rational, 1, long, 2>(10);
		testVirtualRelation<int, 1, float, 1>(10);
		testVirtualRelation<rational, 1, int, 1>(10);
		testVirtualRelation<rational, 1, float, 2>(10);
		testVirtualRelation<rational, 1, rational, 1>(10);
	}
	
	if (lopt("-red", argc, argv)) {
		testMapReduction();
	}
	
	if (lopt("-tools", argc, argv)) {
		testMapTools();
	}
	
	if (lopt("-rat", argc, argv)) {
		testrational();
	}

	return 0;
}
