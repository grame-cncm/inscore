
%{
/*

  INScore Project

  Copyright (C) 2019  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

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
%token ACOS ACOSH
%token ADD
%token ANYADDR
%token ASIN ASINH ATAN ATANH
%token CBRT
%token CEIL
%token COLON
%token COMMA
%token COS COSH
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
%token GREATER GREATEREQ
%token HAS
%token IDENTIFIER
%token INT
%token JSCRIPT
%token LDOTS
%token LEFTBRACE LEFTBRACKET LEFTPAR
%token LESS  LESSEQ
%token LETTERS
%token LOG LOG10 LOG2
%token MAX MIN
%token MODULO MULT
%token NEG
%token POW
%token QUEST
%token RAND
%token REGEXP
%token RIGHTBRACE RIGHTBRACKET RIGHTPAR
%token ROUND SIN SINH
%token SLASH
%token SQRT
%token STRING
%token SUB
%token TAN
%token TANH
%token URLPREFIX
%token VARIABLE
%token WITH

%token STIME MSTIME

%left INT FLOAT
%left URLPREFIX LETTERS IDENTIFIER STRING EXPANDID REGEXP VARIABLE LDOTS
%left QUEST NEG EQ GREATER GREATEREQ LESS LESSEQ MIN MAX HAS	
%left ADD SUB MODULO DIV MULT
%left SIN COS TAN ASIN ACOS ATAN SINH COSH TANH ASINH ACOSH ATANH 
%left EXP LOG LOG10 LOG2 POW SQRT CBRT 
%left CEIL FLOOR ROUND RAND 
 

%left PAR SEQ OP MFUN
%left COMMA  DECL LDECL LEFTPAR LEFTBRACE SLASH

/*------------------------------   types  ------------------------------*/
%union
{
	inscore2::INode* 		treeptr;
}

%type <treeptr> 	identifier number delay string tree variable operator prefix mfunction varname exval expandval

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
			| prefix				{ $$ = $1; }
            | number                { $$ = $1; }
            | expandval             { $$ = $1; }
            | delay                 { $$ = $1; }
			| variable				{ $$ = $1; }
			| operator				{ $$ = $1; }					%prec OP
			| mfunction tree		{ $$ = context->seq($1, $2); }	%prec MFUN
			| SLASH identifier		{ $$ = context->slash($2); }
			| SLASH variable		{ $$ = context->slash($2); }
			| ANYADDR				{ $$ = context->slash(context->create ("*")); }
			| tree tree				{ $$ = context->seq($1, $2); }  %prec SEQ
			| tree COMMA tree		{ $$ = context->par($1, $3); }  %prec PAR
			| LEFTPAR tree RIGHTPAR { $$ = $2; }
			;

identifier	: LETTERS		{ $$ = context->create (context->fText); }
			| IDENTIFIER	{ $$ = context->create (context->fText); }
			| EXPANDID		{ $$ = context->expand (context->fText); }
			| REGEXP		{ $$ = context->create (context->fText); }
			;

prefix		: URLPREFIX		{ $$ = context->prefix (context->fText); }
			;

string		: STRING		{ $$ = context->create (context->fText); }
			;

exval		: LEFTBRACKET number LDOTS number RIGHTBRACKET	{ $$ = context->expandVal ($2, $4); }
			;

expandval	: exval									{ $$ = $1; }
			| exval LEFTBRACE varlist RIGHTBRACE	{ $$ = context->setEnv($1); context->popEnv(); }
			;

 //listval		: LEFTBRACKET number LDOTS number RIGHTBRACKET	{ $$ = context->create ($2->getValue()+"..."+$4->getValue()); delete $2; delete $4; }
			;

vardecl	    : identifier EQUAL tree {context->declare ($1->getValue(), $3); delete $1; }  %prec DECL
			;

pushvardecl	: identifier EQUAL tree { context->pushEnv(); context->declare ($1->getValue(), $3); delete $1; }  %prec LDECL
			;

variable	: varname					{ $$ = context->variable ($1->getValue()); delete $1; } 
			| varname LEFTBRACE varlist  RIGHTBRACE { $$ = context->variable ($1->getValue()); context->popEnv(); delete  $1; }
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

delay       : STIME         { $$ = context->delay (context->fText); }
            | MSTIME        { $$ = context->delay (context->fText); }
            ;

number      : INT           { $$ = context->create (context->fText, INode::kInt); }
            | FLOAT         { $$ = context->create (context->fText, INode::kFloat); }
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
