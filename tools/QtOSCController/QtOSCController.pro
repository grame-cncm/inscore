SOURCES += main.cpp MainWindow.cpp
HEADERS += *.h
FORMS += *.ui

MOC_DIR = ./tmpSrc
RCC_DIR = ./tmpSrc
UI_DIR  = ./tmpSrc
DESTDIR = $$PWD

macx:CONFIG+=x86 x86_64
macx:LIBS += -L$$PWD/../../lib/oscpack -loscpack
ios:LIBS += -L$$PWD/../../lib/oscpack/build/iOS/Release-iphoneos -loscpack
win32:LIBS += $$PWD/../../lib/oscpack/cmake/Release/oscpack.lib
unix:!macx:LIBS += -L$$PWD/../../lib/oscpack/cmake/Release -loscpack
QT += widgets 
QT += network

INCLUDEPATH += $$PWD/../../lib/oscpack
