win32 { TEMPLATE = vcapp }
else  { TEMPLATE = app }

unix:!macx:!ios:!android:TARGET = inscoreviewer
else { TARGET = INScoreViewer }
OBJECTS_DIR = tmp
MOC_DIR		= tmp
RCC_DIR		= tmp

VERSION = 1.13

QT += core gui widgets svg printsupport multimedia multimediawidgets qml websockets

############################## 
# locations
############################## 
ROOT = $$PWD/..
SRC  = $$ROOT/src
APPL = $$SRC/application
LIB  = $$SRC/library

############################## 
# source and headers
############################## 
NOVIEW { SOURCES += $$APPL/INScoreNoView.cpp } 
else   { SOURCES += $$APPL/INScoreAppl.cpp }
HEADERS 	+= $$APPL/INScoreAppl.h
INCLUDEPATH += $$APPL $$LIB/interface

############### Resources
RESOURCES += $$ROOT/rsrc/inscore.qrc
ICON = $$ROOT/rsrc/INScoreViewer.icns

############################## 
# macos x support
############################## 
macx {
	QMAKE_LFLAGS += -F$$PWD/macos/Release
	LIBS += -framework INScore
	QMAKE_INFO_PLIST = $$PWD/Info.plist
	RSRC.files 	= $$ROOT/rsrc/INScoreViewer.icns
	RSRC.path 	= Contents/Resources
	QMAKE_BUNDLE_DATA += RSRC
	ICON 		= $$ROOT/rsrc/INScoreViewer.icns
}

##############################
# ios support
##############################
ios {
        LIBS += -L. -lINScore $$ROOT/lib/GuidoEngine/ios/libGUIDOEngine.a
        QMAKE_INFO_PLIST = $$PWD/Info.plist
        ios_icon.files = $$files($$ROOT/rsrc/ios/*.png)
        QMAKE_BUNDLE_DATA += ios_icon
        ICON 		= $$ROOT/rsrc/INScoreViewer.icns
}

############################## 
# windows support
# assumes environment is MSVC
############################## 
win32 {
	VERSION = ""
	CONFIG(debug,debug|release) { LIBS   += debug/INScore.lib }
	else { LIBS   += release/INScore.lib }
	RC_FILE = $$ROOT/win32/Viewer/INScoreViewer.rc
}

############################## 
# linux support
############################## 
unix:!android:!macx:LIBS += -L. -lINScore -lGUIDOEngine

############################## 
# android support
############################## 
android {
        LIBS += -L. -lINScore
	ANDROID_EXTRA_LIBS = $$ROOT/lib/GuidoEngine/android/libGUIDOEngine.so
        DISTFILES += android/AndroidManifest.xml
        ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
        QT += androidextras
}

