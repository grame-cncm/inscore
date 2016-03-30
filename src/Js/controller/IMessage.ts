
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
	    return this.fArguments[0] + ''; 
    }

    param(i: number): Param<any> { return this.fArguments[i] } 
    
    isParam(i: number, type: string): boolean {  
        if (typeof this.fArguments[i] === type) { return true }
        else { return false }
    }    

}