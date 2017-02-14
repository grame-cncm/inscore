
///<reference path="inscore-interface.ts"/>
///<reference path="controller/IMessage.ts"/>
///<reference path="controller/THandlersPrototypes.ts"/>
///<reference path="controller/IGlue.ts"/>
///<reference path="lib/ITLError.ts"/>
///<reference path="lib/ITLOut.ts"/>
///<reference path="lib/TEnums.ts"/>
///<reference path="model/IObject.ts"/>
///<reference path="globals.ts"/>


class INScoreImpl extends INScoreInterface {
	private fVersion: number = 0.6;
	private fGlue: IGlue;
	private fErrStrings = new Array<string>();

	protected status2string (err: msgStatus) : string {
		let str = this.fErrStrings[err];
		return (str ? str : "unknown error " + err);
	}
	
	// ------------------------------------------------------------
	constructor ()		{ 
		super();
		this.fErrStrings[msgStatus.kBadAddress] = "bad OSC address";
		this.fErrStrings[msgStatus.kProcessed] = "processed";
		this.fErrStrings[msgStatus.kProcessedNoChange] = "processed without change";
		this.fErrStrings[msgStatus.kBadParameters] = "bad parameter";
		this.fErrStrings[msgStatus.kCreateFailure] = "create failed";
	}

	// ------------------------------------------------------------
	// static methods
	// ------------------------------------------------------------
	version () : number { return this.fVersion; }

	start (scene?: string) : void {
		if (!this.fGlue) {
			this.fGlue = new IGlue();
			this.fGlue.initEventHandlers();
		}
		this.fGlue.start(scene);
		ITLOut.write ("INScore version " + this.version());
	}

	getRoot() : IObject		{ return this.fGlue.getRoot(); }

	checkStatus (status: msgStatus, msg: IMessage) : void {
    	if (!(status & msgStatus.kProcessed + msgStatus.kProcessedNoChange))
    		ITLError.write (msg.toString() + ": " + this.status2string(status));
	}

	postMessage (address: string, params: Array<any>) : void {
    	let msg = new IMessage (address, params);
    	this.checkStatus (this.getRoot().process (msg), msg);
	}
}

INScore = new INScoreImpl();
function StartINScore(scene?: string) : void { 
	INScore.start(scene); 
}
