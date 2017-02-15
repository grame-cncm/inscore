
%{

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "IExprParser.h"
#include "IExprParse.hpp"
#include "ExprFactory.h"

#ifdef WIN32
#pragma warning (disable : 4267 4065 4100)
#endif

%}


%pure-parser
%locations
%defines
%error-verbose
%parse-param { inscore::IExprParser* context }
%lex-param { void* scanner  }

/*------------------------------ tokens ------------------------------*/
%union
{
	int	num;
	float	real;
	std::string* str;
	std::vector<std::string>* strList;
	inscore::SIExprArg* argbase;
}

%token EXPR_START EXPR_END
%token VARSTART AMPERSAND TILDE

%token QUOTEDSTRING STRING
%token IDENTIFIER

/*------------------------------   types  ------------------------------*/
%type <str>		identifier string
%type <str>		operator
%type <strList>		variable
%type <argbase>		exprArg arg expression

%{

#include <iostream>
#include <sstream>
#include <string>

#include "IExprParser.h"
#include "IExprParse.hpp"

#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

typedef void * yyscan_t;

int yyerror (const YYLTYPE* locp, inscore::IExprParser *context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int lineno(inscore::IExprParser* context);


#define CHECKVAR(VAR, SIZE) if(VAR ->size() != SIZE) { yyerror(&yyloc, context, "wrong variable content"); YYABORT; }

#define scanner context->fScanner

using namespace std;

//namespace inscore
//{

%}

%%

//_______________________________________________
// relaxed simple IExpression format specification
//_______________________________________________
start		: expression			{context->fRootNode = inscore::SIExprArg(*$1); delete $1;}
			;

//_______________________________________________
//misc

identifier	: IDENTIFIER			{ $$ = new string(context->fText); }
			;

string		: identifier
			| STRING				{ $$ = new string(context->fText);}
			| QUOTEDSTRING			{ $$ = new string(context->fText);}
			;

variable	: VARSTART identifier	{ $$ = context->readVar($2, lineno(context));}
			;


//_______________________________________________
// expression declaration
expression	: EXPR_START operator exprArg exprArg EXPR_END	{ $$ = new inscore::SIExprArg( inscore::ExprFactory::createExpr(*$2,*$3,*$4)); delete $2; delete $3; delete $4;}
			| EXPR_START exprArg EXPR_END					{ $$ = $2; }
			| EXPR_START operator variable EXPR_END			{ CHECKVAR($3, 2) $$ = new inscore::SIExprArg( inscore::ExprFactory::createExpr(*$2,
																														inscore::ExprFactory::createArg( $3->at(0) ) ,
																														inscore::ExprFactory::createArg( $3->at(1) ))); delete $2; delete $3;}
//			| EXPR_START variable exprArg EXPR_END			{ CHECKVAR($2, 2) $$ = new inscore::SIExprArg( inscore::ExprFactory::createExpr($2->at(0),$2->at(1), *$3)); delete $2; delete $3;}
			;

operator	: identifier
			| variable	{ CHECKVAR($1, 1) $$ = new string($1->at(0)); delete $1; }
			;

exprArg		: arg
			| AMPERSAND arg	{ $$ = $2; (*$$)->switchToDynamic(); }
			| TILDE arg	{ $$ = $2; (*$$)->switchToCopy(); }
			| expression
			;

arg			: string	{ $$ = new inscore::SIExprArg( inscore::ExprFactory::createArg(*$1) ); delete $1; }
			| variable	{ CHECKVAR($1, 1) $$ = new inscore::SIExprArg( inscore::ExprFactory::createArg($1->at(0)) ); delete $1; }
			;

%%

//} // end namespace

namespace inscore 
{



SIExprArg IExprParser::parse()
{
	yyparse (this);
	return fRootNode;
}
}

using namespace inscore;

int lineno (IExprParser* context)
{
	return context->fLine + context->fLineOffset;
}

int yyerror(const YYLTYPE* loc, IExprParser* context, const char*s) {
#ifdef NO_OSCSTREAM
	cerr << "error line: " << loc->last_line + context->fLineOffset << " col: " << loc->first_column + (loc->last_line==1 ? context->fColumnOffset : 1) << ": " << s << endl;
#else
	ITLErr << "error line: " << loc->last_line + context->fLineOffset << " col: " << loc->first_column + (loc->last_line==1 ? context->fColumnOffset : 1) <<  ": " << s << ITLEndl;
#endif
	return 0;
}
