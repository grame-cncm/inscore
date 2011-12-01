SOURCES += *.cpp
HEADERS += *.h
FORMS += *.ui

macx:LIBS += -L../../lib/oscpack -loscpack
win32:LIBS += ../../lib/oscpack/oscpack.lib
unix:!macx:LIBS += -L../../lib/oscpack/cmake -loscpack

INCLUDEPATH += ../../lib/oscpack