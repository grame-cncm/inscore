/*
  Interlude Library
  Copyright (C) 2009,2010  Grame

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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifdef WIN32
# pragma warning (disable : 4786 4244 4018 4065)
# pragma warning (disable : 4996)
# pragma warning (disable : 4102)
#endif

#include <iostream>
#include <locale.h>

#include "mapparser.h"
#include "mapreader.h"
#include "ITLError.h"
inscore::mapreader * gReader;

#define yyleng				itlmapleng
#define yyin				itlmapin
#define yyrestart			itlmaprestart
#define yy_current_buffer	itlmap_current_buffer
#define yy_delete_buffer	itlmap_delete_buffer
#define yy_scan_string		itlmap_scan_string

//#define yyDebug
#ifdef yyDebug
#define YYDEBUG	1
extern int yydebug;
#endif

#ifndef WIN32
static void yyunput(int, char*) __attribute__((unused));
#endif

#include "mapparse.c++"

using namespace std;

namespace inscore 
{

//--------------------------------------------------------------------------
void mapparser::start () 
{
	gReader = fReader;
	setlocale(LC_NUMERIC, "C");
	yylineno = 1;
}
void mapparser::stop () 
{
	setlocale(LC_NUMERIC, 0);
}

//--------------------------------------------------------------------------
int mapparser::parse (FILE *fd) 
{
	if (!fd) {
		const char* msg = "parse mapping: invalid file descriptor"; 
		ITLErr << msg << ITLEndl;
		return(-1);
	}

	start();
	yyin = fd;
#ifdef yyDebug
	yydebug = 1;
#endif
	int res = yyparse();

	yyrestart(yyin);
	BEGIN(INITIAL);
	stop();
	return res;
}

//--------------------------------------------------------------------------
int mapparser::parse (const char *filename) 
{
	int res;
	if( !filename ) return -1; // parse error
	FILE * fd = fopen(filename,"r");
	if (fd == NULL){
		string msg = "parse mapping: cannot open file \""; 
		msg += filename;
		msg += "\"";
		ITLErr << msg << ITLEndl;
		return(-1);
	}

	res = parse(fd);
	fclose(fd);
	return res;
}

//--------------------------------------------------------------------------
bool mapparser::readstring (const char * buffer) 
{
	if (!buffer) return false;		// error for null buffers
	if (!*buffer) return false;		// error for empty buffers

	start();
	YY_BUFFER_STATE b;
    /* Copy string into new buffer and Switch buffers */
    b = yy_scan_string (buffer);

    /*Parse the string*/
    int ret = yyparse();

    /*Delete the new buffer*/
    yy_delete_buffer(b);
	yyrestart(yyin);

	BEGIN(INITIAL);
	stop();
 	return ret==0;
}

//--------------------------------------------------------------------------
bool mapparser::readfile (FILE* fd) 
{
	int ret = parse (fd);
 	return ret==0;
}

//--------------------------------------------------------------------------
bool mapparser::readfile (const char * file)  
{
	int ret = parse (file);
 	return ret==0;
}

} // end namespace

