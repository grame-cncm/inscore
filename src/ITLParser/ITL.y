%{

#include <iostream>
#include <string>
#include <assert.h>

#include "IMessageStream.h"
#include "ITLError.h"

extern INScore::IMessageList* gMessageList;

typedef union {         
	public:
	int		num;
	float	real;
	std::string* str;
	INScore::Sbaseparam *			p;
	INScore::IMessage::argslist*	plist;
	INScore::IMessage*			msg;
	INScore::IMessageList*		msgList;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED
#define YYERROR_VERBOSE

#include "ITLparse.h++"
#include "ITLlex.c++"

int ITLerror(const char*s);
int	ITLwrap()		{ return(1); }

using namespace std;
namespace INScore
{

%}

//%pure_parser

%start ITLfile

/*------------------------------ tokens ------------------------------*/
%token INT
%token FLOAT
%token IDENTIFIER
%token MAPIDENTIFIER
%token REGEXP
%token PATHSEP
%token WINSEP
%token STRING
%token MSG
%token ERROR
%token ENDMSG

/*------------------------------   types  ------------------------------*/
%type <num> 	INT
%type <real>	FLOAT
%type <str>		STRING MSG PATHSEP IDENTIFIER MAPIDENTIFIER REGEXP 
%type <str>		identifier oscaddress oscbase msgstring
%type <msg>		message
%type <p>		param
%type <plist>	params
%type <msgList>	ITLfile

%%

//_______________________________________________
// relaxed simple ITL format specification
//_______________________________________________
ITLfile		: message			{ gMessageList->push_back($1); }
			| ITLfile message	{ gMessageList->push_back($2); }
			;

//_______________________________________________
message		: oscaddress params				{	$$ = $2 ? new INScore::IMessage(*$1, "", *$2) : new INScore::IMessage(*$1); delete $1; delete $2; }
			| oscaddress msgstring params	{	$$ = $3 ? new INScore::IMessage(*$1, *$2, *$3) : new INScore::IMessage(*$1, *$2); 
												delete $1; delete $2; delete $3;
											}
			;

oscaddress	: oscbase				{ $$ = $1; }
			| oscaddress oscbase	{ *$1 += *$2; $$ = $1; delete $2; }
			;

oscbase		: PATHSEP identifier	{ $$ = new string("/" + *$2); delete $2; }
			;

identifier	: IDENTIFIER		{ $$ = new string(ITLtext); }
			| REGEXP			{ $$ = new string(ITLtext); }
			;

msgstring	: MSG				{ $$ = new string(ITLtext); }
			| IDENTIFIER		{ $$ = new string(ITLtext); }
			| REGEXP			{ $$ = new string(ITLtext); }
			| MAPIDENTIFIER		{ $$ = new string(ITLtext); }
			;

params		:					{ $$ = 0; }
			| param				{ $$ = new INScore::IMessage::argslist; $$->push_back(*$1); delete $1; }
			| params param		{ $1->push_back(*$2); $$ = $1; delete $2; }
			;

param		: INT				{ $$ = new Sbaseparam(new INScore::IMsgParam<int>(atoi(ITLtext))); }
			| FLOAT				{ $$ = new Sbaseparam(new INScore::IMsgParam<float>(atof(ITLtext))); }
			| STRING			{ $$ = new Sbaseparam(new INScore::IMsgParam<std::string>(ITLtext)); }
			| IDENTIFIER		{ $$ = new Sbaseparam(new INScore::IMsgParam<std::string>(ITLtext)); }
			| MAPIDENTIFIER		{ $$ = new Sbaseparam(new INScore::IMsgParam<std::string>(ITLtext)); }
			;

%%

} // end namespace

using namespace INScore;
int ITLerror(const char*s) {
//	int err = gReader->error(s, ITLlineno);
	YY_FLUSH_BUFFER;
#if 1
	cerr << "error line " << ITLlineno << ": " << s << endl;
#else
	ITLErr << "error line " << ITLlineno << ": " << s << ITLEndl;
#endif
	ITLlineno = 1;
	return 0; //err;
}
