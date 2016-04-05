
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
        if (typeof this.fArguments[i].getValue() === type) { return true }
        else { return false }
    }   
    
    size(): number {
        var n: number = this.fArguments.length; 
        return this.fHasMessage ? n -1 : n; 
    }
    
    cast_param(i: number, val: number): Array<any> {
        var result = new Array;
        if ( this.fHasMessage ) { i ++; }
        if ( this.isParam(i, 'number')) {
            val = this.param(i).getValue();
            result['val'] = val;
            result['status'] = true;
            return result;
        }
        
        else {
            result['val'] = 0;
            result['bool'] = false;
            return result;
        }     
    }            
}