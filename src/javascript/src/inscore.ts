
///<reference path="inscore-interface.ts"/>
///<reference path="controller/IMessage.ts"/>
///<reference path="controller/IGlue.ts"/>
///<reference path="lib/ITLError.ts"/>
///<reference path="lib/ITLOut.ts"/>
///<reference path="lib/TEnums.ts"/>
///<reference path="model/IObject.ts"/>
///<reference path="model/TILoader.ts"/>


class INScoreImpl extends INScoreInterface 
{
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

	start (scene: string, position?: string) : void {
		if (!this.fGlue) {
			this.fGlue = new IGlue();
			this.fGlue.initEventHandlers();
		}
		this.fGlue.start(scene, position ? position : "relative");
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

	load (data: any): void {
		let loader = new TILoader;
		if (typeof data == "string") 	{ loader.process (data, this.getRoot()); }
		else 							{ loader.load (data, this.getRoot()); }		
	}

	register (tag : string): void {
		var elts = document.getElementsByTagName (tag);
		for (var i= 0 ; i < elts.length; i++) {
			var icode = elts[i].textContent;
			INScore.load (icode);
			elts[i].textContent = "";
		}
		while (elts.length)
			elts[0].parentElement.removeChild (elts[0]);
	}
}

INScore = new INScoreImpl();
