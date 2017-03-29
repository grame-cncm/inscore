
/* INScore lexical grammar */

%{	
	function debugyacc(str){
//		typeof console !== 'undefined' ? console.log(str) : print(str);
	}

	function array2string(a){
		if (typeof a == "string") return a;
		if (typeof a == "object") {
			let out = "";
			for (let i=0; i<a.length; i++) {
				out += array2string(a[i]) + "\n";
			}
			return out;
		}
		return "";
	}
	function rparse(str){
		if (!str.length) return;
		INScoreParser.parse (str);
	}
	function getvar(v){
		let vars = parser.vars;
		let out  = "";
		for (let key in vars)
			if (key === v) return vars[key];
		console.log("Warning! variable $" + v + " is undefined");
		return "$"+v;
	}
	function context_vars(){
		let vars = parser.vars;
		let out  = "";
		for (let key in vars)
			out += "var " + key + "=" + vars[key][0].toString() + ";\n";
		return out;
	}
	function context_eval(str) {
		if (__testparser) return "";

		var gInscoreParserContext = this;
		this['print'] = function (s) { console.log(s); }
		return gInscoreParserContext.eval( context_vars() + str);
	}

	var __testparser = false;
	if (typeof ITLError === 'undefined') {		// we're in a test context
		ITLError = [];
		ITLError['write'] = function (s) { console.log(s); }
		function context_eval(str) { return ""; }
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
			| ENDSCRIPT				{ debugyacc("expr ENDSCRIPT "); return true; }
			;

//_______________________________________________
// javascript support
//_______________________________________________
script		: JSCRIPT			{ if ($1.length) rparse (array2string(context_eval($1) )); }
			;

//_______________________________________________
// messages specification (extends osc spec.)
//_______________________________________________
message		: address			{ $$ = new Message($1, new Array()); }
			| address params	{ $$ = new Message($1, $2); debugyacc($$.toString()); }
			| address eval LEFTPAR messagelist RIGHTPAR	{ $4.unshift($2); $$ = new Message($1, $4); }
			| address eval variable						{ $3.unshift($2); $$ = new Message($1, $3); }
			;

messagelist : message									{ $$ = new Array(); $$.push($1); }
			| messagelist messagelistseparator message 	{ $1.push($3); $$ = $1; }
			;
messagelistseparator	: COMMA
						| COLON
						;

//_______________________________________________
// address specification (extends osc spec.)
//_______________________________________________
address		: OSCADDRESS			{ $$ = new Address("", 0, $1); }
			| relativeaddress		{ $$ = new Address("", 0, $1); }
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
params		: param					{ $$ = [$1]; }
			| variable				{ $$ = [$1]; }
			| params variable		{ $$ = $1.concat($2); }
			| params param			{ $1.push($2); $$ = $1; }
			;

variable	: VARSTART varname					{ $$ = getvar($2); }
			| VARSTART LEFTPAR message RIGHTPAR { $$ = new Array($3); }
			;

param	: INT				{ $$ = parseInt($1); }
		| UINT				{ $$ = parseInt($1); }
		| FLOAT				{ $$ = parseFloat($1); }
		| identifier		{ $$ = $1; }
		| STRING			{ $$ = $1; }
		| EXPRESSION		{ $$ = $1; }
		| HOSTNAME			{ $$ = $1; }
		| LEFTPAR messagelist RIGHTPAR	{ $$ = $2; }
		| script			{ $$ = $1; }
		;

//_______________________________________________
// variable declaration
//_______________________________________________
variabledecl : varname EQUAL params	{ debugyacc("variabledecl: " + $1 + " = " + $3); parser.vars[$1] = $3; }
			;

varname		: IDENTIFIER			{ $$ = $1; }
			;


%%
parser.msgs = new Array;
parser.vars = new Array;

function Address (ip, port, osc) {
	this.ip = ip;				// a string
	this.port = port;			// an integer
	this.osc = osc;				// a string
	this.toString = function() { return this.ip + (this.port ? (":" + this.port) : "") + this.osc; }
}

function Message (addr, params) {
	this.address = addr;		// a prototyped array (see below)
	this.params = params;		// an array
	this.toString = function() { return this.address.toString() + " " + this.params.toString(); }
}

parser.get = (function () {
	var msgs = parser.msgs;
	parser.msgs = [];
	parser.vars = [];
	return msgs;
})

parser.parseError = function(str, hash) { ITLError.write(str); }

