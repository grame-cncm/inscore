%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno
 /*%option yymore*/

%{

#ifdef WIN32
#pragma warning (disable : 4267 4100 4244)
#endif

//#include <stdio.h>
#include <iostream>
#include "IMessage.h"
#include "ITLparser.h"
#include "ITLparse.hpp"

using namespace std;

#define YY_NO_INPUT
#define YY_EXTRA_TYPE inscore::ITLparser*
#define YY_USER_ACTION  yyextra->fLine = yylloc->last_line = yylineno; yylloc->first_column += strlen(yytext);

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
// debug utility
#define LDEBUG	0
#if LDEBUG
static  void debug (const char * str, string context) {
	cout << "LEX " << str << " : " << context << endl;
}
#else 
#define debug(a, b)
#endif

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
%x EXPRSECTION
		/* osc address */
%x OSCSECTION

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

 /* allowed character for filename and path as defined for windows 7 with some specification for INScore compatibility: no = ; */
FILECHAR [^ \t\\/?:*><|"';=]

 /* regular expression characters
    as defined by the OSC specification */
RECHAR  [-_a-zA-Z0-9?+*]
RECLASS [-_a-zA-Z0-9^]

 /*ANYCHAR	[^ \t"'\x0a\x0d?+*] */

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

"__END__"			return ENDSCRIPT;

 /* ----------------------------------------- */
 /*	method requiring messages as argument */
 /* ----------------------------------------- */
"eval"			yyextra->fText = yytext; return EVAL;

{EOL}					yylloc->first_column=0; /* ignore */

 /* ----------------------------------------- */
 /*	math operators */
 /* ----------------------------------------- */
"+"				return ADD;
 /*{SPACE}"++"		return PREINC;*/
 /*"++"			return POSTINC;*/
"-"				return MINUS;
 /*{SPACE}"--"		return PREDEC;*/
 /*"--"			return POSTDEC;*/
"-"{SPACE}		return SUB;
{SPACE}"/"		return DIV;
"*"				return MULT;
"%"				return MODULO;
{SPACE}"?"{SPACE} return QUEST;
"!"				return NEG;
"=="			return EQ;
">"				return GREATER;
">="			return GREATEREQ;
"<"				return LESS;
"<="			return LESSEQ;
"@min"		return MIN;
"@max"		return MAX;



 /* ----------------------------------------- */
 /*	comments */
 /* ----------------------------------------- */
{SPACE}*"#"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"(*"		nested++; 
 /* check the current context (EXPRSECTION or INITIAL) to close comment */
<COMMENT>"*)"		if (--nested==0) {if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;}
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

 /* ----------------------------------------- */
 /*	variables */
"$"{STARTID}{IDCHAR}*			yyextra->fText = &yytext[1]; debug("VARIABLE", yyextra->fText); return VARIABLE;
"$"{STARTID}{IDCHAR}*"++"		yyextra->fText = &yytext[1]; debug("VARIABLE", yyextra->fText); return VARIABLEPOSTINC;
"$"{STARTID}{IDCHAR}*"--"		yyextra->fText = &yytext[1]; debug("VARIABLE", yyextra->fText); return VARIABLEPOSTDEC;
"++$"{STARTID}{IDCHAR}*			yyextra->fText = &yytext[1]; debug("VARIABLE", yyextra->fText); return VARIABLEPREINC;
"--$"{STARTID}{IDCHAR}*			yyextra->fText = &yytext[1]; debug("VARIABLE", yyextra->fText); return VARIABLEPREDEC;

 /* ----------------------------------------- */
 /*	quoted strings */
 /* ----------------------------------------- */
"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;

<DQSTR>([^\"]|"\\\"")*		if (!expressionNested){ yyextra->fText = unescape(yytext); debug("STRING", yytext); return STRING;} else yyextra->fText += string("\"") + unescape(yytext) + "\"";
<DQSTR>\"					if (expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;

<QSTR>([^']|"\\'")*			if (!expressionNested){ yyextra->fText = unescape(yytext); return STRING;} else yyextra->fText += string("'") + unescape(yytext) + "'";
<QSTR>'						if (expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;

 /* ----------------------------------------- */
 /*	identifiers */
 /* ----------------------------------------- */
{STARTID}{IDCHAR}*				yyextra->fText = yytext; return IDENTIFIER;

 /* ----------------------------------------- */
 /*	hostname and IP */
 /* ----------------------------------------- */
({HOSTCHAR}({HOSTCHAR}*|'.'))+":"				yyextra->fText = yytext; yyextra->fText.pop_back(); debug("HOSTNAME", yytext); return HOSTNAME;
{DIGIT}+"."{DIGIT}+"."{DIGIT}+"."{DIGIT}+		yyextra->fText = yytext; debug("IPNUM", yytext); return IPNUM;

 /* ----------------------------------------- */
 /*	non quoted file path */
 /* ----------------------------------------- */
("/"|(".""."?"/")*)({FILECHAR}+"/"?)+"."[a-zA-Z]+		yyextra->fText = yytext; debug("FSTRING", yytext); return STRING;	/*file path without space*/

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
{RECHAR}*"{"[_a-zA-Z0-9,]+"}"{RECHAR}*	yyextra->fText = yytext; debug("RECHAR", yytext); return REGEXP;			/* regular expression */

 /* ----------------------------------------- */
 /*	OSC address */
 /* ----------------------------------------- */
{SPACE}*"/"{IDCHAR}+								{ yyextra->fText = yytext; BEGIN OSCSECTION; }
<OSCSECTION>"/"										{ yyextra->fText += yytext; }
<OSCSECTION>"$"?{STARTID}{IDCHAR}*					{ yyextra->fText += yytext; }
<OSCSECTION>{RECHAR}+								{ yyextra->fText += yytext; }
<OSCSECTION>{RECHAR}*"["{RECLASS}+"]"{RECHAR}*		{ yyextra->fText += yytext; }
<OSCSECTION>{RECHAR}*"{"[_a-zA-Z0-9,]+"}"{RECHAR}*	{ yyextra->fText += yytext; }
<OSCSECTION>{SPACE}|{EOL}|","|";"					{ yyless(0); BEGIN INITIAL; debug("OSCADDRESS", yyextra->fText); return OSCADDRESS; }


 /* ----------------------------------------- */
 /*	evaluable expression section */
 /* ----------------------------------------- */
<EXPRSECTION>"("				expressionNested++; yyextra->fText += yytext;
<EXPRSECTION>")"				yyextra->fText += yytext; if(!--expressionNested){ BEGIN INITIAL; return EXPRESSION;}
<EXPRSECTION>"\""				BEGIN DQSTR;
<EXPRSECTION>"'"				BEGIN QSTR;
<EXPRSECTION>[^()"']*			yyextra->fText += yytext;
"expr"{SPACE}*"("				expressionNested = 1; BEGIN EXPRSECTION; yyextra->fText = yytext; yyextra->fExprStartLine = yylloc->last_line;

 /* ----------------------------------------- */
 /*	basic delimiters and markers */
 /* ----------------------------------------- */
"="					return EQUAL;
";"					return ENDEXPR;			/* end of expression */
"$"					return VARSTART;
":"					return COLON;
","					debug("COMMA", ","); return COMMA;
"."					return POINT;
"("					debug("LEFTPAR", "("); return LEFTPAR;
")"					debug("RIGHTPAR", ")"); return RIGHTPAR;

{SPACE}+			;   /* eat up space */

<<EOF>>					return ENDSCRIPT;

.						yyextra->fText = yytext; debug("ERR", yyextra->fText); return ERR;

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

