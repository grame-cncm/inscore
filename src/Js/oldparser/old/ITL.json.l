%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno
%option yymore

%{

// ----------------------------------------------------------------------------------------
// strip escape char '\' from escaped characters
function unescape (str) {
	var n = str.length;
	// browse the string:  'r' is an index to the current read location
	//                     'w' is an index to the current write location
	for (r=0, w=0; r <= n; r++) {		
		if (str[r] == '\\') {			// escape char '\' is found
			var next = str[r+1];
			if ((next != '\'') && (next != '"')) 	// escape only ' and "
				str[w++] = str[r];		// output the escape char 
		}
		else str[w++] = str[r];			// no escape: put the current char at write location 
	}
	return str;
}

var nested = 0;
var expressionNested = 0;

// ----------------------------------------------------------------------------------------

%}

%x CMNTLN
%x COMMENT
		/* for double quoted strings */
%x DQSTR
		/* for quoted strings */
%x QSTR
		/* javascript section */
%x JSECTION
		/* evaluable expression section */
%x EXPRSECTION


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
"eval"			print( yytext ); return EVAL;


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
 {HOSTCHAR}+						print( yytext ); return HOSTNAME;
 {DIGIT}+"."{DIGIT}+"."{DIGIT}+"."{DIGIT}+		print( yytext ); return IPNUM;

 /* ----------------------------------------- */
 /*	identifiers */
 /* ----------------------------------------- */
{STARTID}{IDCHAR}*				print( yytext ); return IDENTIFIER;

 /* ----------------------------------------- */
 /*	quoted strings */
 /* ----------------------------------------- */
"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;

<DQSTR>([^\"]|"\\\"")*		if(!expressionNested){ yyextra->fText = unescape(yytext); return STRING;} /*else yyextra->fText += string("\"") + unescape(yytext) + "\"";*/
<QSTR>([^']|"\\'")*			if(!expressionNested){ yyextra->fText = unescape(yytext); return STRING;} /*else yyextra->fText += string("'") + unescape(yytext) + "'";*/
<DQSTR>\"					if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;
<QSTR>'						if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;


 /* ----------------------------------------- */
 /*	non quoted file path */
 /* ----------------------------------------- */
("/"|(".""."?"/")*)({FILECHAR}+"/"?)+"."{IDCHAR}+			print( yytext ); return STRING;	/*file path without space*/

 /* ----------------------------------------- */
 /*	lang sections */
 /* ----------------------------------------- */
"<?"{SPACE}*"javascript"	BEGIN JSECTION;
<JSECTION>"?>"				if(expressionNested) BEGIN EXPRSECTION; else BEGIN INITIAL;
<JSECTION>({EOL}|"?"[^>]|[^?])*		yyextra->fText = unescape(yytext); return JSCRIPT;

 /* ----------------------------------------- */
 /*	regular expressions */
 /* ----------------------------------------- */
{RECHAR}+								print( yytext ); return REGEXP;			/* regular expression */
{RECHAR}*"["{RECLASS}+"]"{RECHAR}*		print( yytext ); return REGEXP;			/* regular expression */
{RECHAR}*"{"[_a-zA-Z0-9,]+"}"{RECHAR}*	print( yytext ); return REGEXP;			/* regular expression */


 /* ----------------------------------------- */
 /*	evaluable expression section */
 /* ----------------------------------------- */

<EXPRSECTION>"("		expressionNested++; print( yytext ); /* yyextra->fText += yytext; */
<EXPRSECTION>")"		print( yytext ); if(!--expressionNested){ BEGIN INITIAL; return EXPRESSION;}
<EXPRSECTION>"\""		BEGIN DQSTR;
<EXPRSECTION>"'"		BEGIN QSTR;
<EXPRSECTION>[^()"']*	print( yytext );
"expr("					expressionNested = 1; BEGIN EXPRSECTION; print( yytext ); /* yyextra->fExprStartLine = yylloc->last_line; */

 /* ----------------------------------------- */
 /*	basic delimiters and markers */
 /* ----------------------------------------- */
"="					return EQUAL;
"../"				return BACKPATH;
"/"					return PATHSEP;			/* OSC address and path separator */
";"					return ENDEXPR;			/* end of expression */
"$"					return VARSTART;
":"					return COLON;
","					return COMMA;
"."					return POINT;
"("					return LEFTPAR;
")"					return RIGHTPAR;


 /*"["				return LEFTBRACKET; */
 /*"]"				return RIGHTBRACKET; */

{SPACE}+			;   /* eat up space */

{EOL}					/* yylloc->first_column=0; ignore */

<<EOF>>					return ENDSCRIPT;

.						print( yytext ); return ERR;

%%
