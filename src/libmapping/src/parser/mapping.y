%{

#include <iostream>
#include <assert.h>
#include "mapreader.h"

%}

%pure-parser
%locations
%defines
%error-verbose
%lex-param { void* scanner  }
%parse-param { libmapping::mapparser* context }

%start mapping

/*------------------------------ tokens ------------------------------*/
%token NUMBER FLOAT
%token SEGMENT_START SEGMENT_END
%token RATIONAL_BAR  INTERVAL_BAR SEP TIMESEP ERROR

/*------------------------------ types ------------------------------*/
%union 
{         
	long int				num;
	float					real;
	libmapping::rational*							rat;
	libmapping::TInterval<long>*					longInterv;
	libmapping::TInterval<float>*					floatInterv;
	libmapping::TSegment<long,2>*					long2Dseg;
	libmapping::TSegment<float,2>*					float2Dseg;
	libmapping::TSegment<libmapping::rational,1>*	rationalseg;
	libmapping::TSegment<long,1>*					longseg;
	libmapping::TSegment<float,1>*					floatseg;
};

%type <num>			NUMBER number
%type <real>		FLOAT floatnumber abstime
%type <rat>			rational
%type <longInterv>	longInterval
%type <floatInterv>	floatInterval
%type <long2Dseg>	long2DSegment
%type <float2Dseg>	float2DSegment
%type <rationalseg>	rationalSegment abstimeSegment
%type <longseg>		longSegment
%type <floatseg>	floatSegment

%{

#include <iostream>
#include "mapparser.h"
#include "mapreader.h"

typedef void * yyscan_t;

int yyerror (YYLTYPE* locp, libmapping::mapparser*, const char*);
int maperror (libmapping::mapparser*);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void*);
int	yywrap(yyscan_t yyscanner)		{ return(1); }

#define scanner context->fScanner
#define _maperror maperror(context); YYERROR;
//#define _maperror YYERROR;

%}


%%

//_______________________________________________
mapping		: long2D_to_rational_map
			| float2D_to_rational_map
			| long_to_rational_map
			| float_to_rational_map
			| long2D_to_atime_map
			| float2D_to_atime_map
			| long_to_atime_map
			| float_to_atime_map
			;


//_______________________________________________
// time segment definition
rationalSegment	: SEGMENT_START INTERVAL_BAR rational SEP rational INTERVAL_BAR SEGMENT_END	
									{ $$ = new libmapping::TSegment<libmapping::rational,1>(*$3,*$5);  delete $3; delete $5;}
				;

abstime  		: number TIMESEP number TIMESEP number	
									{ $$ = ((($1 * 60) + $3) * 100 + $5) / 100.f; }
				;

abstimeSegment  : SEGMENT_START INTERVAL_BAR abstime SEP abstime INTERVAL_BAR SEGMENT_END	
									{ $$ = new libmapping::TSegment<libmapping::rational,1>(libmapping::rational($3/4),libmapping::rational($5/4));}
				;



//_______________________________________________
// intpoint to relative time mapping
long2D_to_rational_map	: long2D_to_rational_relation
						| long2D_to_rational_relation long2D_to_rational_map
						;
long2D_to_rational_relation	: long2DSegment rationalSegment						{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}
long2DSegment			: SEGMENT_START longInterval longInterval SEGMENT_END	{ $$ = new libmapping::TSegment<long,2>(*$2,*$3); delete $2; delete $3; }
						;
longInterval			: INTERVAL_BAR number SEP number INTERVAL_BAR			{ $$ = new libmapping::TInterval<long>($2,$4); }
						;

//_______________________________________________
// frame to relative time mapping
long_to_rational_map	: long_to_rational_relation
						| long_to_rational_relation long_to_rational_map
						;
long_to_rational_relation: longSegment rationalSegment							{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}
longSegment				: SEGMENT_START longInterval SEGMENT_END				{ $$ = new libmapping::TSegment<long,1>(*$2); delete $2; }
						;

//_______________________________________________
// float to relative time mapping
float_to_rational_map	: float_to_rational_relation
						| float_to_rational_relation float_to_rational_map
						;
float_to_rational_relation: floatSegment rationalSegment						{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}
floatSegment			: SEGMENT_START floatInterval SEGMENT_END				{ $$ = new libmapping::TSegment<float,1>(*$2); delete $2; }
						;
floatInterval			: INTERVAL_BAR floatnumber SEP floatnumber INTERVAL_BAR	{ $$ = new libmapping::TInterval<float>($2,$4); }
						;

//_______________________________________________
// graphic to relative time mapping
float2D_to_rational_map : float2D_to_rational_relation
						| float2D_to_rational_relation float2D_to_rational_map
						;
float2D_to_rational_relation: float2DSegment rationalSegment					{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}
float2DSegment			: SEGMENT_START floatInterval floatInterval SEGMENT_END	{ $$ = new libmapping::TSegment<float,2>(*$2,*$3);  delete $2; delete $3; }
						;


//_______________________________________________
// absolute time mappins
long2D_to_atime_map			: long2D_to_atime_relation
							| long2D_to_atime_relation long2D_to_atime_map
long2D_to_atime_relation	: long2DSegment abstimeSegment						{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}

float2D_to_atime_map 		: float2D_to_atime_relation
							| float2D_to_atime_relation float2D_to_atime_map
float2D_to_atime_relation	: float2DSegment abstimeSegment						{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}

long_to_atime_map			: long_to_atime_relation
							| long_to_atime_relation long_to_atime_map
							;
long_to_atime_relation		: longSegment abstimeSegment						{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}

float_to_atime_map			: float_to_atime_relation
							| float_to_atime_relation float_to_atime_map
							;
float_to_atime_relation		: floatSegment abstimeSegment						{ if (!context->fReader->map(*$1,*$2)) { _maperror } delete $1; delete $2;}


//_______________________________________________
// numbers
rational		: number RATIONAL_BAR number	{ $$ = new libmapping::rational($1,$3); }
				;
number			: NUMBER						{ $$ = context->fInt; }
				;
floatnumber		: FLOAT							{ $$ = context->fFloat; }
				;

%%


namespace libmapping 
{

bool mapparser::parse() 
{
	return yyparse (this) ? false : true;
}

} // end namespace

int maperror (libmapping::mapparser* context) {
	return yyerror ( 0, context, context->fReader->maperror());	
}

int yyerror(YYLTYPE* loc, libmapping::mapparser* context, const char*s) {
	context->fReader->error(s, (loc ? loc->last_line : 0));
	if (loc) loc->last_line = 1;
	return 1;
}


