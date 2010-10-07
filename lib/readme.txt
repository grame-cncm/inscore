----------------------------------------------------------------------
   INScore project - external libraries
----------------------------------------------------------------------
The INScore project depends on external libraries:
 - the GuidoEngine version 1.40 or greater (see http://guidolib.sourceforge.net)
 - the GuidoQt static library, actually part of the GuidoEngine library
 - oscpack
 - optionaly: the MusicXML library  (see http://libmusicxml.sourceforge.net)
   when you want to support the MusicXMl format.   
The GuidoEngine, the GuidoQt and oscpack are required to compile INScore.

Mac OS
----------------------------
The GuidoEngine and GuidoQt libraries are included in binary form in the macosx folders.
You just need to extract the GUIDOEngine framework from the GUIDOEngine.tgz archive in the GuidoEngine/macosx folder. In case you run in trouble using the library, due to dependency, the 'localise' script should change the library dependency to the appropriate location.
For oscpack see the 'All platform section'

Windows
----------------------------
The GuidoEngine and GuidoQt libraries are included in binary form in the win32 folders.
The files are .lib and .dll files compiled with Visual C++. The GuidoQt library is static.
For oscpack see the 'All platform section'

Linux
----------------------------
You need to compile the Guido Engine and the GuidoQt libraries from the GUIDOLib project
(http://sourceforge.net/projects/guidolib). You can get the source code from svn:
	svn co https://guidolib.svn.sourceforge.net/svnroot/guidolib guidolib
or from the src distribution:
	http://sourceforge.net/projects/guidolib/files/Guidolib-src/
This project requires the Guido Engine version 1.40 or greater. 
See the linux folder for detailed instructions.
For oscpack see the 'All platform section'

All platform
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
The project is based on cmake. Compile and install the library where the INScore Viewer can find it.
The library is not required to compile the INScore project.


In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
