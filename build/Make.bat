
@echo off

IF NOT EXIST inscoredir (
	echo Create output folder
	mkdir inscoredir
	GOTO QMAKE
)

IF [%1]==[] GOTO COMPILE

IF %1==-qmake GOTO QMAKE
IF %1==-dlls GOTO DLLS
IF %1==-deploy GOTO DEPLOY

GOTO USAGE


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
windeployqt bin/INScoreViewer.exe

:DLLS
echo Copy libraries
xcopy /Y "..\lib\GUIDOEngine\win64\GUIDOEngine64.dll" "bin\"
IF NOT EXIST bin/Plugins (
	mkdir bin/Plugins
)
xcopy /Y "..\lib\libMusicXML\win64\libmusicxml2.dll" "bin\Plugins\"
xcopy /Y "..\lib\GuidoAR\win64\guidoar.dll" "bin\"
GOTO DONE

:USAGE
echo Usage: %0 [OPTION]
echo where OPTION is in:
echo -qmake  : regenerate the qmake output
echo -dlls   : copy dependant dlls
echo -deploy : call windeployqt

:DONE
