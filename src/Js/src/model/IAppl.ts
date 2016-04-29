///<reference path="../controller/THandlersPrototypes.ts"/>
///<reference path="../lib/OSCAddress.ts"/>
///<reference path="IObject.ts"/>
///<reference path="IProxy.ts"/>

class IAppl extends IObject {
 
    protected kApplType: string;
    protected fReceivedMsgs: number;
    
    constructor() {
        super('ITL');
        this.kApplType = 'IAppl';
        this.fTypeString = 'IAppl';
        this.fReceivedMsgs = 0;
    } 

    getAppl() : IObject					{ return this; }
    getSet(address: string): IMessage	{ return new IMessage(address); }
    getOSCAddress(): string 			{ return "/ITL"; }

    processMsg (address: string, addressTail: string , msg: IMessage): number {
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
		if (tail.length) 			// application is not the final destination of the message
			status = super.processMsg(head, tail, msg);
	
//		else if (match(head)) {		// the message is for the application itself
		else if (head === "ITL") {		// the message is for the application itself
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