TEMPLATE = lib

TARGET = INScore
DESTDIR = ..
OBJECTS_DIR = tmp
MOC_DIR = tmp

VERSION = 1.11

QT += core gui widgets svg printsupport multimedia multimediawidgets qml websockets

ROOT = $$PWD/../../src

CONFIG -= $$REMOVECONFIG

unix:QMAKE_CXXFLAGS += -Wno-unused-parameter

# INScore sources folders
FOLDERS = controller events lib model view mapping interface graph signal signal/faust ITLParser scripting 
LIBMAPFOLDERS = libmapping/src/misc libmapping/src/parser libmapping/src/relations libmapping/src/segments

FOLDERS += $$LIBMAPFOLDERS

# Add plugin sources
FOLDERS += plugins/gesturefollower
FOLDERS += plugins/faustDSP
FOLDERS += plugins/httpserver

MAP = $$ROOT/libmapping

RSRC = $$ROOT/../rsrc
LOCALLIB = $$ROOT/../lib
OSC_PATH = $$LOCALLIB/oscpack
GUIDO_PATH = $$LOCALLIB/GuidoEngine
GUIDOQT_PATH = $$LOCALLIB/GuidoQt

NOVIEW {
        message ("Compiled with no view - remove CONFIG += NOVIEW to change.")
	DEFINES += NOVIEW
	INSFOLDERS += VoidView
} else {
    message ("Compiled with view - add CONFIG += NOVIEW to change.")
}

LUA {
        message ("lua will be supported - remove CONFIG += LUA to change.")
	DEFINES += LUA
	
	win32:win64 {
		LIBS += $$LOCALLIB/lua/win32/lua.lib
		INCLUDEPATH += $$LOCALLIB/lua/win32
	}
	macx {
		LIBS += -llua
		INCLUDEPATH += /usr/local/include
	}
	unix {
		message("TODO")
	}
} else {
    message ("lua will not be supported - Add CONFIG += LUA to change.")
}

DEFINES += QTJSENGINE

############### Sources
for(folder, FOLDERS) {
    SOURCES += $$files($$ROOT/$$folder/*.cpp)
    HEADERS += $$files($$ROOT/$$folder/*.h*)
    INCLUDEPATH += $$ROOT/$$folder
}

INCLUDEPATH += $$OSC_PATH
INCLUDEPATH += $$GUIDO_PATH/include
INCLUDEPATH += $$GUIDOQT_PATH/include

message($$INCLUDEPATH)
############### libraries
# Linux
unix:!ios:LIBS += -L$$OSC_PATH/cmake -loscpack \
	-L$$ROOT/../lib/GuidoQt/linux -lGuidoQt \
	-L/home/guillaume/Stage/guidolib-code/build
	-lGUIDOEngine

# Windows MinGw
win32:*-g++*:LIBS += $$OSC_PATH/MinGW/liboscpack.a \
	$$LOCALLIB/GuidoQt/win32/libGuidoQt.a \
	$$LOCALLIB/GuidoEngine/win32/libGUIDOEngine.dll.a

# Windows MSVC
win32:*-msvc*:LIBS += ${OSC_PATH}/cmake/release/oscpack.lib \
	$$LOCALLIB/GuidoEngine/win32/GUIDOEngine.lib \
	winmm.lib ws2_32.lib 
win32:*-msvc*:debug:LIBS += $$LOCALLIB/GuidoQt/win32/GuidoQtD.lib
win32:*-msvc*:release:LIBS += $$LOCALLIB/GuidoQt/win32/GuidoQt.lib

ios:LIBS += 
macx:LIBS += 
macx:LIBS += -framework CoreFoundation

