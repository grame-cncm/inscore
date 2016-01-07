#ifndef DOC_H
#define DOC_H

#ifndef VERSION
#define VERSION "1.0"
#endif

const char* DOC=
"Use: ITLBundleCreator INPUT_FILE [OPTIONS] \n"
"Print any OSC messages from a given port \n"
"Version: "
VERSION
"\n\n"
" -- OPTIONS --\n"
"  -o --output  OUTPUT_FILE  Specify the output file\n"
"  -v --verbose              Print processing logs\n"
"  -h  --help                Print this message and quit\n"
"\n"
" -- EXAMPLES --\n"
"ITLBundleCreator script.inscore\n"
"   will bundle script.inscore into script.itlbundle \n"
"   with all the needed ressources.\n"
"\n"
;

const char* USAGE=
"Usage: ITLBundleCreator INPUT_FILE [OPTIONS] \n"
"  try ITLBundleCreator -h for details.\n"
;
#endif // DOC_H

