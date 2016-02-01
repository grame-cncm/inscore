#ifndef DOC_H
#define DOC_H

#ifndef VERSION
#define VERSION "1.0"
#endif

const char* DOC=
"Bundle creator use:       IBundle INPUT_SCRIPT [OPTIONS] \n"
"Package an Inscore scritp and all its dependencies into a compressed bundle \n\n"

"Bundle extractor use:     IBundle INPUT_BUNDLE -e [OPTIONS] \n"
"Extract the content of an ibundle archive. \n\n"

"Version: "
VERSION
"\n\n"
" --- OPTIONS ---\n"
"  -o --output   OUTPUT_FILE Specify the output file\n"
"  -f --force-overwrite      If the file exist, overwrites it without asking\n"
"  -h  --help                Print this message and quit\n"
"Bundle creator specific:\n"
"  -v --verbose  OPTION      Print processing logs\n"
"                hierarchy   Details dependencies for each scripts\n"
"  -l --rootpath PATH        Set default root path to PATH\n"
"  -js --parse-javascript    Javascript sections are parsed to detect ressources\n"
"      --fail-safe           See further for details about the fail-sage mode\n"
"Bundle extractor specific:\n"
"  -e --extract              Extract the content of an ibundle archive\n"
"  -k --keepOriginalPath     Recreate the original hierarchy of the bundle\n"
"\n"
" --- FAIL-SAFE MODE ---\n"
"While the standard mode automatically detects dependencies, the fail-safe mode\n"
"allows to manually specify which files should be included in the bundle without\n"
"parsing or modifying any script."
"The input file should be a list of the files (one file per line) and the first\n"
"file should be the launched script."

" --- EXAMPLES ---\n"
"IBundle script.inscore\n"
"   will bundle script.inscore into script.itlbundle \n"
"   with all the needed ressources.\n"
"\n"
"IBundle script.ibundle -e\n"
"   will extract script.ibundle into the folder \"script/\" \n"
"\n"
;

const char* USAGE=
"Usage: IBundle INPUT_FILE [OPTIONS] \n"
"  try IBundle -h for details.\n"
;
#endif // DOC_H

