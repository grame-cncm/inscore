# INScore project
------------------------------------------------------
[GRAME](http://www.grame.fr) - Centre national de creation musicale  
Copyright GRAME (c) 2009-2021
------------------------------------------------------

This folder contains various INScore sample scripts and Max/MSP or PureData patches provided as tools or sample of INScore use. The enclosed folders complie to the following naming scheme:
 - folder starting with 'M' contain Max/MSP samples or tools. 
 - folder starting with 'P' contain PureData samples or tools. 
 - samples in folders starting with 'MP' support both Max/MSP or PureData  

The Standalone folder contains standalone scripts i.e. INScore scripts that don't require
an external application to interact with the score. 


The INScore Viewer supports drag & drop. You can drag & drop any file to an INScore window:
 - when the file is a `.inscore` file, the corresponding messages are sent to 
   the scene
 - for any other file, the system tries to detect the file type and creates 
   a new object which OSC address will be `/ITL/scene/<filename>`  
   Note that `filename` is a translation of the dropped file name:
   	- file extension is omitted
   	- forbidden characters in OSC address space are replaced

If you have a text editor that supports drag & drop, you can also drag & drop text to an INScore windows. Of course, the dropped text must be syntactically correct.

See the [INScore documentation](https://inscoredoc.grame.fr/) for more information about the INScore scripting language.

------------------------------------------------------

