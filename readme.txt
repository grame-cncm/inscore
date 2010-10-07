----------------------------------------------------------------------
Compiling the INScore project
----------------------------------------------------------------------

The INScore project depends on external libraries. See the 'lib/readme.txt' 
file for instructions to resolve these dependencies.

The INScore project relies on CMake, a cross-platform, open-source build 
system ( see http://www.cmake.org/).
The cmake folder contains the project description and is used to generate 
native projects. 
You should resolve the external dependencies prior running cmake.

To compile:
	change to cmake directory
	type:  cmake -G "your target generator"
	run your project/makefile and compile
	

Note for Windows platforms:
--------------------------
	The CMake project description is "Visual Studio" oriented. 
	Using MingW may require some adaptation.

In case of trouble, contact me: <fober@grame.fr>

----------------------------------------------------------------------
Copyright 2009, 2010 Grame 
D. Fober, C. Daudin
----------------------------------------------------------------------
