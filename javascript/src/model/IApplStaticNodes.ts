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
        this.fMsgHandlerMap[kget_SetMethod] 		= new TMethodHandler	( (msg: IMessage): eMsgStatus => { return this.get(msg); } );

        this.fMsgHandlerMap[kclear_SetMethod] 		= new TMsgHandlerVoid	( (): void => { this.clear(); } );
        this.fMsgHandlerMap[kwrite_SetMethod] 		= new TMethodHandler	( (msg: IMessage): eMsgStatus => { return this.write(msg); } );
        this.fMsgHandlerMap[kforeground_SetMethod] 	= new TMsgHandlerVoid	( (): void => { this.foreground(); } );

        this.fMsgHandlerMap[kwrap_GetSetMethod] 	= new TMsgHandlerNum	( (n: number): void => { this.wrap(n); } );
        this.fMsgHandlerMap[ksave_SetMethod] 		= new TMsgHandlerText	( (s: string): void => { this.savelog(s); } );
        this.fMsgHandlerMap[kx_GetSetMethod] 		= new TMsgHandlerNum	( (n: number): void => { this.fPosition.setXPos(n); } );
        this.fMsgHandlerMap[ky_GetSetMethod] 		= new TMsgHandlerNum	( (n: number): void => { this.fPosition.setYPos(n); } );
        this.fMsgHandlerMap[kwidth_GetSetMethod]	= new TMsgHandlerNum	( (n: number): void => { this.setWidth(n); } );
        this.fMsgHandlerMap[kheight_GetSetMethod]	= new TMsgHandlerNum	( (n: number): void => { this.setHeight(n); } );
        this.fMsgHandlerMap[kshow_GetSetMethod]		= new TMsgHandlerNum	( (n: number): void => { this.fPosition.setVisible(n); } );
		// support the scale message due to the current strategy to handle window resize
        this.fMsgHandlerMap[kscale_GetSetMethod] 	= new TMethodHandler( (m: IMessage): eMsgStatus => { return eMsgStatus.kProcessedNoChange; } );

        this.fGetMsgHandlerMap[kx_GetSetMethod]		= new TGetMsgHandlerNum	( (): number => { return this.fPosition.getXPos(); } )
        this.fGetMsgHandlerMap[ky_GetSetMethod]		= new TGetMsgHandlerNum	( (): number => { return this.fPosition.getYPos(); } )
        this.fGetMsgHandlerMap[kwidth_GetSetMethod]	= new TGetMsgHandlerNum	( (): number => { return this.fPosition.getWidth(); } )
        this.fGetMsgHandlerMap[kheight_GetSetMethod]= new TGetMsgHandlerNum	( (): number => { return this.fPosition.getHeight(); } )
        this.fGetMsgHandlerMap[kshow_GetSetMethod] 	= new TGetMsgHandlerNum	( (): number => { return this.fPosition.getVisible(); } )
    }

	content(): Array<string> 	{ return this.fLog; }
	done(): void 				{ this.fLog=[]; this.fClear = false; }
	cleared(): boolean 			{ return this.fClear; }
	clear(): void 				{ this.fClear = true; this.fLog=[]; }

	write(msg: IMessage): eMsgStatus {
		let p = msg.params();
		let s = "";
		for (let i=1; i<p.length; i++)
			s += p[i].toString() + " ";
		this.fLog.push(s);
		return eMsgStatus.kProcessed; 
	}

	foreground(): void 			{ }
	wrap(n: number): void 		{ }
	savelog(file: string): void { }
}