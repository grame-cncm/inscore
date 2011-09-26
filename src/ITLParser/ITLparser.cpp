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

#include "ITLparser.h"
#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

#define yyleng				ITLleng
#define yyin				ITLin
#define yyrestart			ITLrestart
#define yy_current_buffer	ITL_current_buffer
#define yy_delete_buffer	ITL_delete_buffer
#define yy_scan_string		ITL_scan_string

//#define yyDebug
#ifdef yyDebug
#define YYDEBUG	1
extern int yydebug;
#endif

#ifndef WIN32
static void yyunput(int, char*) __attribute__((unused));
#endif

#include "ITLparse.c++"

using namespace std;

inscore::TScripting* gScripter = 0;

namespace inscore 
{

//--------------------------------------------------------------------------
void ITLparser::start () 
{
//	gMessageList =  new inscore::IMessageList;
	gScripter =  new inscore::TScripting;
	setlocale(LC_NUMERIC, "C");
	ITLlineno = 1;
}

void ITLparser::stop () 
{
	setlocale(LC_NUMERIC, 0);
}

void ITLparser::clean(TScripting* s) 
{
	if (s) {
		if (s->messages()) s->messages()->clear();
		delete s;
	}
}

//--------------------------------------------------------------------------
int ITLparser::parse (FILE *fd) 
{
	if (!fd) {
#ifndef NO_OSCSTREAM
		ITLErr << "ITL parser: invalid file descriptor" << ITLEndl;
#else
		cerr << "ITL parser: invalid file descriptor" << endl;
#endif
		return(-1);
	}

	yyin = fd;
#ifdef yyDebug
	yydebug = 1;
#endif
	int res = ITLparse();

	yyrestart(yyin);
	BEGIN(INITIAL);
	stop();
	return res;
}

//--------------------------------------------------------------------------
int ITLparser::parse (const char *filename) 
{
	int res;
	if( !filename ) return -1; // parse error
	FILE * fd = fopen(filename,"r");
	if (fd == NULL){
		string msg = "ITL parser: cannot open file \""; 
		msg += filename;
		msg += "\"";
#ifndef NO_OSCSTREAM
		ITLErr << msg << ITLEndl;
#else
		cerr << msg << endl;
#endif
		return(-1);
	}

	res = parse(fd);
	fclose(fd);
	return res;
}

//--------------------------------------------------------------------------
IMessageList* ITLparser::readstring (const char * buffer) 
{
	if (!buffer) return false;		// error for null buffers
	if (!*buffer) return false;		// error for empty buffers

	start();
	YY_BUFFER_STATE b;
    /* Copy string into new buffer and Switch buffers */
    b = yy_scan_string (buffer);

    /*Parse the string*/
    int ret = ITLparse();

    /*Delete the new buffer*/
    yy_delete_buffer(b);
	yyrestart(yyin);

	BEGIN(INITIAL);
	stop();

	if (ret == 0) return gScripter->messages();
 	clean(gScripter);
	gScripter = 0;
	return 0;
}

//--------------------------------------------------------------------------
IMessageList* ITLparser::readfile (FILE* fd) 
{
	start();
	if (parse (fd) == 0) return gScripter->messages();
 	clean(gScripter);
	gScripter = 0;
	return 0;
}

//--------------------------------------------------------------------------
IMessageList* ITLparser::readfile (const char * file)  
{
	start();
	if (parse (file) == 0) return gScripter->messages();
 	clean(gScripter);
	gScripter = 0;
	return 0;
}

} // end namespace

