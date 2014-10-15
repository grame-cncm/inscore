SOURCES += main.cpp MainWindow.cpp
HEADERS += *.h
FORMS += *.ui

macx:CONFIG+=x86 x86_64
macx:LIBS += -L../../lib/oscpack/build/MacOS/Release -loscpack
ios:LIBS += -L../../lib/oscpack/build/iOS/Release-iphoneos -loscpack
win32:LIBS += ../../lib/oscpack/cmake/Release/oscpack.lib
unix:!macx:LIBS += -L../../lib/oscpack/cmake/Release -loscpack
QT += widgets 
QT += network

INCLUDEPATH += ../../lib/oscpack