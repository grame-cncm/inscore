%option reentrant
%option never-interactive
%option bison-locations
%option bison-bridge
%option noyywrap
%option nounput
%option yylineno
%option yymore

%{

#ifdef WIN32
#pragma warning (disable : 4267 4100)
#endif

//#include <stdio.h>
#include <iostream>
#include "IExprParser.h"
#include "IExprParse.hpp"

using namespace std;

#define YY_EXTRA_TYPE inscore::IExprParser*
#define YY_USER_ACTION yylloc->last_line = yylineno; yylloc->first_column += strlen(yytext);

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

#define YY_NO_UNISTD_H
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

%}
		/* for double quoted strings */
%x DQSTR
		/* for quoted strings */
%x QSTR



 /* allowed character in operator*/
IDENTIFIERCHAR  [-_a-zA-Z0-9]

 /* allowed character for args */
STARTARGCHAR[-_a-zA-Z0-9+*<>/^\\?:[]
ARGCHAR [-_a-zA-Z0-9+*<>/^\\?:"'[\]]

 /* A string can't begin with " or ' (conflict with QUOTEDSTRING), ( or ) (conflict with expression definition)*/
 /*  neither with & nor ~ (conflict with prefix) and finnaly not $ (conflict with variable)*/
STARTANYCHAR	[^ \t"'\x0a\x0d?+*&~$()]
ANYCHAR		[^ \t\x0a\x0d?+*()]
ENDANYCHAR	[^ \t\x0a\x0d?+*()]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%
 /* ----------------------------------------- */
 /*	evaluable expression section */
 /* ----------------------------------------- */

"expr("			return EXPR_START;
"("				return EXPR_START;
")"				return EXPR_END;



 /* ----------------------------------------- */
 /*	quoted strings */
 /* ----------------------------------------- */
"\""			BEGIN DQSTR;
"'"				BEGIN QSTR;

<DQSTR>([^\"]|"\\\"")*		yyextra->fText = unescape(yytext); return QUOTEDSTRING;
<QSTR>([^']|"\\'")*		yyextra->fText = unescape(yytext); return QUOTEDSTRING;
<DQSTR>\"			BEGIN INITIAL;
<QSTR>'				BEGIN INITIAL;

 /* ----------------------------------------- */
 /*	non quoted identifier */
 /* ----------------------------------------- */

{IDENTIFIERCHAR}*				yyextra->fText = yytext; return IDENTIFIER;
{STARTANYCHAR}+({ANYCHAR}*{ENDANYCHAR}+)?	yyextra->fText = yytext; return STRING;

"&"				return AMPERSAND;
"~"				return TILDE;
"$"				return VARSTART;

{SPACE}+			;   /* eat up space */
{EOL}					yylloc->first_column=0; /* ignore */


%%

namespace inscore 
{

void IExprParser::initScanner()
{
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void IExprParser::destroyScanner()
{
	yylex_destroy(fScanner);
}

} // end namespace

