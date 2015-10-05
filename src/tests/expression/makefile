
#ARCH = -arch x86_64

LIB := ../../library
MAP := ../../libmapping
PARSER := $(LIB)/ITLParser

###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -I$(PARSER) -I$(LIB)/controller -I$(LIB)/lib -I$(LIB)/interface -I$(LIB)/mapping -I$(LIB)/model -I$(LIB)/events -I$(LIB)/view -I$(LIB)/scripting -I$(LIB)/signal -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack -I./ $(ARCH) -DEXPRESSIONTEST -DPARSERTEST -std=c++11

#CXXFLAGS :=  -g -DNO_OSCSTREAM -I$(PARSER) -I$(LIB)/controller -I$(LIB)/lib -I$(LIB)/interface -I$(LIB)/mapping -I$(LIB)/model -I$(LIB)/events -I$(LIB)/view -I$(LIB)/atomic -I$(LIB)/scripting -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack $(ARCH) -DEXPRESSIONTEST -DPARSERTEST

OBJ := $(PARSER)/ITLparser.o $(PARSER)/ITLparse.o $(PARSER)/ITLlex.o $(MAP)/src/misc/rational.o $(LIB)/controller/IMessage.o  $(LIB)/lib/Tools.o $(LIB)/scripting/TScripting.o IExpression.o IExpressionFactory.o ExprEvaluator.o ExprReader.o testExpression.o

testExpressionFactory: $(OBJ)
	g++  -g $(CXXFLAGS)  $(OBJ) -o testExpression

check: testparser
	valgrind -v --dsymutil=yes --leak-check=full --show-reachable=yes ./testExpression $(FILE) 2> memcheck.txt
	open memcheck.txt

clean:
	rm -f $(OBJ)

$(PARSER)/ITLparser.o : $(PARSER)/ITL.l $(PARSER)/ITL.y
