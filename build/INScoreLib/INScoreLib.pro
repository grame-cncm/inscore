win32 { TEMPLATE = vclib }
else  { TEMPLATE = lib }

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

# Add specific source for windows visual studio
win32:*-msvc*: {
    FOLDERS += ../win32/dirent
    DEFINES += MSVC _USE_MATH_DEFINES NOMINMAX INScore_EXPORTS
    QMAKE_CXXFLAGS_DEBUG += /wd4100 /EHsc
    QMAKE_CXXFLAGS_RELEASE += /wd4100 /EHsc
}

win32 {
    contains(QMAKE_HOST.arch, x86_64): {
        DEFINES += __x86_64__
        TARGET = INScore64
    }
}

macx {
    # TODO force use MacOSX10.9.sdk for drag & drop
    DIST {
        CONFIG+= i386 x86_64
    } else {
        message("Only the current architecture will be compiled - Use CONFIG+=DIST to change.")
    }
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.6
}

ios {
    DEFINES += IOS
    CONFIG += c++11
    CONFIG+= arm64 armv7 armv7s
}

# resources
RSRC = $$ROOT/../rsrc

NOVIEW {
        message ("Compiled with no view - remove CONFIG+=NOVIEW to change.")
	DEFINES += NOVIEW
	INSFOLDERS += VoidView
} else {
    message ("Compiled with view - add CONFIG+=NOVIEW to change.")
}

LUA {
        message ("lua will be supported - remove CONFIG+=LUA to change.")
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
                LIBS += -llua5.1
                INCLUDEPATH += /usr/include/lua5.1

	}
} else {
    message ("lua will not be supported - Add CONFIG+=LUA to change.")
}

DEFINES += QTJSENGINE

############### Librairies path
LOCALLIB = $$ROOT/../lib
OSC_PATH = $$LOCALLIB/oscpack
GUIDO_PATH = $$LOCALLIB/GuidoEngine
GUIDOQT_PATH = $$LOCALLIB/GuidoQt

############### Sources
message($$FOLDERS)
for(folder, FOLDERS) {
    SOURCES += $$files($$ROOT/$$folder/*.cpp)
    HEADERS += $$files($$ROOT/$$folder/*.h*)
    INCLUDEPATH += $$ROOT/$$folder
}
message($$INCLUDEPATH)
############## Include
INCLUDEPATH += $$OSC_PATH
INCLUDEPATH += $$GUIDO_PATH/include
INCLUDEPATH += $$GUIDOQT_PATH/include

############### libraries
# Linux
unix:!ios:!android:LIBS += -L$$OSC_PATH/cmake -loscpack \
        -L$$ROOT/../lib/GuidoQt/linux -lGuidoQt \
	-lGUIDOEngine

# Windows MinGw
win32:*-g++*:LIBS += $$OSC_PATH/MinGW/liboscpack.a \
	$$LOCALLIB/GuidoQt/win32/libGuidoQt.a \
        $$LOCALLIB/GuidoEngine/win32/libGUIDOEngine.dll.a \
        winmm ws2_32

# Windows MSVC
win32:*-msvc*:LIBS += $$OSC_PATH/cmake/release/oscpack.lib \
	$$LOCALLIB/GuidoEngine/win32/GUIDOEngine.lib \
        winmm.lib ws2_32.lib
win32:*-msvc*:LIBS += $$LOCALLIB/GuidoQt/win32/GuidoQt.lib

ios:LIBS += $$OSC_PATH/build/iOS/Release-iphoneos/liboscpack.a \
        $$ROOT/../lib/GuidoQt/ios/libGuidoQt.a \
        $$ROOT/../lib/GuidoEngine/ios/libGUIDOEngine.a

android:LIBS += -L$$OSC_PATH/oscpack/lib -loscpack \
        -L$$ROOT/../lib/GuidoQt/android -lGuidoQt-android \
        -L$$ROOT/../lib/GuidoEngine/android -lGUIDOEngine

macx:LIBS += 
macx:LIBS += -framework CoreFoundation
