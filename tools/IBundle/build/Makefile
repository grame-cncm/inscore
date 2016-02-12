.PHONY : macos win32 win64 linux

QMAKE ?= qmake

system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET = macos
	BUILDF ?= macos
	SPEC = -spec macx-xcode
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET = windows
else
ifeq ($(system), MINGW32_NT-6.2)
	TARGET = windows
else
	TARGET = linux
	BUILDF ?= linux
endif
endif
endif

ifeq ($(TARGET), windows)
 WINARCH ?= $(shell ../../../build/qt-arch)
 MSVC ?= $(shell  ../../../build/vs-path)
 WINOPTS := /maxcpucount:4 /p:Configuration=Release /p:Platform=$(WINARCH)
 SPEC ?= -spec win32-msvc2013
ifeq ($(WINARCH), x64)
	BUILDF ?= win64
 else
	BUILDF ?= win32
 endif
endif

ibundle:
	make $(TARGET)

#===============================================================
# building IBundle on Mac OS X
#===============================================================
macos : $(BUILDF)/IBundle.xcodeproj
	cd $(BUILDF) && xcodebuild -jobs 8 -project IBundle.xcodeproj -target IBundle -configuration Release
	cp -f $(BUILDF)/Release/IBundle ..

$(BUILDF)/IBundle.xcodeproj : IBundle.pro
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && qmake ../IBundle.pro
	
install :
	cp -f IBundle $(HOME)/bin/IBundle

#===============================================================
# building IBundle on Windows
#===============================================================
windows : $(BUILDF)/IBundle.vcxproj
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(BUILDF)/IBundle.vcxproj $(WINOPTS)"
	cp -f $(BUILDF)/Release/IBundle.exe ..

$(BUILDF)/IBundle.vcxproj : IBundle.pro
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) $(SPEC) ../IBundle.pro

#===============================================================
# building IBundle on linux
#===============================================================
linux : $(BUILDF)/Makefile IBundle

$(BUILDF)/Makefile: IBundle.pro
	[ -d $(BUILDF) ] || mkdir $(BUILDF)
	cd $(BUILDF) && $(QMAKE) ../IBundle.pro

IBundle:
	make -j 4 -C $(BUILDF)
	cp linux/IBundle ..

