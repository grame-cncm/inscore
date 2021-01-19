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
GUIDO_PATH	= $$LOCALLIB/GuidoEngine

APPL   = $$SRC/inscoreviewer
NOVIEW 	{ SRCDIR = $$APPL/noview }
else	{ SRCDIR = $$APPL/qtview }
LIB    = $$SRC/inscore
OSC    = $$LOCALLIB/oscpack
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

VERSION = $$system(cat $$ROOT/version.txt)

CONFIG += c++11

############################## 
# source and headers
############################## 
SOURCES = $$SRCDIR/*.cpp
HEADERS = $$SRCDIR/*.h
INCLUDEPATH += $$SRCDIR $$LIB/interface
INCLUDEPATH += $$LIB/model $$LIB/controller $$LIB/lib $$LIB/mapping $$LIB/events $$LIB/view
INCLUDEPATH += $$LIB/signal $$LIB/scripting $$LIB/expression
INCLUDEPATH += $$SRC/view/guidoqt $$GUIDO_PATH/include
INCLUDEPATH += $$files($$OSC)
INCLUDEPATH += $$files($$SRC/libmapping/src/[^.]*)
INCLUDEPATH += $$SRC/inscore2


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
	QMAKE_INFO_PLIST = $$PWD/Info.plist
	RSRC.files 	= $$ROOT/rsrc/INScoreViewer.icns
	RSRC.path 	= Contents/Resources
	PLUG.files 	= $$ROOT/lib/libMusicXML/macosx/libmusicxml2.dylib
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
	LIBS += -lINScore $$ROOT/lib/GuidoEngine/ios/libGUIDOEngine.a $$ROOT/lib/GuidoAR/ios/libguidoar.a
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
	LIBS += -L. -L$$DESTDIR -lINScore -lGUIDOEngine -lguidoar -lmicrohttpd
}

############################## 
# android support
############################## 
android {
	isEmpty(ARCH) 	{ ARCH = armeabi-v7a }
	LIBS += -L. -lINScore
	ANDROID_EXTRA_LIBS = $$ROOT/lib/GuidoEngine/android/$${ARCH}/libGUIDOEngine.so
	ANDROID_EXTRA_LIBS += $$ROOT/lib/GuidoAR/android/$${ARCH}/libguidoar.so
	ANDROID_EXTRA_LIBS += libINScore.so
	DISTFILES +=  $$ROOT/rsrc/android/AndroidManifest.xml
	ANDROID_PACKAGE_SOURCE_DIR = $$ROOT/rsrc/android
	QT += androidextras
	QT += quick quickwidgets
	DEFINES += ANDROID __MOBILE__
	RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobile.qrc
}

mobile_ui{
    DEFINES += __MOBILE__
    RESOURCES += $$PWD/tmp-rsc/inscoremobile.qrc $$ROOT/rsrc/inscorescriptmobile.qrc
}

