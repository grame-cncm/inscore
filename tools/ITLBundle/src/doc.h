#ifndef DOC_H
#define DOC_H

#ifndef VERSION
#define VERSION "1.0"
#endif

const char* DOC_CREATOR=
"Use: ITLBundleCreator INPUT_ITL_SCRIPT [OPTIONS] \n"
"Package an Inscore scritp and all its dependencies into a compressed bundle \n"
"Version: "
VERSION
"\n\n"
" -- OPTIONS --\n"
"  -o --output  OUTPUT_FILE  Specify the output file\n"
"  -v --verbose OPTION       Print processing logs\n"
"               hierarchy    Details dependencies for each scripts\n"
"  -l --local                Set INScore root path to the current folder\n"
"  -f --force-overwrite      If the file exist, overwrites it without asking\n"
"  -h  --help                Print this message and quit\n"
"\n"
" -- EXAMPLES --\n"
"ITLBundleCreator script.inscore\n"
"   will bundle script.inscore into script.itlbundle \n"
"   with all the needed ressources.\n"
"\n"
;

const char* USAGE_CREATOR=
"Usage: ITLBundleCreator INPUT_FILE [OPTIONS] \n"
"  try ITLBundleCreator -h for details.\n"
;

const char* DOC_EXTRACTOR=
"Use: ITLBundleExtractor INPUT_BUNDLE [OPTIONS] \n"
"Extract the content of an INScore bundle.\n"
"Version: "
VERSION
"\n\n"
" -- OPTIONS --\n"
"  -o --output  OUTPUT_FILE  Specify the output folder\n"
"  -f --force-overwrite      If the folder exist, overwrites it without asking\n"
"  -k --keepOriginalPath     Recreate the original hierarchy of the bundle\n"
"  -h  --help                Print this message and quit\n"
"\n"
;

const char* USAGE_EXTRACTOR=
"Usage: ITLBundleExtractor INPUT_BUNDLE [OPTIONS] \n"
"  try ITLBundleExtractor -h for details.\n"
;
#endif // DOC_H

