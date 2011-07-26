
#CXXFLAGS := -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -I../../../lib/oscpack -arch i386 -DPARSERTEST

CXXFLAGS := -DNO_OSCSTREAM -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -arch i386 -DPARSERTEST
OBJ := ../ITLparser.o  ../../lib/rational.o ../../controller/IMessage.o  ../../scripting/TLoop.o ../../scripting/TLoopEval.o ../../scripting/TScripting.o testparser.o
OSCPACK=""

testparser: $(OBJ) 
	g++ $(CXXFLAGS)  $(OBJ) $(OSCPACK) -o testparser

clean:
	rm -f $(OBJ) testparser

../ITLparser.o : ../ITL.l ../ITL.y
