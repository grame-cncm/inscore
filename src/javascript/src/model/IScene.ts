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
        this.fMsgHandlerMap[knew_SetMethod] = new TMsgHandlerVoid(this._newScene());
        this.fMsgHandlerMap["redraw"] = new TMsgHandlerVoid(this._redraw());
        this.fMsgHandlerMap[kposition_GetSetMethod] = new TMsgHandlerText(this._setPositionStyle());
        this.fGetMsgHandlerMap[kposition_GetSetMethod] = new TGetMsgHandlerText(this._getPositionStyle());

        this.fMsgHandlerMap[kfullscreen_GetSetMethod] = new TMsgHandlerNum(this._setFullScreen());
        this.fGetMsgHandlerMap[kfullscreen_GetSetMethod] = new TGetMsgHandlerNum(this._getFullScreen());
    }

    getPositionStyle(): string { return this.fAbsolutePos ? IScene.kAbsolute : IScene.kRelative; }
    _getPositionStyle(): GetStringMethod { return () => this.getPositionStyle(); }

    setPositionStyle(position: string): eMsgStatus {
        switch (position) {
            case IScene.kAbsolute:
                this.fAbsolutePos = true;
                return eMsgStatus.kProcessed;
            case IScene.kRelative:
                this.fAbsolutePos = false;
                return eMsgStatus.kProcessed;
            default:
                return eMsgStatus.kBadParameters
        }
    }
    _setPositionStyle(): SetStringMethod { return (type: string) => this.setPositionStyle(type) }

    getRScale(): number { return this.fPosition.getScale(); }
    getRSizeAsScale(): number { return Math.min(this.fPosition.getWidth(), this.fPosition.getHeight()) / 2; }
    timeAble(): void { }

    redraw(): void { this.posPropagate(); }
    _redraw(): SetVoidMethod { return () => this.redraw(); };

    newScene(): void { }
    _newScene(): SetVoidMethod { return () => this.newScene(); };

    getScene(): IObject { return this; }
    getSet(): IMessage { return new IMessage(this.getOSCAddress(), knew_SetMethod); }

    //-----------------------FullScreen-GetSet---------------------------
    getFullScreen(): number {
        if (this.fFullScreen) return 1;
        else return 0;
    }
    _getFullScreen(): GetNumMethod { return () => this.getFullScreen(); }

    setFullScreen(full: number): eMsgStatus {
        this.fFullScreen = full ? true : false;
        return eMsgStatus.kProcessed;
    }
    _setFullScreen(): SetNumMethod { return (full: number) => this.setFullScreen(full) }
}