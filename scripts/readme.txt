======================================================
INScore project
------------------------------------------------------
GRAME - Centre national de creation musicale
http://www.grame.fr
fober@grame.fr
======================================================
Copyright GRAME (c) 2009-2016

This folder contains various INScore sample scripts and Max/MSP or PureData patches provided as tools or sample of INScore use. The enclosed folders complie to the following naming scheme:
 - folder starting with 'M' contain Max/MSP samples or tools. 
 - folder starting with 'P' contain PureData samples or tools. 
 - samples in folders starting with 'MP' support both Max/MSP or PureData
The Standalone folder contains standalone scripts i.e. INScore scripts that don't require
any external application to run. 


The INScore Viewer supports drag & drop. You can drag & drop any file to a scene window:
 - when the file is a .inscore file, the corresponding messages are sent to 
   the scene
 - for any other file, the system tries to detect the file type and creates 
   a new object which OSC address will be /ITL/scene/filename
   Note that 'filename' is a translation of the dropped file name, without 
   extension. Note that it translates characters that are forbidden in OSC
   address space.
