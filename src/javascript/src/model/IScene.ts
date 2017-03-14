///<reference path="Methods.ts"/>
///<reference path="IRectShape.ts"/>

class IScene extends IRectShape {
    
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kSceneType;        

        this.fPosition.setWidth (1);
        this.fPosition.setHeight (1);
        this.fMsgHandlerMap[knew_SetMethod] = new TMsgHandlerVoid(this._newScene());
        this.fMsgHandlerMap["redraw"]	= new TMsgHandlerVoid(this._redraw());
    }

    getRScale(): number 		{ return this.fPosition.getScale(); }    
    getRSizeAsScale(): number 	{ return Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()) / 2; }
    timeAble(): void 			{ }

    redraw(): void 				{ this.posPropagate(); }
    _redraw(): SetVoidMethod 	{ return () => this.redraw(); };

    newScene(): void 			{ }
    _newScene(): SetVoidMethod 	{ return () => this.newScene(); };
    
    getScene(): IObject 		{ return this; }
    getSet(): IMessage			{ return new IMessage(this.getOSCAddress(), knew_SetMethod); }
}