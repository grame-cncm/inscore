%{

#include <iostream>
#include <assert.h>
#include "mapreader.h"
#include "TInterval.h"
#include "TSegment.h"
#include "TRect.h"
#include "rational.h"

class YYSTYPE {         
	public:
	long int	num;
	float		real;
	INScore::rational				rat;
	INScore::LongInterval			longInterv;
	INScore::FloatInterval			floatInterv;
	INScore::IntPointSegment		ipseg;
	INScore::GraphicSegment			grseg;
	INScore::RelativeTimeSegment	rseg;
	INScore::FrameSegment			intseg;
	INScore::FloatSegment			flseg;
};

#define YYSTYPE_IS_DECLARED
#define YYERROR_VERBOSE

#include "mapparse.h++"
#include "maplex.c++"

int itlmaperror(const char*s);
int	itlmapwrap()		{ return(1); }

extern INScore::mapreader* gReader;

//#define parseDebug
#ifdef parseDebug
#define debug(msg)		cout << msg << endl
#else
#define debug(msg)
#endif

using namespace std;
namespace INScore
{

%}

//%pure_parser

%start mapping

/*------------------------------ numbers ------------------------------*/
%token NUMBER
%token FLOAT

/*------------------------------ markers ------------------------------*/
%token SEGSTART
%token SEGEND
%token INTERVAL

/*------------------------------   misc  ------------------------------*/
%token RATIONALBAR
%token SEP
%token ERROR

/*------------------------------   types  ------------------------------*/
%type <num> 	NUMBER number
%type <real> 	FLOAT floatnumber
%type <rat>		rational
%type <longInterv>	intInterval
%type <floatInterv>	floatInterval
%type <ipseg>	_2DintSegment
%type <grseg>	_2DfloatSegment
%type <rseg>	timeSegment
%type <intseg>	intSegment
%type <flseg>	_1DfloatSegment

%%

//_______________________________________________
mapping		: _2Dint2timemap			{ debug("_2Dint2timemap"); }
			| _2Dfloat2timemap			{ debug("_2Dfloat2timemap"); }
			| _1Dint2timemap			{ debug("_1Dint2timemap"); }
			| _1Dfloat2timemap			{ debug("_1Dfloat2timemap"); }
			;


//_______________________________________________
// time segment definition
timeSegment		: SEGSTART INTERVAL rational SEP rational INTERVAL SEGEND	{ debug("timeSegment"); $$ = RelativeTimeSegment($3,$5); }
				;

//_______________________________________________
// intpoint to relative time mapping
_2Dint2timemap	: _2Dint2timeRelation
				| _2Dint2timeRelation _2Dint2timemap
				;
_2Dint2timeRelation	: _2DintSegment timeSegment				{ debug("map _2DintSegment timeSegment"); if (!gReader->map($1,$2)) YYERROR;}
_2DintSegment	: SEGSTART intInterval intInterval SEGEND	{ debug("_2DintSegment"); $$ = IntPointSegment($2,$3); }
				;
intInterval		: INTERVAL number SEP number INTERVAL		{ debug("intInterval"); $$ = LongInterval($2,$4); }
				;

//_______________________________________________
// frame to relative time mapping
_1Dint2timemap	: _1Dint2timeRelation
				| _1Dint2timeRelation _1Dint2timemap
				;
_1Dint2timeRelation: intSegment timeSegment					{ debug("map intSegment timeSegment"); if (!gReader->map($1,$2)) YYERROR;}
intSegment		: SEGSTART intInterval SEGEND				{ debug("intSegment"); $$ = FrameSegment($2); }
				;

//_______________________________________________
// float to relative time mapping
_1Dfloat2timemap: _1Dfloat2timeRelation
				| _1Dfloat2timeRelation _1Dfloat2timemap
				;
_1Dfloat2timeRelation: _1DfloatSegment timeSegment				{ debug("map _1DfloatSegment timeSegment"); if (!gReader->map($1,$2)) YYERROR;}
_1DfloatSegment	: SEGSTART floatInterval SEGEND					{ debug("_1DfloatSegment"); $$ = FloatSegment($2); }
				;
floatInterval	: INTERVAL floatnumber SEP floatnumber INTERVAL	{ debug("floatInterval"); $$ = FloatInterval($2,$4); }
				;

//_______________________________________________
// graphic to relative time mapping
_2Dfloat2timemap: _2Dfloat2timeRelation
				| _2Dfloat2timeRelation _2Dfloat2timemap
				;
_2Dfloat2timeRelation: _2DfloatSegment timeSegment				{ debug("map _2DfloatSegment timeSegment"); if (!gReader->map($1,$2)) YYERROR;}
_2DfloatSegment	: SEGSTART floatInterval floatInterval SEGEND	{ debug("_2DfloatSegment"); $$ = GraphicSegment($2,$3); }
				;

//_______________________________________________
// misc
rational		: number RATIONALBAR number	{ debug("rational"); $$ = rational($1,$3); }
				;
number			: NUMBER					{ debug("NUMBER"); $$ = atol(itlmaptext); }
				;
floatnumber		: FLOAT						{ debug("FLOAT"); $$ = atof(itlmaptext); }
				;

%%

} // end namespace

int itlmaperror(const char*s) {
	int err = gReader->error(s, itlmaplineno);
	YY_FLUSH_BUFFER;
	itlmaplineno = 1;
	return err;
}
