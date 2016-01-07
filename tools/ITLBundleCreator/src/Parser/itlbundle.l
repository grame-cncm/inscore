%option reentrant
%option bison-locations
%option noyywrap


%{

//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "itlbundleparser.h"
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

static int nested;

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

%x CMNTLN
%x COMMENT
/* for double quoted strings */
%x DQSTR
/* for quoted strings */
%x QSTR



 /* allowed character for filename and path as defined for windows 7*/
FILECHAR [^ \t\\/?:*><|"';=]

ANYCHAR	[^ \t"'\x0a\x0d?+*]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%

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
<COMMENT>"*)"		if (--nested==0) { BEGIN INITIAL;}
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

/* ----------------------------------------- */
/*	comments */
/* ----------------------------------------- */
"__END__"			return ENDSCRIPT;


{STARTID}{IDCHAR}*				yyextra->fText = yytext; return IDENTIFIER;

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



(FILECHAR)*"."(FILECHAR)*		yyextra->fText = unescape(yytext); return FILEPATH;

"load"		return LOAD;
"rootPath"	return ROOTPATH;
"/"			return PATHSEP;
"."			return POINT;

(ANYCHAR)*						return TEXT;


{SPACE}+			;   /* eat up space */

{EOL}					yylloc->first_column=0; /* ignore */

.						yyextra->fText = yytext; return ERR;

%%

namespace itlbundle
{

void itlbundleparser::initScanner()
{
	yylex_init(&fScanner);
	yyset_extra(this, fScanner);
}

void itlbundleparser::destroyScanner()
{
	yylex_destroy(fScanner);
}

} // end namespace

