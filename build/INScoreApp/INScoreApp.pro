TEMPLATE = app
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

unix:LIBS += -L.. -lINScore \
	-lGUIDOEngine \
	-L/home/guillaume/Stage/guidolib-code/build

############### Resources
win32 { RC_FILE = $$ROOT/../win32/INScore.rc }
RESOURCES += $$ROOT/../rsrc/inscore.qrc

QMAKE_SONAME_PREFIX = @rpath
QMAKE_RPATHLINKDIR += .

QMAKE_INFO_PLIST = $$PWD/../Info.plist
ICON = $$ROOT/../rsrc/INScoreViewer.icns
