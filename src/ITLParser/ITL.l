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
HOSTCHAR [-a-zA-Z0-9]

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
 /*";"					return ENDMSG;			 end of expression */
"$"					return VARSTART;

 /* ----------------------------------------- */
 /*	application messages */
 /* ----------------------------------------- */
 /*
"hello"			yyextra->fText = yytext; return HELLO;
"load"			yyextra->fText = yytext; return LOAD;
"require"		yyextra->fText = yytext; return REQUIRE;
"quit"			yyextra->fText = yytext; return QUIT;
"showMouse"		yyextra->fText = yytext; return SHOWMOUSE;
"rootPath"		yyextra->fText = yytext; return ROOTPATH;
"defaultShow"	yyextra->fText = yytext; return DEFAULTSHOW;

"port"			yyextra->fText = yytext; return PORT;
"outport"		yyextra->fText = yytext; return OUTPORT;
"errport"		yyextra->fText = yytext; return ERRPORT;
"rate"			yyextra->fText = yytext; return RATE;

"startBench"	yyextra->fText = yytext; return STARTBENCH;
"stopBench"		yyextra->fText = yytext; return STOPBENCH;
"resetBench"	yyextra->fText = yytext; return RESETBENCH;
"writeBench"	yyextra->fText = yytext; return WRITEBENCH;
 */
 /* ----------------------------------------- */
 /*	boolean */
 /* ----------------------------------------- */
 /*
"yes"		yyextra->fText = yytext; return YES;
"no"		yyextra->fText = yytext; return NO;
 */
 /* ----------------------------------------- */
 /*	application vnode (debug) */
 /* ----------------------------------------- */
 /*"osc"		yyextra->fText = yytext; return OSCDBG; */

 /* ----------------------------------------- */
 /*	(file) watcher messages (should become obsolete) */
 /* ----------------------------------------- */
 /*
"add"		yyextra->fText = yytext; return ADD;
"remove"	yyextra->fText = yytext; return REMOVE;
"clear"		yyextra->fText = yytext; return CLEAR;
 */
 /* ----------------------------------------- */
 /*	mapping messages */
 /* ----------------------------------------- */
 /*
"map"		yyextra->fText = yytext; return MAP;
"map+"		yyextra->fText = yytext; return MAPPLUS;
"mapf"		yyextra->fText = yytext; return MAPFILE;
 */

 /* ----------------------------------------- */
 /*	IGrid messages */
 /* ----------------------------------------- */
 /*
"columns"	yyextra->fText = yytext; return COLUMNS;
"rows"		yyextra->fText = yytext; return ROWS;
"xborder"	yyextra->fText = yytext; return XBORDER;
"yborder"	yyextra->fText = yytext; return YBORDER;
"order"		yyextra->fText = yytext; return ORDER;
 */
 /* ----------------------------------------- */
 /* guido specific messages */
 /* ----------------------------------------- */
 /*
"page"			yyextra->fText = yytext; return PAGE;
"dpage"			yyextra->fText = yytext; return DPAGE;
"pageFormat"	yyextra->fText = yytext; return PAGEFORMAT;
 */

 /* ----------------------------------------- */
 /*	common messages */
 /* ----------------------------------------- */
 /*
"alias"		yyextra->fText = yytext; return ALIAS;
"set"		yyextra->fText = yytext; return SET;
"get"		yyextra->fText = yytext; return GET;
"del"		yyextra->fText = yytext; return DEL;
"export"	yyextra->fText = yytext; return EXPORT;
"rename"	yyextra->fText = yytext; return RENAME;
"save"		yyextra->fText = yytext; return SAVE;
"watch"		yyextra->fText = yytext; return WATCH;
"watch+"	yyextra->fText = yytext; return WATCHPLUS;
"push"		yyextra->fText = yytext; return PUSH;
"pop"		yyextra->fText = yytext; return POP;
 */
 /* ----------------------------------------- */
 /*	common color messages */
 /* ----------------------------------------- */
 /*
"rgb"			yyextra->fText = yytext; return RGB;
"red"			yyextra->fText = yytext; return RED;
"green"			yyextra->fText = yytext; return GREEN;
"blue"			yyextra->fText = yytext; return BLUE;
"alpha"			yyextra->fText = yytext; return ALPHA;
"hsb"			yyextra->fText = yytext; return HSB;
"hue"			yyextra->fText = yytext; return HUE;
"saturation"	yyextra->fText = yytext; return SATURATION;
"brightness"	yyextra->fText = yytext; return BRIGHTNESS;
"drgb"			yyextra->fText = yytext; return DRGB;
"dred"			yyextra->fText = yytext; return DRED;
"dgreen"		yyextra->fText = yytext; return DGREEN;
"dblue"			yyextra->fText = yytext; return DBLUE;
"dalpha"		yyextra->fText = yytext; return DALPHA;
"dhsb"			yyextra->fText = yytext; return DHSB;
"dhue"			yyextra->fText = yytext; return DHUE;
"dsaturation"	yyextra->fText = yytext; return DSATURATION;
"dbrightness"	yyextra->fText = yytext; return DBRIGHTNESS;
 */
 /* ----------------------------------------- */
 /*	common position messages */
 /* ----------------------------------------- */
 /*
"x"			yyextra->fText = yytext; return X;
"y"			yyextra->fText = yytext; return Y;
"z"			yyextra->fText = yytext; return Z;
"angle"		yyextra->fText = yytext; return ANGLE;
"scale"		yyextra->fText = yytext; return SCALE;
"xorigin"	yyextra->fText = yytext; return XORIGIN;
"yorigin"	yyextra->fText = yytext; return YORIGIN;
"dx"		yyextra->fText = yytext; return DX;
"dy"		yyextra->fText = yytext; return DY;
"dz"		yyextra->fText = yytext; return DZ;
"dangle"	yyextra->fText = yytext; return DANGLE;
"dscale"	yyextra->fText = yytext; return DSCALE;
"dxorigin"	yyextra->fText = yytext; return DXORIGIN;
"dyorigin"	yyextra->fText = yytext; return DYORIGIN;

"shear"		yyextra->fText = yytext; return SHEAR;
"rotatex"	yyextra->fText = yytext; return ROTATEX;
"rotatey"	yyextra->fText = yytext; return ROTATEY;
"rotatez"	yyextra->fText = yytext; return ROTATEZ;
"show"		yyextra->fText = yytext; return SHOW;
"hide"		yyextra->fText = yytext; return HIDE;
"effect"	yyextra->fText = yytext; return EFFECT;
 */
 /* ----------------------------------------- */
 /*	common date messages */
 /*
"date"		yyextra->fText = yytext; return DATE;
"duration"	yyextra->fText = yytext; return DURATION;
"ddate"		yyextra->fText = yytext; return DDATE;
"dduration" yyextra->fText = yytext; return DDURATION;
"clock"		yyextra->fText = yytext; return CLOCK;
"durClock"	yyextra->fText = yytext; return DURCLOCK;
*/
 /* ----------------------------------------- */
 /*	common debug messages */
 /* ----------------------------------------- */
 /*
"name"		yyextra->fText = yytext; return NAME;
 */
 /* ----------------------------------------- */
 /*	common rect shaped messages */
 /* ----------------------------------------- */
 /*
"width"		yyextra->fText = yytext; return WIDTH;
"height"	yyextra->fText = yytext; return HEIGHT;
 */
 /* ----------------------------------------- */
 /*	common shape messages */
 /* ----------------------------------------- */
 /*
"penColor"		yyextra->fText = yytext; return PENCOLOR;
"penAlpha"		yyextra->fText = yytext; return PENALPHA;
"pendAlpha"		yyextra->fText = yytext; return PENDALPHA
"penWidth"		yyextra->fText = yytext; return PENWIDTH;
"penStyle"  	yyextra->fText = yytext; return PENSTYLE;
 */
 /* ----------------------------------------- */
 /*	scene messages */
 /* ----------------------------------------- */
 /*
"new"			yyextra->fText = yytext; return NEW;
"reset"			yyextra->fText = yytext; return RESET;
"fullscreen"	yyextra->fText = yytext; return FULLSCREEN;
"frameless"		yyextra->fText = yytext; return FRAMELESS;
"absolutexy"	yyextra->fText = yytext; return ABSOLUTEXY;
 */
 /* ----------------------------------------- */
 /*	sync node messages */
 /* ----------------------------------------- */
 /*
 "*"				yyextra->fText = yytext; return WILDCARD;
 */
 /* ----------------------------------------- */
 /*	signals messages */
 /* ----------------------------------------- */
 /*
"default"			yyextra->fText = yytext; return DEFAULT;
"size"	 			yyextra->fText = yytext; return SIZE;
"\\[[0-9+\\"		yyextra->fText = yytext; return SIGSELECT;
"\\[[0-9+~[0-9*\\"	yyextra->fText = yytext; return SIGSELECTMOD;
"debug"				yyextra->fText = yytext; return DEBUG;
 */
 /* ----------------------------------------- */
 /*	video mapping */
 /* ----------------------------------------- */
 /*
"videoMap"			yyextra->fText = yytext; return VIDEOMAP;
"videoMapf"			yyextra->fText = yytext; return VIDEOMAPFILE;
 */

 /* ----------------------------------------- */
 /*	objects types */
 /* ----------------------------------------- */
 /*
"line"		yyextra->fText = yytext; return TLINE;
"polygon"	yyextra->fText = yytext; return TPOLYGON;
"rect"		yyextra->fText = yytext; return TRECT;
"curve"		yyextra->fText = yytext; return TCURVE;
"ellipse"	yyextra->fText = yytext; return TELLIPSE;

"graph"		yyextra->fText = yytext; return TGRAPH;
"fastgraph"	yyextra->fText = yytext; return TFASTGRAPH;
"grid"		yyextra->fText = yytext; return TGRID;

"gmn"		yyextra->fText = yytext; return TGMN;
"gmnf"		yyextra->fText = yytext; return TGMNFILE;
"html"		yyextra->fText = yytext; return THTML;
"htmlf"		yyextra->fText = yytext; return THTMLFILE;
"svg"		yyextra->fText = yytext; return TSVG;
"svgf"		yyextra->fText = yytext; return TSVGFILE;
"txt"		yyextra->fText = yytext; return TTXT;
"txtf"		yyextra->fText = yytext; return TTXTFILE;

"img"		yyextra->fText = yytext; return TIMG;
"video"		yyextra->fText = yytext; return TVIDEO;
"file"		yyextra->fText = yytext; return TFILE;
 */


 /* ----------------------------------------- */
 /*	special get forms */
 /* ----------------------------------------- */
 /*
"version"			yyextra->fText = yytext; return VERSION;
"guido-version"		yyextra->fText = yytext; return GUIDOVERSION;
"musicxml-version"	yyextra->fText = yytext; return MXMLVERSION;
 */
 /* special gmn get forms */
 /*
"pageCount"			yyextra->fText = yytext; return PAGECOUNT;
"pageDate"			yyextra->fText = yytext; return PAGEDATE;
 */
 /* special signal get forms */
 /*
"dimension"			yyextra->fText = yytext; return DIMENSION;
 */
 /* special faust plugin get forms */
 /*
"in"				yyextra->fText = yytext; return IN;
"out"				yyextra->fText = yytext; return OUT;
 */
 /* ----------------------------------------- */
 /*	effects */
 /* ----------------------------------------- */
 /*
"none"				yyextra->fText = yytext; return NONE;
"blur"				yyextra->fText = yytext; return BLUR;
"colorize"			yyextra->fText = yytext; return COLORIZE;
"shadow"			yyextra->fText = yytext; return SHADOW;
 */
 /* ----------------------------------------- */
 /*	blur hint */
 /* ----------------------------------------- */
 /*
"performance"		yyextra->fText = yytext; return BPERFORMANCE;
"quality"			yyextra->fText = yytext; return BQUALITY;
"animation"			yyextra->fText = yytext; return BANIMATION;
 */
 /* ----------------------------------------- */
 /*	pen styles */
 /* ----------------------------------------- */
 /*
"solid"				yyextra->fText = yytext; return PENSOLID;
"dash"				yyextra->fText = yytext; return PENDASH;
"dot"				yyextra->fText = yytext; return PENDOT;
"dashDot"			yyextra->fText = yytext; return PENDASHDOT;
"dashDotDot"		yyextra->fText = yytext; return PENDASHDOTDOT;
 */
 /* ----------------------------------------- */
 /*	sync align and stretch */
 /* ----------------------------------------- */
 /*
"syncOver"		yyextra->fText = yytext; return SYNCOVER;
"syncTop"		yyextra->fText = yytext; return SYNCTOP;
"syncBottom"	yyextra->fText = yytext; return SYNCBOTTOM;
"h"				yyextra->fText = yytext; return HSTRETCH;
"v"				yyextra->fText = yytext; return VSTRETCH;
"hv"			yyextra->fText = yytext; return HVSTRETCH;
 */
 /* ----------------------------------------- */
 /*	interaction messages */
 /* ----------------------------------------- */
 /*
"mouseDown"		yyextra->fText = yytext; return MOUSEDOWN;
"mouseUp"		yyextra->fText = yytext; return MOUSEUP;
"mouseEnter"	yyextra->fText = yytext; return MOUSEENTER;
"mouseLeave"	yyextra->fText = yytext; return MOUSELEAVE;
"mouseMove"		yyextra->fText = yytext; return MOUSEMOVE;
"doubleClick"	yyextra->fText = yytext; return DOUBLECLICK;

"timeEnter"		yyextra->fText = yytext; return TIMEENTER;
"timeLeave"		yyextra->fText = yytext; return TIMELEAVE;
"durEnter"		yyextra->fText = yytext; return DURENTER;
"durLeave"		yyextra->fText = yytext; return DURLEAVE;

"newElement"	yyextra->fText = yytext; return NEWELEMENT;
 */

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

 /* ----------------------------------------- */
 /*	identifiers */
 /* ----------------------------------------- */
{STARTID}{IDCHAR}*						yyextra->fText = yytext; return IDENTIFIER;		/* identifiers */
 /*"$"{STARTID}{IDCHAR}*					yyextra->fText = yytext; return VARIABLE;	 */
{LETTER}{IDCHAR}*":"{LETTER}{IDCHAR}*	yyextra->fText = yytext; return MAPIDENTIFIER;	/* identifiers with map name */

 /* ----------------------------------------- */
 /*	quoted strings */
 /* ----------------------------------------- */
"\""						BEGIN DQSTR;
"'"							BEGIN QSTR;
<DQSTR>([^\"]|"\\\"")*		yyextra->fText = unescape(yytext); return STRING;
<QSTR>([^']|"\\'")*			yyextra->fText = unescape(yytext); return STRING;
<DQSTR>\"					BEGIN INITIAL;
<QSTR>'						BEGIN INITIAL;


 /* ----------------------------------------- */
 /*	lang sections */
 /* ----------------------------------------- */
"<?"{SPACE}*"lua"			BEGIN LUASECTION;
<LUASECTION>"?>"			BEGIN INITIAL;
<LUASECTION>({EOL}|"?"[^>]|[^?])*	yyextra->fText = unescape(yytext); return LUASCRIPT;

"<?"{SPACE}*"javascript"	BEGIN JSECTION;
<JSECTION>"?>"				BEGIN INITIAL;
<JSECTION>({EOL}|"?"[^>]|[^?])*		yyextra->fText = unescape(yytext); return JSCRIPT;

 /* ----------------------------------------- */
 /*	hostname part */
 /* ----------------------------------------- */
 /* {HOSTCHAR}+				return HOSTNAME; */

 /* ----------------------------------------- */
 /*	regular expressions */
 /* ----------------------------------------- */
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

