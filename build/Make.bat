
@echo off

set MSVC="Visual Studio 15 2017 Win64"

IF [%1]==[]     GOTO USAGE
IF %1==modules 	CALL :MODULES
IF %1==inscore 	CALL :COMPILE
IF %1==deploy 	CALL :DEPLOY
IF %1==help 	GOTO USAGE

GOTO DONE

:DEPLOY
	echo Call windeployqt
	set dest=bin
	windeployqt %dest%/INScoreViewer.exe

	echo Copy libraries
	xcopy /y "lib\INScore.dll" "%dest%\"
	xcopy /y "..\modules\guidolib\build\lib\GUIDOEngine64.dll" "%dest%\"
	IF NOT EXIST %dest%\Plugins (
		mkdir %dest%\Plugins
	)
	xcopy /y "..\modules\libmusicxml\build\lib\musicxml2.dll" "%dest%\Plugins\"
EXIT /B

:MODULES
	echo Compiles submodules
	cd ../modules
echo in modules
	CALL Make.bat
	cd ../build
EXIT /B

:COMPILE
	IF NOT EXIST  ..\modules\guidolib\build\lib\GUIDOEngine64.lib (
		CALL :MODULES
	)
	IF NOT EXIST inscoredir (
		echo Create output folder
		mkdir inscoredir
	)
	cd inscoredir
	cmake .. -G %MSVC%
	cmake --build . --config Release
	cd ..
EXIT /B


:USAGE
echo Usage: %0 [COMMAND]
echo where COMMAND is in:
echo   modules : compile submodules
echo   inscore : compile inscore
echo   deploy  : call windeployqt and copy dependent libraries
echo   help    : display this help

:DONE
