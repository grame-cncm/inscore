///<reference path="IObject.ts"/>

class IRectShape extends IObject {
    protected kRectShapeType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        
        this.kRectShapeType = '';
    }

    create(name: string, parent: IObject): IRectShape { return new IRectShape(name, parent); }
    
    //accept (Updater*): void
    // virtual MsgHandler::msgStatus set (const IMessage* msg);
		
}