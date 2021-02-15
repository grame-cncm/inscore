
@echo off

set MSVC="Visual Studio 15 2017 Win64"
set VERSION="1.2.7"

IF [%1]==[]     GOTO USAGE
IF %1==modules (
	CALL :MODULES
	GOTO DONE
)
IF %1==inscore (
	CALL :COMPILE
	GOTO DONE
)
IF %1==deploy (
	CALL :DEPLOY
	GOTO DONE
)
IF %1==install (
	CALL :INSTALL
	GOTO DONE
)
IF %1==package (
	CALL :PACKAGE
	GOTO DONE
)
IF %1==help 	GOTO USAGE

GOTO USAGE

@rem --- installation -------------------------------
:INSTALL
cd inscoredir
cmake .. -DPREFIX=../INScore-%VERSION%
cmake --build . --config Release --target install
cd ..
EXIT /B

@rem --- packaging ----------------------------------
:PACKAGE
cd inscoredir
cmake .. -DPACK=on
cmake --build . --config Release 
cpack -G NSIS64
move INScore-*.exe ..
cd ..
EXIT /B

@rem --- deployment ----------------------------------
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

@rem --- submodules compilation ----------------------
:MODULES
	echo Compiles submodules
	cd ../modules
echo in modules
	CALL Make.bat
	cd ../build
EXIT /B

@rem --- inscore compilation -------------------------
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
echo   inscore : compile inscore (call modules when not already done)
echo   deploy  : call windeployqt and copy dependent libraries
echo   install : install inscore in current folder
echo   package : build the inscore package
echo   help    : display this help
echo This script is using %MSVC% to compile, edit 
echo the script and set the MSVC variable to change. 

:DONE
