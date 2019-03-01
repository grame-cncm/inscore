
win32 { TEMPLATE = vclib }
else  { TEMPLATE = lib }

TARGET = INScore
OBJECTS_DIR = tmp
MOC_DIR = tmp

VERSION = $$system(cat ../version.txt)
CONFIG += c++11
CONFIG += warn_off

############################## 
# locations
############################## 
ROOT 		= $$PWD/..
SRC 		= $$ROOT/src
LOCALLIB 	= $$ROOT/lib
GUIDO_PATH	= $$LOCALLIB/GuidoEngine
GUIDOAR_PATH= $$LOCALLIB/GuidoAR
OSC         = $$LOCALLIB/oscpack
QRENCODE    = $$LOCALLIB/qrencode
JSON        = $$SRC/json
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

QT += core gui widgets svg printsupport multimedia multimediawidgets websockets 
QT += quick qml quickwidgets sensors
DEFINES += INScore_EXPORTS
DEFINES += HAVE_CONFIG_H  # defined for the qrencode library
DEFINES += QTJSENGINE	# use the Qt Javascript engine
DEFINES += JSON_ONLY    # json library doesn't use osc stream.
greaterThan(QT_MINOR_VERSION, 3) { DEFINES += QTFUNCTOR } else { DEFINES += QT_LESS_55}


############################## 
# source and headers
############################## 
SOURCES  =  $$files($$SRC/inscore/*.cpp, true)
SOURCES +=  $$files($$SRC/libmapping/src/*.cpp, true)		# libmapping source files
SOURCES +=  $$files($$OSC/ip/*.cpp)							# oscpack files
SOURCES +=  $$files($$OSC/osc/*.cpp)						# oscpack files
SOURCES +=  $$files($$OSCIP/*.cpp)							# oscpack files
SOURCES +=  $$files($$QRENCODE/*.c)							# qrencode files
SOURCES +=  $$files($$JSON/*.cpp)

HEADERS  =  $$files($$SRC/inscore/*.h, true)
HEADERS +=  $$files($$SRC/inscore/*.y, true)
HEADERS +=  $$files($$SRC/inscore/*.l, true)
HEADERS +=  $$files($$SRC/libmapping/src/*.h, true)
HEADERS +=  $$files($$OSC/ip/*.h)
HEADERS +=  $$files($$OSC/OSC/*.h)
HEADERS +=  $$files($$JSON/*.h)
win32:HEADERS +=  $$files($$ROOT/win32/dirent/*.h)

#QArchive
include($$SRC/QArchive/qarchive.pri)

############################## 
# include directories
############################## 
INCLUDEPATH  =  $$files($$SRC/inscore/[^.]*)
INCLUDEPATH +=  $$files($$SRC/inscore/plugins/*)
INCLUDEPATH +=  $$files($$SRC/inscore/signal/faust)
INCLUDEPATH +=  $$files($$SRC/inscore/expression/parser)
INCLUDEPATH +=  $$files($$SRC/libmapping/src/[^.]*)
INCLUDEPATH +=  $$files($$OSC)
INCLUDEPATH +=  $$files($$QRENCODE)
INCLUDEPATH +=  $$files($$JSON)
INCLUDEPATH +=  $$GUIDO_PATH/include
INCLUDEPATH +=  $$GUIDOAR_PATH/include


############################## 
# No view support, intended
# for mem leak detection
############################## 
NOVIEW {
	message ("Compiled with no view - remove CONFIG+=NOVIEW to change.")
	DEFINES += NOVIEW
	SOURCES  +=  $$files($$SRC/VoidView/*.cpp)
	HEADERS  +=  $$files($$SRC/VoidView/*.h)
	INCLUDEPATH +=  $$files($$SRC/VoidView)
} else {
    message ("Compiled with Qt view - add CONFIG+=NOVIEW to change to no view.")
}


############################## 
# windows support
# assumes environment is MSVC
############################## 
win32 {
	DESTDIR = $$PWD/bin
	QT += opengl
    VERSION = ""
	DEFINES += MSVC _USE_MATH_DEFINES NOMINMAX _CRT_SECURE_NO_WARNINGS WINDOWS 
	# Variable to add to DEFINES to avoid execution errors when debbuging on windows "_ITERATOR_DEBUG_LEVEL=0"
    QMAKE_CXXFLAGS_DEBUG += /wd4100 /EHsc
    QMAKE_CXXFLAGS_RELEASE += /wd4100 /EHsc
    LIBS += winmm.lib ws2_32.lib
    RC_FILE = $$ROOT/win32/INScore.rc
    INCLUDEPATH += $$ROOT/win32/dirent
	contains(QMAKE_HOST.arch, x86_64): {
        DEFINES += __x86_64__
		LIBS += $$LOCALLIB/GuidoEngine/win64/GUIDOEngine64.lib
		LIBS += $$LOCALLIB/GuidoAR/win64/guidoar.lib
   }
	else {
		LIBS += $$LOCALLIB/GuidoEngine/win32/GUIDOEngine.lib
		LIBS += $$LOCALLIB/GuidoAR/win32/guidoar.lib
	}
}
!win32 {
    QMAKE_CFLAGS_WARN_OFF = -Wno-deprecated-register -Wno-unused-parameter
}

############################## 
# macos x support
############################## 
macx {
	DESTDIR = $$PWD/bin
	QT += opengl
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7 
	CONFIG += lib_bundle explicitlib
	QMAKE_INFO_PLIST = $$PWD/libInfo.plist
	QMAKE_LFLAGS += -F$$ROOT/lib/GuidoEngine/macosx/
	QMAKE_LFLAGS += -F$$ROOT/lib/GuidoAR/macosx/
	LIBS += -framework GUIDOEngine -framework GuidoAR -framework CoreFoundation
	INCLUDEPATH += /usr/local/include
	LIBS += -L/usr/local/lib -lmicrohttpd
    QMAKE_FRAMEWORK_VERSION = $${VERSION}
    QMAKE_FRAMEWORK_BUNDLE_NAME = $$PWD/macos/Release/INScore
    DEFINES += MACOS

	############################## 
	# public headers
	FRAMEWORK_HEADERS.version = Versions
	FRAMEWORK_HEADERS.files = $$files($$SRC/inscore/interface/*.h)
	FRAMEWORK_HEADERS.path = Headers
	QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}

############################## 
# ios x support
############################## 
ios {
    QMAKE_IOS_DEPLOYMENT_TARGET = 11.0
    SOURCES  +=  $$files($$SRC/mobile/*.cpp)
    HEADERS  +=  $$files($$SRC/mobile/*.h)
    INCLUDEPATH  +=  $$files($$SRC/mobile)
    DEFINES += INSCORE_IOS __MOBILE__
    CONFIG += arm64 x86_64   # armv7 armv7s
    CONFIG += staticlib
    LIBS += $$ROOT/lib/GuidoEngine/ios/libGUIDOEngine.a
    LIBS += $$ROOT/lib/GuidoAR/ios/libguidoar.a
}

############################## 
# linux support
############################## 
unix:!macx:!ios:!android {
	DESTDIR = $$PWD/bin
	QT += opengl
    DEFINES += OSC_HOST_LITTLE_ENDIAN __LINUX__
    LIBS += -lGUIDOEngine -lguidoar
}

############################## 
# android support
############################## 
android {
    SOURCES  +=  $$files($$SRC/mobile/*.cpp)
    HEADERS  +=  $$files($$SRC/mobile/*.h)
    INCLUDEPATH  +=  $$files($$SRC/mobile)
    DEFINES += ANDROID __MOBILE__ OSC_HOST_LITTLE_ENDIAN
    LIBS += -L$$ROOT/lib/GuidoEngine/android -lGUIDOEngine
    LIBS += -L$$ROOT/lib/GuidoAR/android -lguidoar
    QT += androidextras
}

##############################
# mobile test
##############################
mobile_ui{
    DEFINES += __MOBILE__ MOBILE_TEST
    SOURCES  +=  $$files($$SRC/mobile/*.cpp)
    HEADERS  +=  $$files($$SRC/mobile/*.h)
    INCLUDEPATH  +=  $$files($$SRC/mobile)
}
