win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }
CONFIG += console
CONFIG -= app_bundle

TARGET = ITLBundleCreator
OBJECTS_DIR	= tmp
MOC_DIR		= tmp

QT -= gui;

VERSION = 1.0
DEFINES += ITLBUNDLE




############################## 
# locations
############################## 
ROOT 		= $$PWD/..
SRC 		= $$ROOT/src

ITLROOT		= $$ROOT/../../
ITLSRC		= $$ITLROOT/src/inscore/

############################## 
# source and headers
############################## 
SOURCES +=	$$SRC/ITLBundleCreator.cpp\
		$$SRC/BundleCreator.cpp \
		$$SRC/BundleLog.cpp\
		$$SRC/Parsing/ParsedData.cpp \
		$$SRC/Parsing/ScriptsParser.cpp \
		$$SRC/Parsing/TDummyJs.cpp \
		$$SRC/BundlePackager.cpp \
		$$ITLROOT/src/inscore/expression/ExprInfo.cpp





HEADERS +=	$$SRC/BundleCreator.h \
		$$SRC/doc.h \
		$$SRC/BundleLog.h \
		$$SRC/Parsing/ParsedData.h \
		$$SRC/Parsing/ScriptsParser.h \
		$$SRC/Parsing/TDummyJs.h \
		$$SRC/BundlePackager.h \
		$$ITLROOT/src/inscore/expression/ExprInfo.h


INCLUDEPATH +=	$$SRC/\
		$$SRC/Parsing/

include ($$SRC/QArchive/qarchive.pri)



############################## 
# import inscore parser
############################## 

include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)
