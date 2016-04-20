
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
        var out = this.paramStr(0);
        if (out.verif) { return out.param ; }
    }

    paramStr(i: number): { verif: boolean, param: string } { 
    	if (this.isString(i)) {
    		var param = this.fArguments[i];
    		return { verif: true, param: param };
    	}
    	return { verif: false, param: param };
    } 
    paramNum(i: number): { verif: boolean, param: number } { 
    	if (this.isNumber(i)) {
    		var param = this.fArguments[i];
    		return { verif: true, param: param };
    	}
    	return { verif: false, param: param };
    } 
    paramArray(i: number): { verif: boolean, param: Array<any> } { 
    	if (this.isArray(i)) {
    		var param = this.fArguments[i];
    		return { verif: true, param: param };
    	}
    	return { verif: false, param: param };
    } 
    
    isString(i: number): boolean 	{ return (typeof this.fArguments[i] === "string") ? true : false; }   
    isNumber(i: number): boolean 	{ return (typeof this.fArguments[i] === "number") ? true : false; }   
    isArray(i: number): boolean 	{ return (typeof this.fArguments[i] === "object") ? true : false; }   

   	size(): number 					{ return this.fArguments.length; }    
}