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
		$$ITLROOT/src/inscore/expression/ExprInfo.cpp \
    ../src/Parsing/TDummyJs.cpp \
    ../src/BundlePackager.cpp \
    ../src/Archiving/QArchive.cpp \
    ../src/Archiving/QSubIODevice.cpp \
    ../src/Archiving/QArchiveHeader.cpp




HEADERS +=	$$SRC/BundleCreator.h \
		$$SRC/BundleLog.h\
		$$SRC/Parsing/ParsedData.h \
		$$SRC/Parsing/ScriptsParser.h \
		$$ITLROOT/src/inscore/expression/ExprInfo.h \
    ../src/Parsing/TDummyJs.h \
    ../src/BundlePackager.h \
    ../src/Archiving/QArchive.h \
    ../src/Archiving/QSubIODevice.h \
    ../src/Archiving/Tree.h \
    ../src/Archiving/Tree.tpp \
    ../src/Archiving/QArchiveHeader.h

INCLUDEPATH +=	$$SRC/\
		$$SRC/Parsing/ \
		$$SRC/Archiving/




############################## 
# import inscore parser
############################## 

include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)
