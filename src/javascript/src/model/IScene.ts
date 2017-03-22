///<reference path="Methods.ts"/>
///<reference path="MethodsJS.ts"/>
///<reference path="IRectShape.ts"/>

interface Document {
    mozCancelFullScreen(): void;
    msExitFullscreen(): void;
}
interface HTMLElement {
    mozRequestFullScreen(): void;
    msRequestFullscreen(): void;
}

class IScene extends IRectShape {
    static kAbsolute: string = "absolute";
    static kRelative: string = "relative";

    fAbsolutePos: boolean;
    fPositionTypeModified: boolean;
    fFullScreen: boolean;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kSceneType;
        this.fAbsolutePos = false;
        this.fPosition.setWidth(1);
        this.fPosition.setHeight(1);
    }
    
    setHandlers() : void {
    	super.setHandlers();
        this.fMsgHandlerMap[knew_SetMethod] 			= new TMsgHandlerVoid ( () : void => { this.newScene(); });
        this.fMsgHandlerMap["redraw"] 					= new TMsgHandlerVoid ( () : void => { this.redraw(); });
        this.fMsgHandlerMap[kposition_GetSetMethod] 	= new TMsgHandlerText ( (s: string): void => { this.setPositionStyle(s); } );
        this.fMsgHandlerMap[kfullscreen_GetSetMethod] 	= new TMsgHandlerNum  ( (n: number): void => { this.setFullScreen(n); } );

        this.fGetMsgHandlerMap[kfullscreen_GetSetMethod]= new TGetMsgHandlerNum ( () : number => { return this.getFullScreen(); } );
        this.fGetMsgHandlerMap[kposition_GetSetMethod] 	= new TGetMsgHandlerText( () : string => { return this.getPositionStyle(); } );
    }

    getPositionStyle(): string { return this.fAbsolutePos ? IScene.kAbsolute : IScene.kRelative; }
    setPositionStyle(position: string): void { this.fAbsolutePos =  (position === IScene.kAbsolute); this.fPosition.modify(); }

    getRScale(): number 		{ return this.fPosition.getScale(); }
    getRSizeAsScale(): number 	{ return Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()) / 2; }
    timeAble(): void { }

    redraw(): void { this.posPropagate(); }
    newScene(): void { }

    getScene(): IObject { return this; }
    getSet(): IMessage 	{ return new IMessage(this.getOSCAddress(), knew_SetMethod); }

    //-----------------------FullScreen-GetSet---------------------------
    getFullScreen(): number 			{ return this.fFullScreen ? 1 : 0; }
    setFullScreen(full: number): void 	{ this.fFullScreen = full ? true : false; }
}
