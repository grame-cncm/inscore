
%{

#include <iostream>
#include <sstream>
#include <string>

#include "ITLparser.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "ITLparse.hpp"

#ifdef WIN32
#pragma warning (disable : 4267 4100)
#endif

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
%token IDENTIFIER OSCADDRESS
%token EQUAL
%token REGEXP
%token FILEPATH
%token STRING
%token EVAL
%token ERR
%token ENDEXPR ENDSCRIPT

%token VARSTART VARIABLE VARIABLEPOSTINC VARIABLEPOSTDEC VARIABLEPREINC VARIABLEPREDEC LEFTPAR RIGHTPAR
%token COLON COMMA POINT HOSTNAME IPNUM

%token EXPRESSION

%token LUASCRIPT
%token JSCRIPT

%token ADD SUB DIV MULT QUEST MIN MAX GREATER GREATEREQ LESS LESSEQ EQ MINUS NEG MODULO ;
 /*%token PREINC PREDEC POSTINC POSTDEC;*/

%left GREATER GREATEREQ LESS LESSEQ EQ
%left NEG PREINC PREDEC POSTINC POSTDEC MINUS ADD SUB
%left MULT DIV MODULO

 /*%expect 2					/expected shift reduce conflicts, currently from  mathexpr in line 230, 231 (SUB) */

/*------------------------------   types  ------------------------------*/
%type <num> 	number mathbool
%type <real>	FLOAT
%type <str>		STRING FILEPATH IDENTIFIER REGEXP LUASCRIPT JSCRIPT
%type <str>		oscaddress identifier relativeaddress varname variabledecl hostname
%type <msg>		message
%type <msgList>	messagelist script
%type <p>		param expression sparam
%type <plist>	params variable msgvariable eval mathexpr mathmax mathmin
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
char *ITLget_text (yyscan_t yyscanner );

#define scanner context->fScanner

using namespace std;
// ----------------------------------------------------------------------------------------
// debug utility
#define YDEBUG	0
#if YDEBUG
static  void debug (const char * str, string context) {
	cout << "YACC " << str << " : " << context << endl;
}
#else 
#define debug(a, b)
#endif

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
expr		: message  ENDEXPR		{ context->fReader.add(*$1); debug("===> message", (*$1)->toString()); delete $1; }
			| variabledecl ENDEXPR	{ delete $1; }
			| script				{	if (*$1) {
										for (unsigned int i=0; i < (*$1)->list().size(); i++)
											context->fReader.add((*$1)->list()[i]);
										}
										delete $1;
									}
			| ENDSCRIPT				{ YYACCEPT; }
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

message		: address					{ $$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc)); (*$$)->setUrl($1->fUrl); delete $1; debug ("message address", "");}
			| address params			{ $$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc, *$2, $1->fUrl)); delete $1; delete $2; debug ("message address params", "sep");}
			| address eval LEFTPAR messagelist RIGHTPAR
										{	$$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc, *$2, $1->fUrl));
											(*$$)->add(*$4); delete $1; delete $2; delete $4; }
			| address eval variable		{	$$ = new inscore::SIMessage(inscore::IMessage::create($1->fOsc, *$2, $1->fUrl));
											(*$$)->add(*$3); delete $1; delete $2; delete $3; }
			;

messagelist : message					{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
											(*$$)->list().push_back(*$1);
											debug ("messagelist single", (*$1)->toString()); delete $1; }
			| messagelist messagelistseparator message {	$$ = $1; (*$$)->list().push_back(*$3); delete $3; debug ("messagelist", "sep"); }
			;
messagelistseparator	: COMMA			{ debug ("messagelistseparator", ","); }
						| COLON
						;

//_______________________________________________
// address specification (extends osc spec.)
address		: oscaddress				{ $$ = new inscore::ITLparser::address (context->fText); }
			| relativeaddress			{ $$ = new inscore::ITLparser::address (*$1); delete $1;}
			| urlprefix oscaddress		{ $$ = new inscore::ITLparser::address (*$2, *$1); debug("urladdress", *$2); delete $1; delete $2; }
			;

oscaddress  : OSCADDRESS				{ $$ = new string(context->fText); debug("oscaddress", *$$);}
			;

relativeaddress	: POINT oscaddress		{ $$ = new string("." +*$2);  delete $2; }
			;

urlprefix	: hostname UINT				{ $$ = new inscore::IMessage::TUrl($1->c_str(), context->fInt); delete $1; debug("urlprefix name", *$$); }
			| IPNUM COLON UINT			{ $$ = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); debug("urlprefix ip", *$$); }
			;

hostname	: HOSTNAME					{ $$ = new string(context->fText); debug("hostname", *$$); }
			;

identifier	: IDENTIFIER				{ $$ = new string(context->fText); }
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

params		: sparam				{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; debug("params: sparam", "");}
			| params sparam			{ $1->push_back(*$2);  $$ = $1; delete $2; debug("params: params sparam", "");}
			| mathexpr				{ $$ = $1;  debug("params: mathexpr", ""); }
			| params mathexpr		{ $1->push_back($2);  $$ = $1; delete $2; debug("params: params mathexpr", "");}
			;

variable	: VARIABLE				{ $$ = new inscore::IMessage::argslist; debug("variable", context->fText.c_str()); 
									  $$->push_back (context->fReader.resolve(context->fText.c_str(), lineno(context))); }
			| VARIABLEPOSTINC		{ $$ = new inscore::IMessage::argslist; debug("variable postinc", context->fText);
								  			  $$->push_back (context->fReader.resolveinc(context->fText.c_str(), true, lineno(context)));
								  	}
			| VARIABLEPOSTDEC		{ $$ = new inscore::IMessage::argslist; debug("variable postdec", context->fText);
								  			  $$->push_back (context->fReader.resolvedec(context->fText.c_str(), true, lineno(context)));
								  	}
			| VARIABLEPREINC		{ $$ = new inscore::IMessage::argslist; debug("variable preinc", context->fText);
								  			  $$->push_back (context->fReader.resolveinc(context->fText.c_str(), false, lineno(context)));
								  	}
			| VARIABLEPREDEC		{ $$ = new inscore::IMessage::argslist; debug("variable predec", context->fText);
								  			  $$->push_back (context->fReader.resolvedec(context->fText.c_str(), false, lineno(context)));
								  	}
			;

msgvariable	: VARSTART LEFTPAR message RIGHTPAR { $$ = new inscore::IMessage::argslist; debug("variable msg", "");
								  $$->push_back (context->fReader.resolve(*$3));
								  delete $3;
								}
			;

param	: number				{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<int>($1));  debug("int param", ""); }
		| FLOAT					{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat));  debug("float param", ""); }
		| identifier			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText));  debug("identifier param", context->fText); delete $1; }
		| STRING				{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText));  debug("string param", context->fText); }
		;

sparam	: expression			{ $$ = $1;}			/* params excluded from math expression */
		| LEFTPAR messagelist RIGHTPAR	{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*$2)); delete $2; debug("messagelist param", ""); }
		| script			{ $$ = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*$1)); debug("script param", ""); delete $1; }
		;

//_______________________________________________
// math expressions
mathexpr	: param							{ $$ = new inscore::IMessage::argslist; $$->push_back (*$1); delete $1; debug("mathexpr param", ""); }
			| variable						{ $$ = $1; debug("mathexpr variable", ""); }
			| msgvariable					{ $$ = $1; debug("mathexpr msgvariable", ""); }
			| mathexpr ADD mathexpr			{ $$ = context->math().add($1, $3); delete $1; delete $3; debug("mathexpr", "ADD"); }
			| mathexpr SUB mathexpr			{ $$ = context->math().sub($1, $3); delete $1; delete $3; debug("mathexpr", "SUB"); }
			| MINUS mathexpr				{ $$ = $$ = context->math().minus($2);   delete $2; debug("mathexpr", "MINUS"); }
			| mathexpr MULT mathexpr		{ $$ = context->math().mult($1, $3); delete $1; delete $3; debug("mathexpr", "MULT");  }
			| mathexpr DIV mathexpr			{ $$ = context->math().div($1, $3);  delete $1; delete $3; debug("mathexpr", "DIV"); }
			| mathexpr MODULO mathexpr		{ $$ = context->math().mod($1, $3);  delete $1; delete $3; debug("mathexpr", "MOD"); }
			| LEFTPAR mathexpr RIGHTPAR 	{ $$ = $2; }
			| MIN LEFTPAR mathmin RIGHTPAR	{ $$ = $3; debug("mathexpr", "MIN"); }
			| MAX LEFTPAR mathmax RIGHTPAR	{ $$ = $3; debug("mathexpr", "MAX"); }
			| LEFTPAR mathbool QUEST mathexpr COLON mathexpr RIGHTPAR { $$ = $2 ? (delete $6, $4) : (delete $4, $6); debug("mathexpr", "?"); } 
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
			;

//_______________________________________________
// misc
number		: UINT					{ $$ = context->fInt; }
			| INT					{ $$ = context->fInt; }
			;

//_______________________________________________
// expression declaration

expression	: EXPRESSION	{ $$ = context->fReader.parseExpr(context->fText, context->fExprStartLine, yyloc.first_column + 1 - context->fText.length());}
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
	return context->fLine + context->fLineOffset; 
}

int yyerror(const YYLTYPE* loc, ITLparser* context, const char*s) {
#ifdef NO_OSCSTREAM
	cerr << "error line " << loc->last_line + context->fLineOffset << " col " << loc->first_column << ": " << s << endl;
#else
	context->fReader.error (loc->last_line + context->fLineOffset, loc->first_column, s);
#endif
	return 0;
}
