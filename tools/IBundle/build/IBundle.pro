win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }
CONFIG += console
CONFIG += warn_off
CONFIG -= app_bundle

TARGET      = IBundle
OBJECTS_DIR	= tmp
MOC_DIR		= tmp
DESTDIR     = $$PWD/..

QT = core

VERSION = 1.0

##############################
# locations
##############################
ROOT 		= $$PWD/..
SRC 		= $$ROOT/src
ITLROOT		= $$ROOT/../../
ITLSRC		= $$ITLROOT/src

DEFINES += IBUNDLE
win32 						{ DEFINES += NOHOSTNAME WINDOWS }
android 					{ DEFINES += ANDROID }
ios 						{ DEFINES += IOS }
macx 						{ DEFINES += MACOS }
unix:!macx:!ios:!android 	{ DEFINES += __LINUX__ }
greaterThan(QT_MINOR_VERSION, 3) { DEFINES += QTFUNCTOR } else { DEFINES += QT_LESS_55}

!win32 {
    QMAKE_CFLAGS_WARN_OFF += -Wno-deprecated-register -Wno-unused-parameter
}

##############################
# source and headers
##############################
SOURCES  =	$$files($$SRC/*.cpp, true)
SOURCES +=	$$ITLROOT/src/inscore/expression/ExprInfo.cpp

HEADERS  = $$files($$SRC/*.h, true)
INCLUDEPATH +=	$$SRC/ $$SRC/Parsing/ 
INCLUDEPATH +=	$$ITLSRC/inscore/signal/
INCLUDEPATH +=	$$ITLSRC/inscore2
INCLUDEPATH +=	$$ITLSRC/inscore2/sorter

include($$ITLROOT/src/QArchive/qarchive.pri)

##############################
# import inscore parser
##############################
include ($$ITLROOT/src/inscore/ITLParser/ITLParser.pri)
