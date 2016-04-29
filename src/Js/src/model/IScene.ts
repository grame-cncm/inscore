///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>

class IScene extends IRectShape {
    
    protected kSceneType: string;
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.kSceneType = 'scene';
        this.fTypeString = this.kSceneType;
        
        this.fMsgHandlerMap[knew_SetMethod] = new TMsgHandlerVoid(this._newScene());
    }
    
    newScene(): void 			{ }
    _newScene(): SetVoidMethod 	{ return () => this.newScene(); };
    
    getScene(): IObject 		{ return this; }
    getSet(): IMessage			{ return new IMessage(this.getOSCAddress(), knew_SetMethod); }
}