
ARCH = -arch x86_64

LIB := ../../library
MAP := ../../libmapping
PARSER := $(LIB)/ITLParser

###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -I$(PARSER) -I$(LIB)/controller -I$(LIB)/lib -I$(LIB)/interface -I$(LIB)/mapping -I$(LIB)/model -I$(LIB)/events -I$(LIB)/view -I$(LIB)/atomic -I$(LIB)/scripting -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack $(ARCH) -DPARSERTEST

OBJ := $(PARSER)/ITLparser.o $(PARSER)/ITLparse.o $(PARSER)/ITLlex.o  $(MAP)/src/misc/rational.o $(LIB)/controller/IMessage.o  $(LIB)/scripting/TScripting.o $(LIB)/lib/Tools.o testparser.o 

###################
# lua options
CXXFLAGSLUA :=  $(CXXFLAGS) -DLUA `pkg-config --cflags lua`
OBJLUA := $(OBJ) ../../scripting/TLua.o
LUALIB := `pkg-config --libs lua`

###################
# javascript options
CXXFLAGSJS :=  $(CXXFLAGS) -DV8ENGINE -I../../../lib/javascript/v8/include
OBJJS := $(OBJ) ../../scripting/TV8Js.o
JSLIB :=  -L/Users/fober/src/v8 -lv8

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

$(PARSER)/ITLparser.o : $(PARSER)/ITL.l $(PARSER)/ITL.y
