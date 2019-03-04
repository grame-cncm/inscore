
@echo off

set /p VERSION=<..\version.txt
set PACK=INScore-%VERSION%-win64
set BUILDDIR=..\build\bin

IF [%1]==[]    GOTO PACKAGE
IF %1==-deploy GOTO DEPLOY
GOTO USAGE

:DEPLOY
echo Call windeployqt
windeployqt %BUILDDIR%\INScoreViewer.exe


:PACKAGE
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

:USAGE
echo Usage: %0 [OPTION]
echo where OPTION is in:
echo -deploy : call windeployqt

:DONE
