
///<reference path="../globals.ts"/>

class ITLError {
    
    static write (str: string) {
    	let errmsg = "Error: " + str; 
    	console.log (errmsg); 
    	INScore.postMessage ("/ITL/log", ["write", errmsg]);
    }
    static badParameter (msg: string, p: any) 	{ this.write ("bad parameter " + p + " in " + msg); }

}