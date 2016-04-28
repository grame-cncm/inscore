///<reference path="IObject.ts"/>

class IRectShape extends IObject {
    protected kRectShapeType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kRectShapeType = '';
    }
    
    //accept (Updater*): void
    // virtual MsgHandler::msgStatus set (const IMessage* msg);
		
}