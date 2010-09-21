

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "TSegment.h"
#include "TSegmentation.h"
#include "TRelation.h"
#include "TVirtualRelation.h"
#include "TComposition.h"
#include "TMappingComposer.h"
#include "rational.h"


using namespace std;
using namespace interlude;


static const char* bstr(bool v)		{ return (v ? "yes" : "no"); }

template <typename T> 
std::ostream& operator << (std::ostream& out, const vector<T>& v) { 
	for (int i=0; i < v.size(); i++)
		out << v[i] << " ";
	return out;
}

template <typename T> 
std::ostream& operator << (std::ostream& out, const pair<T,T>& p) { 
	out << p.first << "," << p.second;
	return out;
}

//--------------------------------------------------------------------------------
template<typename T, int D> struct randomSegment {};

template<typename T> struct randomSegment<T,1>
{
	TSegment<T,1> operator() () {
		T v1 = (rand() / float(RAND_MAX)) * 200;
		T v2 = v1 + T((rand() / float(RAND_MAX)) * 100);
		return TSegment<T,1>(v1,v2);
	}
};

template<typename T> struct randomSegment<T,2>
{
	TSegment<T,2> operator() () {
		T v1 = (rand() / float(RAND_MAX)) * 200;
		T v2 = v1 + (rand() / float(RAND_MAX)) * 100;
		T v3 = (rand() / float(RAND_MAX)) * 200;
		T v4 = v3 + (rand() / float(RAND_MAX)) * 100;
		return TSegment<T,2>(v1, v3, v2, v4);
	}
};

//--------------------------------------------------------------------------------
template<typename T> void print(const T& s)
{
	cout << s << " \t size: " << s.size() << " empty? " << bstr(s.empty()) << endl;
}

//--------------------------------------------------------------------------------
template<typename T, unsigned int D> void testSegments(int n)
{
	cout << "\ntestSegments " << D << "D (" << n << ")" << endl;
	cout << "---------------------------" << endl;
	for (int i=0; i< n; i++) {
		TSegment<T,D> s1 = randomSegment<T, D>()();
		TSegment<T,D> s2 = randomSegment<T, D>()();
		print (s1);
		print (s2);
		cout << "=> intersection: " ;
		print (s1 & s2);
	}
}

//--------------------------------------------------------------------------------
template<typename T, int D> SMARTP<TSegmentation<TSegment<T,D> > > buildSegmentation(int n, const TSegment<T,D>& r)
{
	SMARTP<TSegmentation<TSegment<T,D> > > s = TSegmentation<TSegment<T,D> >::create(r);
	for (int i=0; i < n; ) {
		TSegment<T,D> seg = randomSegment<T, D>()();
		if (seg.size() && s->add( seg )) i++;
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
	
	SMARTP<TSegmentation<TSegment<T,D> > > s = buildSegmentation<T,D>(n, r);
	cout << (*s) << endl;

	for (int i=0; i < n; i++) {
		TSegment<T,D> r = randomSegment<T, D>()();
		TSegment<T,D> foundbeg = s->find(r.start());
		TSegment<T,D> foundend = s->find(r.end());
		cout << "looking for segment " << r << " locations: ";
		if (foundbeg.size()) cout << r.start() << " -> " << foundbeg << " ";
		if (foundend.size()) cout << r.end() << " -> " << foundend;
		cout << endl;
	}
}

template <typename T1, unsigned int D1, typename T2, unsigned int D2> struct relInfos{
	SMARTP<TSegmentation<TSegment<T1,D1> > > seg1;
	SMARTP<TSegmentation<TSegment<T2,D2> > > seg2;
//	SMARTP<R> mapping;
	SMARTP<TRelation<TSegment<T1,D1>, TSegment<T2,D2> > > mapping;
	SMARTP<TRelation<TSegment<T2,D2>, TSegment<T1,D1> > > revmapping;
};

//--------------------------------------------------------------------------------
template<typename T1, unsigned int D1, typename T2, unsigned int D2, typename R, typename RR> 
struct relInfos<T1,D1,T2,D2> buildRelation(int n, int rel=1)
{
	typedef TSegment<T1,D1> TS1;
	typedef TSegment<T2,D2> TS2;
	
	struct relInfos<T1,D1,T2,D2> out;

	TS1 bounds1 (TInterval<T1>(T1(0), T1(200)));
	out.seg1 = buildSegmentation<T1, D1>(n, bounds1);
	TS2 bounds2 (TInterval<T2>(T2(0), T2(200)));
	out.seg2 = buildSegmentation<T2, D2>(n*rel, bounds2);

	out.mapping = R::create();
	out.revmapping = R::create();
	for (int i=0; i<n; i++) {
		for (int j=0; j<rel; j++) {
			out.mapping->addRelation (out.seg1->getSegmentation()[i], out.seg2->getSegmentation()[i+j]);
			out.revmapping->addRelation (out.seg2->getSegmentation()[i+j], out.seg1->getSegmentation()[i]);
		}
	}
	return out;
}

//--------------------------------------------------------------------------------
template<typename T1, unsigned int D1, typename T2, unsigned int D2> 
SMARTP <TRelation <TSegment<T1,D1>, TSegment<T2,D2> > > 
buildRelation(SMARTP<TSegmentation<TSegment<T1,D1> > > seg1, SMARTP<TSegmentation<TSegment<T2,D2> > > seg2, int n)
{
	SMARTP <TRelation <TSegment<T1,D1>, TSegment<T2,D2> > > r = TRelation <TSegment<T1,D1>, TSegment<T2,D2> >::create();
	for (int i=0; i<n; i++)
		r->addRelation (seg1->getSegmentation()[i], seg2->getSegmentation()[i]);
	return r;
}

//--------------------------------------------------------------------------------
template<typename T1, unsigned int D1, typename T2, unsigned int D2> 
SMARTP <TRelation <TSegment<T1,D1>, TSegment<T2,D2> > > 
buildVirtualRelation(SMARTP<TSegmentation<TSegment<T1,D1> > > seg1, SMARTP<TSegmentation<TSegment<T2,D2> > > seg2, int n)
{
	SMARTP <TRelation <TSegment<T1,D1>, TSegment<T2,D2> > > r = TVirtualRelation <TSegment<T1,D1>, TSegment<T2,D2> >::create();
	for (int i=0; i<n; i++)
		r->addRelation (seg1->getSegmentation()[i], seg2->getSegmentation()[i]);
	return r;
}

//--------------------------------------------------------------------------------
template<typename T1, unsigned int D1, typename T2, unsigned int D2> void testRelation(int n)
{
	typedef TSegment<T1,D1> TS1;
	typedef TSegment<T2,D2> TS2;
	typedef TRelation<TS1, TS2> R;
	typedef TRelation<TS2, TS1> RR;

	cout << "\ntestRelation " << D1 << "D to " << D2 << "D (" << n << ")" << endl;
	struct relInfos<T1,D1,T2,D2> map = buildRelation<T1,D1,T2,D2,R,RR>(n);

	cout << *(map.mapping) << endl;
	for (int i=0; i<n; i++) {
		const TS1 a = map.seg1->getSegmentation()[i];
		const TS2 b = map.seg2->getSegmentation()[i];
		vector<TS1> ra; 
		vector<TS2> rb; 
		cout << a << " \tdirect relation: " << map.mapping->directRelation(a, rb) << endl;
		cout << b << " revers relation: " << map.mapping->reverseRelation(b, ra) << endl;
	}
}

////--------------------------------------------------------------------------------
template<typename T1, unsigned int D1, typename T2, unsigned int D2> void testVirtualRelation(int n)
{
	typedef TSegment<T1,D1> TS1;
	typedef TSegment<T2,D2> TS2;
	typedef TVirtualRelation<TS1, TS2> R;
	typedef TVirtualRelation<TS2, TS1> RR;

	cout << "\ntestVirtualRelation " << D1 << "D to " << D2 << "D (" << n << ")" << endl;
	struct relInfos<T1,D1,T2,D2> map = buildRelation<T1,D1,T2,D2,R,RR>(n,1);

	cout << *(map.mapping) << endl;
	cout << "----------------------" << endl;
	cout << *(map.revmapping) << endl;
	
	for (int i=0; i<n; i++) {
		const TS1 a = randomSegment<T1,D1>()();
		vector<TS2> rbd, rbr;
		cout << a << " \tdirect relation         : " << map.mapping->directRelation(a, rbd) << endl;
//		cout << rbd << " \tdirect relation control: " << map.revmapping->reverseRelation(rbd, rbr) << endl;
		const TS2 b = randomSegment<T2,D2>()();
		vector<TS1> rad, rar;
		cout << b << " \treverse relation        : " << map.mapping->reverseRelation(b, rad) << endl;
//		cout << rad << " \treverse relation control: " << map.mapping->reverseRelation(rad, rar) << endl;
	}	

//	const TS1 a = TS1(6,13);
//	const TS1 b = TS1(31,40);
//	vector<TS1> v;
//	v.push_back(a);
//	v.push_back(b);
//	vector<TS2> rb;
//	cout << v << " \tdirect relation: " << map.mapping->directRelation(v, rb) << endl;
}

////--------------------------------------------------------------------------------
template<typename T1, unsigned int D1, typename T2, unsigned int D2, typename T3, unsigned int D3> void testcomposition(int n)
{
	typedef TSegment<T1,D1> S1;
	typedef TSegment<T1,D2> S2;
	typedef TSegment<T3,D3> S3;
	typedef SMARTP<TSegmentation<S1> > SS1;
	typedef SMARTP<TSegmentation<S2> > SS2;
	typedef SMARTP<TSegmentation<S3> > SS3;
	typedef SMARTP<TRelation<S1,S2> > R1;
	typedef SMARTP<TRelation<S2,S3> > R2;
	typedef SMARTP<TRelation<S1,S3> > CR;

	SS1 s1 = buildSegmentation<T1, D1> (n, TSegment<T1,D1>(T1(0), T1(200)));
	SS2 s2 = buildSegmentation<T2, D2> (n, TSegment<T2,D2>(T2(0), T2(200)));
	SS3 s3 = buildSegmentation<T3, D3> (n, TSegment<T3,D3>(T3(0), T3(200)));
	
	R1 r1 = buildVirtualRelation<T1, D1, T2, D2>(s1, s2, n);
	R2 r2 = buildVirtualRelation<T2, D2, T3, D3>(s2, s3, n);
	SMARTP<TComposition<S1, S2, S3> > c = TComposition<S1, S2, S3>::create(r1, r2);
	cout << "R1:\n" << *r1 << endl;
	cout << "R2:\n" << *r2 << endl;
	cout << "C (R1 o R2):\n" << *c << endl;
	
	CR m = TVirtualRelation<S1,S3>::create();
	TMappingComposer<S1, S2, S3>().compose(c, m);
	cout << "M :\n" << *m << endl;

	for (int i=0; i<5; i++) {
		const S1 a = randomSegment<T1,D1>()();
		vector<S2> sv2, svm2;
		cout << a << " \tdirect relation using C : " << c->directRelation(a, sv2) << endl;
		cout << a << " \tdirect relation using M : " << m->directRelation(a, svm2) << endl;
		const S2 b = randomSegment<T2,D2>()();
		vector<S1> sv1, svm1;
		cout << b << " \treverse relation using C: " << c->reverseRelation(b, sv1) << endl;
		cout << b << " \treverse relation using M: " << m->reverseRelation(b, svm1) << endl;
	}	

}

//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	cout << "---------------------------" << endl;
	cout << "Segments tests" << endl;
	cout << "---------------------------" << endl;
		
//	testSegments<int, 1>(10);
//	testSegments<rational,1>(10);
//	testSegments<int,2>(10);

//	testSegmentation<int,1>(10);
//	testSegmentation<rational,1>(10);
//	testSegmentation<int,2>(10);

//	testRelation<long, 1, rational, 1>(10);
//	testRelation<rational, 1, float, 2>(10);

//	testVirtualRelation<int, 1, int, 1>(8);
//	testVirtualRelation<int, 1, int, 2>(10);

	testcomposition<int, 1, int, 1, int, 1>(10);

	return 0;
}
