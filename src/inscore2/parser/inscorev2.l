%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno

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

#ifdef WIN32
#pragma warning (disable : 4267 4100 4244)
#endif

#include <iostream>
#include <fstream>
#include <string>

#include "IParser2.h"
#include "inscoreparse.hpp"

#define YY_NO_UNISTD_H
#define YY_NO_INPUT
#define YY_EXTRA_TYPE inscore2::IParser*
#define YY_USER_ACTION  yyextra->fLine = yylloc->last_line = yylineno; yyextra->fColumn = yylloc->first_column += strlen(yytext);

#define register		// to get rid of the -Wdeprecated-register

// ----------------------------------------------------------------------------------------
// debug utility
#define LDEBUG	0
#if LDEBUG
static  void ldebug (const char * str, std::string context) {
	std::cerr << "LEX " << str << " : " << context << std::endl;
}
#else 
#define ldebug(a, b)
#endif
static  void localdebug (const char * str, std::string context) {
	std::cout << "LEX " << str << " : " << context << std::endl;
}

// ----------------------------------------------------------------------------------------
#define YY_INPUT(buf,result,max_size)   \
   {                                       \
	  char c;                              \
      yyextra->fStream->get( c );                 \
	  if (yyextra->fStream->eof())               \
         result = YY_NULL;                 \
      else {                               \
         buf[0] = c;                       \
         result = 1;                       \
      }                                    \
   }

// ----------------------------------------------------------------------------------------
// strip escape char '\' from escaped characters
static  char* unescape (char * str) {
	int n = strlen(str);
	// browse the string:  'r' is an index to the current read location
	//                     'w' is an index to the current write location
	for (int r=0, w=0; r <= n; r++) {		
		if (str[r] == '\\') {			// escape char '\' is found
			char next = str[r+1];
			if ((next != '\'') && (next != '"')) 	// escape only ' and "
				str[w++] = str[r];		// output the escape char 
		}
		else str[w++] = str[r];			// no escape: put the current char at write location 
	}
	return str;
}

// ----------------------------------------------------------------------------------------
// strip escape char '\' from escaped characters
static  char* unquote (char * str) {
	int n = strlen(str);
	str[n-1] = 0;
	return &str[1];
}

// ----------------------------------------------------------------------------------------

%}

%x JSECTION


DIGIT	[0-9]
LETTER  [a-zA-Z]

 /* allowed character set for first identifier char */
STARTID [_a-zA-Z]
 /* allowed character set for first variable char */
STARTVAR [0-9a-zA-Z]
 /* allowed character set for first identifier char */
IDCHAR  [_a-zA-Z0-9]
 
 /* allowed character set for host names
	see RFC952 and RFC1123
 */
HOSTCHAR [-a-zA-Z0-9]

 /* allowed character for filename and path as defined for windows 7 with some specification for INScore compatibility: no = ; */
FILECHAR [^ \t\\/?:*><|"';=]

 /* regular expression characters
    as defined by the OSC specification */
RECHAR  [-_a-zA-Z0-9?+*]
RECLASS [-_a-zA-Z0-9!]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%

 /* ----------------------------------------- */
 /*	digits */
 /* ----------------------------------------- */
{DIGIT}+				yyextra->fText = yytext; return UINT;
"+"{DIGIT}+				yyextra->fText = yytext; return INT;
"-"{DIGIT}+				yyextra->fText = yytext; return INT;

[+-]*{DIGIT}+"."{SPACE} 					yyextra->fText = yytext; return FLOAT;
[+-]*{DIGIT}+"."{DIGIT}* 					yyextra->fText = yytext; return FLOAT;
[+|-]*{DIGIT}+"."{DIGIT}+e[-|+]?{DIGIT}+ 	yyextra->fText = yytext; return FLOAT;
[+|-]*{DIGIT}+e[-|+]?{DIGIT}+ 				yyextra->fText = yytext; return FLOAT;

"__END__"			return ENDSCRIPT;
"with"				return WITH;

 /* ----------------------------------------- */
 /*	math operators */
 /* ----------------------------------------- */
"+"				return ADD;
"-"				return SUB;
"/ "			return DIV;
"*"				return MULT;
"%"				return MODULO;
"?"				return QUEST;
"!"				return NEG;
"=="			return EQ;
">"				return GREATER;
">="			return GREATEREQ;
"<"				return LESS;
"<="			return LESSEQ;
"math.min"		return MIN;
"math.max"		return MAX;
"math.has"		return HAS;

"="			    return EQUAL;

 /* ----------------------------------------- */
 /*	math functions */
 /* ----------------------------------------- */
"math.cos"			return COS;
"math.sin"			return SIN;
"math.tan"			return TAN;
"math.acos"			return ACOS;
"math.asin"			return ASIN;
"math.atan"			return ATAN;
"math.cosh"			return COSH;
"math.sinh"			return SINH;
"math.tanh"			return TANH;
"math.acosh"		return ACOSH;
"math.asinh"		return ASINH;
"math.atanh"		return ATANH;

"math.exp"			return EXP;
"math.log"			return LOG;
"math.log10"		return LOG10;
"math.log2"			return LOG2;
"math.pow"			return POW;
"math.sqrt"			return SQRT;
"math.cbrt"			return CBRT;

"math.ceil"			return CEIL;
"math.floor"		return FLOOR;
"math.round"		return ROUND;

"math.rand"			return RAND;


 /* ----------------------------------------- */
 /*	delimiters */
 /* ----------------------------------------- */
"/"					 	return SLASH;
"("					 	return LEFTPAR;
")"					 	return RIGHTPAR;
"{"					 	return LEFTBRACE;
"}"					 	return RIGHTBRACE;
"["					 	return LEFTBRACKET;
"]"					 	return RIGHTBRACKET;
";"					 	return ENDSTATEMENT;
":"					 	return COLON;
","					 	return COMMA;
"..."					return LDOTS;


 /* ----------------------------------------- */
 /*	comments */
 /* ----------------------------------------- */
"#".*						;
"(*"(.|{EOL})*"*)"			;


 /* ----------------------------------------- */
 /*	identifiers, strings  */
 /* ----------------------------------------- */
{LETTER}+								yyextra->fText = yytext; return LETTERS;
{IDCHAR}+								yyextra->fText = yytext; return IDENTIFIER;
"\""([^"]|"\\\"")*"\""					yyextra->fText = unescape(unquote(yytext)); return STRING;
"'"([^']|"\\'")*"'"						yyextra->fText = unescape(unquote(yytext)); return STRING;

 /* ----------------------------------------- */
 /*	variables */
 /* ----------------------------------------- */
"$"+{STARTVAR}{IDCHAR}*					yyextra->fText = &yytext[1]; return VARIABLE;


 /* ----------------------------------------- */
 /*	regular expressions */
 /* ----------------------------------------- */
{RECHAR}+								yyextra->fText = yytext; return REGEXP;	
{RECHAR}*"["{RECLASS}+"]"{RECHAR}*		yyextra->fText = yytext; return REGEXP;
{RECHAR}*"{"[_a-zA-Z0-9,]+"}"{RECHAR}*	yyextra->fText = yytext; return REGEXP;
"/*"									yyextra->fText = yytext; return ANYADDR;

 /* ----------------------------------------- */
 /*	expanded identifiers */
 /* ----------------------------------------- */
{IDCHAR}*"["({LETTER}:){0,1}{DIGIT}+"..."{DIGIT}+"]"					yyextra->fText = yytext; return EXPANDID;
{IDCHAR}*"["({LETTER}:){0,1}{LETTER}"..."{LETTER}"]"					yyextra->fText = yytext; return EXPANDID;
{IDCHAR}*"["({LETTER}:){0,2}{LETTER}{LETTER}"..."{LETTER}{LETTER}"]"	yyextra->fText = yytext; return EXPANDID;

 /* ----------------------------------------- */
 /*	javascript section */
 /* ----------------------------------------- */
"<?"{SPACE}*"javascript"	BEGIN JSECTION;
<JSECTION>"?>"				BEGIN INITIAL;
<JSECTION>({EOL}|"?"[^>]|[^?])*		yyextra->fText = unescape(yytext); return JSCRIPT;

 /* ----------------------------------------- */
 /*	hostname and IP */
 /* ----------------------------------------- */
{HOSTCHAR}+":"{DIGIT}+								yyextra->fText = yytext; return URLPREFIX;
({HOSTCHAR}+\.)+{HOSTCHAR}{2,}":"{DIGIT}+			yyextra->fText = yytext; return URLPREFIX;
({DIGIT}{1,3}\.){3}{DIGIT}{1,3}":"{DIGIT}+			yyextra->fText = yytext; return URLPREFIX;


{SPACE}+			;   /* eat up space */
{EOL}+		 			{ yyextra->fColumn = yylloc->first_column = 1; } 	/* return EOL;  eat up end of line */

<<EOF>>					return ENDSCRIPT;

.						yyextra->fText = yytext; ldebug("ERR", yyextra->fText); return ERR;

%%

namespace inscore2
{

void IParser::initScanner()
{
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void IParser::destroyScanner()
{
	yylex_destroy(fScanner);
}

} // end namespace

