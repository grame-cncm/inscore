#
# 
#

.PHONY : macos ios win32 win64 linux android installAndroid help mobileUI

QMAKE ?= qmake
MAKE  ?= make
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

INSCOREDIR  ?= inscoredir
DESTDIR ?= 

ifeq ($(system), Darwin)
	LIBPROJ = INScore.xcodeproj
	VIEWPROJ = INScoreViewer.xcodeproj
	SPEC    = -spec macx-xcode
	TARGET  = macos
	QMAKEIOS = qmake-ios
	PREFIX  ?= /usr/local
endif

ifeq ($(system), MINGW)
	TARGET = windows
	LIBPROJ = INScore.vcxproj
	VIEWPROJ = INScoreViewer.vcxproj
	PREFIX  ?= "C:/Program Files"
endif

ifeq ($(system), Linux)
	TARGET   = linux
	LIBPROJ  = Makefile.lib
	VIEWPROJ = Makefile.app
	PREFIX  ?= /usr/local
endif



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
# building inscore
#===============================================================
macos : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
	$(MAKE) -C ../lib/GuidoEngine/macosx
	$(MAKE) -C ../lib/GuidoAR/macosx
	xcodebuild -jobs 8 -project $(INSCOREDIR)/$(LIBPROJ)  -target INScore -configuration Release
	xcodebuild -jobs 8 -project $(INSCOREDIR)/$(VIEWPROJ) -target INScoreViewer -configuration Release
	$(MAKE) -C ../tools/IBundle/build

linux : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
	$(MAKE) -C $(INSCOREDIR) -f $(LIBPROJ)
	$(MAKE) -C $(INSCOREDIR) -f $(VIEWPROJ)
	$(MAKE) -C ../tools/IBundle/build


ios : QMAKE=qmake-ios
ios : INSCOREDIR=iosdir
ios : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
	@which $(QMAKE) || (echo "### you must create an alias named '$(QMAKE)' that point to qmake inside your qt/ios distribution and that is available from your PATH."; false;)
	cp -rf ../rsrc/ tmp-rsc
	make -C $(MOBILESCRIPTS)
	xcodebuild -jobs 8 -project $(INSCOREDIR)/$(LIBPROJ)  -target INScore -configuration Release
	xcodebuild -jobs 8 -project $(INSCOREDIR)/$(VIEWPROJ) -target INScoreViewer -configuration Release -allowProvisioningUpdates

windows : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(BUILDF)/INScore.vcxproj $(WINOPTS)"
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(BUILDF)/INScoreViewer.vcxproj $(WINOPTS)"
	$(MAKE) -C ../tools/IBundle/build
	$(MAKE) windlls


#===============================================================
# building projects
#===============================================================
$(INSCOREDIR)/$(LIBPROJ) : $(INSCOREDIR) library.pro
	cd $(INSCOREDIR) && $(QMAKE) $(SPEC) ../library.pro -o $(LIBPROJ)

$(INSCOREDIR)/$(VIEWPROJ) : $(INSCOREDIR) viewer.pro
	cd $(INSCOREDIR) && $(QMAKE) $(SPEC) ../viewer.pro -o $(VIEWPROJ)

$(INSCOREDIR):
	mkdir $(INSCOREDIR)

#===============================================================
# windows dll special target
#===============================================================
windlls: bin/GUIDOEngine64.dll bin/guidoar.dll in/Plugins/libmusicxml2.dll

bin/GUIDOEngine64.dll: ../lib/GUIDOEngine/win64/GUIDOEngine64.dll
	cp -f ../lib/GUIDOEngine/win64/GUIDOEngine64.dll bin

bin/Plugins/libmusicxml2.dll:  ../lib/libMusicXML/win64/libmusicxml2.dll
	[ -d bin/Plugins ] || mkdir bin/Plugins
	cp -f ../lib/libMusicXML/win64/libmusicxml2.dll bin/Plugins

bin/guidoar.dll: ../lib/GuidoAR/win64/guidoar.dll
	cp -f ../lib/GuidoAR/win64/guidoar.dll bin


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
SHARED  = $(DESTDIR)$(PREFIX)/share
INSTALLBIN := $(DESTDIR)$(PREFIX)/bin
INSTALLLIB := $(DESTDIR)$(PREFIX)/lib
RSRC := ../package/debian/usr/share

install:
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
	$(MAKE) QMAKE="$(QMAKE) CONFIG+=mobile_ui" INSCOREDIR="mobileUI"


#===============================================================
clean :
	rm -rf $(INSCOREDIR)

