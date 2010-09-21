
#CXXFLAGS := -I../../lib -I.. -I../../model -I../../../lib/oscpack -arch i386 -DPARSERTEST
CXXFLAGS := -Wall -I../../lib -I.. -I../../../lib/oscpack
OBJ :=  ../../lib/rational.o ../mapparser.o testsync.o
NOBJ :=  ../../lib/rational.o ../MapTools.o
OSCPACK=../../../lib/oscpack/liboscpack.a

testnew:
	g++ -Wall -I.. -I../../lib testnew.cpp $(NOBJ) -o testnew

testsegments:
	g++  -I.. -I../../lib testsegments.cpp ../../lib/rational.o -o testsegments

testsync: testsync.o
	g++ -arch i386 testsync.o -o testsync

testparser: testparser.cpp ../../lib/rational.o ../mapparser.o ../mapreader.o ../../lib/ITLError.o ../../lib/OSCStream.o
	g++ $(CXXFLAGS) ../../lib/rational.o  ../mapparser.o  ../mapreader.o ../../lib/ITLError.o ../../lib/OSCStream.o $(OSCPACK) testparser.cpp -o testparser

all: testsync testparser

clean:
	rm -f $(OBJ) $(NOBJ) testsegments testsync testparser testnew

testsegments:  testsegments.cpp ../TSegment.h ../TSegmentation.h ../TInterval.h ../TRelation.h ../TVirtualRelation.h ../../lib/rational.o ../TComposition.h ../TMappingComposer.h

../MapTools.o:  ../MapTools.h 
../mapparser.o:   ../mapping.y ../mapping.l

testnew:  testnew.cpp ../TSegment.h ../TSegmentation.h ../TInterval.h ../TRelation.h ../TVirtualRelation.h ../TMapping.h ../TComposition.h  ../MapTools.h $(NOBJ)

../../lib/rational.o: ../../lib/rational.h