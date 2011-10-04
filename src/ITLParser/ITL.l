%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno
%option yymore

%{

//#include <stdio.h>
#include <iostream>
#include "IMessage.h"
#include "ITLparser.h"
#include "ITLparse.hpp"

using namespace std;

#define YY_EXTRA_TYPE inscore::ITLparser*
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

static int nested;

#define YY_NO_UNISTD_H
// ----------------------------------------------------------------------------------------
// strip escape char '\' from escaped characters
static  char* unescape (char * str) {
	int n = strlen(str);
	// browse the string:  'r' is an index to the current read location
	//                     'w' is an index to the current write location
	for (int r=0, w=0; r <= n; r++) {		
		if (str[r] == '\\') {			// escape char '\' is found
			if (str[r+1] == '\\') {		// when next char is also an escape char '\'
				str[w++] = str[r++];	// the put the '\' at write location
			}
		}
		else str[w++] = str[r];			// no escape: put the current char at write location 
	}
	return str;
}

// ----------------------------------------------------------------------------------------

%}

%x CMNTLN
%x COMMENT
%x DQSTR
%x QSTR
%x LUASCRIPT
%x JSCRIPT

DIGIT	[0-9]
LETTER  [a-zA-Z]
MSGLETTER  [a-zA-Z+]
STARTID [_a-zA-Z]
IDCHAR  [-_a-zA-Z0-9]

RECHAR  [-_a-zA-Z0-9?+*]
RESTART [_a-zA-Z?+*]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%
{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"+"{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"-"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;

[+-]*{DIGIT}*"."{DIGIT}* 				yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}*"."{DIGIT}*e[-+]?{DIGIT}+ 	yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			yyextra->fFloat = atof(yytext); return FLOAT;

"="					return EQUAL;
"("					return LPAR;
")"					return RPAR;
","					return SEP;
"/"					return PATHSEP;			/* OSC address and path separator */
";"					return ENDEXPR;			/* end of expression */
"$"					return VARSTART;

{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"!"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"(*"		nested++; 
<COMMENT>"*)"		if (--nested==0) BEGIN INITIAL;
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

{STARTID}{IDCHAR}*						yyextra->fText = yytext; return IDENTIFIER;		/* identifiers */
{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*	yyextra->fText = yytext; return MAPIDENTIFIER;	/* identifiers with map name */
{MSGLETTER}*							yyextra->fText = yytext; return MSG;			/* messages */

"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;
<DQSTR>([^\"]|"\\\"")*		yyextra->fText = unescape(yytext); return STRING;
<QSTR>([^']|"\\'")*			yyextra->fText = unescape(yytext); return STRING;
<DQSTR>\"					BEGIN INITIAL;
<QSTR>'						BEGIN INITIAL;

"<?"{SPACE}*"lua"			BEGIN LUASCRIPT;
<LUASCRIPT>([^>]|"\\\>")*	yyextra->fText = unescape(yytext); return LUA;
<LUASCRIPT>">"				BEGIN INITIAL;

"<?"{SPACE}*"javascript"	BEGIN JSCRIPT;
<JSCRIPT>([^>]|"\\\>")*		yyextra->fText = unescape(yytext); return JAVASCRIPT;
<JSCRIPT>">"				BEGIN INITIAL;


{RESTART}{RECHAR}*				yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RESTART}*"["..*"]"{RECHAR}*	yyextra->fText = yytext; return REGEXP;			/* regular expression */

{SPACE}+			;   /* eat up space */

{EOL}					yylloc->first_column=0; /* ignore */

.						yyextra->fText = yytext; return ERR;

%%

namespace inscore 
{

void ITLparser::initScanner()
{
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void ITLparser::destroyScanner()
{
	yylex_destroy(fScanner);
}

} // end namespace

