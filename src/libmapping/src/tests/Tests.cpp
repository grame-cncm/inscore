
#include <iostream>

#include "rational.h"

#include "TInterval.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "TRefinement.h"

#include "TRelation.h"
//#include "TVirtualRelation.h"
#include "TMapping.h"
#include "TComposition.h"
#include "TRefinedRelation.h"
#include "TRefinedComposition.h"

#include "TVariety.h"

using namespace std;
using namespace libmapping;

//--------------------------------------------------------------------------------
template<typename T> T random (T range)			{ return T((rand() / float(RAND_MAX)) * float(range)); }
//--------------------------------------------------------------------------------
template<typename T> TInterval<T> randomInterval (T range)
{
	T a = random (range);
	T b = random (range);
	return TInterval<T> (min(a,b), max(a,b));
}
template<> TInterval<rational> randomInterval<rational> (rational range)
{
	rational a (random (int(range.getNumerator())), random (7)+1);
	rational b (random (int(range.getNumerator())), random (7)+1);
//cout << "randomInterval: " << range << " -> " << a << " - " << b << endl;
	return TInterval<rational> (min(a,b), max(a,b));
}
template<typename T> TInterval<T> randomInterval (const TInterval<T>& i)
{
	T a = i.first() + random (i.size());
	T b = i.first() + random (i.size());
//cout << "randomInterval (TInterval): " << i << " -> " << a << " - " << b << endl;
	return TInterval<T> (min(a,b), max(a,b));
}


//--------------------------------------------------------------------------------
template<typename T, int D> struct randomSegment {};

template<typename T> struct randomSegment<T,1>
{
	TSegment<T,1> operator() (int range=200) {
		TInterval<T> i = randomInterval(range);
		return TSegment<T,1>(i);
	}
};

template<typename T> struct randomSegment<T,2>
{
	TSegment<T,2> operator() (int range=200) {
		TInterval<T> i1 = randomInterval(range);
		TInterval<T> i2 = randomInterval(range);
		return TSegment<T,2>(i1, i2);
	}
};


//--------------------------------------------------------------------------------
template<typename T> void testIntervals(int n)
{
	cout << "\ntestIntervals (" << n << ")" << endl;
	for (int i = 0; i < n; i++) {
		TInterval<T> i1;
		do { i1 = randomInterval (T(50)); } while (i1.empty());
		TInterval<T> i2 = randomInterval (T(50));
		cout << i1 << " - " << i2 << " merge: " << i1.merge(i2) << " intersect: " << (i1 & i2) << " union: " << (i1 | i2) << endl;
	}
}

//--------------------------------------------------------------------------------
template<typename T, unsigned int D> void testSegments(int n)
{
	cout << "\ntestSegments " << D << "D (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	for (int i=0; i< n; ) {
		TSegment<T,D> s1 = randomSegment<T, D>()(50);
		TSegment<T,D> s2 = randomSegment<T, D>()(50);
		if (s1.intersect(s2)) {
			cout << string(s1) << " - " << string(s2) << " => intersection: " << string(s1 & s2) << endl;
			i++;
		}
	}
}

//--------------------------------------------------------------------------------
template<typename T, unsigned int D> void testVariety1(int n)
{
	cout << "\ntestVariety " << D << "D (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	for (int i=0; i< n; i++) {
		TSegment<T,D> s1 = randomSegment<T, D>()(50);
		TSegmentVariety<T,D> v(s1);
		float loc = random (1.f);
		cout << string(s1) << " get loc 0.5: " << v.get(0.5f) << endl;
		cout << "\t\t get loc " << loc << ": " << v.get(loc) << endl;
	}
	TSegment<T,D> s1(0,1);
	TSegmentVariety<T,D> v(s1);
	float loc = random (1.f);
	cout << string(s1) << " get loc 0.5: " << v.get(0.5f) << endl;
	cout << "\t\t get loc " << loc << ": " << v.get(loc) << endl;
}

//--------------------------------------------------------------------------------
template<typename T> void testVariety2(int n)
{
	cout << "\ntestVariety functions" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	for (int i=0; i< n; i++) {
		TInterval<T> i1 = randomInterval (T(50));
		TInterval<T> i2 = randomInterval (i1);
		TAXBFunction<T> f(i1, i2);
		TIntervalVariety<T> v(i1, &f);
		cout << i1 << " - " << i2 << " f: " << f.getA() << "x + " << f.getB() << " -> get: " << v.get() << endl;
		if (!i2.near(v.get())) cerr << ">>> incorrect variety " << v.get() << endl;
		float loc = random (1.f);
		cout << "\t\t get loc 0.5: " << v.get(0.5f) << endl;
		cout << "\t\t get loc " << loc << ": " << v.get(loc)   << endl;
	}
}

//--------------------------------------------------------------------------------
template<typename T> void testSegmentation1D(int n)
{
	cout << "\ntestSegmentation1D" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	SMARTP<TSegmentation<int, 1> > s = TSegmentation<T, 1>::create (TSegment<T,1>(0, 0));
	s->add( TSegment<T,1>(0, 10) );
	s->add( TSegment<T,1>(90, 95) );
	s->add( TSegment<T,1>(60, 80) );
	s->add( TSegment<T,1>(20, 50) );
	s->setResource();
	cout << s << endl;
	cout << "check [OK] " << s->check() << endl;
	s->add( TSegment<T,1>(95, 110) );
	cout << s << endl;
	cout << "check [FALSE] " << s->check() << endl;
	s->add( TSegment<T,1>(50, 70) );
	cout << s << endl;
	cout << "check [FALSE] " << s->check() << endl;
}

//--------------------------------------------------------------------------------
template<typename T> void testRefinement1D(int n)
{
	cout << "\ntestRefinement1D" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	SMARTP<TSegmentation<int, 1> > s1 = TSegmentation<T, 1>::create (TSegment<T,1>(0, 98));
	s1->add( TSegment<T,1>(5, 10) );
	s1->add( TSegment<T,1>(10, 50) );
	s1->add( TSegment<T,1>(60, 80) );
	s1->add( TSegment<T,1>(90, 95) );
	SMARTP<TSegmentation<int, 1> > s2 = TSegmentation<T, 1>::create (TSegment<T,1>(0, 95));
	s2->add( TSegment<T,1>(0, 5) );
	s2->add( TSegment<T,1>(8, 12) );
	s2->add( TSegment<T,1>(15, 30) );
	s2->add( TSegment<T,1>(30, 60) );
	s2->add( TSegment<T,1>(60, 92) );
	s2->add( TSegment<T,1>(92, 95) );
	TRefinement<T, 1> refine;
	cout << s1 << endl;
	cout << s2 << endl;
	SMARTP<TSegmentation<int, 1> > r = refine(s1, s2);
	cout << "refined to:\n" << r << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void testMapping(int n)
{
	typedef TSegment<T1, 1> S1;
	typedef TSegment<T2, 1> S2;
	cout << "\ntestMapping" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	SMARTP<TMapping<T1,1,T2,1> > mapping = TMapping<T1,1,T2,1>::create();
	for (int i=0; i< n; i++) {
		S1 i1 = randomSegment<T1, 1>() (50);
		S2 i2 = randomSegment<T2, 1>() (50);
		cout << "adding relation " << i1 << " -> " << i2 << endl;
		mapping->add (i1, i2);
		set< TSegment<T2, 1> > gl2 = mapping->direct().get(i1);
		if (gl2.size() != 1) cout << "warning: direct get " << i1 << " size " << gl2.size() << endl;
		else {
			S2 g2 = *(gl2.begin());
			if (g2 != i2) cout << "warning: direct get " << i1 << " gives " << g2 << endl;
		}
		set<S1> gl1 = mapping->reverse().get(i2);
		if (gl1.size() != 1) cout << "warning: reverse get " << i2 << " size " << gl1.size() << endl;
		else {
			S1 g1 = *(gl1.begin());
			if (g1 != i1) cout << "warning: reverse get " << i2 << " gives " << g1 << endl;
		}
	}
	cout << *mapping << endl;
	SMARTP<TSegmentation<T1,1> > s = mapping->direct().getPrimarySet();
	cout << "mapping primary set: " << endl << s << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2, typename T3> void testComposition(int n)
{
	cout << "\ntestComposition" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	SMARTP<TMapping<T1,1,T2,1> > map1 = TMapping<T1,1,T2,1>::create();
	SMARTP<TMapping<T2,1,T3,1> > map2 = TMapping<T2,1,T3,1>::create();
	for (int i=0; i< n; i++) {
		TSegment<T1,1> i1 = randomSegment<T1,1>() (50);
		TSegment<T2,1> i2 = randomSegment<T2,1>() (50);
		TSegment<T3,1> i3 = randomSegment<T3,1>() (50);
		map1->add (i1, i2);
		map2->add (i2, i3);
	}
	SMARTP<TMapping<T1,1,T3,1> >comp = TComposition<T1,1,T2,1,T3,1>::create (map1->direct(), map2->direct());
	cout << "map1: \n" << *map1 << endl;
	cout << "map2: \n" << *map2 << endl;
	cout << "composition: \n" << *comp << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void testRefinedRelation11(int n)
{
	cout << "\ntestRefinedRelation dim. 1 & 1" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	TRelation<T1,1,T2,1> r;
	r.add (TSegment<T1,1>(0,10), TSegment<T2,1>(10,20));
	r.add (TSegment<T1,1>(10,20), TSegment<T2,1>(20,30));
	r.add (TSegment<T1,1>(20,30), TSegment<T2,1>(30,40));
	SMARTP<TSegmentation<T1,1> > segm = TSegmentation<T1,1>::create();
	segm->add (TSegment<T1,1>(0,5));
	segm->add (TSegment<T1,1>(5,10));
	segm->add (TSegment<T1,1>(12,18));
	segm->add (TSegment<T1,1>(20,30));
	cout << "relation: " << endl << r << endl;
	cout << "refined segmentation: " << endl << segm << endl;
	
	TRefinedRelation <T1,1,T2,1> rr (r, segm);
	cout << "refined relation: " << endl << rr << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2> void testRefinedRelation12(int n)
{
	cout << "\ntestRefinedRelation dim. 1 & 2" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	TRelation<T1,1,T2,2> r;
	r.add (TSegment<T1,1>(0,10), TSegment<T2,2>(TInterval<T2>(10,20), TInterval<T2>(0,50)));
	r.add (TSegment<T1,1>(10,20), TSegment<T2,2>(TInterval<T2>(20,30), TInterval<T2>(0,50)));
	r.add (TSegment<T1,1>(20,30), TSegment<T2,2>(TInterval<T2>(30,40), TInterval<T2>(0,50)));
	SMARTP<TSegmentation<T1,1> > segm = TSegmentation<T1,1>::create();
	segm->add (TSegment<T1,1>(0,5));
	segm->add (TSegment<T1,1>(5,10));
	segm->add (TSegment<T1,1>(12,18));
	segm->add (TSegment<T1,1>(20,30));
	cout << "relation: " << endl << r << endl;
	cout << "refined segmentation: " << endl << segm << endl;
	
	TRefinedRelation <T1,1,T2,2> rr (r, segm);
	cout << "refined relation: " << endl << rr << endl;
}

//--------------------------------------------------------------------------------
static void debugRefinedComposition()
{
	cout << "\ndebugRefinedComposition" << endl;
	cout << "---------------------------" << endl;
 	SMARTP<TMapping<rational,1,rational,1> > map1 = TMapping<rational,1,rational,1>::create();
 	SMARTP<TMapping<rational,1,rational,1> > map2 = TMapping<rational,1,rational,1>::create();

	map1->add (TSegment<rational,1>(rational(0,1),rational(5,4)), TSegment<rational,1>(rational(0,1),rational(5,4)));

	map2->add (TSegment<rational,1>(rational(0,1),rational(1,4)), TSegment<rational,1>(rational(0,1),rational(1,4)));
	map2->add (TSegment<rational,1>(rational(1,4),rational(1,2)), TSegment<rational,1>(rational(1,4),rational(1,2)));
	map2->add (TSegment<rational,1>(rational(1,2),rational(3,4)), TSegment<rational,1>(rational(1,2),rational(3,4)));
	map2->add (TSegment<rational,1>(rational(3,4),rational(1,1)), TSegment<rational,1>(rational(3,4),rational(1,1)));
	map2->add (TSegment<rational,1>(rational(1,1),rational(6,4)), TSegment<rational,1>(rational(1,1),rational(6,4)));
	
	cout << "map1 :\n" << map1->direct() << endl;
	cout << "map2 :\n" << map2->direct() << endl;

	typedef TRefinedComposition <libmapping::rational,1,rational,1, rational,1> T2TComposition;
	SMARTP<TMapping<rational,1,rational,1> > t2t = T2TComposition::create( map1->direct(), map2->direct() );
	cout << "refined comp. :\n" << t2t->direct() << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2, typename T3> void testRefinedComposition121(int n)
{
	cout << "\ntestRefinedComposition 121" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
 	SMARTP<TMapping<T1,1,T2,2> > map1 = TMapping<T1,1,T2,2>::create();
 	SMARTP<TMapping<T2,2,T3,1> > map2 = TMapping<T2,2,T3,1>::create();

	map1->add (TSegment<T1,1>(0,10), TSegment<T2,2>(TInterval<T2>(10,20), TInterval<T2>(0,50)));
	map1->add (TSegment<T1,1>(10,20), TSegment<T2,2>(TInterval<T2>(20,30), TInterval<T2>(0,50)));
	map1->add (TSegment<T1,1>(20,30), TSegment<T2,2>(TInterval<T2>(30,40), TInterval<T2>(0,50)));

	map2->add (TSegment<T2,2>(TInterval<T2>(15,25), TInterval<T2>(0,50)), TSegment<T3,1>(5,15));
	map2->add (TSegment<T2,2>(TInterval<T2>(25,35), TInterval<T2>(0,50)), TSegment<T3,1>(15,25));
	map2->add (TSegment<T2,2>(TInterval<T2>(35,45), TInterval<T2>(0,50)), TSegment<T3,1>(25,35));

	cout << "map1: " << endl << *map1 << endl;
	cout << "map2: " << endl << *map2 << endl;
	SMARTP<TMapping<T1,1,T3,1> > rmap = TRefinedComposition<T1,1,T2,2,T3,1>::create(map1->reverse(), map2->direct());
	cout << "refined mapping: " << endl << *rmap << endl;
}

//--------------------------------------------------------------------------------
template<typename T1, typename T2, typename T3> void testRefinedComposition212(int n)
{
	cout << "\ntestRefinedComposition 212" << " (" << n << ")" << endl;
	cout << "---------------------------" << endl;
 	SMARTP<TMapping<T1,2,T2,1> > map1 = TMapping<T1,2,T2,1>::create();
 	SMARTP<TMapping<T2,1,T3,2> > map2 = TMapping<T2,1,T3,2>::create();

	map1->add (TSegment<T1,2>(TInterval<T2>(0,10), TInterval<T2>(0,50)), TSegment<T2,1>(0,10));
	map1->add (TSegment<T1,2>(TInterval<T2>(10,20), TInterval<T2>(0,50)), TSegment<T2,1>(10,20));
	map1->add (TSegment<T1,2>(TInterval<T2>(20,30), TInterval<T2>(0,50)), TSegment<T2,1>(20,30));
	map1->add (TSegment<T1,2>(TInterval<T2>(30,40), TInterval<T2>(0,50)), TSegment<T2,1>(30,40));

	map2->add (TSegment<T2,1>(5,15),  TSegment<T3,2>(TInterval<T3>(5,15), TInterval<T3>(0,50)));
	map2->add (TSegment<T2,1>(15,25), TSegment<T3,2>(TInterval<T3>(15,25), TInterval<T3>(0,50)));
	map2->add (TSegment<T2,1>(25,35), TSegment<T3,2>(TInterval<T3>(25,35), TInterval<T3>(0,50)));
	map2->add (TSegment<T2,1>(35,45), TSegment<T3,2>(TInterval<T3>(35,45), TInterval<T3>(0,50)));

	cout << "map1: " << endl << *map1 << endl;
	cout << "map2: " << endl << *map2 << endl;
	SMARTP<TMapping<T1,2,T3,2> > rmap = TRefinedComposition<T1,2,T2,1,T3,2>::create(map1->reverse(), map2->direct());
	cout << "refined mapping: " << endl << *rmap << endl;
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
static void usage(const char* name)
{
	cout << "usgae: " << name << " options" << endl;
	cout << "available options are: " << endl;
	cout << "  -interval : intervals test" << endl;
	cout << "  -segment : segments test" << endl;
	cout << "  -variety : variety test" << endl;
	cout << "  -varfunction : variety functions test" << endl;
	cout << "  -segmentation : segmentation test" << endl;
	cout << "  -refinement : refinement test" << endl;
	cout << "  -mapping : mapping test" << endl;
	cout << "  -composition : mapping composition test" << endl;
	cout << "  -refinedrel : refined relation test" << endl;
	cout << "  -refinedcomp : refined composition test" << endl;
	exit (1);
}

int main (int argc, char* argv[])
{
	int done = 0;
	cout << "Test segments & relations" << endl;
	if ((argc==1) || lopt("-help", argc, argv)) usage (argv[0]);

	if (lopt("-interval", argc, argv)) {
		testIntervals<long> (10);
		testIntervals<double> (10);
		testIntervals<rational> (10);
		done++;
	}

	if (lopt("-segment", argc, argv)) {
		testSegments<int, 1>(10);
		testSegments<int,2>(10);
		testSegments<rational,1>(10);
		done++;
	}

	if (lopt("-variety", argc, argv)) {
		testVariety1<float,1>(10);
		testVariety1<rational,1>(10);
		done++;
	}

	if (lopt("-varfunction", argc, argv)) {
		testVariety2<int>(10);
		testVariety2<float>(10);
		testVariety2<rational>(10);
		done++;
	}

	if (lopt("-segmentation", argc, argv)) {
		testSegmentation1D<int>(10);
		done++;
	}

	if (lopt("-refinement", argc, argv)) {
		testRefinement1D<int>(10);
		done++;
	}

	if (lopt("-mapping", argc, argv)) {
		testMapping<int,int >(10);
		testMapping<int,rational>(10);
		done++;
	}

	if (lopt("-composition", argc, argv)) {
		testComposition<int, rational, int>(6);
		done++;
	}

	if (lopt("-refinedrel", argc, argv)) {
		testRefinedRelation11<int, int>(6);
		testRefinedRelation11<int, rational>(6);
		testRefinedRelation12<int,int>(6);
		testRefinedRelation12<rational,int>(6);
		done++;
	}

	if (lopt("-refinedbg", argc, argv)) {
		debugRefinedComposition();
		done++;
	}

	if (lopt("-refinedcomp", argc, argv)) {
		testRefinedComposition121<int, int, int>(6);
		testRefinedComposition212<int, rational, int>(6);
		done++;
	}
	if (!done) usage (argv[0]);
	return 0;
}
