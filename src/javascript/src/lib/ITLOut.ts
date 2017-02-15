
///<reference path="../globals.ts"/>

class ITLOut {
    
    static write (str: string) { 
    	console.log (str); 
    	INScore.postMessage ("/ITL/log", ["write", str]);
    }
}