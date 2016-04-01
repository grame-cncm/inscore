
class Param<T> {
	protected fParam: T;    
    
    constructor(val:T) {
    this.fParam = val;    
    }
    
    getValue(): T { return this.fParam }
}

class IMessage {
 
    protected fAddress: string;
    protected fArguments: Array<Param<any>>;
    protected fHasMessage: boolean = true;		
    
    constructor(address: string) {
        this.fAddress = address; 
        this.fArguments = new Array;      
    }   
   
    add<T>(val: T): void { this.fArguments.push(new Param<T>(val)) };
    
    address(): string { return this.fAddress }
    
    message(): string { 
        if (!this.fHasMessage) { return "" };
	    return this.fArguments[0].getValue(); 
    }

    param(i: number): Param<any> { return this.fArguments[i] } 
    
    isParam(i: number, type: string): boolean {  
        if (typeof this.fArguments[i] === type) { return true }
        else { return false }
    }   
    
    size(): number {
        var n: number = this.fArguments.length; 
        return this.fHasMessage ? n -1 : n; 
    }
    /*
    cast_param(i: number, val: number): boolean {
        if (param(i)->isType<float>()) {
            val = param(i)->value<float>(0);
            return true;
        }
        if (param(i)->isType<int>()) {
            int nval = param(i)->value<int>(0);
            val = float(nval);
            return true;
        }
        return false;
    }
    
    param(int i, rational& val): boolean
    { 
        if (size() < (i+2)) return false;
        int num, denum;
        if (!param(i, num))		return false;
        if (!param(i+1, denum)) return false;
        val = rational(num, denum);
        return true;
    }
*/
}