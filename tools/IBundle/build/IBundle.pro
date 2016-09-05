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

win32 { DEFINES += NOHOSTNAME }

##############################
# source and headers
##############################
SOURCES  =	$$files($$SRC/*.cpp, true)
#SOURCES +=	$$files($$SRC/Parsing/*.cpp, true)
SOURCES +=	$$ITLROOT/src/inscore/expression/ExprInfo.cpp


HEADERS  = $$files($$SRC/*.h, true)
INCLUDEPATH +=	$$SRC/ $$SRC/Parsing/

include($$ITLROOT/src/QArchive/qarchive.pri)

##############################
# import inscore parser
##############################
include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)

