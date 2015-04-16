#
# 
#

.PHONY : macos ios win32 win64 linux

system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET = macos
	SPEC = -spec macx-xcode
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET = win32
	SPEC = -spec win32-msvc2010
else
	TARGET = linux
endif
endif


OUT  := INScore.framework
WIN32VS := "Visual Studio 10"
WIN64VS := "Visual Studio 10 Win64"
MSVC := C:\Program Files (x86)\Microsoft Visual Studio 10.0

all :
	make $(TARGET)

#===============================================================
# building INScore on Mac OS X
#===============================================================
macos : macos/INScore.xcodeproj macos/INScoreViewer.xcodeproj INScoreMac

xcodeproj:
	[ -d macos ] || mkdir macos
	cd macos && qmake $(SPEC) ../library.pro 
	cd macos && qmake $(SPEC) ../viewer.pro 

INScoreMac : 
	xcodebuild -jobs 8 -project macos/INScore.xcodeproj -target INScore -configuration Release
	xcodebuild -jobs 8 -project macos/INScoreViewer.xcodeproj -target INScoreViewer -configuration Release

macos/INScore.xcodeproj : library.pro
	[ -d macos ] || mkdir macos
	cd macos && qmake $(SPEC) ../library.pro 

macos/INScoreViewer.xcodeproj : viewer.pro
	[ -d macos ] || mkdir macos
	cd macos && qmake $(SPEC) ../viewer.pro 

#===============================================================
# building the library on linux
#===============================================================
linux : linux/Makefile.lib linux/Makefile.app INScoreLinux

linuxproj:
	[ -d linux ] || mkdir linux
	cd linux && qmake ../library.pro && mv Makefile Makefile.lib 
	cd linux && qmake ../viewer.pro && mv Makefile Makefile.app

linux/Makefile.lib: library.pro
	[ -d linux ] || mkdir linux
	cd linux && qmake ../library.pro && mv Makefile Makefile.lib 

linux/Makefile.app: viewer.pro
	[ -d linux ] || mkdir linux
	cd linux && qmake ../viewer.pro && mv Makefile Makefile.app

INScoreLinux:
	make -j 4 -C linux -f Makefile.lib
	make -j 4 -C linux -f Makefile.app

linuxclean:
	make -C linux -f Makefile.lib clean
	make -C linux -f Makefile.app clean


#===============================================================
# building the library on windows
#===============================================================
win32 : win32/INScore.vcxproj win32/INScoreViewer.vcxproj INScoreWin32 win32/release/GUIDOEngine.dll

win32projects : 
	[ -d win32 ] || mkdir win32
	cd win32 && qmake $(SPEC) ../library.pro
	cd win32 && qmake $(SPEC) ../viewer.pro

INScoreWin32:
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win32/INScore.vcxproj /maxcpucount:4 /p:Configuration=Release"
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win32/INScoreViewer.vcxproj /maxcpucount:4 /p:Configuration=Release"

win32/INScore.vcxproj : library.pro
	make win32projects

win32/INScoreViewer.vcxproj : viewer.pro
	make win32projects

win32/release/GUIDOEngine.dll: ../lib/GUIDOEngine/win32/GUIDOEngine.dll
	cp ../lib/GUIDOEngine/win32/GUIDOEngine.dll win32/release

win32clean:
	rm -f win32/tmp

#===============================================================
clean :
	rm -rf macos win32 linux

