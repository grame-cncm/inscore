SOURCES += *.cpp
HEADERS += *.h
FORMS += *.ui

macx:CONFIG+=x86 x86_64
macx:LIBS += -L../../lib/oscpack/cmake/Release -loscpack
win32:LIBS += ../../lib/oscpack/cmake/Release/oscpack.lib
unix:!macx:LIBS += -L../../lib/oscpack/cmake/Release -loscpack

INCLUDEPATH += ../../lib/oscpack