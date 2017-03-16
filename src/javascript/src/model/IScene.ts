///<reference path="Methods.ts"/>
///<reference path="MethodsJS.ts"/>
///<reference path="IRectShape.ts"/>

const kabsolute : string = "absolute";
const krelative : string = "relative";

class IScene extends IRectShape {

        fAbsolutePos          : boolean;
        fPositionTypeModified : boolean;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kSceneType;        
        this.fAbsolutePos = false;

        this.fPosition.setWidth (1);
        this.fPosition.setHeight (1);
        this.fMsgHandlerMap[knew_SetMethod] = new TMsgHandlerVoid(this._newScene());
        this.fMsgHandlerMap["redraw"]	= new TMsgHandlerVoid(this._redraw());
        this.fMsgHandlerMap[kposition_GetSetMethod] = new TMsgHandlerText(this._setPositionStyle());
        this.fGetMsgHandlerMap[kposition_GetSetMethod]  = new TGetMsgHandlerText(this._getPositionStyle());
    }

    getPositionStyle()   : string 	    	{ if (this.fAbsolutePos) return kabsolute;
                                              else return krelative;}
    _getPositionStyle() : GetStringMethod 	{ return () => this.getPositionStyle(); }

    setPositionStyle (position : string): void 	{
        switch (position){
            case kabsolute : this.fAbsolutePos = true;
            break;
            case krelative : this.fAbsolutePos = false;
            break;
            default : ITLError.badParameter("position", position);}}
    _setPositionStyle(): SetStringMethod    { return (type : string) => this.setPositionStyle(type) }

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