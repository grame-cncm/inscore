win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }

TARGET = inscoreviewer
DESTDIR = ..
OBJECTS_DIR = tmp
MOC_DIR = tmp

VERSION = 1.11

QT += core gui widgets svg printsupport multimedia multimediawidgets qml websockets

ROOT = $$PWD/../../src


NOVIEW { 
	SOURCES += $$ROOT/INScoreNoView.cpp
} else {
	SOURCES += $$ROOT/INScoreAppl.cpp
}
HEADERS += $$ROOT/INScoreAppl.h

INCLUDEPATH += $$ROOT $$ROOT/interface

unix:!android:LIBS += -L.. -lINScore \
        -lGUIDOEngine

android:LIBS += -L.. -lINScore
android:ANDROID_EXTRA_LIBS = $$ROOT/../lib/GuidoEngine/android/libGUIDOEngine.so \
    $$ROOT/../lib/oscpack/android/libs/armeabi/liboscpack.so \
    libINScore.so

win32:LIBS+= ../INScore1.lib

############### Resources
win32 { RC_FILE = $$ROOT/../win32/Viewer/INScoreViewer.rc }
RESOURCES += $$ROOT/../rsrc/inscore.qrc

QMAKE_INFO_PLIST = $$PWD/../Info.plist
ICON = $$ROOT/../rsrc/INScoreViewer.icns

android:DISTFILES += \
    ../android/AndroidManifest.xml

android:ANDROID_PACKAGE_SOURCE_DIR = $$PWD/../android

