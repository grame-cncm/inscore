
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
	inscore::ITLparser::address*	addr;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage::TUrl*		url;
	inscore::SIMessage*				msg;
    inscore::SIMessageList*			msgList;
}

%token INT UINT FLOAT
%token IDENTIFIER
%token EQUAL
%token REGEXP
%token PATHSEP BACKPATH
%token FILEPATH
%token STRING
%token WATCH EVAL
%token ERR
%token ENDEXPR ENDSCRIPT

%token VARSTART LEFTPAR RIGHTPAR
%token COLON COMMA POINT HOSTNAME IPNUM

%token EXPRESSION

%token LUASCRIPT
%token JSCRIPT

/*------------------------------   types  ------------------------------*/
%type <num> 	number
%type <real>	FLOAT
%type <str>		STRING FILEPATH PATHSEP IDENTIFIER REGEXP LUASCRIPT JSCRIPT
%type <str>		identifier oscaddress relativeaddress oscpath varname variabledecl hostname
%type <msg>		message
%type <msgList>	messagelist script
%type <p>		param expression
%type <plist>	params variable eval
%type <url>		urlprefix
%type <addr>	address

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

//#define ERROR_CB() [&yyloc, &context](const char *s) -> void {yyerror(&yyloc, context, s);}
//#define HANDLE_READER_ERROR() if(context->fReader.hasFailed()){ yyerror(&yyloc, context, context->fReader.errorlog().c_str()); YYABORT; }

typedef void * yyscan_t;

int VARerror(YYLTYPE* locp, inscore::ITLparser* context, const char*s, const char* var);
int yyerror (const YYLTYPE* locp, inscore::ITLparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int lineno(inscore::ITLparser* context);

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
// expression of the script language
//_______________________________________________
expr		: message  ENDEXPR		{ context->fReader.add(*$1); delete $1; }
			| variabledecl ENDEXPR	{ delete $1; }
			| script			{	if (*$1) {
										for (unsigned int i=0; i < (*$1)->list().size(); i++)
											context->fReader.add((*$1)->list()[i]);
									}
									delete $1;
								}
			| ENDSCRIPT			{ YYACCEPT; }
			;

//_______________________________________________
// javascript and lua support
//_______________________________________________
script		: LUASCRIPT			{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
									*$$ = context->fReader.luaEval(context->fText.c_str());
								}
			| JSCRIPT			{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
									*$$ = context->fReader.jsEval(context->fText.c_str(), yylloc.last_line);
								}
			;

//_______________________________________________
// messages specification (extends osc spec.)
//____________________________________expArg expression___________

message		: address					{ $$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc)); (*$$)->setUrl($1->fUrl); delete $1; }
			| address params			{ $$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc, *$2, $1->fUrl)); delete $1; delete $2; }
			| address eval LEFTPAR messagelist RIGHTPAR
										{	$$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc, *$2, $1->fUrl));
											(*$$)->add(*$4); delete $1; delete $2; delete $4; }
			| address eval variable		{	$$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc, *$2, $1->fUrl));
											(*$$)->add(*$3); delete $1; delete $2; delete $3; }
			;

messagelist : message					{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
											(*$$)->list().push_back(*$1);
											delete $1; }
			| messagelist COMMA message {	$$ = $1; (*$$)->list().push_back(*$3); delete $3; }
			;

//_______________________________________________
// address specification (extends osc spec.)
address		: oscaddress				{ $$ = new inscore::ITLparser::address (*$1); delete $1;}
			| relativeaddress			{ $$ = new inscore::ITLparser::address (*$1); delete $1;}
			| urlprefix oscaddress		{ $$ = new inscore::ITLparser::address (*$2, *$1); delete $1; delete $2; }
			;

oscaddress	: oscpath					{ $$ = $1; }
			| oscaddress oscpath		{ *$1 += *$2; $$ = $1; delete $2; }
			;

relativeaddress	: POINT oscaddress		{ $$ = new string("." + *$2); delete $2; }
			;

oscpath		: PATHSEP identifier		{ $$ = new string("/" + *$2); delete $2; }
			| PATHSEP WATCH				{ $$ = new string("/" + context->fText); }
			| PATHSEP VARSTART varname	{ $$ = new string("/$" + *$3); delete $3; }
			;

urlprefix	: hostname COLON UINT		{ $$ = new inscore::IMessage::TUrl($1->c_str(), context->fInt); delete $1; }
			| IPNUM COLON UINT			{ $$ = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); }
			;

hostname	: HOSTNAME					{ $$ = new string(context->fText); }
			| hostname POINT HOSTNAME	{ *$1 += '.' + context->fText; $$=$1; }
			;

identifier		: IDENTIFIER		{ $$ = new string(context->fText); }
			| HOSTNAME		{ $$ = new string(context->fText); }
			| REGEXP		{ $$ = new string(context->fText); }
			;

//_______________________________________________
// parameters definitions
// eval need a special case since messages are expected as argument
eval		: EVAL				{ $$ = new inscore::IMessage::argslist; 
								  inscore::Sbaseparam * p = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText));
								  $$->push_back(*p); delete p; }

params		: param							{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; }
			| variable				{ $$ = $1; }
			| params variable				{ $1->push_back($2);  $$ = $1; delete $2; }
			| params param					{ $1->push_back(*$2); $$ = $1; delete $2; }
			;

variable	: VARSTART varname	{ $$ = new inscore::IMessage::argslist;
								  std::string var = "$" + *$2;
								  $$->push_back (context->fReader.resolve($2->c_str(), var.c_str()));
								  delete $2;
								}
			| VARSTART LEFTPAR message RIGHTPAR { $$ = new inscore::IMessage::argslist;
								  $$->push_back (context->fReader.resolve(*$3));
								  delete $3;
								}
			;

param		: number			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<int>($1)); }
		| FLOAT				{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat)); }
		| identifier			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); delete $1; }
		| STRING			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); }
		| expression			{ $$ = $1;}
		| LEFTPAR messagelist RIGHTPAR	{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*$2)); delete $2; }
		| script			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*$1)); delete $1; }
		;


//_______________________________________________
// variable declaration
variabledecl : varname EQUAL params	{ $$=$1; context->fReader.variable($1->c_str(), $3); delete $3;}
			;

varname		: IDENTIFIER			{ $$ = new string(context->fText); }
			| HOSTNAME				{ $$ = new string(context->fText); }
			;

//_______________________________________________
// misc
number		: UINT					{ $$ = context->fInt; }
			| INT					{ $$ = context->fInt; }
			;

//_______________________________________________
// expression declaration

expression		: EXPRESSION	{ $$ = context->fReader.parseExpr(context->fText, yyloc.last_line - count(context->fText.begin(), context->fText.end(), '\n'), yyloc.first_column + 1 - context->fText.length());}
			;

%%

//} // end namespace

namespace inscore 
{

SIMessageList ITLparser::parse()
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

int yyerror(const YYLTYPE* loc, ITLparser* context, const char*s) {
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
