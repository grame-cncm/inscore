
#ARCH = -arch x86_64

LIB := ../../library
MAP := ../../libmapping
PARSER := $(LIB)/ITLParser
EXPR := $(LIB)/expression

###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -I$(PARSER) -I$(LIB)/controller -I$(LIB)/lib -I$(LIB)/interface -I$(LIB)/mapping -I$(LIB)/model -I$(LIB)/events -I$(LIB)/view -I$(LIB)/scripting -I$(LIB)/signal -I$(LIB)/expression -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack -I./ $(ARCH) -lguidoar -DPARSERTEST -std=c++11



OBJ := $(PARSER)/ITLparser.o $(PARSER)/ITLparse.o $(PARSER)/ITLlex.o $(MAP)/src/misc/rational.o $(LIB)/controller/IMessage.o  $(LIB)/lib/Tools.o $(LIB)/scripting/TScripting.o $(EXPR)/IExpression.o $(EXPR)/ExprFactory.o  $(EXPR)/ExprReader.o $(EXPR)/Operators.o testExpression.o

testExpressionFactory: $(OBJ)
	g++  -g $(CXXFLAGS)  $(OBJ) -o testExpression

check: testparser
	valgrind -v --dsymutil=yes --leak-check=full --show-reachable=yes ./testExpression $(FILE) 2> memcheck.txt
	open memcheck.txt

clean:
	rm -f $(OBJ)

$(PARSER)/ITLparser.o : $(PARSER)/ITL.l $(PARSER)/ITL.y
