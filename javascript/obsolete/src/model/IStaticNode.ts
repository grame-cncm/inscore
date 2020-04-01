///<reference path="IObject.ts"/>

abstract class IStaticNode extends IObject {

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = 'static'; 
    }    

    abstract setHandlers(): void;
    del(): void 			{ }								// a static node cannot be deleted
	getSet(): IMessage 		{ let m: IMessage; return m; }	// and cannot be created using set
}