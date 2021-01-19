
///<reference path="IObject.ts"/>

//-------------------------------------------------------------- 
// Debug node of IObject
//-------------------------------------------------------------- 
class IDebug extends IObject {
    fShowMap : 	boolean; 
    fShowName : boolean;
    
    constructor(name: string, parent: IObject) { 
        super( name, parent );
        this.fTypeString = kDebugType;
        this.fShowMap = false; 
        this.fShowName = false; 
    }

    setHandlers(): void {
        this.fMsgHandlerMap[kname_GetSetMethod] = new TMsgHandlerNum( (n: number): void => { this.setShowName(n); } );
        this.fMsgHandlerMap[kmap_GetSetMethod] 	= new TMsgHandlerNum( (n: number): void => { this.setShowMap(n);  } );
        this.fMsgHandlerMap[kget_SetMethod] 	= new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.get(msg); } );

        this.fGetMsgHandlerMap[kname_GetSetMethod] 	= new TGetMsgHandlerNum( (): number => { return this.getShowName(); } );
        this.fGetMsgHandlerMap[kmap_GetSetMethod] 	= new TGetMsgHandlerNum( (): number => { return this.getShowMap(); } );
    }

	getShowMap() : number 		{ return this.fShowMap ? 1 : 0; }
	getShowName() : number 		{ return this.fShowName ? 1 : 0; }

	setShowMap(val: number) : void 		{ this.fShowMap  = val ? true : false; this.fParent.addState(eObjState.kModified); }
	setShowName(val: number) : void 	{ this.fShowName = val ? true : false; this.fParent.addState(eObjState.kModified); }

    createStaticNodes() : void {}
}
