
system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET ?= macos
	QMAKEIOS ?= $(HOME)/Qt5.4.0/5.4/ios/bin/qmake
	DEST := ..
	OUT = $(DEST)/$(PROJECT)$(APP)
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET = windows
	QMAKEWIN ?= $(shell ../../../qt-win32)
	MSVC 	 ?= $(shell ../../../vs-win32)
	DEST := ../..
	OUT = $(DEST)/$(PROJECT).exe
else

endif
endif

QMAKE    ?= qmake
ROOT    := ..
PROJECT := QtOSCController

.PHONY : macos ios win32

all:
	make $(TARGET)

mac:
	make macos
	make ios


windows: win32/$(PROJECT).vcxproj  $(PROJECT).exe 
	@echo ===================================
	@echo Build $(PROJECT) for win32
	@echo ===================================


macos: macos/$(PROJECT).xcodeproj  $(PROJECT) 
	@echo ===================================
	@echo Build $(PROJECT) for mac os done
	@echo ===================================

ios: ios/$(PROJECT).xcodeproj  ios/$(PROJECT) 
	@echo ===================================
	@echo Build $(PROJECT) for ios done
	@echo ===================================


###################
# MacOS part
###################
macos/$(PROJECT).xcodeproj : $(ROOT)/$(PROJECT).pro 
	[ -d macos ] || mkdir macos
	cd macos && $(QMAKE) $(SPEC) $(ROOT)/..

$(PROJECT):
	xcodebuild -jobs 8 -project  macos/$(PROJECT).xcodeproj -target $(PROJECT) -configuration Release
	cp -R macos/Release//$(PROJECT).app $(DEST)


###################
# iOS part
###################
ios/$(PROJECT).xcodeproj : $(ROOT)/$(PROJECT).pro 
	[ -d ios ] || mkdir ios
	cd ios && $(QMAKEIOS) $(SPEC) $(ROOT)/..

ios/$(PROJECT):
	xcodebuild -jobs 8 -project  ios/$(PROJECT).xcodeproj -target $(PROJECT) -configuration Release

###################
# windows part
###################
win32/$(PROJECT).vcxproj : $(ROOT)/$(PROJECT).pro 
	[ -d win32 ] || mkdir win32
	cd win32 && $(QMAKEWIN) $(SPEC) $(ROOT)/..

$(PROJECT).exe:
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win32/$(PROJECT).vcxproj /maxcpucount:4 /p:Configuration=Release"
	cp -R win32/Release/$(PROJECT).exe $(DEST)

clean:
	rm -rf $(OUT) macos win32 ios
