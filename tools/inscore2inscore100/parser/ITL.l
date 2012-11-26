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
			char next = str[r+1];
//			if (next == '\\')			// when next char is also an escape char '\'
//				str[w++] = str[r++];	// then put the '\' at write location
//			else 
			if ((next != '\'') && (next != '"')) 	// escape only ' and "
				str[w++] = str[r];		// output the escape char 
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
%x LUASECTION
%x JSECTION

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
{SPACE}*{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
{SPACE}*"+"{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
{SPACE}*"-"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;

{SPACE}*[+-]*{DIGIT}*"."{DIGIT}* 				yyextra->fFloat = atof(yytext); return FLOAT;
{SPACE}*[+-]*{DIGIT}*"."{DIGIT}*e[-+]?{DIGIT}+ 	yyextra->fFloat = atof(yytext); return FLOAT;
{SPACE}*[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			yyextra->fFloat = atof(yytext); return FLOAT;

{SPACE}*"="{SPACE}*	return EQUAL;
{SPACE}*"("			return LPAR;
")"					return RPAR;
","					return SEP;
"/"					return PATHSEP;			/* OSC address and path separator */
";"					return ENDEXPR;			/* end of expression */
{SPACE}*"$"			return VARSTART;

{SPACE}*"#"			BEGIN CMNTLN; yyextra->fText = yytext; return COMMENTSTR;
{SPACE}*"!"			BEGIN CMNTLN; yyextra->fText = yytext; return COMMENTSTR;
<CMNTLN>.*			yyextra->fText = yytext; return COMMENTSTR; 
<CMNTLN>{EOL}		BEGIN INITIAL; yyextra->fText = yytext; return COMMENTSTR;

<COMMENT>.|{EOL}	yyextra->fText = yytext; return COMMENTSTR;
<COMMENT>"(*"		yyextra->fText = yytext; nested++; return COMMENTSTR;
<COMMENT>"*)"		yyextra->fText = yytext; if (--nested==0) { BEGIN INITIAL; } return COMMENTSTR;
{SPACE}*"(*"		yyextra->fText = yytext;  nested=1; BEGIN COMMENT; return COMMENTSTR;

{SPACE}*{STARTID}{IDCHAR}*{SPACE}*						yyextra->fText = yytext; return IDENTIFIER;		/* identifiers */
{SPACE}*{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*{SPACE}*	yyextra->fText = yytext; return MAPIDENTIFIER;	/* identifiers with map name */
{SPACE}*{MSGLETTER}*{SPACE}*							yyextra->fText = yytext; return MSG;			/* messages */

{SPACE}*"\""				BEGIN DQSTR;
{SPACE}*"'"					BEGIN QSTR;
<DQSTR>([^\"]|"\\\"")*		yyextra->fText = unescape(yytext); return STRING;
<QSTR>([^']|"\\'")*			yyextra->fText = unescape(yytext); return STRING;
<DQSTR>\"					BEGIN INITIAL;
<QSTR>'						BEGIN INITIAL;

{SPACE}*"<?"{SPACE}*"lua"			BEGIN LUASECTION;
<LUASECTION>"?>"			BEGIN INITIAL;
<LUASECTION>({EOL}|"?"[^>]|[^?])*	yyextra->fText = unescape(yytext); return LUASCRIPT;

{SPACE}*"<?"{SPACE}*"javascript"	BEGIN JSECTION;
<JSECTION>"?>"				BEGIN INITIAL;
<JSECTION>({EOL}|"?"[^>]|[^?])*		yyextra->fText = unescape(yytext); return JSCRIPT;


{RESTART}{RECHAR}*				yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RESTART}*"["..*"]"{RECHAR}*	yyextra->fText = yytext; return REGEXP;			/* regular expression */

{SPACE}+			;   yyextra->fText = yytext; return SPACE;

{EOL}					yylloc->first_column=0; yyextra->fText = yytext; return EOL;

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

