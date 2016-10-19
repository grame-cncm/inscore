
files 	= $(shell grep -v '^\#' testfiles.txt)
out    := $(patsubst ../../../%.inscore, checkout/%.inscore, $(files))

#ARCH = -arch x86_64

LIB := ../../inscore
MAP := ../../libmapping
PARSER := $(LIB)/ITLParser
EXPR := $(LIB)/expression

###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -DMACOS -I$(PARSER) -I$(LIB)/controller -I$(LIB)/lib -I$(LIB)/interface -I$(LIB)/mapping -I$(LIB)/model -I$(LIB)/events -I$(LIB)/view -I$(LIB)/scripting -I$(LIB)/signal -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack -I$(EXPR) -I$(EXPR)/parser -DPARSERTEST -std=c++11 -Wno-deprecated-register

OBJ := $(PARSER)/ITLparser.o $(PARSER)/ITLparse.o $(PARSER)/ITLlex.o  $(MAP)/src/misc/rational.o $(LIB)/controller/IMessage.o  $(LIB)/scripting/TScripting.o $(LIB)/scripting/TMaths.o $(LIB)/lib/Tools.o 
#EXPRESSION
OBJ := $(OBJ) $(EXPR)/parser/IExprParse.o $(EXPR)/parser/IExprParser.o $(EXPR)/parser/IExprlex.o $(EXPR)/IExpression.o $(LIB)/expression/ExprFactory.o 

#TEST PARSER
OBJ := $(OBJ) testparser.o

all:
	make -C ../../inscore/ITLParser/
	make testparser
	
testparser: $(OBJ) 
	g++  -g $(CXXFLAGS)  $(OBJ) -o testparser

checkmem: testparser
	valgrind -v --dsymutil=yes --leak-check=full --show-reachable=yes ./testparser $(FILE) 2> memcheck.txt
	open memcheck.txt

clean:
	rm -f $(OBJ)  testparser

###################
# no script options
check: testparser $(out)

test:
	echo $(out)

checkout/%.inscore: ../../../%.inscore
	@[ -d $(@D) ] || mkdir -p $(@D)
	./testparser $< > $@ || rm -f $@


$(PARSER)/ITLparser.o : $(PARSER)/ITL.l $(PARSER)/ITL.y
