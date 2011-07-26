%{

#include <stdio.h>

#define YY_NO_UNISTD_H
static int nested;

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
//			else if (str[r+1] != '"') { // when the next char 
//				str[w++] = str[r];
//			}
		}
		else str[w++] = str[r];			// no escape: put the current char at write location 
	}
	return str;
}

// ----------------------------------------------------------------------------------------

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
MSGLETTER  [a-zA-Z+]
STARTID [_a-zA-Z]
IDCHAR  [-_a-zA-Z0-9]
IDLOOP  [-_a-zA-Z0-9%]

RECHAR  [-_a-zA-Z0-9?+*]
RELOOP  [-_a-zA-Z0-9?+*%]
RESTART [_a-zA-Z?+*]
RELOOPSTART [_a-zA-Z?+*%]

PCHAR	[^ \t\x0a\x0d*?]
SPACE	[ \t\x0a\x0d]
EOL		[\x0a\x0d]

%%
{DIGIT}+				return UINT;
"+"{DIGIT}+				return UINT;
"-"{DIGIT}+				return INT;

[+-]*{DIGIT}*"."{DIGIT}* 				return FLOAT;
[+-]*{DIGIT}*"."{DIGIT}*e[-+]?{DIGIT}+ 	return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			return FLOAT;

"="					return EQUAL;
"("					return LPAR;
")"					return RPAR;
","					return SEP;
"loop"				return LOOP;
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

{STARTID}{IDCHAR}*						return IDENTIFIER;		/* identifiers */
{STARTID}{IDLOOP}*						return LOOPIDENTIFIER;	/* identifiers */
{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*	return MAPIDENTIFIER;	/* identifiers with map name */
{MSGLETTER}*							return MSG;				/* messages */

"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;
<DQSTR>([^\"]|"\\\"")*		unescape(yytext); return STRING;
<QSTR>([^']|"\\'")*			unescape(yytext); return STRING;
<DQSTR>\"					BEGIN INITIAL;
<QSTR>'						BEGIN INITIAL;

{RESTART}{RECHAR}*					return REGEXP;			/* regular expression */
{RESTART}*"["..*"]"{RECHAR}*		return REGEXP;			/* regular expression */
{RELOOPSTART}{RELOOP}*				return LOOPREGEXP;		/* regular expression */
{RELOOPSTART}*"["..*"]"{RELOOP}*	return LOOPREGEXP;		/* regular expression */

{SPACE}+			;   /* eat up space */

"-"					return HYPHEN;		// uncatched '-' is an error
