%{

#include <iostream>
#include <string>
#include <assert.h>

#include "IMessageStream.h"
#include "TScripting.h"
#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

extern inscore::TScripting* gScripter;

typedef union {
	public:
	int		num;
	float	real;
	std::string* str;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage*			msg;
	inscore::IMessageList*		msgList;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED
#define YYERROR_VERBOSE
#define VARERROR(str, var)	{ VARerror(str, var); YYABORT; }
#define LOOPERROR(n)		{ LOOPerror(n); YYABORT; }

#include "ITLparse.h++"
#include "ITLlex.c++"

int ITLerror (const char*s);
int VARerror (const char*s, const char* var);
int LOOPerror(int line);
int	ITLwrap()		{ return(1); }

using namespace std;
namespace inscore
{

%}

//%pure_parser

%start ITLfile

/*------------------------------ tokens ------------------------------*/
%token INT
%token UINT
%token FLOAT
%token IDENTIFIER
%token EQUAL
%token MAPIDENTIFIER
%token REGEXP
%token PATHSEP
%token STRING
%token MSG
%token HYPHEN
%token ENDEXPR

%token LPAR
%token RPAR
%token SEP
%token LOOP
%token LOOPIDENTIFIER
%token LOOPREGEXP
%token VARSTART

%token LUA

/*------------------------------   types  ------------------------------*/
%type <num> 	INT count number
%type <real>	FLOAT
%type <str>		STRING MSG PATHSEP IDENTIFIER MAPIDENTIFIER REGEXP LUA
%type <str>		identifier oscaddress oscpath msgstring varname
%type <str>		loopidentifier loopaddress looppath
%type <msg>		message loopmessage
%type <p>		param
%type <plist>	params

%%

//_______________________________________________
// relaxed simple ITL format specification
//_______________________________________________
ITLfile		: expr
			| ITLfile expr
			;

//_______________________________________________
expr		: message  			{ gScripter->add($1); }
			| variable ENDEXPR
			| loop
			| lua
			| HYPHEN			{ ITLerror("unexpected '-' char"); YYABORT; }
			;

//_______________________________________________
lua			: LUA				{ cout << "got lua script: " << ITLtext << endl; }
//_______________________________________________
message		: oscaddress params	ENDEXPR				{	$$ = new inscore::IMessage(*$1, "", *$2); delete $1; delete $2; }
			| oscaddress msgstring ENDEXPR			{	$$ = new inscore::IMessage(*$1, *$2);  delete $1; delete $2; }
			| oscaddress msgstring params ENDEXPR	{	$$ = new inscore::IMessage(*$1, *$2, *$3); delete $1; delete $2; delete $3; }
			;

oscaddress	: oscpath				{ $$ = $1; }
			| oscaddress oscpath	{ *$1 += *$2; $$ = $1; delete $2; }
			;

oscpath		: PATHSEP identifier	{ $$ = new string("/" + *$2); delete $2; }
			;

identifier	: IDENTIFIER		{ $$ = new string(ITLtext); }
			| REGEXP			{ $$ = new string(ITLtext); }
			;

msgstring	: MSG				{ $$ = new string(ITLtext); }
			| IDENTIFIER		{ $$ = new string(ITLtext); }
			;

params		: param				{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; }
			| params param		{ $1->push_back(*$2); $$ = $1; delete $2; }
			;

param		: number			{ $$ = new Sbaseparam(new inscore::IMsgParam<int>($1)); }
			| FLOAT				{ $$ = new Sbaseparam(new inscore::IMsgParam<float>(atof(ITLtext))); }
			| STRING			{ $$ = new Sbaseparam(new inscore::IMsgParam<std::string>(ITLtext)); }
			| VARSTART varname	{ $$ = gScripter->resolve($2->c_str()); if (!$$) { VARERROR("unknown variable ", $2->c_str()) }; delete $2; }
			;


//_______________________________________________
variable	: varname EQUAL number	{ gScripter->variable($1->c_str(), $3);						delete $1; }
			| varname EQUAL FLOAT	{ gScripter->variable($1->c_str(), (float)atof(ITLtext));	delete $1; }
			| varname EQUAL STRING	{ gScripter->variable($1->c_str(), ITLtext);				delete $1; }
			;

varname		: IDENTIFIER			{ $$ = new string(ITLtext); }
			;

number		: UINT					{ $$ = atoi(ITLtext); }
			| INT					{ $$ = atoi(ITLtext); }
			;
			
//_______________________________________________
loop		: loopstart SEP loopbody RPAR ENDEXPR	{ int n = gScripter->endLoop(); if (n) { LOOPERROR(n); } }
			;
			
loopstart	: LOOP LPAR varname SEP count 			{ gScripter->startLoop($3->c_str(), $5, ITLlineno); delete $3; }
			;

loopbody	: looped			
			| loopbody looped
			;

looped		: loopmessage				{ gScripter->add($1); }
			| loop
			;

loopmessage	: loopaddress params	ENDEXPR			{	$$ = new inscore::IMessage(*$1, "", *$2); delete $1; delete $2; }
			| loopaddress msgstring ENDEXPR			{	$$ = new inscore::IMessage(*$1, *$2);  delete $1; delete $2; }
			| loopaddress msgstring params ENDEXPR	{	$$ = new inscore::IMessage(*$1, *$2, *$3); delete $1; delete $2; delete $3; }
			;

loopaddress	: looppath				{ $$ = $1; }
			| loopaddress looppath	{ *$1 += *$2; $$ = $1; delete $2; }
			;

looppath	: PATHSEP loopidentifier	{ $$ = new string("/" + *$2); delete $2; }
			;

loopidentifier : 
			  identifier				{ $$ = $1; }
			| LOOPIDENTIFIER			{ $$ = new string(ITLtext); }
			| LOOPREGEXP				{ $$ = new string(ITLtext); }

count		: UINT						{ $$ = atoi(ITLtext); }
			;

%%

} // end namespace

using namespace inscore;
int ITLerror(const char*s) {
	YY_FLUSH_BUFFER;
#ifdef NO_OSCSTREAM
	cerr << "error line " << ITLlineno << ": " << s << endl;
#else
	ITLErr << "error line " << ITLlineno << ": " << s << ITLEndl;
#endif
	ITLlineno = 1;
	return 0; //err;
}

int VARerror(const char*s, const char* var) {
	YY_FLUSH_BUFFER;
#ifdef NO_OSCSTREAM
	cerr << "error line " << ITLlineno << ": " << s << var << endl;
#else
	ITLErr << "error line " << ITLlineno << ": " << s << var << ITLEndl;
#endif
	ITLlineno = 1;
	return 0; //err;
}

int LOOPerror(int line) {
	YY_FLUSH_BUFFER;
#ifdef NO_OSCSTREAM
	cerr << "error line " << ITLlineno << ": unknown variable in loop started line " << line << endl;
#else
	ITLErr << "error line " << ITLlineno << ": unknown variable in loop started line " << line << ITLEndl;
#endif
	ITLlineno = 1;
	return 0; //err;
}
