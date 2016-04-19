
class IMessage {
 
    protected fAddress: string;
    protected fArguments: Array<any>;
    
    constructor(address: string, params? : Array<any>) {
        this.fAddress = address; 
        this.fArguments = params ? params : new Array<any>();      
    }   
   
    add(val: any): void { this.fArguments.push(val); };
    
    address(): string { return this.fAddress; }
    
    message(): string { 
        var out="";
        this.paramStr(0, out);
        return out;
    }

    paramStr(i: number, out: string): boolean { 
    	if (this.isString(i)) {
    		out = this.fArguments[i];
    		return true;
    	}
    	return false;
    } 
    paramNum(i: number, out: number): boolean { 
    	if (this.isNumber(i)) {
    		out = this.fArguments[i];
    		return true;
    	}
    	return false;
    } 
    paramArray(i: number, out: Array<any>): boolean { 
    	if (this.isArray(i)) {
    		out = this.fArguments[i];
    		return true;
    	}
    	return false;
    } 
    
    isString(i: number): boolean 	{ return (typeof this.fArguments[i] === "string") ? true : false; }   
    isNumber(i: number): boolean 	{ return (typeof this.fArguments[i] === "number") ? true : false; }   
    isArray(i: number): boolean 	{ return (typeof this.fArguments[i] === "object") ? true : false; }   

   	size(): number 					{ return this.fArguments.length; }    
}