///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="IObject.ts"/>
///<reference path="Constants.ts"/>
///<reference path="IProxy.ts"/>
///<reference path="IApplStaticNodes.ts"/>

class IAppl extends IObject {
 
    protected kApplType: string;
    protected fReceivedMsgs: number;
    protected fViewRate: number;
    protected fModelRate: number;
    
    constructor() {
        super('ITL');
        this.kApplType = kApplType;
        this.fTypeString = kApplType;
        this.fReceivedMsgs = 0;
        this.fViewRate = 100;
        this.fModelRate = 1000;
    } 

    createStaticNodes() : void {
    	let log = new IApplLog ("log", this);
    	this.addChild (log);
    }

    getAppl() : IObject					{ return this; }
    getSet(): IMessage					{ let msg : IMessage; return msg; }
    getOSCAddress(): string 			{ return "/ITL"; }
    getViewRate(): number 					{ return this.fViewRate; }
    setViewRate(rate: number): void 		{ this.fViewRate = rate; }
    getModelRate(): number 					{ return this.fModelRate; }
    setModelRate(rate: number): void 		{ this.fModelRate = rate; }

	// prevent the output of color, position and time data at application level
	colorAble(): void		{}	
	positionAble(): void	{}
	timeAble() : void		{}

    processMsg (address: string, addressTail: string , msg: IMessage): msgStatus {
    	this.fReceivedMsgs++;

		let status = msgStatus.kBadAddress;
		let head = address;
		let tail = addressTail;

/*
		SIMessage msg = IMessage::create (*imsg);
		TAliasesMap::const_iterator i = fAliases.find(imsg->address());
		if (i != fAliases.end()) {
			msg->setAddress (i->second.first);
			if (i->second.second.size()) 
				msg->setMessage(i->second.second);
			head = OSCAddress.addressFirst(i->second.first);
			tail = OSCAddress.addressTail(i->second.first);
		}
*/
		if (tail.length) {			// application is not the final destination of the message
			status = super.processMsg(head, tail, msg);
		}
	
		else if (this.match(head)) {		// the message is for the application itself
			status = this.execute(msg);
			if (status & msgStatus.kProcessed)
				this.setState(objState.kModified);
		}
//		if ((status == msgStatus.kProcessed) || (status == msgStatus.kProcessedNoChange))
			return status;
    }

	protected newObj (msg: IMessage, name: string): { status: msgStatus, obj?: IObject } 
    				{ return this.proxy_create(msg, name, this); }                
    protected proxy_create (msg: IMessage, name: string, parent: IObject): { status: msgStatus, obj?: IObject }	
    				{ return IProxy.execute (msg, name, parent); }
}