----------------------------------------------------------------------
Compiling the INScore project
----------------------------------------------------------------------

The INScore project depends on external libraries:
 - the Qt framework version 4.6 or later (see http://qt.nokia.com/)
 - the GuidoEngine version 1.40 or greater (see http://guidolib.sourceforge.net)
 - the GuidoQt static library, actually part of the GuidoEngine library
 - oscpack
 - optionaly: the MusicXML library  (see http://libmusicxml.sourceforge.net)
   when you want to support the MusicXMl format.   
The GuidoEngine, the GuidoQt and oscpack are required to compile INScore.


======================================================================
1) Resolving the external dependencies
----------------------------------------------------------------------

>>>>>> Mac OS
----------------------------
The GuidoEngine and GuidoQt libraries are included in binary form in the macosx folders.
You just need to extract the GUIDOEngine framework from the GUIDOEngine.tgz archive in the GuidoEngine/macosx folder. In case you run in trouble using the library, due to dependency, the 'localise' script should change the library dependency to the appropriate location.
For oscpack see the 'All platform section'

>>>>>> Windows
----------------------------
The GuidoEngine and GuidoQt libraries are included in binary form in the win32 folders.
The files are .lib and .dll files compiled with Visual C++. The GuidoQt library is static.
For oscpack see the 'All platform section'

>>>>>> Linux
----------------------------
You need to compile the Guido Engine and the GuidoQt libraries from the GUIDOLib project
(http://sourceforge.net/projects/guidolib). You can get the source code from svn:
	svn co https://guidolib.svn.sourceforge.net/svnroot/guidolib guidolib
or from the src distribution:
	http://sourceforge.net/projects/guidolib/files/Guidolib-src/
This project requires the Guido Engine version 1.40 or greater. 

a) Compiling the GUIDO library 
----------------------------
To compile the GUIDO library do the following:
  > cd /your_path_to_the_guido_project/cmake
  > cmake -G "Unix Makefiles"
  > make
  > sudo make install

b) Compiling the GuidoQt library 
----------------------------
The GuidoQt library depends on the Qt framework. You need to have Qt SDK version 4.6 or later 
installed before compiling the GuidoQt library (see at http://qt.nokia.com/).
The Qt SDK can be gotten from synaptic (for Ubuntu users).
To compile the GuidoQt library do the following:
  > cd /your_path_to_the_guido_project/Qt/GuidoQt
  > qmake
  > make
The resulting binary is expected to be find in the GuidoQt folder under the name 'libGuidoQt.a'
You have to copy the library to the INScore project:
  > cp libGuidoQt.a /your_path_to_the_INScore_project/lib/GuidoQt/linux

c) Compiling oscpack 
----------------------------
To compile oscpack do the following:
  > cd /your_path_to_the_INScore_project/lib/oscpack/cmake
  > cmake -G "Unix Makefiles"
  > make

>>>>>> All platform
----------------------------
You need to compile the oscpack library from the oscpack folder.
The oscpack library is based on cmake but includes also makefiles from the original distribution. 
Cmake output files are where the INScore project expects to find them.


MusicXML support
----------------------------
You should get the MusicXML library version 2.0 or later from SourceForge from svn:
	svn co https://libmusicxml.svn.sourceforge.net/svnroot/libmusicxml libmusicxml
or from the src distribution:
	http://sourceforge.net/projects/libmusicxml/files/libmusicxml-src/
The library is not required to compile the INScore project, nor to run the INScore viewer. 
When the library is not present, MusicXML support is not available.
To compile the MusicXML library do the following:
  > cd /your_path_to_the_musicxml_project/cmake
  > cmake -G "Unix Makefiles"
  > make
  > sudo make install


======================================================================
2) Compiling INScore
----------------------------------------------------------------------
The INScore project relies on CMake, a cross-platform, open-source build 
system ( see http://www.cmake.org/).
The cmake folder contains the project description and is used to generate 
native projects. 
You should resolve the external dependencies prior running cmake.

To compile:
	change to cmake directory
	type:  cmake -G "your target generator"
	run your project/makefile and compile
	
Note for Linux platforms:
--------------------------
	The procedure to compile can be close to the usual 'configure' 'make' 'make install'
	steps. Actually, you can simply do the following:
	> cd /your_path_to_the_project/cmake
	> cmake -G "Unix Makefiles"
	> make
	> sudo make install

Note for Windows platforms:
--------------------------
	The CMake project description is "Visual Studio" oriented. 
	Using MingW may require some adaptation.

======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2009, 2010, 2011 (c) Grame 
======================================================================



