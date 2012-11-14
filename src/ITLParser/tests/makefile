
#CXXFLAGS := -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -I../../../lib/oscpack -arch i386 -DPARSERTEST

CXXFLAGS :=  -DNO_OSCSTREAM -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -I../../libmapping/package/libmapping -I../../../lib/oscpack -I../../../lib/javascript/v8/include -arch x86_64 -DPARSERTEST
SCRIPTBIB :=  -L/Users/fober/src/v8 -lv8 -llua

OBJ := ../ITLparser.o ../ITLparse.o ../ITLlex.o  ../../libmapping/src/misc/rational.o ../../controller/IMessage.o  ../../scripting/TScripting.o testparser.o 

#../../lib/ITLError.o ../../lib/OSCStream.o

OSCPACK="../../../lib/oscpack/liboscpack.a"

testparser: $(OBJ) 
	g++ $(CXXFLAGS)  $(OBJ) $(OSCPACK) -o testparser

clean:
	rm -f $(OBJ) testparser

../ITLparser.o : ../ITL.l ../ITL.y
