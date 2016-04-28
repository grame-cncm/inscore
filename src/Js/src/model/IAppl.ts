///<reference path="IObject.ts"/>
///<reference path="IProxy.ts"/>

class IAppl extends IObject {
 
    protected kApplType: string;
    
    constructor() {
        super('ITL');
        this.kApplType = 'IAppl';
        this.fTypeString = 'IAppl'; 
    } 

    getAppl() : IObject		{ return this; }

    protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: msgStatus, obj?: IObject }	{
        return IProxy.execute (msg, name, parent);
    }
}