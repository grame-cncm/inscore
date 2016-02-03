
.PHONY : macos ios win32 win64 linux android

APP := QtOSCSender

################################################
macos: macos/$(APP).xcodeproj
	cd macos &&  xcodebuild -jobs 8 -project $(APP).xcodeproj -target $(APP) -configuration Release
	cp -r macos/Release/$(APP).app .

macos/$(APP).xcodeproj : $(APP).pro
	[ -d macos ] || mkdir macos
	cd macos && qmake ..

################################################
ios: ios/$(APP).xcodeproj
	cd ios &&  xcodebuild -jobs 8 -project $(APP).xcodeproj -target $(APP) -configuration Release

ios/$(APP).xcodeproj : $(APP).pro
	[ -d ios ] || mkdir ios
	cd ios && qmake-ios ..

################################################
SIGN=--sign ../../../rsrc/inscore.keystore grame-inscore  --storepass grameinscore

android: android/Makefile
	make -j 8 -C android
	cd android && make INSTALL_ROOT=android-build install
	cd android && androiddeployqt --input android-lib$(APP).so-deployment-settings.json --output android-build --deployment bundled --gradle $(SIGN)
	cp android/android-build//build/outputs/apk/android-build-release-signed.apk $(APP).apk

android/Makefile : $(APP).pro
	[ -d android ] || mkdir android
	cd android && qmake-android -spec android-g++ ..

installAndroid :
	adb -s $(shell adb get-serialno) install -r android/android-build/build/outputs/apk/android-build-release-signed.apk
