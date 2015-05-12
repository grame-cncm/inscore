
win32 { TEMPLATE = vclib }
else  { TEMPLATE = lib }

TARGET = INScore
OBJECTS_DIR = tmp
MOC_DIR = tmp

VERSION = 1.13

############################## 
# locations
############################## 
ROOT 		= $$PWD/..
SRC 		= $$ROOT/src
LOCALLIB 	= $$ROOT/lib
GUIDO_PATH	= $$LOCALLIB/GuidoEngine
OSC		 	= $$LOCALLIB/oscpack
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

QT += core gui widgets svg printsupport multimedia multimediawidgets qml websockets
DEFINES += QTJSENGINE	# use the Qt Javascript engine

############################## 
# source and headers
############################## 
SOURCES  =  $$files($$SRC/library/*.cpp, true)
SOURCES +=  $$files($$SRC/libmapping/src/*.cpp, true)		# libmapping source files
SOURCES +=  $$files($$OSC/ip/*.cpp)							# oscpack files
SOURCES +=  $$files($$OSC/osc/*.cpp)						# oscpack files
SOURCES +=  $$files($$OSCIP/*.cpp)							# oscpack files

HEADERS  =  $$files($$SRC/library/*.h, true)
HEADERS +=  $$files($$SRC/libmapping/src/*.h, true)
HEADERS +=  $$files($$OSC/ip/*.h)
HEADERS +=  $$files($$OSC/OSC/*.h)
win32:HEADERS +=  $$files($$ROOT/win32/dirent/*.h)

############################## 
# include directories
############################## 
INCLUDEPATH  =  $$files($$SRC/library/[^.]*)
INCLUDEPATH +=  $$files($$SRC/library/plugins/*)
INCLUDEPATH +=  $$files($$SRC/library/signal/faust)
INCLUDEPATH +=  $$files($$SRC/libmapping/src/[^.]*)
INCLUDEPATH +=  $$files($$OSC)
INCLUDEPATH +=  $$GUIDO_PATH/include

############################## 
# No view support, intended
# for mem leak detection
############################## 
NOVIEW {
	message ("Compiled with no view - remove CONFIG+=NOVIEW to change.")
	DEFINES += NOVIEW
	SOURCES  =  $$files($$SRC/VoidView/*.cpp)
	HEADERS  =  $$files($$SRC/VoidView/*.h)
	INCLUDEPATH  =  $$files($$SRC/VoidView)
} else {
    message ("Compiled with Qt view - add CONFIG+=NOVIEW to change to no view.")
}


############################## 
# windows support
# assumes environment is MSVC
############################## 
win32 {
    VERSION = ""
	DEFINES += MSVC _USE_MATH_DEFINES NOMINMAX INScore_EXPORTS _CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS_DEBUG += /wd4100 /EHsc
    QMAKE_CXXFLAGS_RELEASE += /wd4100 /EHsc
    LIBS += $$LOCALLIB/GuidoEngine/win32/GUIDOEngine.lib winmm.lib ws2_32.lib
    RC_FILE = $$ROOT/win32/INScore.rc
    INCLUDEPATH += $$ROOT/win32/dirent
	contains(QMAKE_HOST.arch, x86_64): {
        DEFINES += __x86_64__
        TARGET = INScore64
    }
}

############################## 
# macos x support
############################## 
macx {
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.6
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6 
    QMAKE_MAC_SDK = macosx10.9		# drag & drop doesn't work with macosx10.10 sdk on yosemite
	CONFIG += lib_bundle explicitlib
	QMAKE_INFO_PLIST = $$PWD/libInfo.plist
	QMAKE_LFLAGS += -F$$ROOT/lib/GuidoEngine/macosx/
	QMAKE_LFLAGS += -F$$ROOT/lib/GuidoEngine/macosx/
	LIBS += -framework GUIDOEngine -framework CoreFoundation
    QMAKE_FRAMEWORK_VERSION = $${VERSION}
    QMAKE_FRAMEWORK_BUNDLE_NAME = $$PWD/macos/Release/INScore

	############################## 
	# public headers
	FRAMEWORK_HEADERS.version = Versions
	FRAMEWORK_HEADERS.files = $$files($$SRC/library/interface/*.h)
	FRAMEWORK_HEADERS.path = Headers
	QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}

############################## 
# ios x support
############################## 
ios {
    DEFINES += IOS
    CONFIG += c++11
    CONFIG+= arm64 armv7 armv7s
    CONFIG += staticlib
    LIBS += $$ROOT/lib/GuidoEngine/ios/libGUIDOEngine.a
}

############################## 
# linux support
############################## 
unix:!macx:!ios:!android {
    DEFINES += OSC_HOST_LITTLE_ENDIAN
    LIBS += -lGUIDOEngine
    QMAKE_CXXFLAGS += -Wno-unused-parameter
}

############################## 
# android support
############################## 
android {
    DEFINES += ANDROID OSC_HOST_LITTLE_ENDIAN
    LIBS += -L$$ROOT/lib/GuidoEngine/android -lGUIDOEngine
    QMAKE_CXXFLAGS += -Wno-unused-parameter
    QT += androidextras
}
