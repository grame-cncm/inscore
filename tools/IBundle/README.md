# INScore Bundles
[GRAME](http://www.grame.fr) - Centre national de creation musicale  
Copyright GRAME (c) 2009-2021

## General information
INScore bundles are self contained INScore scripts that can be 
generated or expanded using the IBundle tool.   
A bundle is a compressed archive that makes use of the Qt 
compression algorithm. 

## IBundle usage

~~~~~~~~~~
IBundle <file> [options]
~~~~~~~~~~
IBundle generates or expand INScore bundles that are self contained compressed
INScore scripts including all the resources required by the scripts
It can run in creation or extraction mode
the '-e' option must be use to switch to extration mode.

General options:
~~~~~~~~~~
  -o  --output <file>       Specify the output file
  -f  --force-overwrite     If the file exist, overwrites it without asking
  -h  --help                Print this message and quit
  -v  --version             Print version and quit
~~~~~~~~~~

Creation mode options:
~~~~~~~~~~
  -vv --verbose OPTION      Print processing logs
                hierarchy   Details dependencies for each scripts
  -l  --rootpath <path>     Set default root path to <path>
  -js --parse-javascript    Javascript sections are parsed to detect ressources
      --fail-safe           See further for details about the fail-sage mode
~~~~~~~~~~

Extraction mode options:
~~~~~~~~~~
  -e --extract              Extract the content of an ibundle archive
  -k --keepOriginalPath     Recreate the original hierarchy of the script
~~~~~~~~~~


## FAIL-SAFE MODE

While the standard mode automatically detects dependencies, the fail-safe mode
allows to manually specify which files should be included in the bundle without
parsing or modifying any script.The input file should be a list of the files 
(one file per line) and the first file should be the launched script. 

## EXAMPLES
~~~~~~~~~~
IBundle script.inscore
~~~~~~~~~~
will bundle script.inscore into script.ibundle including all the required ressources.

~~~~~~~~~~
IBundle script.ibundle -e
~~~~~~~~~~
will extract `script.ibundle` into a folder named "script/" 


## Limitations

In creation mode and unless the `--fail-safe` option is active,
the input script is analysed to detect all the ressources associated
to the script i.e. references to files. The detected files are then 
copied to a single folder and the file path is rewritten accordingly.

Unless an absolute path is used, a file reference is relative to the
current rootPath. By default, IBundle assumes that the current rootPath 
is the input script folder, unless the `--rootpath` option is used. 
RootPath changes are correctly handled, unless they result from 
a javacript section.

### Note for javascript sections:

 Javascript sections are reported to the ouput script, prefixed with 
 the current environment (i.e. INScore variables). However, these sections
 are NOT evaluated and as a result, output messages that make reference 
 to files are not visible to the IBundle tool. Thus, the corresponding 
 ressources will be missing from the bundle.
 You can use the --parse-javascript option to try to detect file names
 inside javascript sections.

### Note about variables:

 Variables are expanded by the parser but undefined variables are left 
 unchanged. However and while generating the output script, undefined 
 variables (i.e. parameters that start with a '$') are quoted since in
 a normal case, only interaction variables are supposed to be present
 and need to be quoted. Therefore, a variable that is defined by a 
 javascript section will be quoted on output and thus result in an 
 incorrect interpretation.

## Acknowledgments
The INScore IBundle tool has been designed by Gabriel Lepetit-Aimon.
Many thanks to him.

---------
For more information, contact me at <fober@grame.fr>

