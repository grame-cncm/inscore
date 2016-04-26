
%{
function debugmsg(str){
	typeof console !== 'undefined' ? console.log("  lex: " + str) : print("  lex: " + str);
}
%}

%lex

%%

'#'.*		debugmsg ("COMMENTLINE: " + yytext); 
'!'.*		debugmsg ("COMMENTLINE: " + yytext); 

[_a-zA-Z0-9]+		return 'WORD';

.			;  /* ignore */

/lex

%start expr

%% 

expr		: WORD
			| expr WORD
			;

%%
