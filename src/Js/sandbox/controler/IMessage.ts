
"use strict"

class MsgParamRetVal<T> {
    correct: boolean;
    value: T;
    constructor(check: boolean, val? : T) { this.correct = check; this.value = val; }
}


class IMessage {
 
    protected fAddress: string;
    protected fArguments: Array<any>;
   
    constructor(input: string|IMessage, params? : Array<any>|string) {
        //if input is an adress
        if (typeof input === 'string') {
            this.fAddress = input; 
            if (params) {
        		if (typeof params === 'string')	this.fArguments = new Array<any>(params);
            	else							this.fArguments = params;
            }
            else this.fArguments = new Array<any>();
        } 
        
        if (typeof input === 'object') {
            this.fAddress = input.fAddress; 
            this.fArguments = input.fArguments;
        }   
    }   
   
    // add a value to the parameters
    add(val: any): void 	{ this.fArguments.push(val); };    
    // add values to the parameters; arrays are checked and pushed as values
    push(val: any): void 	{
    	if (Array.isArray(val)) {
    		for (var i=0; i<val.length; i++) this.add (val[i]);
    	}
    	else this.fArguments.push(val); 
    };
    address(): string 		{ return this.fAddress; }
    param(i: number): any 	{ return this.fArguments[i]; }
    params(): Array<any> 	{ return this.fArguments; }

    paramStr(i: number): MsgParamRetVal<string> { 
    	return new MsgParamRetVal<string>(this.isType(i, "string"), this.fArguments[i]);
    }
    paramNum(i: number): MsgParamRetVal<number> { 
    	return new MsgParamRetVal<number>(this.isType(i, "number"), this.fArguments[i]);
    }
    paramArray(i: number): MsgParamRetVal<Array<any>> { 
    	return new MsgParamRetVal<Array<any>>(this.isType(i, "object"), this.fArguments[i]);
    }
    
    message(): MsgParamRetVal<string> 	{ return this.paramStr(0); }
    
    isType(i: number, type: string): boolean 	{ return (typeof this.fArguments[i] === type); }   
    isString(i: number): boolean 	{ return this.isType(i, "string"); }
    isNumber(i: number): boolean 	{ return this.isType(i, "number"); }
    isArray(i: number): boolean 	{ return this.isType(i, "object"); }

   	size(): number 					{ return this.fArguments.length; }
   	toString(): string	{
   		var out: string = this.fAddress;
   		for (var i: number=0; i < this.fArguments.length; i++) {
   			if (this.isType(i, "object"))
	   			out += " ( " + this.fArguments[i].toString() + " )";
   			else out += " " + this.fArguments[i].toString();
   		}
   		return out;
   	}  
}
