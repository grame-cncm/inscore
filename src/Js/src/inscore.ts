
///<reference path="controller/IMessage.ts"/>
///<reference path="controller/THandlersPrototypes.ts"/>
///<reference path="controller/IGlue.ts"/>
///<reference path="lib/ITLError.ts"/>
///<reference path="lib/ITLOut.ts"/>
///<reference path="lib/TEnums.ts"/>
///<reference path="model/IAppl.ts"/>


class INScore {
	private static fVersion: number = 0.5;
	private static fAppl: IAppl;
	private static fGlue: IGlue;
	private static fErrStrings = new Array<string>();

	protected static status2string (err: msgStatus) : string {
		let str = this.fErrStrings[err];
		return (str ? str : "unknown error " + err);
	}
	
	// ------------------------------------------------------------
	constructor (root: IAppl)		{ 
		INScore.fAppl = root; 
		INScore.fErrStrings[msgStatus.kBadAddress] = "bad OSC address";
		INScore.fErrStrings[msgStatus.kProcessed] = "processed";
		INScore.fErrStrings[msgStatus.kProcessedNoChange] = "processed without change";
		INScore.fErrStrings[msgStatus.kBadParameters] = "bad parameter";
		INScore.fErrStrings[msgStatus.kCreateFailure] = "create failed";
	}

	// ------------------------------------------------------------
	// static methods
	// ------------------------------------------------------------
	static version () : number { return INScore.fVersion; }

	static start (scene?: string) : void {
		if (!INScore.fGlue) {
			INScore.fGlue = new IGlue();
			INScore.fGlue.initEventHandlers();
		}
		INScore.fGlue.start(scene);
		ITLOut.write ("INScore version " + INScore.version());
	}

	static getRoot() : IAppl		{ return this.fAppl; }

	static checkStatus (status: msgStatus, msg: IMessage) : void {
    	if (!(status & msgStatus.kProcessed + msgStatus.kProcessedNoChange))
    		ITLError.write (msg.toString() + ": " + this.status2string(status));
	}

	static postMessage (address: string, params: Array<any>) : void {
    	let msg = new IMessage (address, params);
    	INScore.checkStatus (this.fAppl.process (msg), msg);
	}
}

function StartINScore(scene?: string) : void { INScore.start(scene); }
