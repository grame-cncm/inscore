======================================================
INScore project
------------------------------------------------------
GRAME - Centre national de creation musicale
http://www.grame.fr
======================================================
Copyright GRAME (c) 2009-2013


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
The INScore project is an open source project. 
For more information, see at:
 - http://inscore.sourceforge.net

INScore makes use of the following technologies:
  - the GUIDOEngine                           http://guidolib.sf.net
  - the IRCAM Gesture Follower                http://imtr.ircam.fr/imtr/Gesture_Follower
  - the Qt5 cross-platform application and UI framework    http://qt-project.org/qt5
  - the V8 JavaScript Engine                  https://code.google.com/p/v8/
Optionnal dependency:
  - the libMusicXML library                   http://libmusicxml.sf.net

======================================================
 Acknowledgments
======================================================
INScore was initiated in the Interlude project (http://interlude.ircam.fr), 
funded by the French National Research Agency [ANR- 08-CORD-010].
I would like to thank all the people who have been contributing 
to INScore design and development, and especially Christophe Daudin, 
Martin Carlé, Guillaume Gouilloux, Eric Ravel, Camille Le Roi.
Many thanks also to the Interlude team - Frédéric Bevilacqua, Norbert Schnell, 
Nicolas Rasamimanana, Emmanuel Fléty, Fabrice Guédy, Jean-Louis Frechin, 
Uros Petrevski, Bernard Garabédian, Rémi Dury, Bruno Verbrugghe - who contributed
to the elaboration of the project foundations.
And of course, warmest thanks to my colleagues and friends Stéphane Letz 
and Yann Orlarey.

-- 
Dominique Fober

======================================================
For more information, contact me at <fober@grame.fr>
