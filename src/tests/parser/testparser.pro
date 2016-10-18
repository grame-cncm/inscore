 
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle qt

DEFINES += NO_OSCSTREAM

include($$PWD/../../inscore/ITLParser/ITLParser.pri)

SOURCES += $$PWD/testparser.cpp