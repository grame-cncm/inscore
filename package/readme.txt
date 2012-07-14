======================================================
Interlude project (ANR-08-CORD-010)
------------------------------------------------------
GRAME - Centre national de creation musicale
http://www.grame.fr
research@grame.fr
======================================================
Copyright GRAME (c) 2009-2011


======================================================
 General information
======================================================
The INScore Viewer provides augmented music score capabilities.
An augmented score is a graphic space that provides representation, 
composition and manipulation of heterogeneous music objects, 
both in the graphic and time domains. 
It supports arbitrary resources like music scores, images, 
text, vectorial graphics and signals representations. 
It focuses on the graphic synchronization of its components, 
according to their time relations and on signals representation.

The INScore Viewer has no user interface, it is intended to be 
controled via OSC messages i.e. by any external application that 
supports the OSC protocol (typically MaxMSP or Pure Data).

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

======================================================
 Links
======================================================
The INScore project is an open source project. It has been
developped in the framework of the Interlude project (ANR-08-CORD-010)
For more information, see at:
 - http://inscore.sourceforge.net

INScore depedns on the Guido Engine library and optionnaly, on
the libMusicXML library.
The Guido Engine library and applications, and the libMusicXML 
library are open source projects. available at SourceForge.
For more information and to get the latest version, see at:
 - http://www.sourceforge.net/pojects/guidolib
 - http://www.sourceforge.net/pojects/libmusicxml

======================================================
For more information, contact me at <fober@grame.fr>

