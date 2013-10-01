----------------------------------------------------------------------
Compiling the INScore project
----------------------------------------------------------------------

The INScore project depends on external libraries:
 - the Qt framework version 4.6 or later (see http://qt.nokia.com/)
 - the GuidoEngine version 1.40 or greater (see http://guidolib.sourceforge.net)
 - the GuidoQt static library, actually part of the GuidoEngine library
 - the oscpack library
 - the v8 javascript sdk (see "http://code.google.com/p/v8/)
 - optionaly: 
     - the MusicXML library  (see http://libmusicxml.sourceforge.net)
       when you want to support the MusicXMl format.
     - the programming language lua (see http://www.lua.org/)
The GuidoEngine, the GuidoQt, oscpack and v8 libraries are required to compile INScore.

The present document describes how to compile the INScore projects. 
It starts describing how to resolve the required external dependencies.
The next section explains how to compile the INScore project.
The last section describes how to resolve the optional external dependencies.


======================================================================
1) Resolving the required external dependencies
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
Up to version 5 of Qt, you need to install 'libphonon-dev'. With Qt5, multimedia support is 
included in Qt and phonon is not required any more.
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

d) Installing Qt 
----------------
Qt should be installed to compile the GuidoQt library and to compile INScore.
Installation depends on your platform. See at http://qt-project.org/

d) Installing the V8 javascript SDK 
-----------------------------------
V8 is included in the inscore repository in binary form for Mac OS and Windows and the cmake
configuration file will automatically use them.
On Linux, you can find a package for your distribution (named libv8-dev on Debian and Ubuntu).


>>>>>> All platform
----------------------------
You need to compile the oscpack library from the oscpack folder.
The oscpack library is based on cmake but includes also makefiles from the original distribution. 
Cmake output files are where the INScore project expects to find them.



======================================================================
2) Compiling INScore
----------------------------------------------------------------------
The INScore project relies on CMake, a cross-platform, open-source build system 
( see http://www.cmake.org/).
The cmake folder contains the project description and is used to generate native projects. 
You should resolve the external dependencies prior running cmake.

To compile:
	change to cmake directory
	type:  cmake -G "your target generator" [options]
	run your project/makefile and compile

	NOTE: that cmake assumes that Qt5 is installed. Due to differences in Qt packages, you have
	to explicitely ask for Qt4 support when Qt4 is installed. 
	To do so, use the option -DQTVERSION=4 when running cmake.

[options] allows to embed lua or/and javascript support:
	for lua: -DLUA=yes 
Note that MusicXML support makes use of dynamic link: it is available when a library with the required entry point is found.


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
3) Resolving the optional external dependencies
----------------------------------------------------------------------

lua support
----------------------------
You should get the lua source code from the lua web site: http://www.lua.org
The distribution includes a Makefile, thus you can simply type:
  > cd /your_path_to_the_lua_distribution/
  > make
  > sudo make install

Notes: 
- on linux/Ubuntu, you can get a binary destribution: install liblua5.1-0-dev from synaptic.
- for windows, a binary version of the library is included in the INScore distribution
  along with the corresponding headers. Thus lua is ready to be supported without additional step.
- a cmake configuration is provided in lib/lua with instructions to use. It should be used to
  generate universal binaries on Mac OS.


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


======================================================
 Note about the Guido Font
======================================================
INScore is distributed as a standalone application and should
work as is. However, depending on your platform and on your
operating system version, it may fail to load the music font 
correctly. The symptom is strange glyphs when you display
symbolic music notation.
To solve the problem, you have to install the font manually:
 - the music font file is 'guido2.ttf', 
   it is located along the application
 - to install double click the guido2.ttf file.
   On most of the systems, a font manager will open that contains
   an install button.
Note also that to update an existing font file, it is safer to
uninstall the previous version before installing the new one.


======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2009, 2010, 2011 (c) Grame 
======================================================================



