 
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT -= gui;

VERSION = 1.0

TARGET = QArchive



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
SOURCES +=  $$SRC/testqarchive.cpp\
	    $$SRC/Archiving/QArchive.cpp \
	    $$SRC/Archiving/QSubIODevice.cpp \
	    $$SRC/Archiving/QArchiveHeader.cpp




HEADERS +=  $$SRC/Archiving/QArchive.h \
	    $$SRC/Archiving/QSubIODevice.h \
	    $$SRC/Archiving/Tree.h \
	    $$SRC/Archiving/Tree.tpp \
	    $$SRC/Archiving/QArchiveHeader.h

INCLUDEPATH +=	$$SRC/\
		$$SRC/Archiving/

include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)
