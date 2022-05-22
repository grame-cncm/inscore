#########################################################
#              INScore project Makefile
#########################################################

.PHONY : modules android QT6

QMAKE ?= qmake
CMAKE ?= cmake
MAKE  ?= make
RANGE ?= 

INSCOREDIR  ?= inscoredir
IOSDIR  	?= iosdir
WASMDIR  	?= wasmdir
MODELDIR  	?= modeldir
ANDROIDDIR  ?= androiddir

system	:= $(shell uname -s)
# normalizes MINGW versions
system  := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
VERSION := $(shell cat ../version.txt)

MOBILESCRIPTS  := ../scripts/mobile
MODULESCONFIGS := $(wildcard modules/*.cmake)
PKGDIR := $(shell pwd)/INScore-$(VERSION)

MAKEFILE  ?= Makefile		# used to check the dependency to CMakeList
GENERATOR ?= 

all :
	$(MAKE) modules
	$(MAKE) inscore

test: PATH := /Users/Shared/Qt/5.15.2/5.15.2/ios/bin:$(PATH)
test:
	qmake --version

help :
	@echo "========== INScore project Makefile =========="
	@echo "Available targets are : "
	@echo "  all (default) : call the 'modules' and the 'inscore' targets"
	@echo "  inscore       : build inscore library, inscoreviewer and ibundle"
	@echo "  modules       : recursively update and build submodules"
	@echo "  wasm          : build the inscore wasm library"
	@echo "  model         : build the inscore core model library"
	@echo "  ibundle       : build ibundle (with Qt view only)"
	@echo "  ios           : build for iOS"
	@echo "  android       : build for android"
	@echo "  install       : install the package"
	@echo "  package       : build the inscore package (MacOS only)"
	@echo "  installAndroid DEVICE=XXX : to install application on Android device"
	@echo "       with XXX the device serial number (can be retrieved using 'make devandroid')"
	@echo "       DEVICE is optional when only one Android device is connected"
	@echo "  devandroid : to get the serial number of the connected device"
	@echo "Project management: "
	@echo "  cmake    : regenerates the project"
	@echo "  log      : generates the git log with optionnal revisions range"
	@echo "             the range can be specified using the RANGE variable"
	@echo "             e.g make log RANGE=commitref1...commitref2"
	@echo
	@echo "Options:"
	@echo "  INSCOREDIR   : build folder for the 'inscore' target (currently $(INSCOREDIR))"
	@echo "  WASMDIR      : build folder for the 'wasm' target (currently $(WASMDIR))"
	@echo "  MODELDIR     : build folder for the 'model' target (currently $(MODELDIR))"
	@echo "  IOSDIR       : build folder for the 'ios' target (currently $(IOSDIR))"
	@echo "  GENERATOR    : a cmake generator (e.g. '-G Xcode' on MacOS)"
	@echo "  PREFIX       : the install prefix (currently $(PREFIX))"
	@echo "  ANDROIDDIR   : build folder for the 'android' target (currently $(ANDROIDDIR))"
	@echo "  ANDROID_API : define the android API to use (currently $(ANDROID_API))"
	@echo "  ANDROID_ARCH: define the android architecture (currently $(ANDROID_ARCH))"

#===============================================================
# building inscore and inscoreviewer
#===============================================================
inscore: $(INSCOREDIR) $(INSCOREDIR)/$(MAKEFILE)
	$(CMAKE) --build $(INSCOREDIR) --config Release

$(INSCOREDIR):
	mkdir $(INSCOREDIR)

$(INSCOREDIR)/$(MAKEFILE) : CMakeLists.txt $(MODULESCONFIGS)
	cd $(INSCOREDIR) && $(CMAKE) .. $(CMAKEOPTS) $(GENERATOR)

QT6: 
	$(MAKE) inscore CMAKEOPTS='-DQT6=on'


#===============================================================
# building inscore wasm library
#===============================================================
wasm: $(WASMDIR) $(WASMDIR)/Makefile
	$(MAKE) -C $(WASMDIR) wasm

$(WASMDIR):
	mkdir $(WASMDIR)

$(WASMDIR)/Makefile : CMakeLists.txt modules/WASMConfig.cmake
	cd $(WASMDIR) && $(CMAKE) .. -DWASM=on

#===============================================================
# building for iOS
#===============================================================
# ios: 
# 	$(MAKE) inscore INSCOREDIR=$(IOSDIR) CMAKEOPTS='-DIOS=on -DQT6=on' GENERATOR='-G Xcode'

GUIDOMODULE ?= ../modules/guidolib/build
ios : lib/libGUIDOEngine.a
	cp -rf ../rsrc/ tmp-rsc
	make _ios QMAKE=qmake-ios INSCOREDIR=iosdir

lib/libGUIDOEngine.a : $(GUIDOMODULE)/lib/libGUIDOEngine.a
	cp $< $@

$(GUIDOMODULE)/lib/libGUIDOEngine.a:
	$(MAKE) -C $(GUIDOMODULE) ios

_ios : $(INSCOREDIR) $(INSCOREDIR)/INScore.xcodeproj $(INSCOREDIR)/INScoreViewer.xcodeproj
	@which $(QMAKE) > /dev/null || (echo "### you must create an alias named '$(QMAKE)' that point to qmake inside your qt/ios distribution and that is available from your PATH."; false;)
	$(MAKE) -C $(MOBILESCRIPTS)
	xcodebuild -project $(INSCOREDIR)/INScore.xcodeproj  -configuration Release
	xcodebuild -project $(INSCOREDIR)/INScoreViewer.xcodeproj -configuration Release -allowProvisioningUpdates

$(INSCOREDIR)/INScore.xcodeproj: library.pro
	cd $(INSCOREDIR) && $(QMAKE) ../library.pro

$(INSCOREDIR)/INScoreViewer.xcodeproj: viewer.pro
	cd $(INSCOREDIR) && $(QMAKE) ../viewer.pro


#===============================================================
# building inscore model library
#===============================================================
model: $(INSCOREDIR) $(INSCOREDIR)/$(MAKEFILE)
	$(MAKE) inscore INSCOREDIR=$(MODELDIR) CMAKEOPTS='-DMODEL=on'

#===============================================================
# building ibundle
#===============================================================
ibundle : $(INSCOREDIR) $(INSCOREDIR)/$(MAKEFILE)
	$(CMAKE) --build $(INSCOREDIR) --config Release --target IBundle

#===============================================================
# utilities
#===============================================================
log:
	git log --format="%h - %Cblue%s%Creset - %cn %cd"  $(RANGE)

cmake: $(INSCOREDIR)
	cd $(INSCOREDIR) && $(CMAKE) .. $(CMAKEOPTS) $(GENERATOR)

#===============================================================
# submodules management
#===============================================================
modules:
	$(MAKE) -C ../modules
	[ -d lib ] || mkdir lib
	cp -af ../modules/guidolib/build/lib/*GUIDOEngine*[._][^f]* lib
	cp -af ../modules/libmusicxml/build/lib/*musicxml*[._][^f]* lib

guido:
	$(MAKE) -C ../modules guido
	[ -d lib ] || mkdir lib
	cp -af ../modules/guidolib/build/lib/*GUIDOEngine[._][^f]* lib

install_modules:
	$(MAKE) -C ../modules install

modules_ios:
	git submodule update --init --recursive
	$(MAKE) -C ../modules/guidolib/build ios
	$(MAKE) -C ../modules/libmusicxml/build ios

modules_android:
	git submodule update --init --recursive
	$(MAKE) -C ../modules/guidolib/build android
	$(MAKE) -C ../modules/libmusicxml/build android


#===============================================================
# installation
#===============================================================
install:
	$(CMAKE) --build $(INSCOREDIR) --config Release --target install

#===============================================================
# packaging (Mac OS only)
#===============================================================
package:
	$(MAKE) cmake CMAKEOPTS="-DPREFIX=$(PKGDIR)"
	$(CMAKE) --build $(INSCOREDIR) --config Release --target install
	$(MAKE) sign
	hdiutil create INScore-$(VERSION).dmg -fs HFS+ -srcfolder $(PKGDIR) -format UDBZ -ov
	@echo "Warning: install location has moved to $(PKGDIR)"

# the certificate below must be installed in the keychain with the associated private key
CERT='Apple Distribution: GRAME (XN9RP996NW)'
sign:
	-codesign -s $(CERT) $(PKGDIR)/IBundle
	-codesign -s $(CERT) --deep $(PKGDIR)/INScoreViewer.app



# ios :
# 	make _ios QMAKE=qmake-ios INSCOREDIR=iosdir
# 
# _ios : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
# 	@which $(QMAKE) > /dev/null || (echo "### you must create an alias named '$(QMAKE)' that point to qmake inside your qt/ios distribution and that is available from your PATH."; false;)
# 	cp -rf ../rsrc/ tmp-rsc
# 	make -C $(MOBILESCRIPTS)
# 	xcodebuild -jobs $(J) -project $(INSCOREDIR)/$(LIBPROJ)  -target INScore -configuration Release
# 	xcodebuild -jobs $(J) -project $(INSCOREDIR)/$(VIEWPROJ) -target INScoreViewer -configuration Release -allowProvisioningUpdates


#===============================================================
# building INScore for Android
#===============================================================
SIGN=--sign ../../rsrc/inscore.keystore grame-inscore  --storepass grameinscore
ANDROID_API ?= 29
ANDROID_ARCH ?= armeabi-v7a
#ANDROIDDEPLOYQT ?= /Users/Shared/Qt6/6.2.0/macos/bin/androiddeployqt
ANDROIDDEPLOYQT ?= androiddeployqt
ANDROIDSETTINGS := android-INScoreViewer-deployment-settings.json
ANDROIDBUILDDIR := $(INSCOREDIR)/android-build
ANDROIDGUIDOLIB := ../modules/guidolib/build/lib
ANDROIDQTLIBS   := $(shell qmake-android --version | grep Qt | sed -e 's/^..*in //')

android : 
	$(MAKE) _android INSCOREDIR?=$(ANDROIDDIR) QMAKE=qmake-android
#	$(MAKE) -f Makefile.android

_android : $(ANDROIDBUILDDIR) $(ANDROIDDIR)/Makefile
	cp -rf ../rsrc/ tmp-rsc
	$(MAKE) -C $(MOBILESCRIPTS)
	$(MAKE) -C $(INSCOREDIR)
	[ -d $(ANDROIDBUILDDIR) ] || mkdir $(ANDROIDBUILDDIR)
	$(MAKE) -C $(INSCOREDIR) INSTALL_ROOT=android-build install
	$(QMAKE) -install qinstall lib/libGUIDOEngine_armeabi-v7a.so $(ANDROIDBUILDDIR)/libs/armeabi-v7a/libGUIDOEngine.so
	$(QMAKE) -install qinstall lib/libGUIDOEngine_arm64-v8a.so $(ANDROIDBUILDDIR)/libs/arm64-v8a/libGUIDOEngine.so
	$(QMAKE) -install qinstall lib/libGUIDOEngine_x86_64.so $(ANDROIDBUILDDIR)/libs/x86_64/libGUIDOEngine.so
	$(QMAKE) -install qinstall lib/libGUIDOEngine_x86.so $(ANDROIDBUILDDIR)/libs/x86/libGUIDOEngine.so
	cd $(INSCOREDIR) && $(ANDROIDDEPLOYQT) $(VERBOSE) --release --input $(ANDROIDSETTINGS) --output android-build  --android-platform android-$(ANDROID_API) --deployment bundled --gradle $(SIGN)
	cp $(ANDROIDBUILDDIR)/build/outputs/apk/release/android-build-release-signed.apk bin/INScoreViewer-$(VERSION).apk

$(ANDROIDBUILDDIR) :
	mkdir -p $(ANDROIDBUILDDIR)

$(ANDROIDDIR)/Makefile: library.pro viewer.pro INScore.pro
	@which qmake-android > /dev/null  || (echo "### you must create an alias named 'qmake-android' that point to qmake inside your qt/android distribution and that is available from your PATH."; false;)
	cd $(ANDROIDDIR) && $(QMAKE) -spec android-clang ANDROID_ABI=armeabi-v7a ../INScore.pro

akey: ../rsrc/inscore.keystore
../rsrc/inscore.keystore :
	keytool -genkey -v -keystore ../inscore.keystore -alias grame-inscore -keyalg RSA -keysize 2048 -validity 10000

devandroid:
	adb get-serialno

# To install INScore on your android device add DEVICE variable with device serial number. It can be retreived with 'adb get-serialno'
installAndroid :
	adb -s $(shell adb get-serialno) install -r $(shell find $(ANDROIDDIR) -name android-build-release-signed.apk) 

uninstallAndroid :
	adb uninstall fr.grame.inscore
	
BT350:
	$(MAKE) android ANDROIDDIR=androidx86-BT350 

installBT350:
	$(MAKE) installAndroid ANDROIDDIR=androidx86-BT350


#===============================================================
# building the library with mobileUI
#===============================================================
mobileUI: 
	cp -rf ../rsrc/ tmp-rsc
	$(MAKE) QMAKE="$(QMAKE) CONFIG+=mobile_ui" INSCOREDIR="mobileUI"

#===============================================================
# the link below is required by macdeployqt to correctly find the inscore framework
link :
	[ -h lib ] || ln -s bin lib
	
#===============================================================
clean :
	rm -rf $(INSCOREDIR)
	
