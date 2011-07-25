%{

#include <stdio.h>

#define YY_NO_UNISTD_H
static int nested;

static  char* unescape (char * str) {
	int n = strlen(str);
	for (int i=0, j=0; i <= n; i++) {		
		if (str[i] == '\\') {
			if (str[i+1] == '\\') {
				str[j++] = str[i++];
			}
			else if (str[i+1] != '"') {
				str[j++] = str[i];
			}
		}
		else str[j++] = str[i];
	}
	return str;
}

%}

%option yylineno
%option never-interactive
%option yymore

%x CMNTLN
%x COMMENT
%x DQSTR
%x QSTR

DIGIT	[0-9]
LETTER  [a-zA-Z]
STARTID [_a-zA-Z]
IDCHAR  [-_a-zA-Z0-9]
RECHAR  [-_a-zA-Z0-9?+*]
PCHAR	[^ \t\x0a\x0d*?]
SPACE	[ \t\x0a\x0d]
EOL		[\x0a\x0d]

%%
[+-]*{DIGIT}+				return INT;

[+-]*{DIGIT}+"."{DIGIT}* 				return FLOAT;
[+-]*{DIGIT}+"."{DIGIT}*e[-+]?{DIGIT}+ 	return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			return FLOAT;
[+-]*"."{DIGIT}+ 						return FLOAT;
[+-]*"."{DIGIT}+e[-+]?{DIGIT}+ 			return FLOAT;

"="					return EQUAL;
"("					return LPAR;
")"					return RPAR;
","					return SEP;
"loop"				return LOOP;
"/"					return PATHSEP;			/* OSC address and path separator */
"\\"				return WINSEP;			/* win path separator */
";"					return ENDEXPR;			/* end of expression */

{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"//"		BEGIN CMNTLN;
{SPACE}*"%"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"(*"		nested++; 
<COMMENT>"*)"		if (--nested==0) BEGIN INITIAL;
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

{STARTID}{IDCHAR}*		return IDENTIFIER;		/* identifiers */
{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*	return MAPIDENTIFIER;		/* identifiers with map name */
{LETTER}*			return MSG;				/* messages */

"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;
<DQSTR>([^\"]|"\\\"")*		unescape(yytext); return STRING;
<QSTR>([^']|"\\'")*			unescape(yytext); return STRING;
<DQSTR>\"					BEGIN INITIAL;
<QSTR>'						BEGIN INITIAL;

{RECHAR}{RECHAR}*			return REGEXP;		/* regular expression */
{RECHAR}*"["..*"]"{RECHAR}*	return REGEXP;		/* regular expression */

{SPACE}+			;   /* eat up space */
