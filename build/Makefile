#
# 
#

.PHONY : macos ios win32 win64 linux android installAndroid help mobileUI

QMAKE ?= qmake
TARGET := undefined

system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	TARGET = macos
	BUILDF ?= macos
	SPEC = -spec macx-xcode
	QMAKEIOS = qmake-ios
else
ifeq ($(system), MINGW)
	TARGET = windows
else
ifeq ($(system), Linux)
	TARGET = linux
	BUILDF ?= linux
endif
endif
endif

ifeq ($(TARGET), windows)
 WINARCH ?= $(shell ./qt-arch)
 MSVC ?= $(shell ./vs-path)
 WINOPTS := /maxcpucount:4 /p:Configuration=Release /p:Platform=$(WINARCH)
 SPEC ?= -spec win32-msvc2013
ifeq ($(WINARCH), x64)
	BUILDF ?= win64
	GUIDOLIB = GUIDOEngine64.dll
 else
	BUILDF ?= win32
	GUIDOLIB = GUIDOEngine.dll
 endif
endif

OUT  := INScore.framework
MOBILESCRIPTS := ../scripts/mobile


all :
	make $(TARGET)

undefined:
	$(error System is undefined, not target available)

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
	@echo "    DEVICE is optional when only one Android device is connected"
	@echo "  devandroid : to get the serial number of the connected device"

#===============================================================
# building INScore on Mac OS X
#===============================================================
macos : INScoreMac

xcodeproj: library.pro viewer.pro
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) $(SPEC) ../library.pro 
	touch $(BUILDF)/INScore.xcodeproj
	cd $(BUILDF) && $(QMAKE) $(SPEC) ../viewer.pro 
	touch $(BUILDF)/INScoreViewer.xcodeproj

INScoreMac : $(BUILDF)/INScore.xcodeproj $(BUILDF)/INScoreViewer.xcodeproj
	make -C ../lib/GuidoEngine/macosx
	make -C ../lib/GuidoAR/macosx
	make -C ../lib/libMusicXML/macosx
	xcodebuild -jobs 8 -project $(BUILDF)/INScore.xcodeproj -target INScore -configuration Release
	xcodebuild -jobs 8 -project $(BUILDF)/INScoreViewer.xcodeproj -target INScoreViewer -configuration Release
	make -C ../tools/IBundle/build

$(BUILDF)/INScore.xcodeproj : library.pro
	make xcodeproj

$(BUILDF)/INScoreViewer.xcodeproj : viewer.pro
	make xcodeproj

# specific target to create a symbolic link to macos/Release
# this link is required for macdeployqt
link:
	cd macos && ln -s Release lib

#===============================================================
# building INScore for iOS 
#===============================================================
ios : ios/INScore.xcodeproj ios/INScoreViewer.xcodeproj INScoreIos

xcodeprojios:
	@which $(QMAKEIOS) || (echo "### you must create an alias named '$(QMAKEIOS)' that point to qmake inside your qt/ios distribution and that is available from your PATH."; false;)
	[ -d ios ] || mkdir ios
	cd ios && $(QMAKEIOS) $(SPEC) ../library.pro 
	cd ios && $(QMAKEIOS) $(SPEC) ../viewer.pro 
	touch ios/INScore.xcodeproj
	touch ios/INScoreViewer.xcodeproj

INScoreIos : 
	cp -rf ../rsrc/ tmp-rsc
	make -C $(MOBILESCRIPTS)
	xcodebuild -jobs 8 -project ios/INScore.xcodeproj -target INScore -configuration Release
	xcodebuild -jobs 8 -project ios/INScoreViewer.xcodeproj -target INScoreViewer -configuration Release -allowProvisioningUpdates

ios/INScore.xcodeproj : library.pro
	make xcodeprojios

ios/INScoreViewer.xcodeproj : viewer.pro
	make xcodeprojios

#===============================================================
# building INScore for Android
#===============================================================
#SPECANDROID = -spec android-g++
SPECANDROID = -spec android-clang
SIGN=--sign ../../rsrc/inscore.keystore grame-inscore  --storepass grameinscore

android : android/Makefile INScoreAndroid

android/Makefile: library.pro INScore.pro
	@which qmake-android || (echo "### you must create an alias named 'qmake-android' that point to qmake inside your qt/android distribution and that is available from your PATH."; false;)
	[ -d android ] || mkdir android
	cd android && qmake-android $(SPECANDROID) ../INScore.pro

INScoreAndroid :
	cp -rf ../rsrc/ tmp-rsc
	make -C $(MOBILESCRIPTS)
	make -j 6 -C android -f Makefile
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
	adb -s $(shell adb get-serialno) install -r android/android-build/build/outputs/apk/android-build-release-signed.apk

uninstallAndroid :
	adb uninstall fr.grame.inscore


#===============================================================
# building the library on linux
#===============================================================
DESTDIR ?= /usr
SHARED  = $(DESTDIR)$(PREFIX)/share
INSTALLBIN := $(DESTDIR)$(PREFIX)/bin
INSTALLLIB := $(DESTDIR)$(PREFIX)/lib
RSRC := ../package/debian/usr/share

linux :  INScoreLinux

linuxproj:
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) ../library.pro && mv Makefile Makefile.lib 
	cd $(BUILDF) && $(QMAKE) ../viewer.pro && mv Makefile Makefile.app

$(BUILDF)/Makefile.lib: library.pro
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) ../library.pro && mv Makefile Makefile.lib 

$(BUILDF)/Makefile.app: viewer.pro
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) ../viewer.pro && mv Makefile Makefile.app

INScoreLinux: $(BUILDF)/Makefile.lib $(BUILDF)/Makefile.app
	make -j 4 -C $(BUILDF) -f Makefile.lib
	make -j 4 -C $(BUILDF) -f Makefile.app
	make -C ../tools/IBundle/build

linuxclean:
	make -C $(BUILDF) -f Makefile.lib clean
	make -C $(BUILDF) -f Makefile.app clean

install: 
	[ $(TARGET) = "linux" ] && make linuxinstall

linuxinstall:
	cp -d linux/libINScore.so* $(INSTALLLIB)
	install -m 755 linux/inscoreviewer  $(INSTALLBIN)
	install -m 755 ../tools/IBundle/IBundle $(INSTALLBIN)
	mkdir -p $(SHARED)/fonts/guido
	install -m 644 ../src/guido2.ttf $(SHARED)/fonts/guido/guido2.ttf 
	install -m 644 $(RSRC)/applications/inscore.desktop $(SHARED)/applications
	install -m 644 $(RSRC)/icons/hicolor/48x48/apps/inscore.png $(SHARED)/icons/hicolor/48x48/apps/inscore.png
	install -m 644 $(RSRC)/icons/hicolor/128x128/apps/inscore.png $(SHARED)/icons/hicolor/128x128/apps/inscore.png

	
#===============================================================
# building the library with mobileUI
#===============================================================
mobileUI: 
	cp -rf ../rsrc/ tmp-rsc
	make QMAKE="$(QMAKE) CONFIG+=mobile_ui" BUILDF="mobileUI"


#===============================================================
# building the library on windows
#===============================================================
WINXML := $(BUILDF)/release/Plugins/libmusicxml2.dll
windows : $(BUILDF)/INScore.vcxproj $(BUILDF)/INScoreViewer.vcxproj INScoreWin $(BUILDF)/release/$(GUIDOLIB) $(BUILDF)/release/guidoar.dll $(WINXML)

winprojects : 
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) $(SPEC) ../library.pro
	cd $(BUILDF) && $(QMAKE) $(SPEC) ../viewer.pro

INScoreWin:
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(BUILDF)/INScore.vcxproj $(WINOPTS)"
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(BUILDF)/INScoreViewer.vcxproj $(WINOPTS)"
	make -C ../tools/IBundle/build

$(BUILDF)/INScore.vcxproj : library.pro
	make winprojects

$(BUILDF)/INScoreViewer.vcxproj : viewer.pro
	make winprojects

$(BUILDF)/release/$(GUIDOLIB): ../lib/GUIDOEngine/$(BUILDF)/$(GUIDOLIB)
	cp -f ../lib/GUIDOEngine/$(BUILDF)/$(GUIDOLIB) $(BUILDF)/release

$(WINXML):  ../lib/libMusicXML/$(BUILDF)/libmusicxml2.dll
	[ -d $(BUILDF)/release/Plugins ] || mkdir $(BUILDF)/release/Plugins
	cp -f ../lib/libMusicXML/$(BUILDF)/libmusicxml2.dll $(WINXML)

$(BUILDF)/release/guidoar.dll: ../lib/GuidoAR/$(BUILDF)/guidoar.dll
	cp -f ../lib/GuidoAR/$(BUILDF)/guidoar.dll $(BUILDF)/release

winclean:
	rm -f $(BUILDF)/tmp

#===============================================================
clean :
	rm -rf $(BUILDF)

