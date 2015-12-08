ROOT 	= $$PWD/../..
OSC     = $$ROOT/lib/oscpack
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

SOURCES += main.cpp Sensors.cpp Sensor.cpp
SOURCES +=  $$files($$OSC/osc/*.cpp)						# oscpack files
SOURCES +=  $$files($$OSC/ip/*.cpp)						# oscpack files
SOURCES +=  $$files($$OSCIP/*.cpp)							# oscpack files
HEADERS += *.h
#FORMS += *.ui

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/rsrc

MOC_DIR = ./tmpSrc
RCC_DIR = ./tmpSrc
UI_DIR  = ./tmpSrc
DESTDIR = $$PWD

macx:CONFIG+=x86_64
QT += qml quick widgets network sensors

INCLUDEPATH += $$OSC

android { 
	OTHER_FILES += rsrc AndroidManifest.xml

	DEFINES += OSC_HOST_LITTLE_ENDIAN 
    DISTFILES +=  AndroidManifest.xml
}
unix:!macx:!ios:!android { DEFINES += OSC_HOST_LITTLE_ENDIAN }

RESOURCES += QtOSCSensor.qrc
