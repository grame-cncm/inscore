%option reentrant
%option bison-locations
%option never-interactive
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
#include "IMessage.h"
#include "IExpression.h"
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
static int expressionNested=0;

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

%x CMNTLN
%x COMMENT
		/* for double quoted strings */
%x DQSTR
		/* for quoted strings */
%x QSTR
		/* lua section */
%x LUASECTION
		/* javascript section */
%x JSECTION
		/* evaluable expression section */
%s EXPRSECTION


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

 /* ----------------------------------------- */
 /*	digits */
 /* ----------------------------------------- */
{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"+"{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"-"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;

[+-]*{DIGIT}+"."{DIGIT}* 				yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+"."{DIGIT}+e[-+]?{DIGIT}+ 	yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			yyextra->fFloat = atof(yytext); return FLOAT;

 /* ----------------------------------------- */
 /*	method requiring messages as argument */
 /* ----------------------------------------- */
"eval"			yyextra->fText = yytext; return EVAL;
"watch"			yyextra->fText = yytext; return WATCH;
"watch+"		yyextra->fText = yytext; return WATCH;
"require"		yyextra->fText = yytext; return WATCH;

 /* ----------------------------------------- */
 /*	comments */
 /* ----------------------------------------- */
{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"!"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"(*"		nested++; 
 /* check the current context (EXPRSECTION or INITIAL) to close comment */
<COMMENT>"*)"		if (--nested==0) {if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;}
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

 /* ----------------------------------------- */
 /*	comments */
 /* ----------------------------------------- */
"__END__"			return ENDSCRIPT;

 /* ----------------------------------------- */
 /*	hostname part */
 /* ----------------------------------------- */
 {HOSTCHAR}+									yyextra->fText = yytext; return HOSTNAME;
 {DIGIT}+"."{DIGIT}+"."{DIGIT}+"."{DIGIT}+		yyextra->fText = yytext; return IPNUM;

 /* ----------------------------------------- */
 /*	identifiers */
 /* ----------------------------------------- */
{STARTID}{IDCHAR}*				yyextra->fText = yytext; return IDENTIFIER;

 /* ----------------------------------------- */
 /*	quoted strings */
 /* ----------------------------------------- */
"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;

<DQSTR>([^\"]|"\\\"")*		yyextra->fText = unescape(yytext); return QUOTEDSTRING;
<QSTR>([^']|"\\'")*			yyextra->fText = unescape(yytext); return QUOTEDSTRING;
<DQSTR>\"					if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;
<QSTR>'						if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;


 /* ----------------------------------------- */
 /*	file path */
 /* ----------------------------------------- */
<EXPRSECTION>"/"?(".""."?"/")*({FILECHAR}+"/"?)+"."{IDCHAR}+			yyextra->fText = unescape(yytext); return FILEPATH;	/*file path without space*/

 /* ----------------------------------------- */
 /*	lang sections */
 /* ----------------------------------------- */
"<?"{SPACE}*"lua"			BEGIN LUASECTION;
<LUASECTION>"?>"			if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;
<LUASECTION>({EOL}|"?"[^>]|[^?])*	yyextra->fText = unescape(yytext); return LUASCRIPT;

"<?"{SPACE}*"javascript"	BEGIN JSECTION;
<JSECTION>"?>"				if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;
<JSECTION>({EOL}|"?"[^>]|[^?])*		yyextra->fText = unescape(yytext); return JSCRIPT;

 /* ----------------------------------------- */
 /*	regular expressions */
 /* ----------------------------------------- */
{RECHAR}+								yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RECHAR}*"["{RECLASS}+"]"{RECHAR}*		yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RECHAR}*"{"[_a-zA-Z0-9,]+"}"{RECHAR}*	yyextra->fText = yytext; return REGEXP;			/* regular expression */


 /* ----------------------------------------- */
 /*	evaluable expression section */
 /* ----------------------------------------- */

 /*"expr("					expressionNested = 1; BEGIN EXPRSECTION; return EXPRESSIONSTART;*/
<EXPRSECTION>"("				expressionNested++; return EXPRESSIONSTART;
<EXPRSECTION>"expr("				expressionNested++; return EXPRESSIONSTART;
<EXPRSECTION>")"				if(!--expressionNested){ BEGIN INITIAL;} return EXPRESSIONEND;
"expr("						expressionNested = 1; BEGIN EXPRSECTION; return EXPRESSIONSTART;

 /* ----------------------------------------- */
 /*	basic delimiters and markers */
 /* ----------------------------------------- */
"="					return EQUAL;
"/"					return PATHSEP;			/* OSC address and path separator */
";"					return ENDEXPR;			/* end of expression */
"$"					return VARSTART;
":"					return COLON;
","					return COMMA;
"."					return POINT;
"("					return LEFTPAR;
")"					return RIGHTPAR;
"&"					return AMPERSAND;
 /*"["					return LEFTBRACKET; */
 /*"]"					return RIGHTBRACKET; */

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

