
///<reference path="../controller/IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>

//--------------------------------------------------------------  
// synchronisation: 
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
