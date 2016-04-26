%{
	function debugmsg(str){
		typeof console !== 'undefined' ? console.log(str) : print(str);
	}
%}

%start expr

%% 

expr		: WORD
			| expr WORD
			;

%%
