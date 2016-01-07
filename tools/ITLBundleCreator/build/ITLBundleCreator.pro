 
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT -= gui;

VERSION = 1.0

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
SOURCES +=	$$SRC/ITLBundleCreator.cpp \
                $$SRC/BundleCreator.cpp \
                $$SRC/BundleLog.cpp



HEADERS +=	$$SRC/BundleCreator.h \
                $$SRC/BundleLog.h




############################## 
# import inscore parser
############################## 

include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)

# javascript
#HEADERS += $$ITLSRC/scripting/TQtJs.h
#SOURCES += $$ITLSRC/scripting/TQtJs.cpp
