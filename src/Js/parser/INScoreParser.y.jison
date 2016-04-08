
/* INScore lexical grammar */

%{
	function debugmsg(str){
		typeof console !== 'undefined' ? console.log(str) : print(str);
	}
%}


%start inscore

%% 
//_______________________________________________
// relaxed simple INScore format specification
//_______________________________________________
inscore		: expr
			| inscore expr
			;

//_______________________________________________
// expression of the script language
//_______________________________________________
expr		: message  ENDEXPR		{ parser.msgs.push($1); }
			| variabledecl ENDEXPR	{ }
			| script				{ }
			| ENDSCRIPT				{ debugmsg("expr ENDSCRIPT "); this.done = true; }
			;

//_______________________________________________
// javascript support
//_______________________________________________
script		: JSCRIPT			{ if ($1.length) debugmsg("expr script: " + $1);}
			;

//_______________________________________________
// messages specification (extends osc spec.)
//_______________________________________________
message		: address			{ $$ = new Message($1, new Array()); }
			| address params	{ debugmsg("message: " + $1.toString() + " " + $2.toString());
								  $$ = new Message($1, $2); }
			;

//_______________________________________________
// address specification (extends osc spec.)
//_______________________________________________
address		: OSCADDRESS			{ $$ = new Address("", 0, $1);}
			| relativeaddress		{ $$ = new Address("", 0, $1);}
			| urlprefix OSCADDRESS	{ $1.osc = $2; $$ = $1; }
			;

relativeaddress	: POINT OSCADDRESS	{ $$ = $1 + $2; }
			;

urlprefix	: hostname COLON UINT	{ $$ = new Address($1, parseInt($3), ""); }
			| IPNUM COLON UINT		{ $$ = new Address($1, parseInt($3), ""); }
			;

hostname	: HOSTNAME				{ $$ = $1; }
			| varname				{ $$ = $1; }
			;

identifier	: IDENTIFIER			{ $$ = $1; }
			| REGEXP				{ $$ = $1; }
			;

//_______________________________________________
// parameters definitions
// eval need a special case since messages are expected as argument
//_______________________________________________
params		: param					{ $$ = new Array(); $$.push($1); }
			| variable				{ $$ = $1; }
			| params variable		{ $$ = $1.concat($2); }
			| params param			{ $1.push($2); $$ = $1; }
			;

variable	: VARSTART varname		{ $$ = new Array(parser.vars[$2]); }
			;

param	: INT				{ $$ = parseInt($1); }
		| UINT				{ $$ = parseInt($1); }
		| FLOAT				{ $$ = parseFloat($1); }
		| identifier		{ $$ = $1; }
		| STRING			{ $$ = $1; }
		| expression		{ $$ = $1; }
		| script			{ $$ = $1; }
		;

//_______________________________________________
// variable declaration
//_______________________________________________
variabledecl : varname EQUAL params	{ debugmsg("variabledecl: " + $1 + " = " + $3); parser.vars[$1] = $3; }
			;

varname		: IDENTIFIER			{ $$ = $1; }
			;


%%
parser.msgs = new Array;
parser.vars = new Array;

function Message (addr, params) {
	this.address = addr;		// a prototyped array (see below)
	this.params = params;		// an array
}

function Address (ip, port, osc) {
	this.ip = ip;				// a string
	this.port = port;			// an integer
	this.osc = osc;				// a string
	this.toString = function() { return this.ip + (this.port ? (":" + this.port) : "") + this.osc; }
}

parser.parseError = function(str, hash) {
	typeof console !== 'undefined' ? console.log(str) : print(str);
}
