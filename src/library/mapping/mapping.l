%{

#include <stdio.h>

#define YY_NO_UNISTD_H
static int nested;

%}

%option yylineno
%option never-interactive

%x CMNTLN
%x COMMENT

DIGIT	[0-9]
SPACE	[ \t\x0a\x0d]
EOL		[\x0a\x0d]

%%
{DIGIT}+			return NUMBER;
-{DIGIT}+			return NUMBER;
{DIGIT}*"."{DIGIT}+		return FLOAT;
{DIGIT}+"."			return FLOAT;
"+"{DIGIT}*"."{DIGIT}+		return FLOAT;
"+"{DIGIT}+"."			return FLOAT;
"-"{DIGIT}*"."{DIGIT}+		return FLOAT;
"-"{DIGIT}+"."			return FLOAT;

{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"//"		BEGIN CMNTLN;
{SPACE}*"%"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"/*"		nested++; 
<COMMENT>"*/"		if (--nested==0) BEGIN INITIAL;
{SPACE}*"/*"		nested=1; BEGIN COMMENT;

"/"					return RATIONALBAR;
"("					return SEGSTART;
")"					return SEGEND;
"["					return INTERVAL;
","					return SEP;


{SPACE}+			/* eat up space */
.					return ERROR;	/* any extra text generates errors */

