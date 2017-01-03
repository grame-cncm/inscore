
ITL := ../../inscore
MAP := ../../libmapping
PARSER := $(ITL)/expression/parser
EXPR := $(ITL)/expression

###################
# no script options
CXXFLAGS :=  -g -DNO_OSCSTREAM -DPARSERTEST -I$(PARSER) -I$(EXPR) -I$(ITL)/controller -I$(ITL)/lib -I$(ITL)/interface -I$(ITL)/mapping -I$(ITL)/model -I$(ITL)/events -I$(ITL)/ITLParser -I$(ITL)/view -I$(ITL)/scripting -I$(ITL)/signal -I$(MAP)/src/misc -I$(MAP)/src/parser -I$(MAP)/src/relations -I$(MAP)/src/segments -I../../../lib/oscpack -I./ $(ARCH) -std=c++11 -DNO_EXPR_VAR_SUPPORT
#LIBS =  -lguidoar
LIBS =   -F../../../lib/GuidoAR/macosx -framework guidoar


OBJ := $(PARSER)/IExprParser.o $(PARSER)/IExprParse.o $(PARSER)/IExprlex.o $(EXPR)/IExpression.o $(EXPR)/ExprFactory.o  $(EXPR)/ExprReader.o $(ITL)/scripting/TScripting.o $(ITL)/scripting/TMaths.o testparser.o

testExpression: $(OBJ)
	g++  -g $(CXXFLAGS)  $(OBJ) $(LIBS) -o testExpression

clean:
	rm -f $(OBJ)

$(PARSER)/IExprParse.o : $(PARSER)/IExpr.l $(PARSER)/IExpr.y
