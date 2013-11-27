----------------------------------------------------------------------
Validating a version in the INScore project
----------------------------------------------------------------------


======================================================================
1) Creating the files to be compared
----------------------------------------------------------------------

  > cd /your_path_to_the_INScore_project/validation
  > make

This will execute various fonctions that you can also call separately : 

  > make log
... generates the .log files

  > make save
... generates the .inscore files
  
  > make pdf
... generates the .pdf files, that can also be generated separately :
  
    > make pdfmouse
  ... for the mouse interaction
    > make pdfgraphic
  ... for the graphical elements
    > make pdfsync
  ... for the synchronization
    > make pdfjava
  ... for the javascript interactions
    > make basic
  ... for all the rest...



======================================================================
2) Looking for differences in the files
----------------------------------------------------------------------

  > cd /your_path_to_the_INScore_project/validation
  > make validate VERSION=an_older_version_that_can_be_taken_as_reference

This will generate a list of all differences between the two versions.
You can simply doucle-click on a line and cut/paste it to see the two files and compare them.

-------------

  Warning :

Some scripts may not generate correctly at the first time (jsgrid, or scoremap for example).
It is possible that this problem come from the inscore-to-pdf mecanism rather than from 
a real difference in the new version. 
You can delete and re-generate those scripts to be sure.

-------------

======================================================================
3) Checking the remaining scripts manually
----------------------------------------------------------------------

Some scripts cannot be tested automatically by the makefile.
These scripts are listed in the manual.txt file.
It is recommended to test them as well, by simply droping them manually and see 
if the result fits the expectations.


======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2009, 2010, 2011 (c) Grame 
======================================================================



