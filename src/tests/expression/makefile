
#ARCH = -arch x86_64

ITL := ../../inscore
MAP := ../../libmapping
PARSER := $(ITL)/expression/parser
EXPR := $(ITL)/expression

###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -I$(PARSER) -I$(EXPR) -I$(ITL)/controller -I$(ITL)/lib -I$(ITL)/interface -I$(ITL)/mapping -I$(ITL)/model -I$(ITL)/events -I$(ITL)/view -I$(ITL)/scripting -I$(ITL)/signal -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack -I./ $(ARCH) -lguidoar -std=c++11 -DNO_EXPR_VAR_SUPPORT



#OBJ := $(PARSER)/IExprParser.o $(PARSER)/IExprParse.o $(PARSER)/IExprLex.o $(MAP)/src/misc/rational.o $(LIB)/controller/IMessage.o  $(LIB)/lib/Tools.o $(LIB)/scripting/TScripting.o $(EXPR)/IExpression.o $(EXPR)/ExprFactory.o  $(EXPR)/ExprReader.o $(EXPR)/Operators.o testExpression.o

OBJ := $(PARSER)/IExprParser.o $(PARSER)/IExprParse.o $(PARSER)/IExprlex.o $(EXPR)/IExpression.o $(EXPR)/ExprFactory.o  $(EXPR)/ExprReader.o $(EXPR)/Operators.o testparser.o

testExpression: $(OBJ)
	g++  -g $(CXXFLAGS)  $(OBJ) -o testExpression

clean:
	rm -f $(OBJ)

$(PARSER)/IExprParse.o : $(PARSER)/IExpr.l $(PARSER)/IExpr.y
