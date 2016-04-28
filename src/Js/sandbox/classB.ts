
///<reference path="classA.ts"/>


class ACaller {
    protected fObject: A;    
    protected fMethod: AMethod;    
    constructor(o: A, method: AMethod) { this.fObject = o; this.fMethod = method; }    
    handle(n: number) { 
		console.log("handling " + n);
    	this.fObject.call(this.fMethod, n ); 
    }
}
