#
# 
#

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
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))

MOBILESCRIPTS := ../scripts/mobile

ifeq ($(system), Darwin)
	GENERATOR ?= -G Xcode
	MAKEFILE = INScore.xcodeproj
endif

ifeq ($(system), MINGW)
	GENERATOR ?= ""
	MAKEFILE = Makefile
endif

ifeq ($(system), Linux)
	GENERATOR ?= ""
	MAKEFILE = Makefile
endif

all :
	$(MAKE) modules
	$(MAKE) inscore

test:
	echo GENERATOR $(GENERATOR)

help :
	@echo "========== INScore project Makefile =========="
	@echo "Available targets are : "
	@echo "  all (default) : call the 'modules' and the 'inscore' targets"
	@echo "  inscore       : build inscore library and inscoreviewer"
	@echo "  modules       : recursively update and build submodules"
	@echo "  wasm          : build the inscore wasm library"
	@echo "  model         : build the inscore core model library"
	@echo "  ios           : build for iOS"
	@echo "  android       : build for android"
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

$(INSCOREDIR)/$(MAKEFILE) : CMakelists.txt
	cd $(INSCOREDIR) && $(CMAKE) .. $(CMAKEOPTS) $(GENERATOR)

#===============================================================
# building inscore wasm library
#===============================================================
wasm: $(WASMDIR) $(WASMDIR)/Makefile
	$(MAKE) -C $(WASMDIR) wasm

$(WASMDIR):
	mkdir $(WASMDIR)

$(WASMDIR)/Makefile : CMakelists.txt modules/WASMConfig.cmake
	cd $(WASMDIR) && $(CMAKE) .. -DWASM=on

#===============================================================
# building for iOS
#===============================================================
ios: 
	$(MAKE) inscore INSCOREDIR=$(IOSDIR) CMAKEOPTS='-DIOS=on'

#===============================================================
# building inscore model library
#===============================================================
model: 
	$(MAKE) inscore INSCOREDIR=$(MODELDIR) CMAKEOPTS='-DMODEL=on'


#===============================================================
# utilities
#===============================================================
log:
	git log --format="%h - %Cblue%s%Creset - %cn %cd"  $(RANGE)

cmake: $(INSCOREDIR)
	cd $(INSCOREDIR) && $(CMAKE) .. $(GENERATOR)


#===============================================================
# submodules management
#===============================================================
modules:
	git submodule update --init --recursive
	$(MAKE) -C ../modules/guidolib/build lib
	$(MAKE) -C ../modules/libmusicxml/build CMAKEOPT="-DLILY=off -DFMWK=off"

install_modules:
	sudo $(MAKE) -C ../modules/guidolib/build install
	sudo $(MAKE) -C ../modules/libmusicxml/build install

modules_ios:
	git submodule update --init --recursive
	$(MAKE) -C ../modules/guidolib/build ios
	$(MAKE) -C ../modules/libmusicxml/build ios

modules_android:
	git submodule update --init --recursive
	$(MAKE) -C ../modules/guidolib/build android
	$(MAKE) -C ../modules/libmusicxml/build android

#===============================================================
# building inscore library and application
#===============================================================

ibundle : 
	$(MAKE) -C ../tools/IBundle/build
	cp ../tools/IBundle/IBundle bin


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
# building projects
#===============================================================
# $(INSCOREDIR)/$(LIBPROJ) : $(INSCOREDIR) library.pro
# 	cd $(INSCOREDIR) && $(QMAKE) $(SPEC) ../library.pro -o $(LIBPROJ)
# 
# $(INSCOREDIR)/$(VIEWPROJ) : $(INSCOREDIR) viewer.pro
# 	cd $(INSCOREDIR) && $(QMAKE) $(SPEC) ../viewer.pro -o $(VIEWPROJ)
# 
# voidview :
# 	$(MAKE) qmake CONFIG="CONFIG+=NOVIEW" INSCOREDIR=noview
# 
# qmake : $(INSCOREDIR)
# 	cd $(INSCOREDIR) && $(QMAKE) $(SPEC) $(CONFIG) ../library.pro -o $(LIBPROJ)
# 	cd $(INSCOREDIR) && $(QMAKE) $(SPEC) $(CONFIG) ../viewer.pro  -o $(VIEWPROJ)


#===============================================================
# building INScore for Android
#===============================================================
# SIGN=--sign ../../rsrc/inscore.keystore grame-inscore  --storepass grameinscore
# ANDROID_API ?= 22
# ANDROID_ARCH ?= armeabi-v7a
# 
# android : 
# 	make _android INSCOREDIR=androiddir QMAKE=qmake-android
# 
# _android : $(INSCOREDIR) $(INSCOREDIR)/Makefile
# 	cp -rf ../rsrc/ tmp-rsc
# 	$(MAKE) -C $(MOBILESCRIPTS)
# 	$(MAKE) -C $(INSCOREDIR)
# 	[ -d $(INSCOREDIR)/android-build ] || mkdir $(INSCOREDIR)/android-build
# 	$(MAKE) -C $(INSCOREDIR) INSTALL_ROOT=android-build install
# 	cd $(INSCOREDIR) && androiddeployqt --android-platform android-$(ANDROID_API) --release --input android-libINScoreViewer.so-deployment-settings.json --output android-build --deployment bundled --gradle $(SIGN)
# 	cp $(INSCOREDIR)/android-build/build/outputs/apk/release/android-build-release-signed.apk $(INSCOREDIR)/../bin/INScoreViewer.apk
# 
# $(INSCOREDIR)/Makefile: library.pro viewer.pro INScore.pro
# 	@which qmake-android > /dev/null  || (echo "### you must create an alias named 'qmake-android' that point to qmake inside your qt/android distribution and that is available from your PATH."; false;)
# 	[ -d $(INSCOREDIR) ] || mkdir $(INSCOREDIR)
# 	cd $(INSCOREDIR) && $(QMAKE) -spec android-clang ../INScore.pro
# 
# akey: ../rsrc/inscore.keystore
# ../rsrc/inscore.keystore :
# 	keytool -genkey -v -keystore ../inscore.keystore -alias grame-inscore -keyalg RSA -keysize 2048 -validity 10000

devandroid:
	adb get-serialno

# To install INScore on your android device add DEVICE variable with device serial number. It can be retreived with 'adb get-serialno'
installAndroid :
	adb -s $(shell adb get-serialno) install -r $(shell find $(INSCOREDIR) -name android-build-release-signed.apk) 

uninstallAndroid :
	adb uninstall fr.grame.inscore
	
BT350:
	make android INSCOREDIR=androidx86-BT350 

installBT350:
	make installAndroid INSCOREDIR=androidx86-BT350

#===============================================================
# install target
#===============================================================
install:
	make -C ../package

uninstall:
	make -C ../package uninstall

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
	
