%option reentrant
%option bison-locations
%option never-interactive
%option noyywrap
%option nounput
%option yylineno
%option yymore

%{

//#include <stdio.h>
#include <iostream>
#include "IMessage.h"
#include "ITLparser.h"
#include "ITLparse.hpp"

using namespace std;

#define YY_EXTRA_TYPE inscore::ITLparser*
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

static int nested;

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

%}

%x CMNTLN
%x COMMENT
%x DQSTR
%x QSTR
%x LUASECTION
%x JSECTION

DIGIT	[0-9]
LETTER  [a-zA-Z]
STARTID [_a-zA-Z]
IDCHAR  [-_a-zA-Z0-9]

RECHAR  [-_a-zA-Z0-9?+*]
RESTART [_a-zA-Z?+*]

SPACE	[ \t]
EOL		[\x0a\x0d]

%%

 /* ----------------------------------------- */
 /*	digits */
 /* ----------------------------------------- */
{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"+"{DIGIT}+				yyextra->fInt = atoi(yytext); return UINT;
"-"{DIGIT}+				yyextra->fInt = atoi(yytext); return INT;

[+-]*{DIGIT}*"."{DIGIT}* 				yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}*"."{DIGIT}*e[-+]?{DIGIT}+ 	yyextra->fFloat = atof(yytext); return FLOAT;
[+-]*{DIGIT}+e[-+]?{DIGIT}+ 			yyextra->fFloat = atof(yytext); return FLOAT;

 /* ----------------------------------------- */
 /*	basic delimiters and markers */
 /* ----------------------------------------- */
"="					return EQUAL;
"("					return LPAR;
")"					return RPAR;
","					return SEP;
"/"					return PATHSEP;			/* OSC address and path separator */
";"					return ENDEXPR;			/* end of expression */
"$"					return VARSTART;

 /* ----------------------------------------- */
 /*	application messages */
 /* ----------------------------------------- */
"hello"			return HELLO;
"load"			return LOAD;
"require"		return REQUIRE;
"quit"			return QUIT;
"mouse"			return MOUSE;
"rootPath"		return ROOTPATH;
"defaultShow"	return DEFAULTSHOW;

"port"			return PORT;
"outport"		return OUTPORT;
"errport"		return ERRPORT;
"rate"			return RATE;

"startBench"	return STARTBENCH;
"stopBench"		return STOPBENCH;
"resetBench"	return RESETBENCH;
"writeBench"	return WRITEBENCH;

 /* ----------------------------------------- */
 /*	boolean */
 /* ----------------------------------------- */
"yes"		return YES;
"no"		return NO;

 /* ----------------------------------------- */
 /*	application vnode (debug) */
 /* ----------------------------------------- */
"osc"		return OSCDBG;

 /* ----------------------------------------- */
 /*	(file) watcher messages (should become obsolete) */
 /* ----------------------------------------- */
"add"		return ADD;
"remove"	return REMOVE;
"clear"		return CLEAR;

 /* ----------------------------------------- */
 /*	mapping messages */
 /* ----------------------------------------- */
"map"		return MAP;
"map+"		return MAPPLUS;
"mapf"		return MAPFILE;


 /* ----------------------------------------- */
 /*	IGrid messages */
 /* ----------------------------------------- */
"columns"	return COLUMNS;
"rows"		return ROWS;
"xborder"	return XBORDER;
"yborder"	return YBORDER;
"order"		return ORDER;

 /* ----------------------------------------- */
 /* guido specific messages */
 /* ----------------------------------------- */
"page"			return PAGE;
"dpage"			return DPAGE;
"pageFormat"	return PAGEFORMAT;


 /* ----------------------------------------- */
 /*	common messages */
 /* ----------------------------------------- */
"alias"		return ALIAS;
"set"		return SET;
"get"		return GET;
"del"		return DEL;
"export"	return EXPORT;
"rename"	return RENAME;
"save"		return SAVE;
"watch"		return WATCH;
"watch+"	return WATCHPLUS;
"push"		return PUSH;
"pop"		return POP;

 /* ----------------------------------------- */
 /*	common color messages */
 /* ----------------------------------------- */
"rgb"			return RGB;
"red"			return RED;
"green"			return GREEN;
"blue"			return BLUE;
"alpha"			return ALPHA;
"hsb"			return HSB;
"hue"			return HUE;
"saturation"	return SATURATION;
"brightness"	return BRIGHTNESS;
"drgb"			return DRGB;
"dred"			return DRED;
"dgreen"		return DGREEN;
"dblue"			return DBLUE;
"dalpha"		return DALPHA;
"dhsb"			return DHSB;
"dhue"			return DHUE;
"dsaturation"	return DSATURATION;
"dbrightness"	return DBRIGHTNESS;

 /* ----------------------------------------- */
 /*	common position messages */
 /* ----------------------------------------- */
"x"			return X;
"y"			return Y;
"z"			return Z;
"angle"		return ANGLE;
"scale"		return SCALE;
"xorigin"	return XORIGIN;
"yorigin"	return YORIGIN;
"dx"		return DX;
"dy"		return DY;
"dz"		return DZ;
"dangle"	return DANGLE;
"dscale"	return DSCALE;
"dxorigin"	return DXORIGIN;
"dyorigin"	return DYORIGIN;

"shear"		return SHEAR;
"rotatex"	return ROTATEX;
"rotatey"	return ROTATEY;
"rotatez"	return ROTATEZ;
"show"		return SHOW;
"effect"	return EFFECT;

 /* ----------------------------------------- */
 /*	common date messages */
 /* ----------------------------------------- */
"date"		return DATE;
"duration"	return DURATION;
"ddate"		return DDATE;
"dduration" return DDURATION;
"clock"		return CLOCK;
"durClock"	return DURCLOCK;

 /* ----------------------------------------- */
 /*	common debug messages */
 /* ----------------------------------------- */
"name"		return NAME;

 /* ----------------------------------------- */
 /*	common rect shaped messages */
 /* ----------------------------------------- */
"width"		return WIDTH;
"height"	return HEIGHT;

 /* ----------------------------------------- */
 /*	common shape messages */
 /* ----------------------------------------- */
"penColor"		return PENCOLOR;
"penAlpha"		return PENALPHA;
"pendAlpha"		return PENDALPHA
"penWidth"		return PENWIDTH;
"penStyle"  	return PENSTYLE;

 /* ----------------------------------------- */
 /*	scene messages */
 /* ----------------------------------------- */
"new"			return NEW;
"reset"			return RESET;
"fullscreen"	return FULLSCREEN;
"frameless"		return FRAMELESS;
"absolutexy"	return ABSOLUTEXY; 

 /* ----------------------------------------- */
 /*	sync node messages */
 /* ----------------------------------------- */
"*"				return WILDCARD;

 /* ----------------------------------------- */
 /*	signals messages */
 /* ----------------------------------------- */
"default"			return DEFAULT;
"size"	 			return SIZE;
"\\[[0-9+\\"		return SIGSELECT;
"\\[[0-9+~[0-9*\\"	return SIGSELECTMOD;
"debug"				return DEBUG;

 /* ----------------------------------------- */
 /*	video mapping */
 /* ----------------------------------------- */
"videoMap"			return VIDEOMAP;
"videoMapf"			return VIDEOMAPFILE;


 /* ----------------------------------------- */
 /*	objects types */
 /* ----------------------------------------- */
"line"		return TLINE;
"polygon"	return TPOLYGON;
"rect"		return TRECT;
"curve"		return TCURVE;
"ellipse"	return TELLIPSE;

"graph"		return TGRAPH;
"fastgraph"	return TFASTGRAPH;
"grid"		return TGRID;

"gmn"		return TGMN;
"gmnf"		return TGMNFILE;
"html"		return THTML;
"htmlf"		return THTMLFILE;
"svg"		return TSVG;
"svgf"		return TSVGFILE;
"txt"		return TTXT;
"txtf"		return TTXTFILE;

"img"		return TIMG;
"video"		return TVIDEO;



 /* ----------------------------------------- */
 /*	special get forms */
 /* ----------------------------------------- */
"version"			return VERSION;
"guido-version"		return GUIDOVERSION;
"musicxml-version"	return MXMLVERSION;

 /* special gmn get forms */
"pageCount"			return PAGECOUNT;
"pageDate"			return PAGEDATE;

 /* special signal get forms */
"dimension"			return DIMENSION;

 /* special faust plugin get forms */
"in"				return IN;
"out"				return OUT;

 /* ----------------------------------------- */
 /*	effects */
 /* ----------------------------------------- */
"none"				return NONE;
"blur"				return BLUR;
"colorize"			return COLORIZE; 
"shadow"			return SHADOW;

 /* ----------------------------------------- */
 /*	blur hint */
 /* ----------------------------------------- */
"performance"		return BPERFORMANCE;
"quality"			return BQUALITY;
"animation"			return BANIMATION;

 /* ----------------------------------------- */
 /*	pen styles */
 /* ----------------------------------------- */
"solid"				return PENSOLID;
"dash"				return PENDASH;
"dot"				return PENDOT;
"dashDot"			return PENDASHDOT;
"dashDotDot"		return PENDASHDOTDOT;

 /* ----------------------------------------- */
 /*	sync align and stretch */
 /* ----------------------------------------- */
"syncOver"		return SYNCOVER;
"syncTop"		return SYNCTOP;
"syncBottom"	return SYNCBOTTOM;
"h"				return HSTRETCH;
"v"				return VSTRETCH;
"hv"			return HVSTRETCH;

 /* ----------------------------------------- */
 /*	interaction messages */
 /* ----------------------------------------- */
"mouseDown"		return MOUSEDOWN;
"mouseUp"		return MOUSEUP;
"mouseEnter"	return MOUSEENTER;
"mouseLeave"	return MOUSELEAVE;
"mouseMove"		return MOUSEMOVE;
"doubleClick"	return DOUBLECLICK;

"timeEnter"		return TIMEENTER;
"timeLeave"		return TIMELEAVE;
"durEnter"		return DURENTER;
"durLeave"		return DURLEAVE;

"newElement"	return NEWELEMENT;


 /* ----------------------------------------- */
 /*	comments */
 /* ----------------------------------------- */
{SPACE}*"#"			BEGIN CMNTLN;
{SPACE}*"!"			BEGIN CMNTLN;
<CMNTLN>.*	
<CMNTLN>{EOL}+		BEGIN INITIAL;

<COMMENT>.|{EOL}*
<COMMENT>"(*"		nested++; 
<COMMENT>"*)"		if (--nested==0) BEGIN INITIAL;
{SPACE}*"(*"		nested=1; BEGIN COMMENT;

{STARTID}{IDCHAR}*						yyextra->fText = yytext; return IDENTIFIER;		/* identifiers */
{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*	yyextra->fText = yytext; return MAPIDENTIFIER;	/* identifiers with map name */

"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;
<DQSTR>([^\"]|"\\\"")*		yyextra->fText = unescape(yytext); return STRING;
<QSTR>([^']|"\\'")*			yyextra->fText = unescape(yytext); return STRING;
<DQSTR>\"					BEGIN INITIAL;
<QSTR>'						BEGIN INITIAL;

"<?"{SPACE}*"lua"			BEGIN LUASECTION;
<LUASECTION>"?>"			BEGIN INITIAL;
<LUASECTION>({EOL}|"?"[^>]|[^?])*	yyextra->fText = unescape(yytext); return LUASCRIPT;

"<?"{SPACE}*"javascript"	BEGIN JSECTION;
<JSECTION>"?>"				BEGIN INITIAL;
<JSECTION>({EOL}|"?"[^>]|[^?])*		yyextra->fText = unescape(yytext); return JSCRIPT;


{RESTART}{RECHAR}*				yyextra->fText = yytext; return REGEXP;			/* regular expression */
{RESTART}*"["..*"]"{RECHAR}*	yyextra->fText = yytext; return REGEXP;			/* regular expression */

{SPACE}+			;   /* eat up space */

{EOL}					yylloc->first_column=0; /* ignore */

.						yyextra->fText = yytext; return ERR;

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

