win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }

unix:!macx:!ios:!android:TARGET = inscoreviewer
else { TARGET = INScoreViewer }
OBJECTS_DIR = tmp
MOC_DIR		= tmp
RCC_DIR		= tmp

QT += core gui widgets svg printsupport multimedia multimediawidgets websockets
QT += qml sensors
#QT += quick quickwidgets

############################## 
# locations
############################## 
ROOT = $$PWD/..
SRC  = $$ROOT/src
LOCALLIB 	= $$ROOT/lib
GUIDO_PATH	= $$LOCALLIB/GuidoEngine

APPL = $$SRC/inscoreviewer
LIB  = $$SRC/inscore
OSC  = $$LOCALLIB/oscpack
win32 { OSCIP = $$OSC/ip/win32 }
else  { OSCIP = $$OSC/ip/posix }

VERSION = $$system(cat $$ROOT/version.txt)

CONFIG += c++11

############################## 
# source and headers
############################## 
NOVIEW { SOURCES += $$APPL/INScoreNoView.cpp } 
else   { SOURCES += $$APPL/INScoreAppl.cpp }
HEADERS 	+= $$APPL/INScoreAppl.h
INCLUDEPATH += $$APPL $$LIB/interface
INCLUDEPATH += $$LIB/model $$LIB/controller $$LIB/lib $$LIB/mapping $$LIB/events $$LIB/view
INCLUDEPATH += $$LIB/signal $$LIB/scripting $$LIB/expression
INCLUDEPATH += $$SRC/inscore/view/guidoqt $$GUIDO_PATH/include
INCLUDEPATH += $$files($$OSC)
INCLUDEPATH += $$files($$SRC/libmapping/src/[^.]*)

############### Resources
RESOURCES += $$ROOT/rsrc/inscore.qrc
ICON = $$ROOT/rsrc/INScoreViewer.icns

############################## 
# macos x support
############################## 
macx {
	DESTDIR = $$PWD/bin
	QMAKE_LFLAGS += -FRelease
	LIBS += -F$$ROOT/bin -framework INScore
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
    CONFIG  += arm64 armv7 armv7s # x86_64
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
	LIBS += -L. -lINScore
	ANDROID_EXTRA_LIBS = $$ROOT/lib/GuidoEngine/android/libGUIDOEngine.so $$ROOT/lib/GuidoAR/android/libguidoar.so libINScore.so
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

