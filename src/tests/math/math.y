
%{

#include <iostream>
#include <sstream>
#include <string>

#include "mathparser.h"

%}


%pure-parser
%locations
%defines
%error-verbose
%parse-param { mathparser* context }
%lex-param { void* scanner  }

/*------------------------------ tokens ------------------------------*/
%union
{
	int		num;
	float	real;
	char * 	str;
}

%token EOL
%token INT FLOAT
%token ADD SUB MULT DIV INC DEC QUEST COLON
%token LEFTPAR RIGHTPAR ERR


%left ADD SUB
%left MULT DIV


/*------------------------------   types  ------------------------------*/
%type <num> 	INT
%type <real>	FLOAT mathexpr
%type <str>		ADD SUB MULT DIV

%{

#include <iostream>
#include <sstream>
#include <string>

int yyerror (const YYLTYPE* locp, mathparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);

#define scanner context->fScanner

using namespace std;
#if 0
void trace (const char* op, float a, float b) { cout << op << " " << a << " " << b << endl; }
#else
#define trace(a,b,c)
#endif

%}

%%

//_______________________________________________
// 
//_______________________________________________
start		: mathexpr		{ cout << $1 << endl; }
			;

//_______________________________________________
// math expressions definition
//_______________________________________________
mathexpr	: INT						{ $$ = context->fInt; }
			| FLOAT						{ $$ = context->fFloat; }
			| mathexpr ADD mathexpr		{ $$ = $1 + $3; trace("add", $1, $3); }
			| mathexpr SUB mathexpr		{ $$ = $1 - $3; trace("sub", $1, $3); }
			| mathexpr MULT mathexpr	{ $$ = $1 * $3; trace("mult", $1, $3); }
			| mathexpr DIV mathexpr		{ $$ = $1 / $3; trace("div", $1, $3); }
			| LEFTPAR mathexpr RIGHTPAR { $$ = $2; trace("()", $2, 0); }
			| LEFTPAR mathexpr QUEST mathexpr COLON mathexpr RIGHTPAR 
										{ $$ = ($2 == 0) ? $6 : $4; trace("?", $4, $6); }
			;

%%

void mathparser::parse()		{ yyparse (this); }

int yyerror(const YYLTYPE* loc, mathparser* context, const char*s) {
	cerr << "error line " << loc->last_line << " col " << loc->first_column << ": " << s << endl;
	return 0;
}
