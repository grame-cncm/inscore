/*
  INScore Project

  Copyright (C) 2009,2016  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/
#ifndef DOC_H
#define DOC_H


const char* DOC=
"Bundle creator use:       IBundle INPUT_SCRIPT [OPTIONS] \n"
"Package an Inscore scritp and all its dependencies into a compressed bundle \n\n"

"Bundle extractor use:     IBundle INPUT_BUNDLE -e [OPTIONS] \n"
"Extract the content of an ibundle archive. \n\n"

" --- OPTIONS ---\n"
"  -o --output   OUTPUT_FILE Specify the output file\n"
"  -f --force-overwrite      If the file exist, overwrites it without asking\n"
"  -h  --help                Print this message and quit\n"
"  -v  --version             Print version and quit\n"
"Bundle creator specific:\n"
"  -vv --verbose OPTION      Print processing logs\n"
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

