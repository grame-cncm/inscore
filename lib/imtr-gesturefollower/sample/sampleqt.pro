#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T15:34:19
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = sampleqt
TEMPLATE = app

DESTDIR = bin

SOURCES  += main.cpp mainwindow.cpp gdrawarea.cpp gfollower.cpp
HEADERS  += mainwindow.h gdrawarea.h gfollower.h
FORMS    += mainwindow.ui

INCLUDEPATH += ../src ../include

#	macx:LIBS += -F../cmake/Release -framework GFLib
#	macx:LIBS += -L../cmake/Release -lGFLib
macx {
exists (../cmake/Release/libGFLib.a) {
   message( "Configuring for static link" )
	macx:LIBS += -L../cmake/Release -lGFLib
} else {
	exists (../lib/libGFLib.a) {
		macx:LIBS += -L../lib -lGFLib
	} else {
		exists (../cmake/Release/GFLib.framework/GFLib) {
   			message( "Configuring for dynamic link" )
			macx:LIBS += -F../cmake/Release -framework GFLib
		} else {
			exists (../lib/GFLib.framework/GFLib) {
				macx:LIBS += -F../lib -framework GFLib
			}
		}
	}
}
}
win32:LIBS += ../cmake/release/GFLib.lib
unix:!macx:LIBS += -L../cmake -lGFLib
