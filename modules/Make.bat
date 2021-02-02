
@echo off

echo Make sure the submodules are up-to-date
echo Compiles guidolib
CALL :COMPILE guidolib GUIDOEngine64 

echo Compiles libmusicxml
CALL :COMPILE libmusicxml musicxml2 "-DLILY=off"
GOTO :DONE

:COMPILE
	cd %~1/build
	IF NOT EXIST win64 (
		echo Create output folder
		mkdir win64
	)
	cd win64
	cmake .. -G "Visual Studio 15 2017 Win64" %~3
	cmake --build . --config Release --target %~2
	cd ../../..
EXIT /B

:DONE
