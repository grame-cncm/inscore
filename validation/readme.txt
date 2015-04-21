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

  > make filter
... generates the .inscore filtering files and the reference output file, that can also be generated separately :
    > make filterref
  ... to generate filter result reference files
    > make filterinscore
  ... to generate inscore file filter from .flt file
    > make filteroutput
  ... to generate inscore output from current running inscore instance

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
4) Validate android version
----------------------------------------------------------------------

To validate android version you have to :
 - copy empty tree folder (androidempty folder) on your android device in /sdcard/inscore and rename it (Version)android.
 - Start INScore on the device and generate the pdf files with :
	make android REMOTEIP=YOUR_DEVICE_IP LOCALIP=YOUR_COMPUTER_IP
YOUR_DEVICE_IP is the device IP (example 192.168.1.2) and YOUR_COMPUTER_IP is the IP address of the computer running the makefile.
 - copy the tree folder with the generated pdf files from your android device to your computer in this folder.
 - compare with an other version (here 1.12) with :
	make validateandroid VERSION=1.12android

======================================================================
In case of trouble, contact me: <fober@grame.fr>
----------------------------------------------------------------------
Copyright 2009, 2010, 2011 (c) Grame 
======================================================================



