ITL = $$PWD/..
MAP = $$ITL/../libmapping
PARSER = $$ITL/ITLParser
EXPR = $$ITL/expression

CONFIG += c++11

DEFINES += NO_OSCSTREAM PARSERTEST

#############################
#   include path
#############################

INCLUDEPATH +=	$$PARSER \
		$$ITL/controller \
		$$ITL/lib \
		$$ITL/interface \
		$$ITL/mapping \
		$$ITL/model \
		$$ITL/events \
		$$ITL/view \
		$$ITL/scripting \
		$$MAP/src/misc \
		$$MAP/src/parser \
		$$MAP/src/relations \
		$$MAP/src/segments \
		$$ITL/../../lib/oscpack \
		$$EXPR \
		$$EXPR/parser


##############################
# inscore parser
############################## 

HEADERS +=  $$PARSER/ITLparser.h \
	    $$PARSER/ITLparse.hpp \
	    $$ITL/controller/IMessage.h \
	    $$MAP/src/misc/rational.h \
	    $$ITL/scripting/TScripting.h \
	    $$ITL/scripting/TMaths.h \
	    $$ITL/signal/TSignal.h \
	    $$ITL/lib/Tools.h

SOURCES +=  $$PARSER/ITLparser.cpp \
	    $$PARSER/ITLparse.cpp \
	    $$PARSER/ITLlex.cpp \
	    $$ITL/controller/IMessage.cpp\
	    $$MAP/src/misc/rational.cpp \
	    $$ITL/scripting/TScripting.cpp \
	    $$ITL/scripting/TMaths.cpp \
	    $$ITL/lib/Tools.cpp

##############################
# Score Expression
##############################

HEADERS +=  $$EXPR/parser/IExprParser.h \
	    $$EXPR/parser/IExprParse.hpp \
		$$EXPR/ExprInfo.h \
	    $$EXPR/IExpression.h \
	    $$EXPR/ExprFactory.h

SOURCES +=  $$EXPR/parser/IExprParser.cpp \
	    $$EXPR/parser/IExprParse.cpp \
	    $$EXPR/parser/IExprlex.cpp \
	    $$EXPR/IExpression.cpp \
	    $$EXPR/ExprFactory.cpp
