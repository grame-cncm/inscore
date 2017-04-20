
///<reference path="../externals/libfaust.d.ts"/>
///<reference path="../lib/ITLError.ts"/>

///<reference path="IObject.ts"/>

class IFaust extends IObject {
	static fAudio: TAudioContext = null;
	private fDspCode 	: string;
	private fFactory 	: TFaustFactory;
	private fDsp 		: TFaustDSP;
	private fUI			: Array<TFaustUIItem>;
	
	fBufferSize	: number;
	        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kFaustType;
        this.fDspCode = "";
        this.fFactory = null;
        this.fDsp = null;
        this.fBufferSize = 1024;
        if (!IFaust.fAudio) {
			let isWebKitAudio = (typeof webkitAudioContext !== "undefined");
			IFaust.fAudio = (isWebKitAudio) ? new webkitAudioContext() : new AudioContext();
        }
    }

	del(): void {
		this.delDSP();
		super.del();
    }
   

	private delDSP(): void {
		if (this.fDsp) {
			this.fDsp.disconnect(IFaust.fAudio.destination);
			faust.deleteDSPInstance (this.fDsp);
			this.fDsp = null;
		}
		if (this.fFactory) {
			faust.deleteDSPFactory (this.fFactory);
			this.fFactory = null;
		}
	}


	private buildUIFromJSON(json: string): void {
		let ui: TFaustJSONDesc;
		eval ("ui="+json);
	}
/*
	buildUI (ui.ui);
		buildItems (ui[i].items, ui[i].label);
	for (var i=0; i< items.length; i++) {
		console.log ("item: " + items[i].type + " path: " + items[i].address + " min: " + items[i].min + " max: " + items[i].max);
	}
*/
    private instanceReady (dsp: TFaustDSP): void {
		if (this.fDsp) {
			this.fDsp.disconnect(IFaust.fAudio.destination);
			faust.deleteDSPInstance (this.fDsp);
		}
		this.fDsp = dsp;		
//		if (dsp.getNumInputs() > 0) activateAudioInput();
		dsp.connect(IFaust.fAudio.destination);
		this.buildUIFromJSON (dsp.json());
    }

    private factoryReady (factory: TFaustFactory): void {
		if (!factory)
			ITLError.write ("Faust factory creation failed: " + faust.getErrorMessage());
		else {
			if (this.fFactory)
				faust.deleteDSPFactory (this.fFactory);
			this.fFactory = factory;
			faust.createDSPInstance(factory, IFaust.fAudio, this.fBufferSize, this.instanceReady);
		}
    }
   
    private createDsp(code: string): boolean { 
        console.log ("createDsp " + code);
		faust.createDSPFactory (code, ["-I", "http://127.0.0.1:8000/libraries/"], this.factoryReady);
		return true;
    }
   
     
// SET HANDLER
//--------------------------------------------------------------    
   set(msg: IMessage): eMsgStatus { 
        let status = super.set(msg);
        if (status & (eMsgStatus.kProcessed + eMsgStatus.kProcessedNoChange)) return status; 

        let n = msg.size();
        if (n != 3) return eMsgStatus.kBadParameters;
        let code =  msg.paramStr(2);
        if (!code.correct) return eMsgStatus.kBadParameters;
        
        if (this.createDsp (code.value))  return eMsgStatus.kProcessed;
		ITLError.write ("Faust dsp creation failed: " + faust.getErrorMessage());
        return eMsgStatus.kProcessed;
    }

// GETSET METHOD
//--------------------------------------------------------------    
    getSet(): IMessage	{ 
    	return new IMessage(this.getOSCAddress(), [kset_SetMethod, this.fTypeString, this.fDspCode] ); 
    }
}
