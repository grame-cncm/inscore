#
# 
#

.PHONY : macos ios win32 win64 linux android installAndroid help

QMAKE ?= qmake

system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET = macos
	SPEC = -spec macx-xcode
	QMAKEIOS = qmake-ios
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET = windows
else
ifeq ($(system), MINGW32_NT-6.2)
	TARGET = windows
else
	TARGET = linux
endif
endif
endif

ifeq ($(TARGET), windows)
 WINARCH ?= $(shell ./qt-arch)
 MSVC ?= $(shell ./vs-path)
 WINOPTS := /maxcpucount:4 /p:Configuration=Release /p:Platform=$(WINARCH)
 SPEC ?= -spec win32-msvc2013
ifeq ($(WINARCH), x64)
	WDEST = win64
	GUIDOLIB = GUIDOEngine64.dll
 else
	WDEST = win32
	GUIDOLIB = GUIDOEngine.dll
 endif
endif

OUT  := INScore.framework

all :
	make $(TARGET)

help :
	@echo "This makefile is intended to build INScore for differents platforms."
	@echo "Available targets are : "
	@echo "  macos : to build for Mac OS"
	@echo "  ios : to build for iOS"
	@echo "  windows : to build for Windows"
	@echo "  linux : to build for Linux"
	@echo "  android : to build for android"
	@echo "  installAndroid DEVICE=XXX : to install application on Android device"
	@echo "    with XXX the device serial number (can be retrieved using 'make devandroid')"
	@echo "  devandroid : to get the serial number of the connected device"

#===============================================================
# building INScore on Mac OS X
#===============================================================
macos : macos/INScore.xcodeproj macos/INScoreViewer.xcodeproj INScoreMac

xcodeproj: library.pro viewer.pro
	[ -d macos ] || mkdir macos
	cd macos && $(QMAKE) $(SPEC) ../library.pro 
	touch macos/INScore.xcodeproj
	cd macos && $(QMAKE) $(SPEC) ../viewer.pro 
	touch macos/INScoreViewer.xcodeproj

INScoreMac : 
	make -C ../lib/GuidoEngine/macosx
	xcodebuild -jobs 8 -project macos/INScore.xcodeproj -target INScore -configuration Release
	xcodebuild -jobs 8 -project macos/INScoreViewer.xcodeproj -target INScoreViewer -configuration Release

macos/INScore.xcodeproj : library.pro
	make xcodeproj

macos/INScoreViewer.xcodeproj : viewer.pro
	make xcodeproj

#===============================================================
# building INScore for iOS 
#===============================================================
ios : ios/INScore.xcodeproj ios/INScoreViewer.xcodeproj INScoreIos

xcodeprojios:
	[ -d ios ] || mkdir ios
	cd ios && $(QMAKEIOS) $(SPEC) ../library.pro 
	cd ios && $(QMAKEIOS) $(SPEC) ../viewer.pro 
	touch ios/INScore.xcodeproj
	touch ios/INScoreViewer.xcodeproj

INScoreIos : 
	xcodebuild -jobs 8 -project ios/INScore.xcodeproj -target INScore -configuration Release
	xcodebuild -jobs 8 -project ios/INScoreViewer.xcodeproj -target INScoreViewer -configuration Release

ios/INScore.xcodeproj : library.pro
	make xcodeprojios

ios/INScoreViewer.xcodeproj : viewer.pro
	make xcodeprojios

#===============================================================
# building INScore for Android
#===============================================================
SPECANDROID = -spec android-g++
SIGN=--sign ../../rsrc/inscore.keystore grame-inscore  --storepass grameinscore

android : android/Makefile INScoreAndroid

android/Makefile: library.pro INScore.pro
	[ -d android ] || mkdir android
	cd android && qmake-android $(SPECANDROID) ../INScore.pro

INScoreAndroid :
	make -j 4 -C android -f Makefile
	[ -d android/android-build ] || mkdir android/android-build
	cd android && make INSTALL_ROOT=android-build install
	cd android && androiddeployqt --input android-libINScoreViewer.so-deployment-settings.json --output android-build --deployment bundled --gradle $(SIGN)
	cp android/android-build//build/outputs/apk/android-build-release-signed.apk INScoreViewer.apk

akey: ../rsrc/inscore.keystore
../rsrc/inscore.keystore :
	keytool -genkey -v -keystore ../inscore.keystore -alias grame-inscore -keyalg RSA -keysize 2048 -validity 10000

devandroid:
	adb get-serialno

# To install INScore on your android device add DEVICE variable with device serial number. It can be retreived with 'adb get-serialno'
installAndroid :
	adb -s $(DEVICE) install -r android/android-build/build/outputs/apk/android-build-release-signed.apk

#===============================================================
# building the library on linux
#===============================================================
linux : linux/Makefile.lib linux/Makefile.app INScoreLinux

linuxproj:
	[ -d linux ] || mkdir linux
	cd linux && $(QMAKE) ../library.pro && mv Makefile Makefile.lib 
	cd linux && $(QMAKE) ../viewer.pro && mv Makefile Makefile.app

linux/Makefile.lib: library.pro
	[ -d linux ] || mkdir linux
	cd linux && $(QMAKE) ../library.pro && mv Makefile Makefile.lib 

linux/Makefile.app: viewer.pro
	[ -d linux ] || mkdir linux
	cd linux && $(QMAKE) ../viewer.pro && mv Makefile Makefile.app

INScoreLinux:
	make -j 4 -C linux -f Makefile.lib
	make -j 4 -C linux -f Makefile.app

linuxclean:
	make -C linux -f Makefile.lib clean
	make -C linux -f Makefile.app clean


#===============================================================
# building the library on windows
#===============================================================
windows : $(WDEST)/INScore.vcxproj $(WDEST)/INScoreViewer.vcxproj INScoreWin $(WDEST)/release/$(GUIDOLIB)

winprojects : 
	[ -d $(WDEST) ] || mkdir $(WDEST)
	cd $(WDEST) && $(QMAKE) $(SPEC) ../library.pro
	cd $(WDEST) && $(QMAKE) $(SPEC) ../viewer.pro

INScoreWin:
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(WDEST)/INScore.vcxproj $(WINOPTS)"
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(WDEST)/INScoreViewer.vcxproj $(WINOPTS)"

$(WDEST)/INScore.vcxproj : library.pro
	make winprojects

$(WDEST)/INScoreViewer.vcxproj : viewer.pro
	make winprojects

$(WDEST)/release/$(GUIDOLIB): ../lib/GUIDOEngine/$(WDEST)/$(GUIDOLIB)
	cp ../lib/GUIDOEngine/$(WDEST)/$(GUIDOLIB) $(WDEST)/release

winclean:
	rm -f $(WDEST)/tmp

#===============================================================
clean :
	rm -rf macos $(WDEST) linux android ios

