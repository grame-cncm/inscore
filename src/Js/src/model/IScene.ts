///<reference path="IRectShape.ts"/>

class IScene extends IRectShape {
    
    protected kSceneType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kSceneType = 'scene';
        this.fTypeString = this.kSceneType;
        
        this.fMsgHandlerMap[knew_SetMethod] = new TMethodHandler<IScene>(this, 'newScene');
    }
    
    newScene():msgStatus { return msgStatus.kProcessed }
    
    getScene(): IObject 			{ return this; }
}