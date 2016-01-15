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
		$$SRC/BundleExtractor.cpp




HEADERS +=	$$SRC/BundleExtractor.h \
		$$SRC/doc.h

INCLUDEPATH +=	$$SRC/

include($$SRC/QArchive/qarchive.pri)
