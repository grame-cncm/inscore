#
# 
#

.PHONY : macos ios win32 win64 linux

system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET = macos
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET = win32
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
	cd macos && qmake -spec macx-xcode ../library.pro 
	cd macos && qmake -spec macx-xcode ../viewer.pro 

INScoreMac : 
	xcodebuild -jobs 8 -project macos/INScore.xcodeproj -target INScore -configuration Release
	xcodebuild -jobs 8 -project macos/INScoreViewer.xcodeproj -target INScoreViewer -configuration Release

macos/INScore.xcodeproj : library.pro
	[ -d macos ] || mkdir macos
	cd macos && qmake -spec macx-xcode ../library.pro 

macos/INScoreViewer.xcodeproj : viewer.pro
	[ -d macos ] || mkdir macos
	cd macos && qmake -spec macx-xcode ../viewer.pro 

#===============================================================
# building the library on windows
#===============================================================
windows :
	make win32

win32 : win32/INScore.sln INScoreWin32 

INScoreWin32:
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win32/INScore.sln /maxcpucount:4 /p:Configuration=Release"

win32/INScore.sln : CMakeLists.txt
	[ -d win32 ] || mkdir win32
	cd win32 && cmake .. -G $(WIN32VS)

#===============================================================
clean :
	rm -rf macos win32 linux
