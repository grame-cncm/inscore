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


{SPACE}*"#"			BEGIN CMNTLN; return COMMENTTEXT;
"//"				BEGIN CMNTLN; yytext[0] = '!'; yytext[1] = 0; return COMMENTTEXT;
"%"					BEGIN CMNTLN; yytext[0] = '!'; return COMMENTTEXT;
<CMNTLN>.*						  return COMMENTTEXT;
<CMNTLN>{EOL}+		BEGIN INITIAL;  return ENDCOMMENT;

<COMMENT>.|{EOL}*	return COMMENTTEXT;
<COMMENT>"(*"		nested++; return COMMENTTEXT;
<COMMENT>"*)"		if (--nested==0) BEGIN INITIAL; return ENDCOMMENT;
{SPACE}*"(*"		nested=1; BEGIN COMMENT; return COMMENTTEXT;

{STARTID}{IDCHAR}*	return IDENTIFIER;		/* identifiers */
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

{SPACE}+			;
