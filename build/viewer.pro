TEMPLATE = app
TARGET = INScoreViewer

OBJECTS_DIR = tmp
MOC_DIR		= tmp
RCC_DIR		= tmp

QT += core gui widgets svg multimedia multimediawidgets websockets # printsupport
QT += qml sensors

############################## 
# locations
############################## 
ROOT = $$PWD/..
SRC  = $$ROOT/src
LOCALLIB 	= $$ROOT/lib
GUIDO_PATH	= $$ROOT/modules/guidolib
LXML_PATH	= $$ROOT/modules/libmusicxml

APPL   = $$SRC/inscoreviewer
NOVIEW 	{ SRCDIR = $$APPL/noview }
else	{ SRCDIR = $$APPL/qtview }
LIB    = $$SRC/inscore
OSC    = $$LOCALLIB/oscpack
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

VERSION = $$system(cat $$ROOT/version.txt)
CONFIG += c++17

############################## 
# source and headers
############################## 
SOURCES = $$files($$SRCDIR/*.cpp)
HEADERS = $$files($$SRCDIR/*.h)
INCLUDEPATH += $$SRCDIR $$LIB/interface
INCLUDEPATH += $$LIB/model $$LIB/controller $$LIB/lib $$LIB/mapping $$LIB/events $$LIB/view
INCLUDEPATH += $$LIB/signal $$LIB/scripting $$LIB/expression
INCLUDEPATH += $$SRC/view/guidoqt $$GUIDO_PATH/src/engine/include
INCLUDEPATH += $$files($$OSC)
INCLUDEPATH += $$files($$SRC/libmapping/src/[^.]*)
INCLUDEPATH += $$SRC/inscore2
INCLUDEPATH += $$GUIDO_PATH/environments/Qt/libs/GuidoQt/include


############### Resources
RESOURCES += $$ROOT/rsrc/inscore.qrc
ICON = $$ROOT/rsrc/INScoreViewer.icns

##############################
# ios support
##############################
ios {
	message ("Generates project for iOS")
    QMAKE_IOS_DEPLOYMENT_TARGET = 13.0
	QMAKE_LFLAGS += $$PWD/lib/libGUIDOEngine.a -LRelease-iphoneos -lINScore
	QMAKE_INFO_PLIST = $$PWD/Info-ios.plist
	ios_icon.files = $$files($$ROOT/rsrc/ios-icons/*.png)
	QMAKE_BUNDLE_DATA += ios_icon
	OBJECTIVE_SOURCES += $$SRC/mobile/ios/QtAppDelegate.mm
	INCLUDEPATH += $$SRC/mobile/ios
	HEADERS += $$files($$SRC/mobile/ios/*.h)
	RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobileios.qrc
	DEFINES += INSCORE_IOS __MOBILE__ 
    QT += quick quickwidgets
}


############################## 
# android support
############################## 
android {
#	LIBS +=  -L$$PWD/androiddir/library
	LIBS +=  -L$$PWD/androiddir
	GUIDOANDROID = $$PWD/lib
    equals(ANDROID_TARGET_ARCH, armeabi-v7a) { 
		message ("Includes armeabi-v7a")
        LIBS +=  -lINScore_armeabi-v7a -L$$GUIDOANDROID -lGUIDOEngine_armeabi-v7a 
		OBJECTS_DIR = tmp_armeabi-v7a
		MOC_DIR = tmp_armeabi-v7a
    }
    equals(ANDROID_TARGET_ARCH, arm64-v8a) {
		message ("Includes arm64-v8a")
        LIBS +=  -lINScore_arm64-v8a -L$$GUIDOANDROID -lGUIDOEngine_arm64-v8a
		OBJECTS_DIR = tmpv_arm64-v8a
		MOC_DIR = tmpv_arm64-v8a
    }
    equals(ANDROID_TARGET_ARCH, x86)  {
		message ("Includes x86")
       	LIBS +=  -lINScore_x86 -L$$GUIDOANDROID -lGUIDOEngine_x86
		OBJECTS_DIR = tmpv_x86
		MOC_DIR = tmpv_x86
    }
    equals(ANDROID_TARGET_ARCH, x86_64)  {
		message ("Includes x86_64")
       	LIBS +=  -lINScore_x86_64 -L$$GUIDOANDROID -lGUIDOEngine_x86_64
		OBJECTS_DIR = tmpv_x86_64
		MOC_DIR = tmpv_x86_64
    }
    ANDROID_API_VERSION = 29
	DISTFILES +=  $$ROOT/rsrc/android/AndroidManifest.xml
	ANDROID_PACKAGE_SOURCE_DIR = $$ROOT/rsrc/android
	QT += quick quickwidgets androidextras 3dextras
	DEFINES += ANDROID __MOBILE__
	RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobile.qrc
}

mobile_ui{
    DEFINES += __MOBILE__
    RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobile.qrc
}

