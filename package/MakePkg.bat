
@echo off

set /p VERSION=<..\version.txt
set PACK=INScore-%VERSION%-win64
set BUILDDIR=..\build\bin

echo Call windeployqt
windeployqt %BUILDDIR%\INScoreViewer.exe


IF NOT EXIST build (
	echo Creating build folder
	mkdir build
)

cd build
echo Creating cmake setup
cmake .. -G "Visual Studio 14 2015 Win64"
cpack -g NSIS64
move INScore-*.exe ..
cd ..