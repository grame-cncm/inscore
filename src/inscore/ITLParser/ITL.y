
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

%token VARSTART VARIABLE LEFTPAR RIGHTPAR
%token VARIABLEPOSTINC VARIABLEPOSTDEC VARIABLEPREINC VARIABLEPREDEC
%token COLON COMMA POINT HOSTNAME IPNUM

%token EXPRESSION

%token JSCRIPT

%token ADD SUB DIV MULT QUEST MIN MAX GREATER GREATEREQ LESS LESSEQ EQ MINUS NEG MODULO ;

%left GREATER GREATEREQ LESS LESSEQ EQ NEQ
%left NEG PREINC PREDEC POSTINC POSTDEC MINUS ADD SUB
%left MULT DIV MODULO

 /*%expect 2					/expected shift reduce conflicts, currently from  mathexpr in line 230, 231 (SUB) */

/*------------------------------   types  ------------------------------*/
%type <num> 	number mathbool
%type <real>	FLOAT
%type <str>		STRING FILEPATH IDENTIFIER REGEXP JSCRIPT
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
#include <stdexcept>

#include "ITLparser.h"
#include "ITLparse.hpp"

#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

typedef void * yyscan_t;

//int VARerror(YYLTYPE* locp, inscore::ITLparser* context, const char*s, const char* var);
void matherror (inscore::ITLparser* context, const std::invalid_argument& e);
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
expr		: message  ENDEXPR		{ context->fReader.process(*$1); delete $1; }
			| variabledecl ENDEXPR	{ delete $1; }
			| script			{	if (*$1) {
										for (unsigned int i=0; i < (*$1)->list().size(); i++)
											context->fReader.process((*$1)->list()[i]);
									}
									delete $1;
								}
			| ENDSCRIPT			{ YYACCEPT; }
			;

//_______________________________________________
// javascript and lua support
//_______________________________________________
script		: JSCRIPT			{	$$ = new inscore::SIMessageList (inscore::IMessageList::create());
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

oscaddress  : OSCADDRESS				{ $$ = new string(context->fText); debug("oscaddress", *$$);}
			;

relativeaddress	: POINT oscaddress		{ $$ = new string("." + *$2); delete $2; }
			;

urlprefix	: hostname  UINT			{ $$ = new inscore::IMessage::TUrl($1->c_str(), context->fInt); delete $1; debug("urlprefix", *$1); }
			| STRING COLON UINT			{ $$ = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); debug("urlprefix", context->fText); }
			| IPNUM COLON UINT			{ $$ = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); debug("urlprefix", context->fText);}
			;

hostname	: HOSTNAME					{ $$ = new string(context->fText); debug("HOSTNAME", context->fText); }
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

params		: sparam				{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; debug("params: sparam", "");}
			| params sparam			{ $1->push_back(*$2);  $$ = $1; delete $2; debug("params: params sparam", "");}
			| mathexpr				{ $$ = $1;  debug("params: mathexpr", ""); }
			| params mathexpr		{ $1->push_back($2);  $$ = $1; delete $2; debug("params: params mathexpr", "");}
			;

variable	: VARIABLE				{ $$ = new inscore::IMessage::argslist; debug("variable", context->fText.c_str()); 
									  $$->push_back (context->fReader.resolve(context->fText.c_str(), lineno(context))); }
			| VARIABLEPOSTINC		{ $$ = new inscore::IMessage::argslist; debug("variable postinc", context->fText);
								  		try { $$->push_back (context->fReader.resolveinc(context->fText.c_str(), true, lineno(context))); }
										catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }
								  	}
			| VARIABLEPOSTDEC		{ $$ = new inscore::IMessage::argslist; debug("variable postdec", context->fText);
								  		try { $$->push_back (context->fReader.resolvedec(context->fText.c_str(), true, lineno(context))); }
										catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }
								  	}
			| VARIABLEPREINC		{ $$ = new inscore::IMessage::argslist; debug("variable preinc", context->fText);
								  		try { $$->push_back (context->fReader.resolveinc(context->fText.c_str(), false, lineno(context))); }
										catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }
								  	}
			| VARIABLEPREDEC		{ $$ = new inscore::IMessage::argslist; debug("variable predec", context->fText);
								  		try { $$->push_back (context->fReader.resolvedec(context->fText.c_str(), false, lineno(context))); }
										catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }
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
			| mathexpr ADD mathexpr			{ try { $$ = context->math().add($1, $3); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }
												delete $1; delete $3; debug("mathexpr", "ADD"); }
			| mathexpr SUB mathexpr			{ try { $$ = context->math().sub($1, $3);  } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }
											  	delete $1; delete $3; debug("mathexpr", "SUB"); }
			| MINUS mathexpr				{ try { $$ = context->math().minus($2);  } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }; 
												delete $2; debug("mathexpr", "MINUS"); }
			| mathexpr MULT mathexpr		{ try { $$ = context->math().mult($1, $3);  } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; }; 
												delete $1; delete $3; debug("mathexpr", "MULT");  }
			| mathexpr DIV mathexpr			{ try { $$ = context->math().div($1, $3); } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; };  
												delete $1; delete $3; debug("mathexpr", "DIV"); }
			| mathexpr MODULO mathexpr		{ try { $$ = context->math().mod($1, $3); } catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; };  
											delete $1; delete $3; debug("mathexpr", "MOD"); }
			| LEFTPAR mathexpr RIGHTPAR 	{ $$ = $2; }
			| MIN LEFTPAR mathmin RIGHTPAR	{ $$ = $3; debug("mathexpr", "MIN"); }
			| MAX LEFTPAR mathmax RIGHTPAR	{ $$ = $3; debug("mathexpr", "MAX"); }
			| LEFTPAR mathbool QUEST mathexpr COLON mathexpr RIGHTPAR { $$ = $2 ? (delete $6, $4) : (delete $4, $6); debug("mathexpr", "?"); } 
			;
				
mathmin 	: mathexpr						{ try { $$ = context->math().min(*$1); } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; }
			| mathmin mathexpr				{ try { inscore::IMessage::argslist* min = context->math().min(*$2); 
												$$ = context->math().less(*$1, *min) ? (delete min, $1) :  (delete $1, min); } 
											  	catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $2; }
			;

mathmax 	: mathexpr						{ try { $$ = context->math().max(*$1); } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; }
			| mathmax mathexpr				{ try { inscore::IMessage::argslist* max = context->math().max(*$2);
												$$ = context->math().greater(*$1, *max) ? (delete max, $1) :  (delete $1, max); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $2; }
			;

mathbool 	: mathexpr						{ try { $$ = context->math().tobool(*$1); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; }
			| NEG mathexpr					{ try { $$ = (context->math().tobool(*$2) ? 0 : 1); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $2; }
			| mathexpr EQ mathexpr 			{ try { $$ = context->math().equal(*$1, *$3); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; delete $3; }
			| mathexpr NEQ mathexpr 		{ try { $$ = !context->math().equal(*$1, *$3); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; delete $3; }
			| mathexpr GREATER mathexpr 	{ try { $$ = context->math().greater(*$1, *$3); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; delete $3; }
			| mathexpr GREATEREQ mathexpr 	{ try { $$ = context->math().greatereq(*$1, *$3); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; delete $3; }
			| mathexpr LESS mathexpr 		{ try { $$ = context->math().less(*$1, *$3); } 
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; delete $3; }
			| mathexpr LESSEQ mathexpr 		{ try { $$ = context->math().lesseq(*$1, *$3); }
												catch (const std::invalid_argument& e) { matherror(context, e); YYABORT; } delete $1; delete $3; }
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

expression	: EXPRESSION	{ $$ = context->fReader.parseExpr(context->fText, context->fExprStartLine, yyloc.first_column + 1 - context->fText.length()); }
			;

%%

namespace inscore 
{

bool ITLparser::parse()
{
	return !yyparse (this);
//	return fReader.messages();
}
}

using namespace inscore;

int lineno (ITLparser* context)	
{ 
	YYLTYPE* loc = (YYLTYPE*)context->fScanner;
	return loc->last_line + context->fLine; 
}

void matherror(ITLparser* context, const std::invalid_argument& e) {
	yyerror (0, context, e.what());
}

int yyerror(const YYLTYPE* loc, ITLparser* context, const char*s) {
	int l = context->fLine + context->fLineOffset;
#if defined(NO_OSCSTREAM) || defined(IBUNDLE)
	cerr << "error line " << l << " col " << context->fColumn << ": " << s << endl;
#else
	context->fReader.error (l, context->fColumn, s);
#endif
	return 0;
}
