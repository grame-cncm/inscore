======================================================
Interlude project (ANR-08-CORD-010)
------------------------------------------------------
GRAME - Centre national de creation musicale
http://www.grame.fr
research@grame.fr
======================================================
Copyright GRAME (c) 2009-2011

The StandAlone folder contains various files that don't require any external 
OSC application to be loaded in the INScore Viewer.

Starting from version 0.70, the INScore Viewer supports drag & drop as well 
as multiple scene windows. You can drag & drop any file to a scene window:
 - when the file is a .inscore file, the corresponding messages are sent to 
   the scene
 - for any other file, the system tries to detect the file type and creates 
   a new object which OSC address will be /ITL/scene/filename
   Note that 'filename' is a translation of the dropped file name, without 
   extension: it actually translates characters that are forbidden in OSC
   address space.

The 'manyscene.inscore' file illustrates multiple scenes support. The file 
should be dropped on the application (and not on a scene).

The 'switch.inscore' file illustrates message based variables: it shows how
objects can exchange their states using message based variables.


Note that the system supports only 8 bits encodings for file names. 
