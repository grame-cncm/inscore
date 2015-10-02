TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    IExpression.cpp

HEADERS += \
    IExpression.h

INCLUDEPATH += ../../libmapping/src/misc

