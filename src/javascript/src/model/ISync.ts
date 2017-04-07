
///<reference path="../lib/TTypes.ts"/>
///<reference path="IObject.ts"/>

//--------------------------------------------------------------  
// synchronisation management
//--------------------------------------------------------------  
class ISync extends IObject  {
	private fSlaves2Masters: Array<TPair<IObject>>
	private fMasters2Slaves: Array<TPair<IObject>>
    
    constructor(name: string, parent: IObject) { 
        super( name, parent );
        this.fTypeString = kSyncType;
        this.fSlaves2Masters = [];
        this.fMasters2Slaves = [];
    }

    //------------------------------------
     private clearSync (obj: IObject): eMsgStatus {
console.log ("ISync clearSync " + obj.getName());
        return eMsgStatus.kProcessedNoChange;
    }

    //------------------------------------
     private clearName (obj: string): eMsgStatus {
console.log ("ISync clearName " + obj);
        return eMsgStatus.kProcessedNoChange;
    }

    //------------------------------------
     private getOne(name: string): IMessage {
console.log ("ISync getOne " + name);
        return null;
    }

    //------------------------------------
    private getAll(): IMessageList {
console.log ("ISync getAll ");
		let out : IMessageList = []
        return out;
    }

    //------------------------------------
    private setSync(msg: IMessage): eMsgStatus {
console.log ("ISync setSync ");
		let out : IMessageList = []
        return eMsgStatus.kProcessedNoChange;
    }

    //------------------------------------
    getCall(msg: IMessage): IMessageList {
console.log ("ISync getCall ");
		let n = msg.size();
		if (n == 1) return this.getAll();

		let out : IMessageList = []
		for (var i=1; i < n; i++) {
			let arg = msg.paramStr(i);
			if (arg.correct) {
				let msg = this.getOne (arg.value);
				if (msg) out.push (msg);
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
	
    createStaticNodes() : void {}
}
