
class IMessage {
 
    protected fAddress: string;
    protected fArguments: Array<any>;
    
    constructor(input: string|IMessage, params? : Array<any>) {
        //if input is an adress
        if (typeof input === 'string') {
            this.fAddress = input; 
            this.fArguments = params ? params : new Array<any>();
        } 
        
        if (typeof input === 'object') {
            this.fAddress = input.fAddress; 
            this.fArguments = input.fArguments;
        }   
    }   
   
    add(val: any): void { this.fArguments.push(val); };
    
    address(): string { return this.fAddress; }
    
    arguments(): Array<any> { return this.fArguments; }
    
    message(): string { 
        var out = this.paramStr(0);
        if (out.verif) { return out.param ; }
    }

    param(i: number): string { return this.fArguments[i] }
    
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