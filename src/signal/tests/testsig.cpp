


#include <iostream>
#include <stdlib.h>

#include "TSignal.h"
#include "RingBuffer.h"
//#include "GraphicSignal.h"

using namespace std;
using namespace inscore;

#define SIZE	10

//--------------------------------------------------------------------------
template <typename T> ostream&	operator << (ostream& out, const vector<T>& v)
{
	out << "{";
	for (int i = 0; i < v.size(); i++)
		out << (i>0 ? ", " : "") << v[i];
	out << "}";
	return out;
}

//--------------------------------------------------------------------------
template <typename T> vector<T>&	operator << (vector<T>& dst, const T& v)
{
	dst.push_back (v);
	return dst;
}

//--------------------------------------------------------------------------
static vector<float> generate(int size)
{
	vector<float> values;
	for (int i=0; i<size; i++)
		values.push_back(float(random())/RAND_MAX);
	return values;
}

//--------------------------------------------------------------------------
static STSignal createSig()
{
	STSignal sig = TSignal::create ("unnamed", SIZE, 0);
	for (int i=0; i<SIZE; i++)
		*sig << float(random())/RAND_MAX;
	return sig;
}

//--------------------------------------------------------------------------
template<typename T> void plot (const T& sig)
{
	cout << "{";
	for (int i=0; i<sig.size(); i++)
		cout << (i>0 ? ", " : "") << sig[i];
	cout << "}" << endl;
}

//--------------------------------------------------------------------------
//static void plotColor (ColorSignal& sig)
//{
//	cout << "{" << endl;
//	for (int i=0; i<sig.size(); i++) {
//		cout << "h: " << sig.get(i).getHue() << " s: " << sig.get(i).getSaturation()
//			 << " b: " << sig.get(i).getBrightness() << " a: " << sig.get(i).getTransparency() << endl;
//	}
//	cout << "}" << endl;
//}
//
////--------------------------------------------------------------------------
//void plotGraphFrame (const GraphicFrame& gf)
//{
//	cout << "pos: " << gf.getPos() << " th: " << gf.getThickness() << " color: " << gf.getColor();
//}
//
////--------------------------------------------------------------------------
//void plotGraph (GraphicSignal& sig)
//{
//	cout << "{" << endl;
//	for (int i=0; i<sig.size(); i++) {
//		plotGraphFrame (sig.get(i));
//		cout << endl;
//	}
//	cout << "}" << endl;
//}
//
////--------------------------------------------------------------------------
//void plotGraphs (GraphicSignals& sig)
//{
//	cout << "{" << endl;
//	for (int i=0; i<sig.size(); i++) {
//		GraphicFrames g = sig.get(i);
//		for (int n=0; n<g.size(); n++) {
//			cout << " {";
//			plotGraphFrame (g[n]);
//			cout << "}";
//		}
//		cout << endl;
//	}
//	cout << "}" << endl;
//}

//--------------------------------------------------------------------------
//static void basicTest()
//{
//	STSignal sig1 = createSig();
//	STSignal sig2 = createSig();
//
//	cout << "=== sig1 available: " << sig1->available() << endl;
//	plot (*sig1);
//	cout << "=== sig2 available: " << sig2->available()  << endl;
//	plot (*sig2);
//	
//	SParallelSignal sigp = ParallelSignal::create();
//	*sigp << sig1 << sig2;
//	cout << "=== sigp: (dim: " << sigp->dimension() << ")" << endl;
//	plot (*sigp);
//
//	SParallelSignal sigpp = ParallelSignal::create();
//	*sigpp << sig1 << sigp << sig2;
//	cout << "=== sigpp: (dim: " << sigpp->dimension() << ")" << endl;
//	plot (*sigpp);
//}

//--------------------------------------------------------------------------
//static void graphicTest1()
//{
//	STSignal sigY = createSig();
//	STSignal sigT = createSig();
//	STSignal sigH = createSig();
//	STSignal sigS = createSig();
//	STSignal sigB = createSig();
//	STSignal sigA = createSig();
//	
//	SColorSignal sigColor = ColorSignal::create();
//	*sigColor << sigH << sigS << sigB << 1; // sigA;
//	cout << "=== sigColor size:" << sigColor->size() << endl;
//	plotColor (*sigColor);
//
//	SGraphicSignal graphSignal = GraphicSignal::create();
//	*graphSignal << sigY << sigT << sigColor;
//	cout << "=== sigGraph size:" << graphSignal->size() << endl;
//	plotGraph (*graphSignal);
//}
//
////--------------------------------------------------------------------------
//static void graphicTest2()
//{
//	STSignal sigY = createSig();
//	
//	SColorSignal sigColor = ColorSignal::create();
//	cout << "create sigColor " << 180.f/360 << " " << 1.f << " " << 1.f << " " << 0 << endl;
//	*sigColor << 180.f/360 << 1.f << 1.f << 0;
//	cout << "=== sigColor size: " << sigColor->size() << endl;
//	plotColor (*sigColor);
//
//	SGraphicSignal graphSignal = GraphicSignal::create();
//	*graphSignal << sigY << 1.f << sigColor;
//	cout << "=== sigGraph1 size: " << graphSignal->size() << " dimension: " << graphSignal->dimension() << endl;
//	plot (*graphSignal);
//	cout << "=== sigGraph2 size: " << graphSignal->size() << " dimension: " << graphSignal->dimension() << endl;
//	plotGraph (*graphSignal);
//}
//
////--------------------------------------------------------------------------
//static void graphicTest3()
//{
//	STSignal sig1 = createSig();
//	STSignal sig2 = createSig();
//	
//	SColorSignal sigColor = ColorSignal::create();
//	*sigColor << 180.f/360 << 1.f << 1.f << 0;
//
//	SGraphicSignal graphSignal1 = GraphicSignal::create();
//	*graphSignal1 << sig1 << 1.f << sigColor;
//	SGraphicSignal graphSignal2 = GraphicSignal::create();
//	*graphSignal2 << sig2 << 2.f << sigColor;
//
//	plotGraph (*graphSignal1);
//	plotGraph (*graphSignal2);
//
//	SGraphicSignals sgs = GraphicSignals::create();
//	*sgs << sig1 << 1.f << sigColor << sig2 << 2.f << sigColor;
//	*sgs << graphSignal2 << graphSignal1;
//	cout << "=== sigGraph parallel size: " << sgs->size() << " dimension: " << sgs->dimension() << endl;
//	plotGraphs (*sgs);
////	plot (*sgs);
//}

//--------------------------------------------------------------------------
static void printLast(const RingBuffer& rb)
{
	unsigned short avail = rb.available();
	cout << "RingBuffer read  last value: ";
	if (avail) cout << rb[avail-1] << " ";
	cout << endl;
}

//--------------------------------------------------------------------------
static void printRB(const RingBuffer& rb)
{
	unsigned short avail = rb.available();
	cout << "RingBuffer read  " << avail << " values: ";
	for (int i = 0; i < avail; i++)
		cout << rb[i] << " ";
	cout << endl;
}

//--------------------------------------------------------------------------
static void writeRB (RingBuffer& rb, int count)
{
	cout << "RingBuffer write " << count << " values: ";
	for (int i = 0; i < count; i++) {
		float value = rand() / float(RAND_MAX);
		cout << value << " ";
		rb.write(value);
	}
	cout << endl;
}

//--------------------------------------------------------------------------
static void ringbuffer()
{
	RingBuffer rb;
	rb.initialize(5);
	cout << "RingBuffer init to size: " << rb.size() << endl;
	writeRB(rb, 4);	
	printRB (rb);
	cout << "RingBuffer done" << endl;
	rb.done();
	printRB (rb);

	writeRB(rb, 3);	
	printRB (rb);

	cout << "RingBuffer resize to 2: " << endl;
	rb.initialize(2);
	printRB (rb);
	cout << "RingBuffer resize to 3: " << endl;
	rb.initialize(3);
	printRB (rb);
	rb.done();
	writeRB(rb, 5);	
	cout << "RingBuffer fix" << endl;
	rb.fix();
	printRB (rb);

	cout << "RingBuffer avail: " << rb.available() << endl;
	writeRB(rb, 3);
	cout << "RingBuffer avail: " << rb.available() << endl;
	printLast (rb);
	cout << "RingBuffer avail: " << rb.available() << endl;
}

//--------------------------------------------------------------------------
//static void projection()
//{
//	STSignal sig1 = createSig();
//	STSignal sig2 = createSig();
//	
//	SColorSignal sigColor = ColorSignal::create();
//	*sigColor << 180.f/360 << 1.f << 1.f << 0;
//
//	SGraphicSignal graphSignal1 = GraphicSignal::create();
//	*graphSignal1 << sig1 << 1.f << sigColor;
//	SParallelSignal graphSignal2 = GraphicSignal::create();
//	*graphSignal2 << sig2 << 2.f << sigColor;
//
//	SGraphicSignals sgs = GraphicSignals::create();
//	*sgs << graphSignal2 << graphSignal1;
//	plotGraphs (*sgs);
//
//	SParallelSignal p = sgs->getProjection(0);
//	cout << "=== proj size: " << p->size() << " dimension: " << p->dimension() << endl;
//	plot (*p);
//
//	p = sgs->getProjection(0,6);
//	cout << "=== proj size: " << p->size() << " dimension: " << p->dimension() << endl;
//	plot (*p);
//}

//--------------------------------------------------------------------------
//static void put()
//{
//	STSignal sig1 = Signal::create (SIZE, 0);
//	STSignal sig2 = Signal::create (SIZE, 0);
//	STSignal sig3 = Signal::create (SIZE, 0);
//	SParallelSignal p = ParallelSignal::create();
//	*p << sig1 << sig2 << sig3;
//	plot (*p);
//	
//	vector<float> data = generate(8);
//	cout << "put data:" << endl;
//	plot (data);
//	cout << "=== p values: " << endl;
//	p->put(data);
//	plot (*p);
//}

//--------------------------------------------------------------------------
int main (int argc, const char* argv[])
{
	cout << "==== RingBuffer tests ====" << endl;
	ringbuffer();
//	cout << "\nTest parallelisation de signaux" << endl;
//	basicTest();
//	cout << "\nTest signaux graphiques" << endl;
//	graphicTest1();
//	cout << "\nTest signaux graphiques avec ConstSignal" << endl;
//	graphicTest2();
//	cout << "\nTest signaux graphiques en parallel" << endl;
//	graphicTest3();
//	cout << "\nTest projections" << endl;
//	projection();
//	cout << "\nTest parallel put" << endl;
//	put();

	return 0;
}
