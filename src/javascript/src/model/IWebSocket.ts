///<reference path="IObject.ts"/>

interface WebSocketInformer {
		getView(): VObjectView;
		getFrequency(): number;
		getPort(): number;
		//getParseEnv(): TParseEnv;
}

interface WebSocketController {
		start(port: number): boolean;
		stop()      : void;
		running()   : boolean;
		clients()   : number;
}
/*
interface TParseEnv {
	getJSEngine(): TJSEngine;
	getLUAEngine(): TLua;
	error(): void;
	parseEnv(): TParseEnv;
}
*/


class IWebSocket extends IObject {
	private fWebServer  : WebSocketController;
    protected fPort     : number;
    protected fFrequency: number;

    public kIWebSocketType  : string;
    public kMethodKey       : string;
    public kIdKey           : string;
    public kStatusKey       : string;
    public kVersionKey      : string;

    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kWebSocketType;
        
        super.setHandlers();
    }



	setControler(ctrl: WebSocketController): void	{ this.fWebServer = ctrl; }
	
    getPort()       : number    { return this.fPort; }
	getFrequency()  : number    { return this.fFrequency; }  

    //getParseEnv()   : TParseEnv	{ return this.getAppl(); }

    running()   : boolean		{ return this.fWebServer.running(); }
    status()    : string		{ return this.running() ? "running" : "stopped"; }
    
    start(port: number) : boolean   { return this.fWebServer.start(port); }    



    set(msg: IMessage): eMsgStatus {
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status;

        // Two parameters are mandatory : port and notification time.
        if (msg.size() != 3) return eMsgStatus.kBadParameters;

        let port = -1;
        let frequency = -1;

        let a = msg.paramNum(3), b = msg.paramNum(4);

        if (!a.correct  ||  !b.correct)     { return eMsgStatus.kBadParameters; }
        if (!a.value    ||  !b.value)       { return eMsgStatus.kBadParameters; }

        let restart = false;
        if (frequency != this.fFrequency) {
            this.fFrequency = frequency;
            restart = true;
        }

        if (port != this.fPort) {
            this.fPort = port;
            restart = true;
        }

        if(restart) {
            if ( !this.start(port) ) {
                //ITLErr << "Cannot create web socket server on port " << this.fPort << ITLEndl;
                return eMsgStatus.kCreateFailure;
            }
        }
        return eMsgStatus.kProcessed;
    }



/*
    getMsgs(msg: IMessage): IMessageList {
        let outMsgs: IMessageList;
        for ( let i = 0 ; i < msg.size() ; i++ ) {
            let param: string = "-";
            msg.param(i, param);

            if ( param == "clients" ) {
                let msg: IMessage = IMessage.create(getOSCAddress(), param);
                msg << fWebServer.clients();
                outMsgs.list().push_back (msg);
            }
        }
        outMsgs.list().push_back (IObject.getMsgs(msg).list());
        return outMsgs;
    }
*/

    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fPort, this.fFrequency]); 
    }


}