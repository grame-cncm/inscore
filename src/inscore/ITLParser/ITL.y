
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
%token EVAL
%token ERR
%token ENDEXPR ENDSCRIPT

%token VARSTART VARIABLE LEFTPAR RIGHTPAR
%token COLON COMMA POINT HOSTNAME IPNUM

%token EXPRESSION

%token LUASCRIPT
%token JSCRIPT

%token ADD SUB DIV MULT QUEST MIN MAX GREATER GREATEREQ LESS LESSEQ EQ MINUS NEG MODULO ;
%token PREINC PREDEC POSTINC POSTDEC;

%left GREATER GREATEREQ LESS LESSEQ EQ
%left NEG PREINC PREDEC POSTINC POSTDEC MINUS ADD SUB
%left MULT DIV MODULO

 /*%expect 2					/expected shift reduce conflicts, currently from  mathexpr in line 230, 231 (SUB) */

/*------------------------------   types  ------------------------------*/
%type <num> 	number mathbool
%type <real>	FLOAT
%type <str>		STRING FILEPATH PATHSEP IDENTIFIER REGEXP LUASCRIPT JSCRIPT
%type <str>		identifier oscaddress relativeaddress oscpath varname variabledecl hostname
%type <msg>		message
%type <msgList>	messagelist script
%type <p>		param expression 
%type <plist>	params variable eval mathexpr mathmax mathmin
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

typedef void * yyscan_t;

//int VARerror(YYLTYPE* locp, inscore::ITLparser* context, const char*s, const char* var);
int yyerror (const YYLTYPE* locp, inscore::ITLparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int lineno(inscore::ITLparser* context);

#define scanner context->fScanner

using namespace std;

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
			| messagelist messagelistseparator message {	$$ = $1; (*$$)->list().push_back(*$3); delete $3; }
			;
messagelistseparator	: COMMA
						| COLON
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
			| PATHSEP VARSTART varname	{ $$ = new string("/$" + *$3); delete $3; }
			;

urlprefix	: hostname COLON UINT		{ $$ = new inscore::IMessage::TUrl($1->c_str(), context->fInt); delete $1; }
			| IPNUM COLON UINT			{ $$ = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); }
			;

hostname	: HOSTNAME					{ $$ = new string(context->fText); }
			| hostname POINT HOSTNAME	{ *$1 += '.' + context->fText; $$=$1; }
			;

identifier	: IDENTIFIER				{ $$ = new string(context->fText); }
			| HOSTNAME					{ $$ = new string(context->fText); }
			| REGEXP					{ $$ = new string(context->fText); }
			;

//_______________________________________________
// parameters definitions
// eval need a special case since messages are expected as argument
eval		: EVAL				{ $$ = new inscore::IMessage::argslist; 
								  inscore::Sbaseparam * p = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText));
								  $$->push_back(*p); delete p; }

 /* params		: param					{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; }
			| variable				{ $$ = $1; }
			| params variable		{ $1->push_back($2);  $$ = $1; delete $2; }
			| params param			{ $1->push_back(*$2); $$ = $1; delete $2; }
			;
 */

params		: mathexpr				{ $$ = $1; }
			| params mathexpr		{ $1->push_back($2);  $$ = $1; delete $2; }
			;

variable	: VARSTART varname	{ $$ = new inscore::IMessage::argslist;
								  std::string var = "$" + *$2;
								  $$->push_back (context->fReader.resolve($2->c_str(), var.c_str()));
								  delete $2;
								}
			| VARSTART varname POSTINC		{ $$ = new inscore::IMessage::argslist; 
								  			  std::string var = "$" + *$2;
								  			  $$->push_back (context->fReader.resolveinc($2->c_str(), true, var.c_str()));
								  			  delete $2;
								  			}
			| VARSTART varname POSTDEC		{ $$ = new inscore::IMessage::argslist; 
								  			  std::string var = "$" + *$2;
								  			  $$->push_back (context->fReader.resolvedec($2->c_str(), true, var.c_str()));
								  			  delete $2;
								  			}
			| PREINC VARSTART varname		{ $$ = new inscore::IMessage::argslist; 
								  			  std::string var = "$" + *$3;
								  			  $$->push_back (context->fReader.resolveinc($3->c_str(), false, var.c_str()));
								  			  delete $3;
								  			}
			| PREDEC VARSTART varname		{ $$ = new inscore::IMessage::argslist; 
								  			  std::string var = "$" + *$3;
								  			  $$->push_back (context->fReader.resolvedec($3->c_str(), false, var.c_str()));
								  			  delete $3;
								  			}
			| VARSTART LEFTPAR message RIGHTPAR { $$ = new inscore::IMessage::argslist;
								  $$->push_back (context->fReader.resolve(*$3));
								  delete $3;
								}
			;

param	: number				{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<int>($1)); }
		| FLOAT					{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat)); }
		| identifier			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); delete $1; }
		| STRING				{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); }
		| expression			{ $$ = $1;}
		| LEFTPAR messagelist RIGHTPAR	{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*$2)); delete $2; }
		| script			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*$1)); delete $1; }
		;

//_______________________________________________
// math expressions
mathexpr	: param							{ $$ = new inscore::IMessage::argslist; $$->push_back (*$1); delete $1 }
			| variable						{ $$ = $1; }
			| mathexpr ADD mathexpr			{ $$ = context->math().add($1, $3); delete $1; delete $3; }
			| mathexpr SUB mathexpr			{ $$ = context->math().sub($1, $3); delete $1; delete $3;  }
			| MINUS mathexpr				{ $$ = $$ = context->math().minus($2);   delete $2; }
			/* | mathexpr INC					{ $$ = context->math().inc($1); delete $1;} */
			/* | mathexpr DEC					{ $$ = context->math().dec($1); delete $1; } */
			| mathexpr MULT mathexpr		{ $$ = context->math().mult($1, $3); delete $1; delete $3; }
			| mathexpr DIV mathexpr			{ $$ = context->math().div($1, $3);  delete $1; delete $3; }
			| mathexpr MODULO mathexpr		{ $$ = context->math().mod($1, $3);  delete $1; delete $3; }
			| LEFTPAR mathexpr RIGHTPAR 	{ $$ = $2; }
			| MIN LEFTPAR mathmin RIGHTPAR	{ $$ = $3; }
			| MAX LEFTPAR mathmax RIGHTPAR	{ $$ = $3; }
			| LEFTPAR mathbool QUEST mathexpr COLON mathexpr RIGHTPAR { $$ = $2 ? (delete $6, $4) : (delete $4, $6); } 
			;

mathmin 	: mathexpr	mathexpr			{ $$ = context->math().less(*$1, *$2) ? (delete $2, $1) : (delete $1, $2); }
			| mathmin mathexpr				{ $$ = context->math().less(*$1, *$2) ? (delete $2, $1) : (delete $1, $2); }
			;

mathmax 	: mathexpr	mathexpr			{ $$ = context->math().greater(*$1, *$2) ? (delete $2, $1) : (delete $1, $2); }
			| mathmax mathexpr				{ $$ = context->math().greater(*$1, *$2) ? (delete $2, $1) : (delete $1, $2); }
			;

mathbool 	: mathexpr						{ $$ = context->math().tobool(*$1); 		delete $1;}
			| NEG mathexpr					{ $$ = (context->math().tobool(*$2) ? 0 : 1); delete $2; }
			| mathexpr EQ mathexpr 			{ $$ = context->math().equal(*$1, *$3);     delete $1; delete $3; }
			| mathexpr GREATER mathexpr 	{ $$ = context->math().greater(*$1, *$3);   delete $1; delete $3; }
			| mathexpr GREATEREQ mathexpr 	{ $$ = context->math().greatereq(*$1, *$3); delete $1; delete $3; }
			| mathexpr LESS mathexpr 		{ $$ = context->math().less(*$1, *$3); 	  	delete $1; delete $3; }
			| mathexpr LESSEQ mathexpr 		{ $$ = context->math().lesseq(*$1, *$3); 	delete $1; delete $3; }
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

expression		: EXPRESSION	{ $$ = context->fReader.parseExpr(context->fText, context->fExprStartLine, yyloc.first_column + 1 - context->fText.length());}
			;

%%

namespace inscore 
{

SIMessageList ITLparser::parse()
{
	fParseSucceed = !yyparse (this);
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
	cerr << "error line " << loc->last_line + context->fLine << " col " << loc->first_column << ":" << s << endl;
#else
	context->fReader.error (loc->last_line + context->fLine, loc->first_column, s);
#endif
	return 0;
}
