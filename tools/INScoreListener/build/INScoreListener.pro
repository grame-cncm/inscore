TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle qt

VERSION = 0.1

############################## 
# locations
############################## 
ROOT 		= $$PWD/..
SRC 		= $$ROOT/src

ITLROOT		= $$ROOT/../../
REGEXPLIB 	= $$ITLROOT/src/inscore/lib
OSCLIB		= $$ITLROOT/lib/oscpack

############################## 
# source and headers
############################## 
SOURCES +=	$$SRC/INScoreListener.cpp
SOURCES +=	$$SRC/ITLlistener.cpp
SOURCES +=	$$SRC/OSCFilter.cpp
SOURCES +=	$$files($$SRC/Parser/*.cpp)

HEADERS +=	$$SRC/ITLlistener.h \
    ../src/Parser/filter.l \
    ../src/Parser/filter.y
HEADERS +=	$$SRC/OSCFilter.h
HEADERS +=	$$files($$SRC/Parser/*.h)
HEADERS +=	$$files($$SRC/Parser/*.hpp)

SOURCES +=	$$REGEXPLIB/OSCRegexp.cpp
HEADERS +=	$$REGEXPLIB/OSCRegexp.h

SOURCES += $$files($$OSCLIB/osc/*.cpp)
SOURCES += $$files($$OSCLIB/ip/*.cpp)
HEADERS += $$files($$OSCLIB/osc/*.h)
HEADERS += $$files($$OSCLIB/ip/*.h)

##############################
# include directories
##############################
INCLUDEPATH +=	$$REGEXPLIB
INCLUDEPATH += $$OSCLIB

############################## 
# osc support
############################## 
unix:!macx:!ios:!android {
    DEFINES += OSC_HOST_LITTLE_ENDIAN __LINUX__
    SOURCES += $$files($$OSCLIB/ip/posix/*.cpp)
}
macx {
    DEFINES += OSC_HOST_LITTLE_ENDIAN __LINUX__
    SOURCES += $$files($$OSCLIB/ip/posix/*.cpp)
}
