///<reference path="IObject.ts"/>

class IAppl extends IObject {
 
    protected kApplType: string;
    
    constructor() {
        super('ITL');
        this.kApplType = 'IAppl';
        this.fTypeString = 'IAppl'; 
    } 

    getAppl() : IObject		{ return this; }
}