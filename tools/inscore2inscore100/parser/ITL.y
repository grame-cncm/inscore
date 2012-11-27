
%{

#include <iostream>
#include <sstream>
#include <string>
#include "ITLparser.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "ITLparse.hpp"

%}


%pure-parser
%locations
%defines
%error-verbose
%parse-param { inscore::ITLparser* context }
%lex-param { void* scanner  }

/*------------------------------ tokens ------------------------------*/
%union
{
	int		num;
	float	real;
	std::string* str;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::SIMessage*				msg;
	inscore::SIMessageList*		msgList;
}

%token INT UINT FLOAT
%token IDENTIFIER
%token EQUAL
%token MAPIDENTIFIER
%token REGEXP
%token PATHSEP
%token STRING
%token MSG
%token ERR
%token ENDEXPR
%token COMMENTSTR SPACE EOL

%token LPAR
%token RPAR
%token SEP
%token LOOP
%token LOOPIDENTIFIER
%token LOOPREGEXP
%token VARSTART

%token LUASCRIPT
%token JSCRIPT

/*------------------------------   types  ------------------------------*/
%type <num> 	INT number
%type <real>	FLOAT
%type <str>		STRING MSG PATHSEP IDENTIFIER MAPIDENTIFIER REGEXP LUASCRIPT JSCRIPT
%type <str>		identifier oscaddress oscpath msgstring varname variable script
%type <msg>		message
%type <p>		param
%type <plist>	params 

%{

#include <iostream>
#include <sstream>
#include <string>

#include "ITLparser.h"
#include "ITLparse.hpp"

#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

#define VARERROR(str, var)	{ VARerror(&yyloc, context, str, var); YYABORT; }

typedef void * yyscan_t;

int VARerror(YYLTYPE* locp, inscore::ITLparser* context, const char*s, const char* var);
int yyerror (YYLTYPE* locp, inscore::ITLparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int lineno(inscore::ITLparser* context);

inscore::SIMessage watchMessage (inscore::SIMessage msg);

#define scanner context->fScanner

using namespace std;

//namespace inscore
//{

%}

%%

//_______________________________________________
// relaxed simple ITL format specification
//_______________________________________________
start		: expr
			| start expr
			;

//_______________________________________________
expr		: message  			{ cout << *$1; }
			| variable ENDEXPR	{ cout << *$1; }
			| script
			| COMMENTSTR		{ cout << context->fText.c_str(); }
			| SPACE				{ cout << context->fText.c_str(); }
			| EOL				{ cout << context->fText.c_str(); }
			;

//_______________________________________________
script		: LUASCRIPT			{ cout << "<? lua " << context->fText.c_str() << "?>;"; }
			| JSCRIPT			{ cout << "<? javascript " << context->fText.c_str() << "?>;"; }
			;

//_______________________________________________
message		: oscaddress params	ENDEXPR				{ $$ = new inscore::SIMessage (inscore::IMessage::create(*$1, *$2, inscore::IMessage::TUrl())); }
			| oscaddress msgstring ENDEXPR			{ $$ = new inscore::SIMessage (inscore::IMessage::create(*$1, *$2)); }
			| oscaddress msgstring params ENDEXPR	{ inscore::SIMessage msg = inscore::IMessage::create(*$1, *$2); 
														msg->add(*$3);
														inscore::SIMessage watch = watchMessage (msg);
														$$ = new inscore::SIMessage (watch ? watch : msg);
													}
			;

oscaddress	: oscpath				{ $$ = $1; }
			| oscaddress oscpath	{ *$1 += *$2; $$ = $1; }
			;

oscpath		: PATHSEP identifier	{ $$ = new string("/" + *$2); }
			;

identifier	: IDENTIFIER		{ $$ = new string(context->fText); }
			| REGEXP			{ $$ = new string(context->fText); }
			;

msgstring	: MSG				{ $$ = new string(context->fText); }
			| IDENTIFIER		{ $$ = new string(context->fText); }
			;

params		: param				{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); }
			| params param		{ $1->push_back(*$2); $$ = $1; }
			;

param		: number			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<int>($1)); }
			| FLOAT				{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat)); }
			| STRING			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); }
			| VARSTART varname  { $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>("$" + *$2)); }
			;


//_______________________________________________
variable	: varname EQUAL number	{ std::stringstream s; s << *$1 << "=" << $3 << ";";  $$ = new string(s.str()); }
			| varname EQUAL FLOAT	{ std::stringstream s; s << *$1 << "=" << context->fFloat << ";";  $$ = new string(s.str()); }
			| varname EQUAL STRING	{ $$ = new string(*$1 + " = " + context->fText.c_str()); }
			;

varname		: IDENTIFIER			{ $$ = new string(context->fText); }
			;

number		: UINT					{ $$ = context->fInt; }
			| INT					{ $$ = context->fInt; }
			;

%%

//} // end namespace

namespace inscore 
{

IMessageList* ITLparser::parse() 
{
	yyparse (this);
	return fReader.messages();
}
}

using namespace inscore;

int lineno (ITLparser* context)	
{ 
	YYLTYPE* loc = (YYLTYPE*)context->fScanner;
	return loc->last_line + context->fLine; 
}

int yyerror(YYLTYPE* loc, ITLparser* context, const char*s) {
#ifdef NO_OSCSTREAM
	cerr << "error line: " << loc->last_line + context->fLine << " col: " << loc->first_column << ": " << s << endl;
#else
	ITLErr << "error line: " << loc->last_line + context->fLine << " col: " << loc->first_column << ": " << s << ITLEndl;
#endif
	return 0;
}

int VARerror(YYLTYPE* loc, ITLparser* context, const char*s, const char* var) {
#ifdef NO_OSCSTREAM
	cerr << "error line " << loc->last_line + context->fLine << ": " << s << var << endl;
#else
	ITLErr << "error line " << loc->last_line + context->fLine << ": " << s << var << ITLEndl;
#endif
	return 0;
}
