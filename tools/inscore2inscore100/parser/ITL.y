
%{

#include <iostream>
#include <sstream>
#include <string>
#include "ITLparser.h"
#include "IMessage.h"
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
%token ERR
%token ENDEXPR

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
%type <str>		identifier oscaddress oscpath msgstring varname
%type <msg>		message
%type <p>		param
%type <plist>	params varvalue 
%type <msgList>	script


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
expr		: message  			{ context->fReader.add(*$1); delete $1; }
			| variable ENDEXPR	{}
			| script			{ if (*$1) {
										for (unsigned int i=0; i < (*$1)->list().size(); i++)
											context->fReader.add((*$1)->list()[i]);
									}
									delete $1;
								}
			;

//_______________________________________________
script		: LUASCRIPT			{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
									*$$ = context->fReader.luaEval(context->fText.c_str());
								}
			| JSCRIPT			{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
									*$$ = context->fReader.jsEval(context->fText.c_str(), yylloc.last_line);
								}
			;

//_______________________________________________
message		: oscaddress params	ENDEXPR				{}// $$ = new inscore::SIMessage (inscore::IMessage::create(*$1, *$2, inscore::IMessage::TUrl())); delete $1; delete $2; }
			| oscaddress msgstring ENDEXPR			{}// $$ = new inscore::SIMessage (inscore::IMessage::create(*$1, *$2));  delete $1; delete $2; }
			| oscaddress msgstring params ENDEXPR	{}// $$ = new inscore::SIMessage (inscore::IMessage::create(*$1, *$2)); (*$$)->add(*$3); delete $1; delete $2; delete $3; }
			;

oscaddress	: oscpath				{ $$ = $1; }
			| oscaddress oscpath	{ *$1 += *$2; $$ = $1; delete $2; }
			;

oscpath		: PATHSEP identifier	{ $$ = new string("/" + *$2); delete $2; }
			;

identifier	: IDENTIFIER		{ $$ = new string(context->fText); }
			| REGEXP			{ $$ = new string(context->fText); }
			;

msgstring	: MSG				{ $$ = new string(context->fText); }
			| IDENTIFIER		{ $$ = new string(context->fText); }
			;

params		: param				{}// $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; }
			| params param		{}// $1->push_back(*$2); $$ = $1; delete $2; }
			| varvalue			{}// $$ = $1; }
			| params varvalue	{}// $1->push_back($2);  $$ = $1; delete $2; }
			;

varvalue	: VARSTART varname	{}// $$ = new inscore::IMessage::argslist;
//								  std::string var = "$" + *$2;
//								  $$->push_back (context->fReader.resolve($2->c_str(), var.c_str()));
//								  delete $2;
//								}
			;

param		: number			{ } // $$ = new inscore::Sbaseparam(new inscore::IMsgParam<int>($1)); }
			| FLOAT				{ } // $$ = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat)); }
			| STRING			{ } // $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); }
			;


//_______________________________________________
variable	: varname EQUAL number	{ context->fReader.variable($1->c_str(), $3);					delete $1; }
			| varname EQUAL FLOAT	{ context->fReader.variable($1->c_str(),  context->fFloat);		delete $1; }
			| varname EQUAL STRING	{ context->fReader.variable($1->c_str(), context->fText.c_str()); delete $1; }
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
