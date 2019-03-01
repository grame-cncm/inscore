
@echo off

IF NOT EXIST ibundledir (
	echo Create output folder
	mkdir ibundledir
	GOTO QMAKE
)

IF [%1]==[] GOTO IBUNDLE

IF %1==-qmake GOTO IQMAKE
GOTO IBUNDLE

:IQMAKE
cd ibundledir
echo Call qmake 
qmake ..
cd ..

:IBUNDLE
msbuild ibundledir/IBundle.vcxproj        /p:Configuration=Release /p:Platform=x64 /maxcpucount:4
