
%{

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
 
#include "IParser2.h"
#include "inscoreparse.hpp"
#include "inscorelex.hpp"

#ifdef WIN32
#pragma warning (disable : 4267 4100)
#endif

using namespace std;
using namespace inscore2;

%}

%pure-parser
%locations
%error-verbose
%parse-param { inscore2::IParser* context }
%lex-param { void* scanner  }

/*------------------------------ tokens ------------------------------*/
%token ACOS
%token ACOSH
%token ADD
%token ANYADDR
%token ASIN
%token ASINH
%token ATAN
%token ATANH
%token CBRT
%token CEIL
%token COLON
%token COMMA
%token COS
%token COSH
%token DIV
%token ENDSCRIPT
%token ENDSTATEMENT
%token EOL
%token EQ
%token EQUAL
%token ERR
%token EXP
%token EXPANDID
%token FLOAT
%token FLOOR
%token GREATER
%token GREATEREQ
%token HAS
%token IDENTIFIER
%token INT
%token JSCRIPT
%token LDOTS
%token LEFTBRACE
%token LEFTBRACKET
%token LEFTPAR
%token LESS
%token LESSEQ
%token LETTERS
%token LOG
%token LOG10
%token LOG2
%token MAX
%token MIN
%token MODULO
%token MULT
%token NEG
%token POW
%token QUEST
%token RAND
%token REGEXP
%token RIGHTBRACE
%token RIGHTBRACKET
%token RIGHTPAR
%token ROUND
%token SIN
%token SINH
%token SLASH
%token SQRT
%token STRING
%token SUB
%token TAN
%token TANH
%token UINT
%token VARIABLE
%token WITH

%left UINT INT FLOAT
%left LETTERS IDENTIFIER STRING EXPANDID REGEXP VARIABLE
%left QUEST NEG EQ GREATER GREATEREQ LESS LESSEQ MIN MAX HAS	
%left ADD SUB MODULO DIV MULT
%left SIN COS TAN ASIN ACOS ATAN SINH COSH TANH ASINH ACOSH ATANH 
%left EXP LOG LOG10 LOG2 POW SQRT CBRT 
%left CEIL FLOOR ROUND RAND 
 

%left OP MFUN  PAR SEQ
%left COMMA SLASH DECL LDECL LEFTPAR LEFTBRACE

/*------------------------------   types  ------------------------------*/
%union
{
	inscore2::INode* 		treeptr;
}

%type <treeptr> 	identifier number string tree variable operator mfunction varname

%start start

%{

int yyerror (const YYLTYPE* locp, IParser* context, const char*s);

#define scanner context->fScanner

// ----------------------------------------------------------------------------------------
// debug utility
#define YDEBUG	1
#if YDEBUG
#define ydebug std::cerr << "Y " 
#define yend std::endl
#else 
class nodebug {	public: template<typename T> nodebug& operator << (T) { return *this;} };
#define yend ""
nodebug ydebug;
#endif

%}

%%

//_______________________________________________
//
// INScore v.2.1 scripting language specification
//_______________________________________________
start		: statement 
			| start statement
			; 

//_______________________________________________
statement	: tree  ENDSTATEMENT		{ context->add ($1); }
			| vardecl ENDSTATEMENT		{ } 
			| JSCRIPT 					{ context->add (context->javascript (context->fText)); }
			| ENDSCRIPT					{ YYACCEPT; }
			;

//_______________________________________________
tree		: identifier			{ $$ = $1; }
			| string				{ $$ = $1; }
			| number				{ $$ = $1; }
			| variable				{ $$ = $1; }
			| operator				{ $$ = $1; }					%prec OP
			| mfunction tree		{ $$ = context->seq($1, $2); }	%prec MFUN
			| SLASH tree			{ $$ = context->slash($2); }
			| ANYADDR				{ $$ = context->slash(context->regexp ("*")); }
			| tree tree				{ $$ = context->seq($1, $2); }  %prec SEQ
			| tree COMMA tree		{ $$ = context->par($1, $3); }  %prec PAR
			| LEFTPAR tree RIGHTPAR { $$ = $2; }
			;

identifier	: LETTERS		{ $$ = context->create (context->fText); }
			| IDENTIFIER	{ $$ = context->create (context->fText); }
			| EXPANDID		{ $$ = context->expand (context->fText); }
			| REGEXP		{ $$ = context->regexp (context->fText); }
			;

string		: STRING		{ $$ = context->create (context->fText); }
			;

vardecl	    : identifier EQUAL tree {context->declare ($1->getName(), $3); delete $1; }  %prec DECL
			;

pushvardecl	: identifier EQUAL tree { context->pushEnv(); context->declare ($1->getName(), $3); delete $1; }  %prec LDECL
			;

variable	: varname					{ $$ = context->variable ($1->getName()); delete $1; } 
			| varname LEFTBRACE varlist  RIGHTBRACE { $$ = context->variable ($1->getName()); context->popEnv(); delete  $1; }
 			;

varlist	    : pushvardecl				{ }
			| varlist COMMA vardecl 	{ } 
			;

varname		: VARIABLE		{ $$ = context->create (context->fText); }
			;

mfunction	: SIN			{ $$ = context->operation (INode::kSin); }
			| COS			{ $$ = context->operation (INode::kCos); }
			| TAN			{ $$ = context->operation (INode::kTan); }
			| ASIN			{ $$ = context->operation (INode::kASin); }
			| ACOS			{ $$ = context->operation (INode::kACos); }
			| ATAN			{ $$ = context->operation (INode::kATan); }
			| SINH			{ $$ = context->operation (INode::kSinh); }
			| COSH			{ $$ = context->operation (INode::kCosh); }
			| TANH			{ $$ = context->operation (INode::kTanh); }
			| ASINH			{ $$ = context->operation (INode::kASinh); }
			| ACOSH			{ $$ = context->operation (INode::kACosh); }
			| ATANH			{ $$ = context->operation (INode::kATanh); }

			| EXP			{ $$ = context->operation (INode::kExp); }
			| LOG			{ $$ = context->operation (INode::kLog); }
			| LOG10			{ $$ = context->operation (INode::kLog10); }
			| LOG2			{ $$ = context->operation (INode::kLog2); }
			| POW			{ $$ = context->operation (INode::kPow); }
			| SQRT			{ $$ = context->operation (INode::kSqrt); }
			| CBRT			{ $$ = context->operation (INode::kCbrt); }


			| CEIL			{ $$ = context->operation (INode::kCeil); }
			| FLOOR			{ $$ = context->operation (INode::kFloor); }
			| ROUND			{ $$ = context->operation (INode::kRound); }
			;

operator	: ADD			{ $$ = context->operation (INode::kAdd); }
			| SUB			{ $$ = context->operation (INode::kSub); }
			| DIV			{ $$ = context->operation (INode::kDiv); }
			| MULT			{ $$ = context->operation (INode::kMult); }
			| MODULO		{ $$ = context->operation (INode::kModulo); }
			| QUEST			{ $$ = context->operation (INode::kQuest); }
			| NEG			{ $$ = context->operation (INode::kNeg); }
			| EQ			{ $$ = context->operation (INode::kEq); }
			| GREATER		{ $$ = context->operation (INode::kGreater); }
			| GREATEREQ		{ $$ = context->operation (INode::kGreatereq); }
			| LESS			{ $$ = context->operation (INode::kLess); }
			| LESSEQ		{ $$ = context->operation (INode::kLesseq); }
			| MIN			{ $$ = context->operation (INode::kMin); }
			| MAX			{ $$ = context->operation (INode::kMax); }
			| HAS			{ $$ = context->operation (INode::kHas); }
			| RAND			{ $$ = context->operation (INode::kRand); }
			;

number		: UINT			{ $$ = context->create (context->fText, INode::kInt); }
			| INT			{ $$ = context->create (context->fText, INode::kInt); }
			| FLOAT			{ $$ = context->create (context->fText, INode::kFloat); }
			;

%%

namespace inscore2
{

bool IParser::parse()
{
	return !yyparse (this);
}

} // end namespace


int yyerror(const YYLTYPE* loc, IParser* context, const char*s) {
	cerr << "error line " << context->fLine << " column " << context->fColumn  << ": " << s << endl;
	context->error(context->fLine, context->fColumn, s);
	return 0;
}
