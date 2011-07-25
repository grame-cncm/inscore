%{

#include <iostream>
#include <string>
#include <assert.h>

#include "IMessageStream.h"
#include "ITLError.h"

extern inscore::IMessageList* gMessageList;

typedef union {         
	public:
	int		num;
	float	real;
	std::string* str;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage*			msg;
	inscore::IMessageList*		msgList;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED
#define YYERROR_VERBOSE

#include "ITLparse.h++"
#include "ITLlex.c++"

int ITLerror(const char*s);
int	ITLwrap()		{ return(1); }

using namespace std;
namespace inscore
{

%}

//%pure_parser

%start ITLfile

/*------------------------------ tokens ------------------------------*/
%token INT
%token FLOAT
%token IDENTIFIER
%token EQUAL
%token MAPIDENTIFIER
%token REGEXP
%token PATHSEP
%token WINSEP
%token STRING
%token MSG
%token ERROR
%token ENDEXPR

%token LPAR
%token RPAR
%token SEP
%token LOOP

/*------------------------------   types  ------------------------------*/
%type <num> 	INT //count
%type <real>	FLOAT
%type <str>		STRING MSG PATHSEP IDENTIFIER MAPIDENTIFIER REGEXP 
%type <str>		identifier oscaddress oscpath msgstring // varname
%type <msg>		message
%type <p>		param
%type <plist>	params
//%type <msgList>	ITLfile

%%

//_______________________________________________
// relaxed simple ITL format specification
//_______________________________________________
ITLfile		: expr
			| ITLfile expr
			;

//_______________________________________________
expr		: message  			{ gMessageList->push_back($1); }
//			| variable ENDEXPR
//			| loop
			;

//_______________________________________________
//variable	: varname EQUAL INT		{ cout << "int    variable " << $1->c_str()  << " -> " << atoi(ITLtext) << endl; }
//			| varname EQUAL FLOAT	{ cout << "float  variable " << $1->c_str()  << " -> " << atof(ITLtext) << endl; }
//			| varname EQUAL STRING	{ cout << "string variable " << $1->c_str()  << " -> " << ITLtext << endl; }
//			;
//			
//loop		: loopstart looped RPAR ENDEXPR			{ cout << "loop end" << endl; }
//			;
//			
//loopstart	: LOOP LPAR varname SEP count			{ cout << "loop " << $3->c_str() << " " << $5 << endl; }
//			;
//
//looped		: messagelist
//			| loop
//			| looped messagelist
//			;
//
//count		: INT							{ $$ = atoi(ITLtext); }
//			;
//
//messagelist :
//			| message						{ gMessageList->push_back($1); }
//			| messagelist message
//			;

//_______________________________________________
message		: oscaddress params	ENDEXPR				{	$$ = new inscore::IMessage(*$1, "", *$2); delete $1; delete $2; }
			| oscaddress msgstring ENDEXPR			{	$$ = new inscore::IMessage(*$1, *$2);  delete $1; delete $2; }
			| oscaddress msgstring params ENDEXPR	{	$$ = new inscore::IMessage(*$1, *$2, *$3) delete $1; delete $2; delete $3; }
			;

oscaddress	: oscpath				{ $$ = $1; }
			| oscaddress oscpath	{ *$1 += *$2; $$ = $1; delete $2; }
			;

oscpath		: PATHSEP identifier	{ $$ = new string("/" + *$2); delete $2; }
			;

identifier	: IDENTIFIER		{ $$ = new string(ITLtext); }
			| REGEXP			{ $$ = new string(ITLtext); }
			;

//varname		: IDENTIFIER		{ $$ = new string(ITLtext); }
//			;

msgstring	: MSG				{ $$ = new string(ITLtext); }
			| IDENTIFIER		{ $$ = new string(ITLtext); }
			| REGEXP			{ $$ = new string(ITLtext); }
			| MAPIDENTIFIER		{ $$ = new string(ITLtext); }
			;

params		: param				{ $$ = new inscore::IMessage::argslist; $$->push_back(*$1); delete $1; }
			| params param		{ $1->push_back(*$2); $$ = $1; delete $2; }
			;

param		: INT				{ $$ = new Sbaseparam(new inscore::IMsgParam<int>(atoi(ITLtext))); }
			| FLOAT				{ $$ = new Sbaseparam(new inscore::IMsgParam<float>(atof(ITLtext))); }
			| STRING			{ $$ = new Sbaseparam(new inscore::IMsgParam<std::string>(ITLtext)); }
//			| IDENTIFIER		{ $$ = new Sbaseparam(new inscore::IMsgParam<std::string>(ITLtext)); }
//			| MAPIDENTIFIER		{ $$ = new Sbaseparam(new inscore::IMsgParam<std::string>(ITLtext)); }
			;

%%

} // end namespace

using namespace inscore;
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
