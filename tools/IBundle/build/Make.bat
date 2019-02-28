
@echo off

IF NOT EXIST ibundledir (
	echo Create output folder
	mkdir ibundledir
	GOTO QMAKE
)

IF [%1]==[] GOTO COMPILE

IF %1==-qmake GOTO QMAKE

GOTO USAGE


:QMAKE
cd ibundledir
echo Call qmake 
qmake ..
cd ..

:COMPILE
msbuild ibundledir/IBundle.vcxproj        /p:Configuration=Release /p:Platform=x64 /maxcpucount:4
GOTO DONE


:USAGE
echo Usage: %0 [OPTION]
echo where OPTION is in:
echo -qmake  : regenerate the qmake output

:DONE
