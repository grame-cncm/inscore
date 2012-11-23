
ARCH = -arch x86_64


###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -I../../libmapping/package/libmapping -I../../../lib/oscpack -I../../../lib/javascript/v8/include $(ARCH) -DPARSERTEST

OBJ := ../ITLparser.o ../ITLparse.o ../ITLlex.o  ../../libmapping/src/misc/rational.o ../../controller/IMessage.o  ../../scripting/TScripting.o testparser.o 

JSLIB :=  -L/Users/fober/src/v8 -lv8

###################
# lua options
CXXFLAGSLUA :=  -g -DNO_OSCSTREAM -DLUA -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -I../../libmapping/package/libmapping -I../../../lib/oscpack `pkg-config --cflags lua`  $(ARCH) -DPARSERTEST

OBJLUA := $(OBJ) ../../scripting/TLua.o

LUALIB := `pkg-config --libs lua`

###################
# javascript options
CXXFLAGSJS :=  -g -DNO_OSCSTREAM -DV8ENGINE -I.. -I../../controller -I../../lib -I../../interface -I../../mapping -I../../model -I../../view -I../../scripting -I../../libmapping/package/libmapping -I../../../lib/oscpack -I../../../lib/javascript/v8/include $(ARCH) -DPARSERTEST

OBJJS := $(OBJ) ../../scripting/TV8Js.o



#../../lib/ITLError.o ../../lib/OSCStream.o

OSCPACK="../../../lib/oscpack/liboscpack.a"

testparser: $(OBJ) 
	g++  -g $(CXXFLAGS)  $(OBJ) $(OSCPACK) -o testparser

testparserjs: CXXFLAGS = $(CXXFLAGSJS)
testparserjs: $(OBJJS) 
	g++  -g $(CXXFLAGS)  $(OBJJS) $(OSCPACK) $(JSLIB) -o testparserjs

testparserlua: CXXFLAGS = $(CXXFLAGSLUA)
testparserlua: $(OBJLUA) 
	g++  -g $(CXXFLAGS)  $(OBJLUA) $(OSCPACK) $(LUALIB) -o testparserlua

check: testparser
	valgrind -v --dsymutil=yes --leak-check=full --show-reachable=yes ./testparser $(FILE) 2> memcheck.txt
	open memcheck.txt

clean:
	rm -f $(OBJJS)  $(OBJLUA) testparser

../ITLparser.o : ../ITL.l ../ITL.y
