
%{

#include <iostream>
#include <sstream>
#include <string>

#include "itlbundleparser.h"
#include "itlbundleparse.hpp"


%}


%pure-parser
%locations
%defines
%error-verbose
%parse-param { itlbundle::itlbundleparser* context }
%lex-param { void* scanner  }

/*------------------------------ tokens ------------------------------*/
%union
{
	int		num;
	float	real;
	std::string* str;
}

%token INT UINT FLOAT
%token IDENTIFIER
%token REGEXP
%token PATHSEP LEFTPAR RIGHTPAR
%token EQUAL NOTEQUAL NOT GREATER GREATEREQUAL LOWER LOWEREQUAL
%token LAND LOR LNOT
%token STRING QUOTEDSTRING
%token ARGID ADDR

/*------------------------------   types  ------------------------------*/
%type <num> 	number argID
%type <real>	FLOAT
%type <str>	STRING QUOTEDSTRING IDENTIFIER REGEXP PATHSEP
%type <str>	oscaddress oscpath identifier string

%{

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "itlbundleparser.h"
#include "filterparse.hpp"

typedef void * yyscan_t;

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int yyerror(const YYLTYPE* loc, itlbundle::itlbundleparser* context, const char*s);

#define scanner context->fScanner


%}

%%

//_______________________________________________
// address specification (extends osc spec.)

oscaddress	: oscpath
		| oscaddress oscpath		{ *$1 += *$2; $$ = $1; delete $2; }
		;

oscpath		: PATHSEP identifier		{ $$ = new std::string("/" + *$2); delete $2; }
		;

identifier	: IDENTIFIER			{ $$ = new std::string(context->fText); }
		| REGEXP			{ $$ = new std::string(context->fText); }
		;

//_______________________________________________
// misc
number		: UINT				{ $$ = context->fInt; }
			| INT				{ $$ = context->fInt; }
			;

string	: QUOTEDSTRING		{$$ = new std::string(context->fText);}
		| IDENTIFIER		{$$ = new std::string(context->fText);}
		;

argID		: ARGID				{ $$ = context->fInt; }
		;

%%

namespace itlbundle
{

std::vector<std::string> *filterparser::parse()
{
	yyparse (this);
	return context->fRessourcesList;
}

}//End namespace

using namespace itlbundle;

int yyerror(const YYLTYPE* loc, itlbundle::itlbundleparser *context, const char*s) {

	cerr << "error line: " << loc->last_line + context->fLine << " col: " << loc->first_column << ": " << s << endl;
	return 0;
}


