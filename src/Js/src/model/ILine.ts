///<reference path="IObject.ts"/>

class ILine extends IObject {
    
    protected kLineType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kLineType = 'line';
        this.fTypeString = this.kLineType;
    }

    getSet(address: string): IMessage	{
    	return new IMessage(address, [kset_SetMethod, this.kLineType]); 
    }
}