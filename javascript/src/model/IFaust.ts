
///<reference path="../externals/libfaust.d.ts"/>
///<reference path="../lib/ITLError.ts"/>

///<reference path="IObject.ts"/>

declare function FAUST_LIBRARIES_PATH() : string;

class IFaust extends IObject {
	static fAudio: TAudioContext = null;
	private fDspCode 	: string;
	private fFactory 	: TFaustFactory;
	private fDsp 		: TFaustDSP;
	private fUI			: Array<TFaustUIItem>;
	private fFaustLibraries : string; // = "http://faust.grame.fr/modules/libraries/";
//	private fFaustLibraries : string = "https://raw.githubusercontent.com/grame-cncm/faust/faust2/libraries/";
	
	fBufferSize	: number;
	        
    constructor(name: string, parent: IObject) {
        super(name, parent);
        this.fTypeString = kFaustType;
        this.fDspCode = "";
        this.fFactory = null;
        this.fDsp = null;
        this.fBufferSize = 2048;
        this.fUI = [];
        if (!IFaust.fAudio) {
			let isWebKitAudio = (typeof webkitAudioContext !== "undefined");
			IFaust.fAudio = (isWebKitAudio) ? new webkitAudioContext() : new AudioContext();
        }
		if (typeof FAUST_LIBRARIES_PATH === 'function')
			this.fFaustLibraries = FAUST_LIBRARIES_PATH();
		else this.fFaustLibraries = "http://faust.grame.fr/modules/libraries/";
		console.log ("new faust " + name + " using path: " + this.fFaustLibraries);
    }

    setHandlers(): void {
        this.fMsgHandlerMap[kset_SetMethod] = new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.set(msg); } );
        this.fMsgHandlerMap[kget_SetMethod] = new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.get(msg); } );
        this.fMsgHandlerMap[ksave_SetMethod]= new TMethodHandler( (msg: IMessage): eMsgStatus => { return this.save(msg); } );
        this.fMsgHandlerMap[kdel_SetMethod] = new TMsgHandlerVoid( (): void => { this.del(); } );

 	    this.eventAble();
        this.fGetMsgsHandlerMap["*"] = new TGetMsgsHandler( (): IMessageList => { return this.getAllItems(); } );
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

	private stripAddressHead(address: string): string 	{ return address.replace(/\/[^\/]*\//, ""); }

	private getAllItems(): IMessageList {
		let out : IMessageList = [];
		this.fUI.forEach( (item: TFaustUIItem) : void => { out.push (this.items2Message(item)); });
		return out;
	}

	private items2Message(item: TFaustUIItem): IMessage {
    	let params : Array<any> = [ this.stripAddressHead(item.address) ];
    	if (item.init) params = params.concat([item.init, item.min, item.max ]);
    	return new IMessage(this.getOSCAddress(), params ); 
	}

	private item2array (item: TFaustUIItem): Array<number> {
		return item.init ? [ item.init, item.min, item.max ] : [];
	}

	private buildUIItem(i: TFaustUIItem | TFaustUIElement): void {
			if (i.type.substr(1) == "group") {
				let group = <TFaustUIElement>i;
				this.buildUIItems (group.items);
			}
			else if (i.type == "attach") {
				// ignore attach type
			}
			else {
				let item = <TFaustUIItem>i
				this.fUI.push (item);
				let shortaddress = this.stripAddressHead(item.address);
	        	this.fMsgHandlerMap[shortaddress]    = new TMsgHandlerNum( (n: number): void => { this.fDsp.setParamValue(item.address, n); });
       			this.fGetMsgHandlerMap[shortaddress] = new TGetMsgHandlerArray( (): Array<number> => { return this.item2array(item); });
			}
	}

	private buildUIItems(items: Array<TFaustUIItem | TFaustUIElement>): void {
		items.forEach( (item: TFaustUIItem | TFaustUIElement): void => { this.buildUIItem (item); });
	}

	private buildUIFromJSON(json: string): void {
		let desc: TFaustJSONDesc;
		eval ("desc="+json);
        this.fUI = [];
		desc.ui.forEach ( (elt: TFaustUIElement): void => { this.buildUIItems (elt.items); });
	}

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
			faust.createDSPInstance(factory, IFaust.fAudio, this.fBufferSize, 
				(arg: TFaustDSP) : void => this.instanceReady(arg));
		}
    }
   
    protected createDsp(code: string): boolean { 
		this.fDspCode = code;
		faust.createDSPFactory (code, ["-I", this.fFaustLibraries], 
			(arg: TFaustFactory) : void => this.factoryReady(arg));
		return true;
    }
   
   protected objectset(msg: IMessage): eMsgStatus { return super.set(msg); }
     
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
