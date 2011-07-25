
CXXFLAGS := -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../../lib/oscpack -arch i386 -DPARSERTEST
OBJ := ../ITLparser.o  ../../lib/OSCStream.o ../../lib/ITLError.o  ../../lib/rational.o ../../controller/IMessage.o testparser.o
OSCPACK=../../../lib/oscpack/cmake/Release/liboscpack.a

testparser: $(OBJ) 
	g++ $(CXXFLAGS)  $(OBJ) $(OSCPACK) -o testparser

clean:
	rm -f $(OBJ) testparser

../ITLparser.o : ../ITL.l ../ITL.y
