
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/OSCRegexp.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="IObject.ts"/>

//--------------------------------------------------------------  
// synchronisation management
//--------------------------------------------------------------  
class TSyncInfo  {
	static kSyncHStr 	= "h";
	static kSyncVStr 	= "v";
	static kSyncHVStr 	= "hv";
	static kSyncOverStr 	= "syncOver";
	static kSyncTopStr 		= "syncTop";
	static kSyncBottomStr 	= "syncBottom";
	static kSyncFrameStr 	= "syncFrame";
	static kSyncAbsoluteStr = "absolute";
	static kSyncRelativeStr = "relative";

	fMode		: eSyncModes;
	fPosition	: eSyncPosition;
	fStretch	: eSyncStretch;

    constructor() { 
		this.fMode		= eSyncModes.kAbsolute;
		this.fPosition	= eSyncPosition.kSyncOver;
		this.fStretch	= eSyncStretch.kSyncDate;
    }

	//---------------------------------------------
	update (info: TSyncInfo) : void {
		this.fMode		= info.fMode;
		this.fPosition	= info.fPosition;
		this.fStretch	= info.fStretch;
	}

	//---------------------------------------------
	set (msg: IMessage) : boolean {
		for (var i=2; i<msg.size(); i++) {
			let param = msg.paramStr(i);
			if (!param.correct) return false;
			switch (param.value) {
				case TSyncInfo.kSyncHStr	:	this.fStretch = eSyncStretch.kSyncH; break;
				case TSyncInfo.kSyncVStr	:	this.fStretch = eSyncStretch.kSyncV; break;
				case TSyncInfo.kSyncHVStr	:	this.fStretch = eSyncStretch.kSyncH + eSyncStretch.kSyncV; break;
				case TSyncInfo.kSyncOverStr :	this.fPosition = eSyncPosition.kSyncOver; break;
				case TSyncInfo.kSyncTopStr :	this.fPosition = eSyncPosition.kSyncTop; break;
				case TSyncInfo.kSyncBottomStr:	this.fPosition = eSyncPosition.kSyncBottom; break;
				case TSyncInfo.kSyncFrameStr:		this.fPosition = eSyncPosition.kSyncFrame; break;
				case TSyncInfo.kSyncRelativeStr:	this.fMode = eSyncModes.kRelative; break;
				case TSyncInfo.kSyncAbsoluteStr:	this.fMode = eSyncModes.kAbsolute; break;
				default: return false;
			}
		}
		return true;
	}
     
   //---------------------------------------------
   // conversion methods
   //---------------------------------------------
    toString(): string { 
    	return TSyncInfo.stretch2String(this.fStretch) + " " + TSyncInfo.mode2String(this.fMode) 
    			+ " " + TSyncInfo.pos2String(this.fPosition); 
    }
    
    toArray(): Array<string> { 
    	let out = [];
    	if (this.fStretch != eSyncStretch.kSyncDate) 	out.push (TSyncInfo.stretch2String(this.fStretch));
    	if (this.fMode == eSyncModes.kRelative) 		out.push (TSyncInfo.mode2String(this.fMode));
    	if (this.fPosition != eSyncPosition.kSyncOver) 	out.push (TSyncInfo.pos2String(this.fPosition));
    	return out;
    }
   
   //---------------------------------------------
   // static methods
   //---------------------------------------------
    static mode2String (mode: eSyncModes) : string	{ return mode == eSyncModes.kRelative ? "relative" : ""; }
    static pos2String (pos: eSyncPosition): string	{ 
    	switch (pos) {
    		case eSyncPosition.kSyncOver:	return "";			// default mode
    		case eSyncPosition.kSyncTop:	return "syncTop";
    		case eSyncPosition.kSyncBottom: return "syncBottom";
    		case eSyncPosition.kSyncFrame:	return "syncFrame";
    	}
    	return ""; 
    }
    static stretch2String (v: eSyncStretch): string	{ 
    	let out = "";
    	if (v & eSyncStretch.kSyncH) out += "h";
    	if (v & eSyncStretch.kSyncV) out += "v";
    	return out; 
    }
}

//--------------------------------------------------------------  
// glue between slave, master and sync params
//--------------------------------------------------------------  
class TSyncNode  {
	fSlave	: IObject;
	fMaster	: IObject;
	fInfos	: TSyncInfo;

    constructor(slave: IObject, master: IObject, info: TSyncInfo) { 
		this.fSlave		= slave;
		this.fMaster	= master;
		this.fInfos		= new TSyncInfo();
		this.fInfos.update (info);		
    }

   //---------------------------------------------
	update (infos: TSyncInfo): void 	{  this.fInfos.update (infos); }

   //---------------------------------------------
   // conversion methods
   //---------------------------------------------
    toString(): string { return this.fSlave.getName() + " " + this.fMaster.getName() +  " " + this.fInfos };
    
    toArray(): Array<string> { 
    	let out = [this.fSlave.getName(), this.fMaster.getName()];
    	out = out.concat(this.fInfos.toArray());
    	return out;
    }   
}


//--------------------------------------------------------------  
// synchronisation management
//--------------------------------------------------------------  
class ISync extends IObject  {
	private fSyncList: Array<TSyncNode>
    
    constructor(name: string, parent: IObject) { 
        super( name, parent );
        this.fTypeString = kSyncType;
        this.fSyncList = [];
    }

    //------------------------------------
	private findSyncByName (name: string): Array<TSyncNode> {
		let out : Array<TSyncNode> = [];
		let f = (sync: TSyncNode): void => { if (sync.fSlave.getName() === name) out.push(sync); }
		if (Tools.regexp(name)) {
			let re = new OSCRegexp(name);
			f = (sync: TSyncNode): void => { if (re.match(sync.fSlave.getName())) out.push(sync); }
		}
		this.fSyncList.forEach( f );
		return out;
	}
    //------------------------------------
	private findSyncNodes (slave: string, master: string): Array<TSyncNode> {
		let out : Array<TSyncNode> = [];

		let sync : Array<TSyncNode> = this.findSyncByName (slave);
		if (!sync.length) return out;
		
		let f = (name: string): boolean => { return name === master; };
		if (Tools.regexp(master)) {
			let re = new OSCRegexp(master);
			let f = (name: string): boolean => { return re.match(name); };
		}
		for (var i=0; i < sync.length; i++)
			if (f (sync[i].fMaster.getName())) out.push (sync[i]);
		return out;
	}

    //------------------------------------
     removeSync (obj: IObject): void {	this.clearName (obj.getName()); }
     private clearName (obj: string): eMsgStatus {
     	let targets = this.findSyncByName (obj);
		targets.forEach ( (sync: TSyncNode): void => { 
			let i=this.fSyncList.indexOf (sync);
			if (i>=0) this.fSyncList.splice(i, 1);
		} );
        return eMsgStatus.kProcessedNoChange;
    }

    //------------------------------------
     private getOne(name: string): IMessageList {
		let out : IMessageList = []
		let syncs = this.findSyncByName (name);
		syncs.forEach( (sync: TSyncNode) : void => { out.push( new IMessage(this.getOSCAddress(), sync.toArray())); } );
        return out;
    }

    //------------------------------------
    private getAll(): IMessageList {
		let out : IMessageList = []
		this.fSyncList.forEach( (sync: TSyncNode) : void => { out.push( new IMessage(this.getOSCAddress(), sync.toArray())); } );
        return out;
    }

    //------------------------------------
    private setSync(msg: IMessage): eMsgStatus {
		let slaveName = msg.paramStr(0);
		let masterName = msg.paramStr(1);
		if (!slaveName.correct || !masterName.correct) return eMsgStatus.kBadParameters;

		let syncparams = new TSyncInfo();
		if (! syncparams.set (msg))  return eMsgStatus.kBadParameters;

		let nodes = this.findSyncNodes (slaveName.value, masterName.value);
		if (nodes.length) {			// update existing nodes
			nodes.forEach( function(node: TSyncNode) { node.update (syncparams) } );
		}
		else {
			let slaves = this.fParent.find (slaveName.value);
			if (!slaves.length) { ITLError.write (slaveName.value + ": no such object!"); return eMsgStatus.kBadParameters; }
			let masters = this.fParent.find (masterName.value);
			if (!masters.length) { ITLError.write (masterName.value + ": no such object!"); return eMsgStatus.kBadParameters; }

			for (var i = 0; i < slaves.length; i++) {
				for (var j = 0; j < masters.length; j++)
					if ((slaves[i].fTypeString != kSyncType) && (masters[j].fTypeString != kSyncType))
						this.fSyncList.push (new TSyncNode(slaves[i], masters[j], syncparams));
			}
		}
        return eMsgStatus.kProcessedNoChange;
    }

    //------------------------------------
    getCall(msg: IMessage): IMessageList {
		let n = msg.size();
		if (n == 1) return this.getAll();

		let out : IMessageList = []
		for (var i=1; i < n; i++) {
			let arg = msg.paramStr(i);
			if (arg.correct) {
				let msgs = this.getOne (arg.value);
				if (msgs) msgs.forEach( function(msg: IMessage) { out.push (msg); } );
			}
		}
        return out;
    }

    //------------------------------------
    // overrides execute: no standard message processing apart for 'get'
    //------------------------------------
    execute (msg: IMessage): eMsgStatus {
		let n = msg.size();
		if (!n)  				return eMsgStatus.kBadParameters;
        let p1 = msg.paramStr(0);
        if (!p1.correct)	 	return eMsgStatus.kBadParameters;

        let get = (p1.value == kget_SetMethod);		// is it a get message?        
        if (get) return this.get(msg);

        if (n == 1) return this.clearName (p1.value);
		return this.setSync (msg);
	}

    //------------------------------------
    // delNotify : notifications activated by nodes
    //------------------------------------
    delNotify(obj: IObject): void 	{ 
		for (var i=0; i < this.fSyncList.length; ) {
			let sync = this.fSyncList[i];
			if (sync.fMaster.getDeleted() || sync.fSlave.getDeleted()) 
				this.fSyncList.splice(i,1);
			else i++
		}
    }
	
    createStaticNodes() : void {}
}
