#########################################################
#              INScore project Makefile
#########################################################

.PHONY : modules

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

ifeq ($(system), Darwin)
	MAKEFILE = Makefile
endif

ifeq ($(system), MINGW)
	MAKEFILE = Makefile
endif

ifeq ($(system), Linux)
	MAKEFILE = Makefile
endif
GENERATOR ?= 

all :
	$(MAKE) modules
	$(MAKE) inscore

test:
	echo PKGDIR $(PKGDIR)

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
ios: 
	$(MAKE) inscore INSCOREDIR=$(IOSDIR) CMAKEOPTS='-DIOS=on'

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
	cp -af ../modules/guidolib/build/lib/*GUIDOEngine.[^f]* lib
	cp -af ../modules/libmusicxml/build/lib/*musicxml2.[^f]* lib

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
# installation and packaging
#===============================================================
install:
	$(CMAKE) --build $(INSCOREDIR) --config Release --target install

package:
	$(MAKE) cmake CMAKEOPTS="-DPREFIX=$(PKGDIR)"
	$(CMAKE) --build $(INSCOREDIR) --config Release --target install
	hdiutil create INScore-$(VERSION).dmg -fs HFS+ -srcfolder $(PKGDIR) -format UDBZ -ov
	@echo "Warning: install location has moved to $(PKGDIR)"


# ios :
# 	make _ios QMAKE=qmake-ios INSCOREDIR=iosdir
# 
# _ios : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
# 	@which $(QMAKE) > /dev/null || (echo "### you must create an alias named '$(QMAKE)' that point to qmake inside your qt/ios distribution and that is available from your PATH."; false;)
# 	cp -rf ../rsrc/ tmp-rsc
# 	make -C $(MOBILESCRIPTS)
# 	xcodebuild -jobs $(J) -project $(INSCOREDIR)/$(LIBPROJ)  -target INScore -configuration Release
# 	xcodebuild -jobs $(J) -project $(INSCOREDIR)/$(VIEWPROJ) -target INScoreViewer -configuration Release -allowProvisioningUpdates

# windows : $(INSCOREDIR)/$(LIBPROJ) $(INSCOREDIR)/$(VIEWPROJ)
# 	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(INSCOREDIR)/INScore.vcxproj $(WINOPTS)"
# 	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(INSCOREDIR)/INScoreViewer.vcxproj $(WINOPTS)"
#	$(MAKE) -C ../tools/IBundle/build


#===============================================================
# building INScore for Android
#===============================================================
SIGN=--sign ../../rsrc/inscore.keystore grame-inscore  --storepass grameinscore
ANDROID_API ?= 26
ANDROID_ARCH ?= armeabi-v7a
 
android : 
	make _android INSCOREDIR?=$(ANDROIDDIR) QMAKE=qmake-android

_android : $(ANDROIDDIR) $(ANDROIDDIR)/Makefile
	cp -rf ../rsrc/ tmp-rsc
	$(MAKE) -C $(MOBILESCRIPTS)
	$(MAKE) -C $(INSCOREDIR)
	[ -d $(INSCOREDIR)/android-build ] || mkdir $(INSCOREDIR)/android-build
	$(MAKE) -C $(INSCOREDIR) INSTALL_ROOT=android-build install
	cd $(INSCOREDIR) && androiddeployqt --android-platform android-$(ANDROID_API) --release --input android-libINScoreViewer.so-deployment-settings.json --output android-build --deployment bundled --gradle $(SIGN)
	cp $(INSCOREDIR)/android-build/build/outputs/apk/release/android-build-release-signed.apk $(INSCOREDIR)/../bin/INScoreViewer.apk

# $(ANDROIDDIR) :
# 	mkdir $(ANDROIDDIR)

$(ANDROIDDIR)/Makefile: library.pro viewer.pro INScore.pro
	@which qmake-android > /dev/null  || (echo "### you must create an alias named 'qmake-android' that point to qmake inside your qt/android distribution and that is available from your PATH."; false;)
	cd $(ANDROIDDIR) && $(QMAKE) -spec android-clang ../INScore.pro

akey: ../rsrc/inscore.keystore
../rsrc/inscore.keystore :
	keytool -genkey -v -keystore ../inscore.keystore -alias grame-inscore -keyalg RSA -keysize 2048 -validity 10000

devandroid:
	adb get-serialno

# To install INScore on your android device add DEVICE variable with device serial number. It can be retreived with 'adb get-serialno'
installAndroid :
	adb -s $(shell adb get-serialno) install -r $(shell find $(INSCOREDIR) -name android-build-release-signed.apk) 

uninstallAndroid :
	adb uninstall fr.grame.inscore
	
BT350:
	make android ANDROIDDIR=androidx86-BT350 

installBT350:
	make installAndroid ANDROIDDIR=androidx86-BT350

#===============================================================
# install target
#===============================================================
# install:
# 	make -C ../package
# 
# uninstall:
# 	make -C ../package uninstall

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
	
