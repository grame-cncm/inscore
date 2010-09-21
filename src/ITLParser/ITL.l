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
%x STR

DIGIT	[0-9]
LETTER  [a-zA-Z]
IDCHAR  [a-zA-Z0-9]
RECHAR  [a-zA-Z0-9?+*]
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


{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"//"		BEGIN CMNTLN;
{SPACE}*"%"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"(*"		nested++; 
<COMMENT>"*)"		if (--nested==0) BEGIN INITIAL;
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

{LETTER}{IDCHAR}*	return IDENTIFIER;		/* identifiers */
{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*	return MAPIDENTIFIER;		/* identifiers with map name */
{LETTER}*			return MSG;				/* messages */
"/"					return PATHSEP;			/* OSC address and path separator */
"\\"				return WINSEP;			/* win path separator */
";"					return ENDMSG;			/* end of osc message */

"\""						BEGIN STR;
<STR>([^\"]|"\\\"")*		unescape(yytext); return STRING;
<STR>\"						BEGIN INITIAL;

{RECHAR}{RECHAR}*			return REGEXP;		/* regular expression */
{RECHAR}*"["..*"]"{RECHAR}*	return REGEXP;		/* regular expression */

	/*{EOL}+				return NL;*/

{SPACE}+			;   /* eat up space */
