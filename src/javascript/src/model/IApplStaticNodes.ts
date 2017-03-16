///<reference path="../controller/IMessage.ts"/>
///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../vhtmlview/VHtmlLog.ts"/>
///<reference path="IStaticNode.ts"/>

class IApplLog extends IStaticNode {
	protected fLog: Array<string>
	protected fClear: boolean

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = 'log';
        this.fLog 	= new Array<string>();
        this.fClear = false;
        this.fPosition.setVisible (0);
        this.fPosition.setWidth (0.8);
        this.fPosition.setHeight (0.5);
        this.setView(new VHtmlLog());
    }    

    setHandlers(): void {
        this.fMsgHandlerMap[kget_SetMethod] 		= new TMethodHandler(this._get());

        this.fMsgHandlerMap[kclear_SetMethod] 		= new TMsgHandlerVoid(this._clear());
        this.fMsgHandlerMap[kwrite_SetMethod] 		= new TMethodHandler(this._write());
        this.fMsgHandlerMap[kforeground_SetMethod] 	= new TMsgHandlerVoid(this._foreground());

        this.fMsgHandlerMap[kwrap_GetSetMethod] 	= new TMsgHandlerNum(this._wrap());
        this.fMsgHandlerMap[ksave_SetMethod] 		= new TMsgHandlerText(this._savelog());
        this.fMsgHandlerMap[kx_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setXPos());
        this.fMsgHandlerMap[ky_GetSetMethod] 		= new TMsgHandlerNum(this.fPosition._setYPos());
        this.fMsgHandlerMap[kwidth_GetSetMethod]	= new TMsgHandlerNum(this._setWidth());
        this.fMsgHandlerMap[kheight_GetSetMethod]	= new TMsgHandlerNum(this._setHeight());
        this.fMsgHandlerMap[kshow_GetSetMethod]		= new TMsgHandlerNum(this.fPosition._setVisible());
        this.fMsgHandlerMap[kscale_GetSetMethod] 	= new TMethodHandler(this._scale());

        this.fGetMsgHandlerMap[kx_GetSetMethod]		= new TGetMsgHandlerNum(this.fPosition._getXPos());
        this.fGetMsgHandlerMap[ky_GetSetMethod]		= new TGetMsgHandlerNum(this.fPosition._getYPos());
        this.fGetMsgHandlerMap[kwidth_GetSetMethod]	= new TGetMsgHandlerNum(this.fPosition._getWidth());
        this.fGetMsgHandlerMap[kheight_GetSetMethod]= new TGetMsgHandlerNum(this.fPosition._getHeight());
        this.fGetMsgHandlerMap[kshow_GetSetMethod] 	= new TGetMsgHandlerNum(this.fPosition._getVisible());
    }

	content(): Array<string> 	{ return this.fLog; }
	done(): void 				{ this.fLog=[]; this.fClear = false; }
	cleared(): boolean 			{ return this.fClear; }
	clear(): void 				{ this.fClear = true; this.fLog=[]; }
	_clear(): SetVoidMethod 	{ return () => this.clear(); }
	// support the scale message due to the current strategy to handle windows resize
	_scale(): SetMsgMethod 		{ return (m) => { return eMsgStatus.kProcessedNoChange; } }

	write(msg: IMessage): eMsgStatus {
		let p = msg.params();
		let s = "";
		for (let i=1; i<p.length; i++)
			s += p[i].toString() + " ";
		this.fLog.push(s);
		return eMsgStatus.kProcessed; 
	}
	_write(): SetMsgMethod	{ return (m) => this.write(m); }

	foreground(): void 		{ }
	_foreground(): SetVoidMethod { return () => this.foreground(); }

	wrap(n: number): void 	{	}
	_wrap(): SetNumMethod	{ return (n) => this.wrap(n); }

	savelog(file: string): void { }
	_savelog(): SetStringMethod { return (f) => this.savelog(f); }

}