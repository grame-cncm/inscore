
@echo off

echo Make sure the submodules are up-to-date
echo Compiles guidolib
CALL :SUBCOMPILE guidolib GUIDOEngine64 "-DMIN=on"

echo Compiles libmusicxml
CALL :SUBCOMPILE libmusicxml musicxml2 "-DGENTOOLS=off -DLILY=off -DGENSTATIC=off"
GOTO :DONE

:SUBCOMPILE
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
