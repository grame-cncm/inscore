
@echo off

goto DLLS

echo Compiles submodules
cd ../modules/
./Make.bat
cd ../build

IF NOT EXIST inscoredir (
	echo Create output folder
	mkdir inscoredir
	GOTO CMAKE
)
GOTO CMAKE

IF [%1]==[] GOTO COMPILE

IF %1==-qmake GOTO QMAKE
IF %1==-dlls GOTO DLLS
IF %1==-deploy GOTO DEPLOY

GOTO USAGE

:CMAKE
cd inscoredir
cmake .. -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release
cd ..

:DEPLOY
echo Call windeployqt
set dest=cmbin
windeployqt %dest%/INScoreViewer.exe

:DLLS
echo Copy libraries
xcopy /y "lib\INScore.dll" "%dest%\"
xcopy /y "..\modules\guidolib\build\lib\GUIDOEngine64.dll" "%dest%\"
IF NOT EXIST %dest%/Plugins (
	mkdir %dest%/Plugins
)
xcopy /y "..\modules\libmusicxml\build\lib\musicxml2.dll" "%dest%\Plugins\"
GOTO DONE

:USAGE
echo Usage: %0 [OPTION]
echo where OPTION is in:
echo -dlls   : copy dependant dlls
echo -deploy : call windeployqt

:DONE
