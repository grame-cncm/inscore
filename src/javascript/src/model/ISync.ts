
///<reference path="../lib/ITLError.ts"/>
///<reference path="../lib/OSCRegexp.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../lib/Tools.ts"/>
///<reference path="../lib/TTypes.ts"/>
///<reference path="IObject.ts"/>
///<reference path="TSyncInfo.ts"/>

//--------------------------------------------------------------  
// glue between slave, master and sync params
//--------------------------------------------------------------  
class TSyncNode  {
	fSlave	: IObject;
	fMaster	: IObject;
	fViews	: Array<VObjectView>;
	fInfos	: TSyncInfo;

    constructor(slave: IObject, master: IObject, info: TSyncInfo, views: Array<VObjectView>) { 
		this.fSlave		= slave;
		this.fMaster	= master;
		this.fInfos		= new TSyncInfo();
		this.fViews		= views;
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

interface getNameHandler { (sync: TSyncNode): string; }

//--------------------------------------------------------------  
// synchronisation management node
//--------------------------------------------------------------  
class ISync extends IObject  {
	private fSyncList: Array<TSyncNode>
    
    constructor(name: string, parent: IObject) { 
        super( name, parent );
        this.fTypeString = kSyncType;
        this.fSyncList = [];
    }

    //------------------------------------
	private findSync (name: string, syncname: getNameHandler): Array<TSyncNode> {
		let out : Array<TSyncNode> = [];
		let f = (sync: TSyncNode): void => { if (syncname(sync) === name) out.push(sync); }
		if (Tools.regexp(name)) {
			let re = new OSCRegexp(name);
			f = (sync: TSyncNode): void => { if (re.match(syncname(sync))) out.push(sync); }
		}
		this.fSyncList.forEach( f );
		return out;
	}

    //------------------------------------
	private findSyncBySlaveName (name: string): Array<TSyncNode> {
		return this.findSync (name, function (sync: TSyncNode) { return sync.fSlave.getName(); } );
	}
    //------------------------------------
	private findSyncByMasterName (name: string): Array<TSyncNode> {
		return this.findSync (name, function (sync: TSyncNode) { return sync.fMaster.getName(); } );
	}
	
    //------------------------------------
	private findSyncNodes (slave: string, master: string): Array<TSyncNode> {
		let out : Array<TSyncNode> = [];

		let sync : Array<TSyncNode> = this.findSyncBySlaveName (slave);
		if (!sync.length) return out;
		
		let f = (name: string): boolean => { return name === master; };
		if (Tools.regexp(master)) {
			let re = new OSCRegexp(master);
			f = (name: string): boolean => { return re.match(name); };
		}
		sync.forEach( function (node: TSyncNode) : void { if (f (node.fMaster.getName())) out.push (node); });
		return out;
	}

    //------------------------------------
	private restoreDefaultView (obj: IObject) {
     	let views = IObjectFactory.createViews (obj, obj.getParent().getViews());
     	views.forEach ( function(view: VObjectView): void { obj.setView (view); });
     	obj.subModPropagate (obj.getParent());
     	obj.allModified ();
	}

    //------------------------------------
     private removeSync (obj: IObject): void {	this.clearName (obj.getName()); }
     private clearName (obj: string): eMsgStatus {
     	let targets = this.findSyncBySlaveName (obj);
		targets.forEach ( (sync: TSyncNode): void => { 
			let i=this.fSyncList.indexOf (sync);
			if (i>=0) {
				sync.fViews.forEach( function(view: VObjectView): void { sync.fSlave.removeView(view); } );
				if (!sync.fSlave.getViews().length) this.restoreDefaultView (sync.fSlave);
				this.fSyncList.splice(i, 1);
			}
		} );
        return eMsgStatus.kProcessedNoChange;
    }

    //------------------------------------
     private updateSync (node: TSyncNode, syncparams: TSyncInfo): void {
     	node.update (syncparams);
     	let slave = node.fSlave;
      	slave.subModPropagate (node.fMaster);
    	slave.posModified();
     }

    //------------------------------------
     private createSync (slave: IObject, master: IObject, syncparams: TSyncInfo): void {
     	let n = this.findSyncBySlaveName(slave.getName()).length;
     	if (!n) {					// first synchronisation
     		slave.removeViews();	// remove the standard view
     	}
     	let views = IObjectFactory.createViews (slave, master.getViews());
     	let sync = new TSyncNode(slave, master, syncparams, views);
    	this.fSyncList.push (sync);

     	views.forEach ( function(view: VObjectView): void { 
     		slave.addView (view);
     		view.setPositionHandler( () : TPosition => { return slave.getSlavePosition (master, sync.fInfos); }) } 
     	);
     	slave.subModPropagate (master);
     	slave.allModified ();
    }

    //------------------------------------
     private getOne(name: string): IMessageList {
		let out : IMessageList = []
		let syncs = this.findSyncBySlaveName (name);
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
		if (nodes.length) 			// update existing nodes
			nodes.forEach( (node: TSyncNode): void => { this.updateSync (node, syncparams); } );
		else {
			let slaves = this.fParent.find (slaveName.value);
			if (!slaves.length) { ITLError.write (slaveName.value + ": no such object!"); return eMsgStatus.kBadParameters; }
			let masters = this.fParent.find (masterName.value);
			if (!masters.length) { ITLError.write (masterName.value + ": no such object!"); return eMsgStatus.kBadParameters; }

			for (var i = 0; i < slaves.length; i++) {
				for (var j = 0; j < masters.length; j++)
					if ((slaves[i].fTypeString != kSyncType) && (masters[j].fTypeString != kSyncType))
						this.createSync (slaves[i], masters[j], syncparams);
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
			if (sync.fSlave.getDeleted()) 
				this.fSyncList.splice(i,1);
			else if (sync.fMaster.getDeleted()) {
				sync.fViews.forEach( function(view: VObjectView): void { sync.fSlave.removeView(view); } );
				if (!sync.fSlave.getViews().length) this.restoreDefaultView (sync.fSlave);
				this.fSyncList.splice(i,1);
			}
			else i++
		}
    }
	
    createStaticNodes() : void {}
}
