%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno
%option yymore

%{

#include "mathparser.h"
#include "mathparse.hpp"

using namespace std;

#define YY_NO_INPUT
#define YY_EXTRA_TYPE mathparser*
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

%}

DIGIT	[0-9]
LETTER  [a-zA-Z]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%

 /* ----------------------------------------- */
 /*	math operators */
 /* ----------------------------------------- */
" + "				return ADD;
" - "				return SUB;
" / "				return DIV;
" * "				return MULT;
"++"				return INC;
"--"				return DEC;
" ? "				return QUEST;
" : "				return COLON;
"("					return LEFTPAR;
")"					return RIGHTPAR;

 /* ----------------------------------------- */
 /*	digits */
 /* ----------------------------------------- */
{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;
"+"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;
"-"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;

[+-]*{DIGIT}+"."{DIGIT}* 				yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+"."{DIGIT}+e[-+]?{DIGIT}+ 	yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			yyextra->fFloat = atof(yytext); return FLOAT;


{SPACE}+			;   /* eat up space */

{EOL}					return EOL; /* ignore */

.						return ERR;

%%

void mathparser::initScanner() {
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void mathparser::destroyScanner() {
	yylex_destroy(fScanner);
}
