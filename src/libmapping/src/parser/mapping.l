
%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno
%option yymore
%option bison-bridge

%{

#ifdef WIN32
#pragma warning (disable : 4267 4100)
#endif

#define YY_NO_UNISTD_H

#include "TInterval.h"
#include "TSegment.h"
#include "rational.h"
#include "mapparser.h"
#include "mapping.tab.hpp"

#define register

#define YY_EXTRA_TYPE libmapping::mapparser*
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

%}

%x CMNTLN
%x COMMENT

DIGIT	[0-9]
SPACE	[ \t\x0a\x0d]
EOL		[\x0a\x0d]

%%
{DIGIT}+				yyextra->fInt = atoi(yytext); return NUMBER;
-{DIGIT}+				yyextra->fInt = atoi(yytext); return NUMBER;
{DIGIT}*"."{DIGIT}+		yyextra->fFloat = atof(yytext); return FLOAT;
{DIGIT}+"."				yyextra->fFloat = atof(yytext); return FLOAT;
"+"{DIGIT}*"."{DIGIT}+	yyextra->fFloat = atof(yytext); return FLOAT;
"+"{DIGIT}+"."			yyextra->fFloat = atof(yytext); return FLOAT;
"-"{DIGIT}*"."{DIGIT}+	yyextra->fFloat = atof(yytext); return FLOAT;
"-"{DIGIT}+"."			yyextra->fFloat = atof(yytext); return FLOAT;

{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"//"		BEGIN CMNTLN;
{SPACE}*"%"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"/*"		yyextra->fNested++; 
<COMMENT>"*/"		if (--yyextra->fNested==0) BEGIN INITIAL;
{SPACE}*"/*"		yyextra->fNested=1; BEGIN COMMENT;

"/"					return RATIONAL_BAR;
"("					return SEGMENT_START;
")"					return SEGMENT_END;
"["					return INTERVAL_BAR;
","					return SEP;

":"					return TIMESEP;


{EOL}				yylloc->first_column=0; /* ignore */
{SPACE}+			/* eat up space */
.					return ERROR;	/* any extra text generates errors */

%%

namespace libmapping 
{

void mapparser::initScanner()
{
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void mapparser::destroyScanner()
{
	yylex_destroy(fScanner);
}

} // end namespace

