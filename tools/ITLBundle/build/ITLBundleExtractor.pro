win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }
CONFIG += console
CONFIG -= app_bundle

TARGET = ITLBundleExtractor
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
SOURCES +=	$$SRC/ITLBundleExtractor.cpp\
    ../src/Archiving/QArchive.cpp \
    ../src/Archiving/QSubIODevice.cpp \
    ../src/Archiving/QArchiveHeader.cpp




HEADERS +=../src/Archiving/QArchive.h \
    ../src/Archiving/QSubIODevice.h \
    ../src/Archiving/Tree.h \
    ../src/Archiving/Tree.tpp \
    ../src/Archiving/QArchiveHeader.h

INCLUDEPATH +=	$$SRC/\
		$$SRC/Archiving/ \
		$$ITLROOT/src/libmapping/src/misc/
