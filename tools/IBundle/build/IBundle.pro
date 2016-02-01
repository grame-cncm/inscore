win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }
CONFIG += console
CONFIG -= app_bundle

TARGET = IBundle
OBJECTS_DIR	= tmp
MOC_DIR		= tmp

QT -= gui;

VERSION = 1.0
DEFINES += IBUNDLE




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
SOURCES +=	$$SRC/IBundle.cpp \
		$$SRC/BundleCreator.cpp \
		$$SRC/BundlePackager.cpp \
		$$SRC/BundleLog.cpp \
		$$SRC/BundleExtractor.cpp \
		$$SRC/Parsing/ParsedData.cpp \
		$$SRC/Parsing/ScriptsParser.cpp \
		$$SRC/Parsing/TDummyJs.cpp \
		$$ITLROOT/src/inscore/expression/ExprInfo.cpp





HEADERS +=	$$SRC/BundleCreator.h \
		$$SRC/BundleExtractor.h \
		$$SRC/doc.h \
		$$SRC/BundlePackager.h \
		$$SRC/BundleLog.h \
		$$SRC/Parsing/ParsedData.h \
		$$SRC/Parsing/ScriptsParser.h \
		$$SRC/Parsing/TDummyJs.h \
		$$ITLROOT/src/inscore/expression/ExprInfo.h


INCLUDEPATH +=	$$SRC/\
		$$SRC/Parsing/

include($$ITLROOT/src/QArchive/qarchive.pri)



##############################
# import inscore parser
##############################

include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)
