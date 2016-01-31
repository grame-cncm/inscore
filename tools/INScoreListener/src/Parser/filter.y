
%{

#include <iostream>
#include <sstream>
#include <string>

#include "filterparser.h"
#include "filterparse.hpp"
#include "../OSCFilter.h"


%}


%pure-parser
%locations
%defines
%error-verbose
%parse-param { inscorelistener::filterparser* context }
%lex-param { void* scanner  }

/*------------------------------ tokens ------------------------------*/
%union
{
	int		num;
	float	real;
	std::string* str;
	inscorelistener::OSCFilterNode* filterNode;
	inscorelistener::OSCFilterExprArg* filterArg;
	inscorelistener::OSCFilterExpr::Operator filterOperator;

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
%type <real>	number FLOAT
%type <str>	STRING QUOTEDSTRING IDENTIFIER REGEXP PATHSEP
%type <str>	oscaddress oscpath identifier string
%type <filterNode> filterExpr filterExprCore filter
%type <filterOperator> filterOp
%type <filterArg> arg

%{

#include <iostream>
#include <sstream>
#include <string>

#include "filterparser.h"
#include "filterparse.hpp"

typedef void * yyscan_t;

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int yyerror(const YYLTYPE* loc, inscorelistener::filterparser* context, const char*s);

#define scanner context->fScanner


%}

%%
//_______________________________________________
// filter specification

filter		: filterExpr					{ $$ = $1; context->fFilterRoot = $$; }
			| filterExpr LAND filter		{ $$ = inscorelistener::OSCFilterLogical::andFilter( $1, $3); context->fFilterRoot = $$; }
			| filterExpr LOR filter			{ $$ = inscorelistener::OSCFilterLogical::orFilter( $1, $3); context->fFilterRoot = $$; }
			;

filterExpr		: filterExprCore
				| LNOT filterExprCore		{ $$ = $2; $$->setNot(); }

filterExprCore	: ADDR EQUAL oscaddress		{ $$ = new inscorelistener::OSCFilterAddress(*$3); delete $3; }
				| arg filterOp arg			{ $$ = new inscorelistener::OSCFilterExpr($2, *$1, *$3); delete $1; delete $3;}
				| LEFTPAR filter RIGHTPAR	{ $$ = $2; }
				;

filterOp		: EQUAL						{ $$ = inscorelistener::OSCFilterExpr::kEQUAL;}
				| NOTEQUAL					{ $$ = inscorelistener::OSCFilterExpr::kNOTEQUAL;}
				| GREATER					{ $$ = inscorelistener::OSCFilterExpr::kGREATER;}
				| GREATEREQUAL				{ $$ = inscorelistener::OSCFilterExpr::kGREATEREQUAL;}
				| LOWER						{ $$ = inscorelistener::OSCFilterExpr::kLOWER;}
				| LOWEREQUAL				{ $$ = inscorelistener::OSCFilterExpr::kLOWEREQUAL;}
				;


//_______________________________________________
// Args specification

arg		: ARGID				{ $$ = inscorelistener::OSCFilterExprArg::fromArg(context->fInt); }
		| string			{ $$ = inscorelistener::OSCFilterExprArg::fromString(*$1); delete $1;}
		| number			{ $$ = inscorelistener::OSCFilterExprArg::fromNbr($1); }
		;

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
number		: UINT				{ $$ = (float)context->fInt; }
			| INT				{ $$ = (float)context->fInt; }
			| FLOAT				{ $$ = context->fFloat;}
			;

string	: QUOTEDSTRING		{$$ = new std::string(context->fText);}
		| IDENTIFIER		{$$ = new std::string(context->fText);}
		;

%%

namespace inscorelistener
{

inscorelistener::OSCFilter* filterparser::parse()
{
	yyparse (this);
	return new OSCFilter(fFilterRoot);
}

}//End namespace

using namespace inscorelistener;

int yyerror(const YYLTYPE* loc, filterparser* context, const char*s) {

	std::cerr << "error col: " << loc->first_column << ": " << s << std::endl;
	return 0;
}


