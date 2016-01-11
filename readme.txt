----------------------------------------------------------------------
Compiling the INScore project
----------------------------------------------------------------------

The INScore project depends on external libraries:
 - the Qt framework version 5.3 or later (see https://www.qt.io/)
 - the GuidoEngine version 1.60 or greater (see http://guidolib.sourceforge.net)
 - the GuidoAR version 1.00 or greater (see http://guidolib.sourceforge.net)
 - the libmicrohttpd library (see https://www.gnu.org/software/libmicrohttpd/)
 - the oscpack library (included in the INScore repository)
 - optionaly: 
     - the MusicXML library  (see http://libmusicxml.sourceforge.net)
       when you want to support the MusicXMl format.
     - the programming language lua (see http://www.lua.org/)
The GuidoEngine SDK is required to compile INScore.

The present document describes how to compile the INScore projects. 
It starts describing how to resolve the required external dependencies.
The next section explains how to compile the INScore project.
The last section describes how to resolve the optional external dependencies.

======================================================================
1) Resolving the required external dependencies
----------------------------------------------------------------------

>>>>>> All platform
----------------------------
You should first install Qt version 5.3 or greater.
Installation depends on your platform. See at https://www.qt.io/

>>>>>> Mac OS
----------------------------
The GuidoEngine library is included in binary form in the lib/GuidoEngine/macosx folders.
You just need to extract the GUIDOEngine framework from the GUIDOEngine.tgz archive. 
The GuidoAR library is included in binary form in the lib/GuidoAR/macosx folders.
You just need to extract the guidoar framework from the guidoar.tgz archive.
In case you run in trouble using the library due to dependency, the 'localise' script should 
change the library dependency to the appropriate location.
Note that when running 'make' the build folder, extraction and localisation is automatically done.

>>>>>> Windows
----------------------------
The GuidoEngine library is included in binary form in the lib/GuidoEngine/win32 and win64 folders.
The GuidoAR library is included in binary form in the lib/GuidoAR/win32 and win64 folders.
The binaries have been compiled with Visual C++ Version 12.
You should check your environment compatibility and notably for the potential runtime issues.
libmicrohttpd is (not yet) required for windows (yet unsupported httpd object) 

>>>>>> Linux
----------------------------
You need to compile the Guido Engine library from the GUIDOLib project
(http://sourceforge.net/projects/guidolib). You can get the source code from git:
	git clone git://git.code.sf.net/p/guidolib/code guidolib-code
or from the src distribution:
	http://sourceforge.net/projects/guidolib/files/Guidolib-src/
You can also get binary packages but only for Ubuntu. 
See at https://sourceforge.net/projects/guidolib/files/DevKits/Ubuntu/

You need to compile the GuidoAR library from the GUIDOLib project
(http://sourceforge.net/projects/guidolib). You can get the source code from git:
	git clone git://git.code.sf.net/p/guidolib/guidoar guidolib-guidoar

a) Compiling the GUIDO library 
----------------------------
To compile the GUIDO library do the following:
  > cd /your_path_to_the_guido_project/build
  > make
  > sudo make -C linux install

a) Compiling the GuidoAR library 
----------------------------
To compile the GUIDO library do the following:
  > cd /your_path_to_the_guidoar_project/build
  > make
  > sudo make -C linux install


======================================================================
2) Compiling INScore
----------------------------------------------------------------------
The INScore project relies on qmake, a cross-platform, open-source build system provided with Qt.
The build folder contains the project description and is used to generate native projects. 
It contains also a makefile that call qmake to generate the native projects (XCode on MacOS, 
Visual Studio on Windows, Makefiles on linux) and compiles the projects in 'release' mode.
You should resolve the external dependencies prior running make.

It's always possible to switch to native environment and to compile using native IDE instead of 
command line (always usefull in dev phase).

To compile:
	change to 'build' directory
	> cd build
	> make
and that's all !!

Note that MusicXML support makes use of dynamic link: it is available when a library with the 
required entry point is found.

Note for Windows platforms:
--------------------------
The project description is "Visual Studio xxx" oriented. Two scripts are describing the version of 
Visual Studio that you use: 
- vs-vers : that gives the full name of your Visual Studio version
- vs-path : that gives the full path of your VisualStudio installation
Another script named 'qt-arch' gives the architecture of the Qt version that you use. Values should 
be in 'Win32' or 'x64'
These scripts are located in the build folder; You should customize these scripts accordingly.
Note that these scripts are used by the Makefile only. You can skip them if you run qmake manually.
Calling qmake and make requires to have unix like commands installed, which is provided by the
MINGW environment.
However, it should always be possible to compile using QTCreator and the .pro files included 
in the build folder.

Note for Android platform:
--------------------------
You need to have Qt for android and the Android SDK and NDK installed on your computer.
You need to have the three following environnement variables :
ANDROID_NDK_ROOT = root path of android NDK
ANDROID_SDK_ROOT = root path of android SDK
ANDROID_HOME = root path of android SDK

You can add these varaibles with this command and Linux and MacOS : 
	> export ANDROID_NDK_ROOT=/myPath/To/NDK

You need to have two alias of qt android binary file :
	- an alias to qmake for android called qmake-android 
	- an alias to androiddeployqt called androiddeployqt

To compile:
	change to 'build' directory
	> cd build
	> make android [KEYSTOREPATH=XXX CERTIFICATEALIAS=YYY]
The two variables KEYSTOREPATH and CERTIFICATEALIAS are optional to sign android application.
	KEYSTOREPATH is the path of your keystorefile.
	CERTIFICATEALIAS is the alias of the certificate.

To install application on your device use :
	> make androidInstall DEVICE=XXX
where DEVICE variable is the serial number of your android device. You can get it with "adb get-serialno".

The folder of the build apk can change with your Qt version and your system. You may have to change the install script folder.

You can also use qtcreator with the INScore.pro project to build and deploy INScore on android.

Note for iOS platform:
--------------------------
You need to have an alias of qt ios binary file :
	- an alias to qmake for ios called qmake-ios 

You can compile INScore for iOS with 
	> make ios

Use XCode to deploy the application on your device.

You can also use qtcreator with the INScore.pro project to build and deploy INScore on iOS.

======================================================================
3) Resolving the optional external dependencies
----------------------------------------------------------------------

MusicXML support
----------------------------
You should get the MusicXML library version 2.0 or later from GitHub:
	https://github.com/dfober/libmusicxml
The library is not required to compile the INScore project, nor to run the INScore viewer. 
When the library is not present, MusicXML support is not available.


Faust Compiler support
----------------------------
You should get the branch faust2 of libfaust development branch from git : 
git clone git://git.code.sf.net/p/faudiostream/code faudiostream-code

To compile libfaust library do the following:
	> cd faudiostream-code
	> git checkout faust2	
	> make dynamic
	> sudo make install-dynamic

lua support
----------------------------
lua support starts to be deprecated. If you want to include lua in inscore, contact me.


Http server support
----------------------------
You should install libmicrohttpd library (a GNU project) on your computer.
Then, you can build the http server in lib/httpserver folder : 
	> cd lib/httpserver/build
	> cmake -G "Your environnement"
	> make

The server can be added in your INScore folder to enabled http server plugin.

Note that the http server library work only on Linux and Mac OS.

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
Copyright 2009-2015 (c) Grame 
======================================================================



