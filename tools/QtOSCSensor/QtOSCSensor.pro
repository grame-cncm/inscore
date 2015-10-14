ROOT 	= $$PWD/../..
OSC     = $$ROOT/lib/oscpack
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

SOURCES += main.cpp MainWindow.cpp Sensor.cpp
SOURCES +=  $$files($$OSC/osc/*.cpp)						# oscpack files
SOURCES +=  $$files($$OSC/ip/*.cpp)						# oscpack files
SOURCES +=  $$files($$OSCIP/*.cpp)							# oscpack files
HEADERS += *.h
FORMS += *.ui

MOC_DIR = ./tmpSrc
RCC_DIR = ./tmpSrc
UI_DIR  = ./tmpSrc
DESTDIR = $$PWD

macx:CONFIG+=x86_64
QT += widgets 
QT += network
QT += sensors

INCLUDEPATH += $$OSC

android { DEFINES += OSC_HOST_LITTLE_ENDIAN }
unix:!macx:!ios:!android { DEFINES += OSC_HOST_LITTLE_ENDIAN }
