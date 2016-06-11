
%{
function debugmsg(str){
	typeof console !== 'undefined' ? console.log(str) : print(str);
}
%}

%lex

EOL		[\x0a\x0d]

%%

'#'.*		debugmsg ("COMMENTLINE: " + yytext); 
'!'.*		debugmsg ("COMMENTLINE: " + yytext); 

[_a-zA-Z0-9]+		return 'WORD';

.			;  /* ignore */
{EOL}		;  /* ignore */

/lex

%start expr

%% 

expr		: WORD			{ debugmsg ("WORD: " + yytext); }
			| expr WORD
			;

%%
