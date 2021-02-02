
@echo off

goto DLLS

echo Compiles submodules
@REM cd ../modules/
@REM ./Make.bat
@REM cd ../build

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
GOTO DEPLOY

:QMAKE
cd inscoredir
echo Call qmake for library.pro
qmake ../library.pro
echo Call qmake for viewer.pro
qmake ../viewer.pro
cd ..

:COMPILE
msbuild inscoredir/INScore.vcxproj        /p:Configuration=Release /p:Platform=x64 /maxcpucount:4
msbuild inscoredir/INScoreViewer.vcxproj  /p:Configuration=Release /p:Platform=x64 /maxcpucount:4
cd ..\tools\IBundle\build
CALL Make.bat
cd ..\..\..\build
xcopy /Y "..\tools\IBundle\IBundle.exe" "bin\"
GOTO DONE

:DEPLOY
set dest=cmbin
windeployqt %dest%/INScoreViewer.exe

:DLLS
echo Copy libraries
xcopy /y "cmlib\INScore.dll" "%dest%\"
xcopy /y "..\modules\guidolib\build\lib\GUIDOEngine64.dll" "%dest%\"
IF NOT EXIST %dest%/Plugins (
	mkdir %dest%/Plugins
)
xcopy /y "..\modules\libmusicxml\build\lib\musicxml2.dll" "%dest%\Plugins\"
GOTO DONE

:USAGE
echo Usage: %0 [OPTION]
echo where OPTION is in:
echo -qmake  : regenerate the qmake output
echo -dlls   : copy dependant dlls
echo -deploy : call windeployqt

:DONE
