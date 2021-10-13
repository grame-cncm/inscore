win32  { TEMPLATE = vcapp }
else   { TEMPLATE = app }


unix:!macx:!ios:!android:TARGET = inscoreviewer
else   { TARGET = INScoreViewer }

OBJECTS_DIR = tmp
MOC_DIR		= tmp
RCC_DIR		= tmp

QT += core gui widgets svg printsupport multimedia multimediawidgets websockets
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

#win32 { VERSION = $$system(type $$PWD\..\version.txt) }
win32 { VERSION = 1.30 }
else  { VERSION = $$system(cat $$ROOT/version.txt) }

CONFIG += c++11

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
# macos x support
############################## 
macx {
	!NOVIEW { DESTDIR = $$PWD/bin }
	QMAKE_LFLAGS += -FRelease
	LIBS += -F$$PWD/bin -framework INScore
	LIBS += -F$$GUIDO_PATH/build/lib -framework GUIDOEngine
	QMAKE_INFO_PLIST = $$PWD/Info.plist
	RSRC.files 	= $$ROOT/rsrc/INScoreViewer.icns
	RSRC.path 	= Contents/Resources
#	PLUG.files 	= $$LXML_PATH/build/lib/libmusicxml2.dylib
	PLUG.files += $$ROOT/lib/GestureFollower/macosx/libGFLib.dylib
	PLUG.files += $$ROOT/lib/faust/macosx/libfaust.dylib
	PLUG.path 	= Contents/PlugIns
	QMAKE_BUNDLE_DATA += PLUG RSRC
	ICON 		= $$ROOT/rsrc/INScoreViewer.icns
}

##############################
# ios support
##############################
ios {
    QMAKE_IOS_DEPLOYMENT_TARGET = 11.0
	QMAKE_LFLAGS += -L Release-iphoneos
	LIBS += -lINScore $$GUIDO_PATH/build/lib/libGUIDOEngine.a 
	QMAKE_INFO_PLIST = $$PWD/Info-ios.plist
	ios_icon.files = $$files($$ROOT/rsrc/ios-icons/*.png)
	QMAKE_BUNDLE_DATA += ios_icon
	OBJECTIVE_SOURCES += $$SRC/mobile/ios/QtAppDelegate.mm
	INCLUDEPATH += $$SRC/mobile/ios
	HEADERS += $$files($$SRC/mobile/ios/*.h)
	RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobileios.qrc
	DEFINES += IOS __MOBILE__
    QT += quick quickwidgets
}

############################## 
# windows support
# assumes environment is MSVC
############################## 
win32 {
	DESTDIR = $$PWD/bin
	VERSION = ""
	CONFIG(debug,debug|release) { LIBS   += $$DESTDIR/INScore.lib }
	else { LIBS   += $$DESTDIR/INScore.lib }
	RC_FILE = $$ROOT/win32/Viewer/INScoreViewer.rc
}

############################## 
# linux support
############################## 
unix:!android:!macx:!ios {
	DESTDIR = $$PWD/bin
	LIBS += -L. -L$$DESTDIR -lINScore -lGUIDOEngine -lmicrohttpd
}

############################## 
# android support
############################## 
android {
#	LIBS +=  -L$$PWD/androiddir/library
	LIBS +=  -L$$PWD/androiddir
	GUIDOANDROID = $$GUIDO_PATH/platforms/android/guido-engine-android/libs/
    equals(ANDROID_TARGET_ARCH, armeabi-v7a) { 
		message ("Includes armeabi-v7a")
        LIBS +=  -lINScore_armeabi-v7a -L$$GUIDOANDROID/armeabi-v7a -lGUIDOEngine
		OBJECTS_DIR = tmp_armeabi-v7a
		MOC_DIR = tmp_armeabi-v7a
    }
    equals(ANDROID_TARGET_ARCH, arm64-v8a) {
		message ("Includes arm64-v8a")
        LIBS +=  -lINScore_arm64-v8a -L$$GUIDOANDROID/arm64-v8a -lGUIDOEngine
		OBJECTS_DIR = tmpv_arm64-v8a
		MOC_DIR = tmpv_arm64-v8a
    }
    equals(ANDROID_TARGET_ARCH, x86)  {
		message ("Includes x86")
       	LIBS +=  -lINScore_x86 -L$$GUIDOANDROID/x86 -lGUIDOEngine
		OBJECTS_DIR = tmpv_x86
		MOC_DIR = tmpv_x86
    }
    equals(ANDROID_TARGET_ARCH, x86_64)  {
		message ("Includes x86_64")
       	LIBS +=  -lINScore_x86_64 -L$$GUIDOANDROID/x86_64 -lGUIDOEngine
        GUIDOLINKPATH = $$GUIDOANDROID/x86_64
		OBJECTS_DIR = tmpv_x86_64
		MOC_DIR = tmpv_x86_64
    }
    ANDROID_API_VERSION = 26
	DISTFILES +=  $$ROOT/rsrc/android/AndroidManifest.xml
	ANDROID_PACKAGE_SOURCE_DIR = $$ROOT/rsrc/android
#	QT += androidextras
	QT += quick quickwidgets
	DEFINES += ANDROID __MOBILE__
	RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobile.qrc
}

mobile_ui{
    DEFINES += __MOBILE__
    RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobile.qrc
}

