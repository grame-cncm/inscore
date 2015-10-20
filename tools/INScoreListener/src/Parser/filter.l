%option reentrant
%option bison-locations
%option noyywrap


%{

//#include <stdio.h>
#include <iostream>
#include "filterparser.h"
#include "filterparse.hpp"

using namespace std;

#define YY_EXTRA_TYPE inscorelistener::filterparser*

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
		else str[w++] = str[r];			// no	escape: put the current char at write location
	}
	return str;
}

%}

/* for double quoted strings */
%x DQSTR
/* for quoted strings */
%x QSTR

DIGIT	[0-9]
LETTER  [a-zA-Z]

 /* allowed character set for first identifier char */
STARTID [_a-zA-Z]
 /* allowed character set for first identifier char */
IDCHAR  [_a-zA-Z0-9]

 /* allowed character set for host names
	see RFC952 and RFC1123
 */
HOSTCHAR [-a-zA-Z0-9]

 /* allowed character for filename and path as defined for windows 7*/
FILECHAR [^ \\/?:*><|"';]

 /* regular expression characters
    as defined by the OSC specification */
RECHAR  [-_a-zA-Z0-9?+*]
RECLASS [-_a-zA-Z0-9^]

ANYCHAR	[^ \t"'\x0a\x0d?+*]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%

{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"+"{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"-"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;

[+-]*{DIGIT}+"."{DIGIT}* 				yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+"."{DIGIT}+e[-+]?{DIGIT}+ 	yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			yyextra->fFloat = atof(yytext); return FLOAT;


 /* ----------------------------------------- */
 /*	quoted strings */
 /* ----------------------------------------- */
"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;

<DQSTR>([^\"]|"\\\"")*			yyextra->fText = unescape(yytext); return QUOTEDSTRING;
<QSTR>([^']|"\\'")*			yyextra->fText = unescape(yytext); return QUOTEDSTRING;
<DQSTR>\"				BEGIN INITIAL;
<QSTR>'					BEGIN INITIAL;

 /* ----------------------------------------- */
 /*	basic delimiters and markers */
 /* ----------------------------------------- */

"/"			return PATHSEP;
"("			return LEFTPAR;
")"			return RIGHTPAR;

"=="			return EQUAL;
"="				return EQUAL;
"!="			return NOTEQUAL;
">"				return GREATER;
">="			return GREATEREQUAL;
"<"				return LOWER;
"<="			return LOWEREQUAL;

"AND"			return LAND;
"&&"			return LAND;
"OR"			return LOR;
"||"			return LOR;

"NOT"			return LNOT;
"!"				return LNOT;

 /* ----------------------------------------- */
 /*	identifiers */
 /* ----------------------------------------- */
{STARTID}{IDCHAR}*				yyextra->fText = yytext; return IDENTIFIER;



 /* ----------------------------------------- */
 /*	regular expressions */
 /* ----------------------------------------- */
{RECHAR}+								yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RECHAR}*"["{RECLASS}+"]"{RECHAR}*		yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RECHAR}*"{"[_a-zA-Z0-9,]+"}"{RECHAR}*	yyextra->fText = yytext; return REGEXP;			/* regular expression */


 /* ----------------------------------------- */
 /*	address and param id token */
 /* ----------------------------------------- */
"%"{DIGIT}+			yyextra->fInt = stoi(string(yytext).erase(0,1)); return ARGID;
"%addr"				return ADDR;

{SPACE}+			;   /* eat up space */

%%

namespace inscorelistener
{

void filterparser::initScanner()
{
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void filterparser::destroyScanner()
{
	yylex_destroy(fScanner);
}

} // end namespace

